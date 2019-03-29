#include "stdafx.h"
#ifndef ASSERT
#include <assert.h>
#define ASSERT assert
#endif
#include "NamedPipeClient.h"
#include "stringhelper.h"

CNamedPipeClient::CNamedPipeClient(NS_IPC::INamePipeClitEvent* pNamedPipeEvent)
: m_npEvent(pNamedPipeEvent), CNamedPipe(&m_npEvent)
{
	m_hThread = INVALID_HANDLE_VALUE;
	m_hConnectEvent = NULL;
	m_bClientPipe = TRUE;
	m_bReconnection = FALSE;
}

CNamedPipeClient::~CNamedPipeClient()
{
}

//断开连接并释放该管道
VOID WINAPI CNamedPipeClient::Release()
{
	StopNamedPipeClient();
	CNamedPipe::Release();
}

INT WINAPI CNamedPipeClient::Connect(LPCSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection)
{
	m_bReconnection = bReconnection;
#ifdef _UNICODE
	std::wstring strPipeName(NS_StringHelper::AsciiToUnicode(szPipeName));
	return StartNamedPipeClient(strPipeName.c_str(), dwWaitTimeOut);
#else
	return StartNamedPipeClient(szPipeName, dwWaitTimeOut);
#endif
}

INT WINAPI CNamedPipeClient::ConnectW(LPCWSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection)
{
	m_bReconnection = bReconnection;
#ifdef _UNICODE
	return StartNamedPipeClient(szPipeName, dwWaitTimeOut);
#else
	CStringA strPipeName(szPipeName);
	return StartNamedPipeClient(strPipeName, dwWaitTimeOut);
#endif
}

/////////////////////////////////////////////////////////////////////////
DWORD WINAPI WaitClientReadWriteCompleted(LPVOID lpParam)
{
	PPIPETHREADPARAMS pThreadParams = (PPIPETHREADPARAMS)lpParam;
	ASSERT(pThreadParams != NULL);
	CNamedPipeClient* pNamedPipeClient = (CNamedPipeClient*)pThreadParams->pNamedPipe;
	ASSERT(pNamedPipeClient != NULL);
	DWORD dwWaitTimeOut = pThreadParams->dwTimeOut;
	TCHAR szNamePipe[MAX_PIPENAME_LEN];
	lstrcpyn(szNamePipe, pThreadParams->szNamePipe, MAX_PIPENAME_LEN);
	HANDLE hStartEvent = pThreadParams->hStartEvent;
	delete pThreadParams;
	pThreadParams = NULL;

	DWORD dwWait, dwTimeOut;
	BOOL bSuccess = TRUE;
	while (bSuccess)
	{
		if (pNamedPipeClient->ConnectToServer(szNamePipe, dwWaitTimeOut))
		{
			dwTimeOut = INFINITE;
		}
		else
		{
			dwTimeOut = dwWaitTimeOut;
		}

		if (hStartEvent)
		{
			::SetEvent(hStartEvent);
			hStartEvent = NULL;
		}

		// Wait for a read or write operation to be completed,
		// which causes a completion routine to be queued for execution. 
		dwWait = WaitForSingleObjectEx(
			pNamedPipeClient->m_hConnectEvent,  // event object to wait for 
			dwTimeOut,       // waits indefinitely 
			TRUE);          // alertable wait enabled 

		switch (dwWait)
		{
			// The wait is satisfied by a completed read or write operation.
			// This allows the system to execute the completion routine. 
		case WAIT_IO_COMPLETION:
			if (!pNamedPipeClient->IsReconnection())
				bSuccess = pNamedPipeClient->IsConnect();
			break;
		case WAIT_TIMEOUT:
			break;
			// The wait conditions are satisfied by a completed connect operation. 
			// An error occurred in the wait function.
			// case WAIT_OBJECT_0:
		default:
			bSuccess = FALSE;
			break;
		}
	}
	if (hStartEvent)
	{
		::SetEvent(hStartEvent);
		hStartEvent = NULL;
	}
	HANDLE hConnectEvent = pNamedPipeClient->m_hConnectEvent;
	HANDLE hThread = pNamedPipeClient->m_hThread;
	pNamedPipeClient->m_hConnectEvent = NULL;
	pNamedPipeClient->m_hThread = INVALID_HANDLE_VALUE;
	::CloseHandle(hConnectEvent);
	::CloseHandle(hThread);
	return 0;
}

