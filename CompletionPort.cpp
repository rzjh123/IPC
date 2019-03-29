#include "stdafx.h"
#include "NamedPipeServer.h"

#pragma warning(disable: 4996)
//////////////////////////////////////////////////////////
//信息打印，带时间戳
int __cdecl ConsolePrintf(LPCTSTR lpszFormat, ...)
{
	INT iSize = 0, iLength = 0;
	TCHAR szLog[1024] = {0};
#ifndef FC_TRACE
	SYSTEMTIME systime;
	::GetLocalTime(&systime);
	iLength = _stprintf(szLog, TEXT("[%4d-%02d-%02d %02d:%02d:%02d.%03d] "),
		systime.wYear,systime.wMonth,systime.wDay,
		systime.wHour, systime.wMinute, systime.wSecond,
		systime.wMilliseconds);
	szLog[iLength] = 0;
#endif
	va_list ptr;
	va_start(ptr, lpszFormat);
	iSize = _vsntprintf(&szLog[iLength], 1024, lpszFormat, ptr);
	iLength += iSize;
	va_end(ptr);
#ifndef FC_TRACE
	::OutputDebugString(szLog);
#else
	FCTRACE(FCPROMPT, szLog);
#endif
	return iLength;

//	HANDLE hStdout = ::GetStdHandle(STD_OUTPUT_HANDLE);
//	if (hStdout == INVALID_HANDLE_VALUE) 
//		return 0;
//
//	DWORD dwNumberOfCharsWritten = 0;
//	::WriteConsole(hStdout, szLog, iLength, &dwNumberOfCharsWritten, NULL);
//	::OutputDebugString(szLog);
//	return (int)dwNumberOfCharsWritten;
}

//#ifndef CP_GB18030
//#define CP_GB18030		54936
//#endif

// LPCWSTR ConvertStringToUnicode(LPCSTR pSrc)
// {
// 	if (!pSrc)
// 		return NULL;
// 
// 	UINT nCodePage = CP_GB18030;
// 	if (!IsValidCodePage(CP_GB18030))
// 	{
// 		nCodePage = CP_ACP;
// 	}
// 	int iLength = ::MultiByteToWideChar(nCodePage, 0, pSrc, -1, NULL, 0);
// 	if (!iLength)
// 		return NULL;
// 
// 	WCHAR* szUnicode = new WCHAR[iLength+1];
// 	iLength = ::MultiByteToWideChar(nCodePage, 0, pSrc, -1, szUnicode, iLength);
// 	szUnicode[iLength] = 0;
// 	return szUnicode;
// }
/////////////////////////////////////////////////////////////////
// CCompletionThread class
CCompletionThread::CCompletionThread()
{
	m_pCompletionPort = NULL;
}

CCompletionThread::~CCompletionThread()
{
	Stop();
}

BOOL CCompletionThread::StartCompletionPort(CCompletionPort* pCompletionPort)
{
	if (!pCompletionPort || m_pCompletionPort)
	{
		return FALSE;
	}

	m_pCompletionPort = pCompletionPort;
	return CThread::Start();
}

void CCompletionThread::Run()
{
	//ASSERT(m_pCompletionPort != NULL);
	m_pCompletionPort->GetCompletionQueued();
}

BOOL CCompletionThread::BeforeRun()
{
	return TRUE;
}

void CCompletionThread::AfterRun()
{
	ConsolePrintf(_T("Exit Thread\n"));
}

void CCompletionThread::Debug(DWORD dwErrCode)
{
	ConsolePrintf(_T("Debug Thread: ErrorCode=%u\n"), dwErrCode);
}
/////////////////////////////////////////////////////////////////
// CCompletionPort class
CCompletionPort::CCompletionPort()
{
	m_hCompletionPort = NULL;
	m_ptrContext = NULL;
	m_bWork = FALSE;
}

CCompletionPort::~CCompletionPort()
{
}

// Create Completion Port,start threads
DWORD CCompletionPort::Start(DWORD dwThreadCount)
{
	if (m_hCompletionPort)
	{
		return (DWORD)m_vecCompletionThread.size();
	}
    
	ConsolePrintf(_T("Create CompletionPort\r\n"));
	HANDLE hCompletionPort = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, (ULONG_PTR)NULL, 0);
	if (!hCompletionPort)
	{
		return 0;
	}
	
	m_hCompletionPort = hCompletionPort;
	if (!dwThreadCount)
	{
		SYSTEM_INFO sysInfo;
		GetSystemInfo(&sysInfo);
		dwThreadCount = sysInfo.dwNumberOfProcessors + (sysInfo.dwNumberOfProcessors + 1)/2;
	}

	ConsolePrintf(_T("Create %d Threads\r\n"),dwThreadCount);
	CCompletionThread* pThread = NULL;
	for (DWORD dwIndex = 0; dwIndex < dwThreadCount; dwIndex++)
	{
		pThread = new CCompletionThread();
		if (pThread->StartCompletionPort(this))
		{
			m_vecCompletionThread.push_back(pThread);
		}
		else
		{
			delete pThread;
		}
	}

	return (DWORD)m_vecCompletionThread.size();
}

