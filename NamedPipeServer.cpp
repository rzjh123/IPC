#include "stdafx.h"
#include "NamedPipeServer.h"
#include "stringhelper.h"

// CNamedPipeServer class
CNamedPipeServer::CNamedPipeServer()
{
	m_pNamedPipeEvent = NULL;
	m_pCurrNamedPipe = NULL;
	m_completionPort.SetContext((ULONG_PTR)this);
	memset(m_szPipeName, 0, MAX_PIPENAME_LEN);
	m_mapNamedPipe.clear();
}

CNamedPipeServer::~CNamedPipeServer()
{
	Stop();
}

VOID WINAPI CNamedPipeServer::Release()
{
	delete this;
}

//连接管道，返回值详见"连接管道的返回值宏定义"
INamedPipe* WINAPI CNamedPipeServer::Create(LPCSTR szPipeName, INamedPipeEvent* pNamedPipeEvent, DWORD dwTimeout)
{
#ifdef _UNICODE
	std::wstring pipe_name(NS_StringHelper::AsciiToUnicode(szPipeName));
	return Start(pipe_name.c_str(), pNamedPipeEvent, dwTimeout);
#else
	return Start(szPipeName, pNamedPipeEvent, dwTimeout);
#endif
}

//连接管道，返回值详见"连接管道的返回值宏定义"
INamedPipe* WINAPI CNamedPipeServer::CreateW(LPCWSTR szPipeName, INamedPipeEvent* pNamedPipeEvent, DWORD dwTimeout)
{
#ifdef _UNICODE
	return Start(szPipeName, pNamedPipeEvent, dwTimeout);
#else
	CStringA strPipeName(szPipeName);
	return Start(strPipeName, pNamedPipeEvent, dwTimeout);
#endif
}

BOOL WINAPI CNamedPipeServer::IsRunning()
{
	return m_completionPort.IsWorking();
}

BOOL WINAPI CNamedPipeServer::Stop()
{
	//先停止完成端口
	m_completionPort.Stop();

	CNamedPipe* pNamedPipe = NULL;
	NAMEDPIPE_MAP::iterator iter = m_mapNamedPipe.begin();
	for (; iter != m_mapNamedPipe.end(); ++iter)
	{
		pNamedPipe = iter->second;
		if (pNamedPipe)
		{
			pNamedPipe->SetNamedPipeInterface(NULL);
			pNamedPipe->DisconnectPipeInstance(FALSE);
			delete pNamedPipe;
			pNamedPipe = NULL;
		}
	}
	
	m_mapNamedPipe.clear();
	m_pCurrNamedPipe = NULL;
	return TRUE;
}

DWORD WINAPI CNamedPipeServer::GetNamedPipeCount()
{
	return (DWORD)m_mapNamedPipe.size();
}

INamedPipe* WINAPI CNamedPipeServer::GetNamedPipe(HANDLE hPipe)
{
	return (INamedPipe*)GetNamedPipeClient(hPipe);
}

VOID WINAPI CNamedPipeServer::RemoveNamedPipe(HANDLE hPipe)
{
	RemoveNamedPipeClient(hPipe);
}

void WINAPI CNamedPipeServer::ForEachNamedPipe(INamedPipeServerRoutine* pRoutine)
{
	if (!pRoutine)
		return;

	NAMEDPIPE_MAP::iterator it;
	m_csLock.Lock();
	try
	{
		it = m_mapNamedPipe.begin();
		for(; it != m_mapNamedPipe.end(); it++)
		{
			if (it->second->IsConnect())
				pRoutine->Routine(it->second);
		}
	}
	catch(...)
	{
		ConsolePrintf(_T("For_Each_NamedPipe Exception\r\n"));
	}
	m_csLock.Unlock();
}