INT CNamedPipeClient::StartNamedPipeClient(LPCTSTR lpszPipeName, DWORD dwWaitTimeOut)
{
	if (m_hThread != INVALID_HANDLE_VALUE)
		return CLIENTPIPE_START_ISCONECTING;

	INT iRet = CreateClientPipeInstance(lpszPipeName, dwWaitTimeOut);
	PPIPETHREADPARAMS pThreadParams = new PIPETHREADPARAMS;
	if (!pThreadParams)
		return iRet;

	if (m_hConnectEvent == NULL)
	{
		// Create one event object for a read or write operation. 
		m_hConnectEvent = CreateEvent(
			NULL,    // default security attribute
			TRUE,    // manual reset event 
			FALSE,    // initial state = unsignaled 
			NULL);   // unnamed event object 
	}

	if (m_hConnectEvent != NULL)
	{
		HANDLE hStartEvent = CreateEvent(
			NULL,    // default security attribute
			TRUE,    // manual reset event 
			FALSE,    // initial state = unsignaled 
			NULL);   // unnamed event object

		pThreadParams->pNamedPipe = this;
		pThreadParams->pContent = 0;
		pThreadParams->hStartEvent = hStartEvent;
		pThreadParams->dwTimeOut = NP_CLIENT_TIMEOUT;
		lstrcpyn(pThreadParams->szNamePipe, lpszPipeName, MAX_PIPENAME_LEN);

		DWORD dwThreadID = 0;
		m_hThread = ::CreateThread(NULL, 0, WaitClientReadWriteCompleted, (LPVOID)pThreadParams, CREATE_SUSPENDED, &dwThreadID);
		if (m_hThread != INVALID_HANDLE_VALUE)
		{
			::SetThreadPriority(m_hThread, THREAD_PRIORITY_BELOW_NORMAL);
			::ResumeThread(m_hThread);

			if (hStartEvent)
			{
				::WaitForSingleObject(hStartEvent, INFINITE);
				::CloseHandle(hStartEvent);
				hStartEvent = NULL;
			}

			if (iRet > CLIENTPIPE_START_FAILED)
			{
				if (PIPE_CREATE_ISEXIST == iRet)
					return CLIENTPIPE_START_ISSTARTED;
				return CLIENTPIPE_START_SUCCEEDED;
			}
			return CLIENTPIPE_START_ISSTARTING;
		}
		if (hStartEvent)
		{
			::CloseHandle(hStartEvent);
			hStartEvent = NULL;
		}
		SetConnectEvent();
		::CloseHandle(m_hConnectEvent);
		m_hConnectEvent = NULL;
	}
	delete pThreadParams;
	return CLIENTPIPE_START_FAILED;
}

BOOL CNamedPipeClient::SetConnectEvent()
{
	BOOL bResult = TRUE;
	if (m_hConnectEvent != NULL)
	{
		bResult = ::SetEvent(m_hConnectEvent);
	}
	return bResult;
}

VOID CNamedPipeClient::StopNamedPipeClient()
{
	DisconnectPipeInstance(FALSE);
	if (m_hThread != INVALID_HANDLE_VALUE)
	{
		::WaitForSingleObject(m_hThread, INFINITE);
		if (m_hThread != INVALID_HANDLE_VALUE)
		{
			::CloseHandle(m_hThread);
			m_hThread = INVALID_HANDLE_VALUE;
		}
	}

	if (m_hConnectEvent != NULL)
	{
		::CloseHandle(m_hConnectEvent);
		m_hConnectEvent = NULL;
	}
}

VOID CNamedPipeClient::DisconnectPipeInstance(BOOL bAutoDelete)
{
	SetConnectEvent();
	CNamedPipe::DisconnectPipeInstance(bAutoDelete);
}

namespace NS_IPC
{
	//////////////////////////////////////////////////////////////////////////////////
	INamedPipe* WINAPI CreateNamePipeClient(INamePipeClitEvent* pClientEvent)
	{
		CNamedPipeClient* pPipeClient = new CNamedPipeClient(pClientEvent);
		return (INamedPipe*)pPipeClient;
	}

};