void CCompletionPort::Stop()
{
	ConsolePrintf(_T("Stop CompletionPort\n"));

	if (!m_hCompletionPort)
	{
		m_bWork = FALSE;
		return;
	}

	//先停止线程
	m_bWork = FALSE;

	DWORD dwThreadCount = (DWORD)m_vecCompletionThread.size();
	//完成端口通知结束命令
	for (DWORD dwIndex = 0; dwIndex < dwThreadCount; ++dwIndex)
	{
		::PostQueuedCompletionStatus(m_hCompletionPort, 0, NULL, NULL);
	}

	CompletionThreadList::iterator itr = m_vecCompletionThread.begin();
	while (itr != m_vecCompletionThread.end())
	{
		(*itr)->Stop();
		delete (*itr);
		itr++;
	}
	m_vecCompletionThread.clear();

	::CloseHandle(m_hCompletionPort);
	m_hCompletionPort = NULL;
}

HANDLE CCompletionPort::BindIoHandle(HANDLE hIoHandle, LPVOID pCompletionKey)
{
	return ::CreateIoCompletionPort(hIoHandle, m_hCompletionPort, (ULONG_PTR)pCompletionKey, 0);
}

BOOL CCompletionPort::PostCompletionData(PCOMPLETIONOVERLAPPEDDATA pCompletionData)
{
	return ::PostQueuedCompletionStatus(m_hCompletionPort, pCompletionData->dwCompletionDataSize, (ULONG_PTR)pCompletionData->pCompletionKey, pCompletionData);
}

#ifndef ERROR_ABANDONED_WAIT_0
#define ERROR_ABANDONED_WAIT_0           735L    // winnt
#endif

