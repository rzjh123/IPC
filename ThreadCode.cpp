#include "stdafx.h"
#include <process.h>
#include "ThreadCode.h"
#include "npdef.h"

CThread::CThread()
{
	m_hThread = NULL;
	m_dwThreadId = 0;
	m_bRunning = FALSE;
}

CThread::~CThread()
{
	Stop();
}

BOOL CThread::Start(BOOL bSuspend/* = FALSE*/, DWORD dwStackSize/* = 0*/)
{
	if (m_hThread)
	{
		return TRUE;
	}

	if (!BeforeRun())
		return FALSE;

	DWORD dwCreationFlags = 0;
	if (bSuspend)
	{
		dwCreationFlags = CREATE_SUSPENDED;
	}

#ifndef _WIN32
	m_hThread = (HANDLE)_beginthreadex(NULL, uStackSize, ThreadFunc, this, dwThreadFlag, &m_dwThreadId);
#else
	m_hThread = ::CreateThread(NULL, dwStackSize, ThreadStartRoutine, this, dwCreationFlags, &m_dwThreadId);
#endif
	if (!m_hThread)
		return FALSE;
	return TRUE;
}

BOOL CThread::Stop(DWORD dwTimeOut)
{
	BOOL bRet = TRUE;
	if (!m_hThread)
	{
		return bRet;
	}

	m_bRunning = FALSE;
	// �����ʱ���˴���ǿ���߳���ֹ��
	// ��ˣ��߳��еĶѽ��޷��õ���ȷ�ͷţ�����ͬ�����������޷��õ������ͷţ���������������
	if (::WaitForSingleObject(m_hThread, dwTimeOut) == WAIT_TIMEOUT)
	{
		::TerminateThread(m_hThread, -1);
		AfterRun();
		bRet = FALSE;
	}

	::CloseHandle(m_hThread);
	m_hThread = NULL;
	m_dwThreadId = 0;
	return bRet;
}


DWORD WINAPI CThread::ThreadStartRoutine(LPVOID lpParameter)
{
	CThread* pSelf = (CThread*)lpParameter;
	try
	{
		pSelf->SetRunning(TRUE);
		while (pSelf->IsRunning())
		{
			pSelf->Run();
			Sleep(10);
		}
	}
	catch(...)
	{
		pSelf->Debug(::GetLastError());
	}
   if (pSelf && pSelf->IsRunning())
   {
	   pSelf->AfterRun();
   }
#ifndef _WIN32
	_endthreadex(0);
#endif
	return 0;
}