CNamedPipe* CNamedPipeServer::Start(LPCTSTR lpszPipeName, INamedPipeEvent* pNamedPipeEvent, DWORD dwTimeout)
{
	if (IsRunning())
		return m_pCurrNamedPipe;

	//创建完成端口并启动线程
	ConsolePrintf(_T("Start Creating CompletionPort and start Threads\r\n"));
	if (!(m_completionPort.Start(1)))
		return NULL;

	CNamedPipe* pNamedPipe = CreatePipeInstance(lpszPipeName, pNamedPipeEvent, TRUE);
	if (!pNamedPipe)
		return NULL;

	m_pNamedPipeEvent = pNamedPipeEvent;
	lstrcpyn(m_szPipeName, lpszPipeName, MAX_PATH);

	//命名管道等待连接
	ConsolePrintf(_T("Wait for Client Connection\r\n"));
	if (!pNamedPipe->ConnectToClient())
	{
		pNamedPipe->DisconnectPipeInstance(FALSE);
		return NULL;
	}
	m_pCurrNamedPipe = pNamedPipe;
	return pNamedPipe;
}

CNamedPipe* CNamedPipeServer::CreatePipeInstance(LPCTSTR lpszPipeName, INamedPipeEvent* pNamedPipeEvent, BOOL bFirstPipeInstance)
{
	CNamedPipe* pNamedPipe = new CNamedPipe(pNamedPipeEvent);
//	ASSERT(pNamedPipe != NULL);
	if (pNamedPipe != NULL)
	{
		ConsolePrintf(_T("Create Host Instance\r\n"));
		if (pNamedPipe->CreateServerPipeInstance(lpszPipeName,bFirstPipeInstance) == PIPE_CREATE_SUCCEEDED)
		{
			ConsolePrintf(_T("Bind Host to CompletionPort\r\n"));
			HANDLE hPipeCompletionPort = m_completionPort.BindIoHandle(pNamedPipe->GetSafeHandle(), (void*)pNamedPipe);
			if (hPipeCompletionPort)
			{
				pNamedPipe->SetPipeCompletionPort(hPipeCompletionPort);
				m_csLock.Lock();
				m_mapNamedPipe[pNamedPipe->GetSafeHandle()]=pNamedPipe;
				m_csLock.Unlock();
				return pNamedPipe;
			}
		}
		delete pNamedPipe;
		pNamedPipe = NULL;
	}

	return pNamedPipe;
}

CNamedPipe* CNamedPipeServer::CreateNextPipeInstance()
{
	CNamedPipe* pNextNamedPipe = NULL;
	//NAMEDPIPE_MAP::iterator itr;
	//m_csLock.Lock();
	//itr = m_mapNamedPipe.begin();
	//for (;itr != m_mapNamedPipe.end();itr++)
	//{
	//	if (itr->second && !itr->second->IsConnect())
	//		pNextNamedPipe = itr->second;
	//}
	//m_csLock.Unlock();
	//if (pNextNamedPipe)
	//{
	//	m_pCurrNamedPipe = pNextNamedPipe;
	//	return pNextNamedPipe;
	//}

	pNextNamedPipe = CreatePipeInstance(m_szPipeName, m_pNamedPipeEvent);
	if (pNextNamedPipe != NULL)
	{
		if (pNextNamedPipe->ConnectToClient())
		{
			m_pCurrNamedPipe = pNextNamedPipe;
			return pNextNamedPipe;
		}
	}
	return NULL;
}

VOID CNamedPipeServer::RemoveNamedPipeClient(HANDLE hPipe)
{
	m_csLock.Lock();
	NAMEDPIPE_MAP::iterator it = m_mapNamedPipe.find(hPipe);
	if (it != m_mapNamedPipe.end())
	{
		m_mapNamedPipe.erase(it);
	}
	m_csLock.Unlock();
}

CNamedPipe* CNamedPipeServer::GetNamedPipeClient(HANDLE hPipe)
{
	CNamedPipe* pTempNamedPipe = NULL;
	m_csLock.Lock();
	NAMEDPIPE_MAP::iterator it = m_mapNamedPipe.find(hPipe);
	if (it != m_mapNamedPipe.end())
	{
		pTempNamedPipe = it->second;
	}
	m_csLock.Unlock();
	return pTempNamedPipe;
}

//////////////////////////////////////////////////////////////////////////////////////
INamedPipeServer* WINAPI CreateNamedPipeServer()
{
	CNamedPipeServer* pPipeServer = new CNamedPipeServer();
	return (INamedPipeServer*)pPipeServer;
}