VOID CCompletionPort::GetCompletionQueued()
{
	DWORD dwBytesTransferred = 0;
	DWORD dwErrorCode = 0;
	CNamedPipe* pNamedPipe = NULL;
	LPCOMPLETIONOVERLAPPEDDATA pCompletionOverlapped = NULL;
	CNamedPipeServer* pNamedPipeServer = (CNamedPipeServer*)m_ptrContext;
	BOOL bResult = FALSE;
	m_bWork = TRUE;
	while (m_bWork)
	{
		pNamedPipe = NULL;
		dwBytesTransferred = 0;
		pCompletionOverlapped = NULL;
		bResult = ::GetQueuedCompletionStatus(m_hCompletionPort, (LPDWORD)&dwBytesTransferred,
			(PULONG_PTR)&pNamedPipe, (LPOVERLAPPED*)&pCompletionOverlapped, INFINITE);
		dwErrorCode = ::GetLastError();
		if (FALSE == m_bWork)
		{
			ConsolePrintf(_T("Stop Completion: HostIndex=0x%p\r\n"));
			break;
		}

		if (!pNamedPipe || !pCompletionOverlapped)
		{
			m_bWork = FALSE;
			ConsolePrintf(_T("GetQueuedCompletionStatus: HostIndex=0x%p ErrCode=%u BytesTransferred=%u CompletionOverlapped=0x%x Result=%d\r\n"),
				pNamedPipe, dwErrorCode, dwBytesTransferred, pCompletionOverlapped, bResult);
			//结束完成端口线程
			break;
		}

		pCompletionOverlapped->dwErrorCode = dwErrorCode;
		if (!bResult)
		{
			ConsolePrintf(_T("GetQueuedCompletionStatus: HostIndex=0x%p ErrCode=%u BytesTransferred=%u CompletionOverlapped=0x%x Result=%d\r\n"),
				pNamedPipe, dwErrorCode, dwBytesTransferred, pCompletionOverlapped, bResult);
			pNamedPipe->DisconnectPipeInstance(TRUE);
			continue;
		}

		if (NAMEDPIPE_IO_END == pCompletionOverlapped->dwCompletionType)
		{
			// 这是内部自定义类型，表示退出完成端口！
			m_bWork = FALSE;
			ConsolePrintf(_T("Exit Completion: HostIndex=0x%p\r\n"), pNamedPipe);
			if (INVALID_HANDLE_VALUE != pNamedPipe->GetSafeHandle())
				pNamedPipe->DisconnectPipeInstance(TRUE);
			break;
		}

		switch (pCompletionOverlapped->dwCompletionType)
		{
		case NAMEDPIPE_IO_CONNECT:
			ConsolePrintf(_T("Host Connect: HostIndex=0x%p ErrorCode=%u\r\n"),
				pNamedPipe, pCompletionOverlapped->dwErrorCode);
			try
			{
				//若管道句柄是无效时，表示外界直接DisconnectPipeInstance而产生的NAMEDPIPE_IO_CONNECT类型的完成情况
				if (INVALID_HANDLE_VALUE != pNamedPipe->GetSafeHandle())
				{
					pNamedPipe->CompletedConnect();
					if (pNamedPipeServer)
					{
						pNamedPipeServer->CreateNextPipeInstance();
					}
				}
				else
				{
					ConsolePrintf(_T("Host DisConnect: HostIndex=0x%p ErrorCode=%u\r\n"),
						pNamedPipe, pCompletionOverlapped->dwErrorCode);
				}
			}
			catch(...)
			{
				ConsolePrintf(_T("Host Connect Crash: HostIndex=0x%p ErrorCode=%u\r\n"),
					pNamedPipe, pCompletionOverlapped->dwErrorCode);
			}
			break;
		case NAMEDPIPE_IO_SENDDATA:
			ConsolePrintf(_T("Host Send Data: HostIndex=0x%p BytesTransferred=%u|%u|%u ErrorCode=%u\r\n"),
				pNamedPipe, dwBytesTransferred, pCompletionOverlapped->dwTransferBytes,
				pCompletionOverlapped->dwCompletionDataSize, pCompletionOverlapped->dwErrorCode);
			try
			{
				if (INVALID_HANDLE_VALUE != pNamedPipe->GetSafeHandle())
				{
					if (!dwBytesTransferred)
					{
						ConsolePrintf(_T("GetQueuedCompletionStatus: HostIndex=0x%p ErrCode=%u BytesTransferred=%u CompletionOverlapped=0x%x|%u\r\n"),
							pNamedPipe, dwErrorCode, dwBytesTransferred, pCompletionOverlapped, pCompletionOverlapped->dwCompletionType);
						pNamedPipe->DisconnectPipeInstance(TRUE);
						break;
					}
					pNamedPipe->CompletedSend((LPCSTR)pCompletionOverlapped, dwBytesTransferred);
					break;
				}
				pNamedPipe->DisconnectPipeInstance(TRUE);
			}
			catch(...)
			{
				ConsolePrintf(_T("Host Send Data Crash: HostIndex=0x%p BytesTransferred=%u|%u|%u ErrorCode=%u\r\n"),
					pNamedPipe, dwBytesTransferred, pCompletionOverlapped->dwTransferBytes,
					pCompletionOverlapped->dwCompletionDataSize, pCompletionOverlapped->dwErrorCode);
			}

			if (pCompletionOverlapped->pCompletionData)
			{
				delete[] pCompletionOverlapped->pCompletionData;
				pCompletionOverlapped->pCompletionData = NULL;
			}

			::HeapFree(GetProcessHeap(), 0, pCompletionOverlapped);
			break;
		case NAMEDPIPE_IO_RECVDATA:
			ConsolePrintf(_T("Host Recv Data: HostIndex=0x%p BytesTransferred=%u|%u|%u ErrorCode=%u\r\n"),
				pNamedPipe, dwBytesTransferred, pCompletionOverlapped->dwTransferBytes,
				pCompletionOverlapped->dwCompletionDataSize, pCompletionOverlapped->dwErrorCode);
			try
			{
				if (INVALID_HANDLE_VALUE != pNamedPipe->GetSafeHandle())
				{
					if (!dwBytesTransferred)
					{
						ConsolePrintf(_T("GetQueuedCompletionStatus: HostIndex=0x%p ErrCode=%u BytesTransferred=%u CompletionOverlapped=0x%x|%u\r\n"),
							pNamedPipe, dwErrorCode, dwBytesTransferred, pCompletionOverlapped, pCompletionOverlapped->dwCompletionType);
						pNamedPipe->DisconnectPipeInstance(TRUE);
						break;
					}
					pNamedPipe->CompletedRecv((LPCSTR)pCompletionOverlapped, dwBytesTransferred);
					break;
				}
				pNamedPipe->DisconnectPipeInstance(TRUE);
			}
			catch(...)
			{
				ConsolePrintf(_T("Host Recv Data Crash: HostIndex=0x%p BytesTransferred=%u|%u|%u ErrorCode=%u\r\n"),
					pNamedPipe, dwBytesTransferred, pCompletionOverlapped->dwTransferBytes,
					pCompletionOverlapped->dwCompletionDataSize, pCompletionOverlapped->dwErrorCode);
			}
			pCompletionOverlapped->dwCompletionDataSize = 0;
			pCompletionOverlapped->dwTransferBytes = 0;
			break;
		case NAMEDPIPE_IO_DISCONNECT:
			ConsolePrintf(_T("Host Disconnect: HostIndex=0x%p ErrorCode=%u\r\n"),
				pNamedPipe, pCompletionOverlapped->dwErrorCode);
			try
			{
				if (INVALID_HANDLE_VALUE != pNamedPipe->GetSafeHandle())
				{
					pNamedPipe->DisconnectPipeInstance(TRUE);
				}
			}
			catch(...)
			{
				ConsolePrintf(_T("Host Disconnect Crash: HostIndex=0x%p ErrorCode=%u\r\n"),
					pNamedPipe, pCompletionOverlapped->dwErrorCode);
			}
			break;
		}
	}
}
