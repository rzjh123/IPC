#include "StdAfx.h"
#include "inpsrv.h"
#include "NamedPipe.h"

/////////////////////////////////////////////////////////////////////////////////
CNamedPipe::CNamedPipe(INamedPipeEvent* pNamedPipeEvent)
{
	m_hPipe = INVALID_HANDLE_VALUE;
	m_hPipeCompletionPort = NULL;
	m_pNamedPipeEvent = pNamedPipeEvent;
	m_ptrContext = NULL;
	m_bMonitor = FALSE;
	m_bStartClientRecv = FALSE;
	m_bClientPipe = FALSE;
	//memset(m_chRecvData, 0, NP_BUFSIZE);
	memset(&m_recvOverlapped, 0, sizeof(m_recvOverlapped));
	memset(&m_recvData, 0, sizeof(COMPLETIONOVERLAPPEDDATA));
	memset(&m_acceptData, 0, sizeof(COMPLETIONOVERLAPPEDDATA));
}

CNamedPipe::~CNamedPipe()
{
	DisconnectPipeInstance(FALSE);
}

//断开连接并释放该管道
VOID WINAPI CNamedPipe::Release()
{
	if (m_bClientPipe)
		delete this;
	else
		DisconnectPipeInstance(FALSE);
}

//获取管道句柄
HANDLE WINAPI CNamedPipe::GetHandle()
{
	return m_hPipe;
}

BOOL WINAPI CNamedPipe::IsClientPipe()
{
	return m_bClientPipe;
}

//设置上下文内容
VOID WINAPI CNamedPipe::SetContext(ULONG_PTR ptrContext)
{
	m_ptrContext = ptrContext;
}

//获取上下文内容
ULONG_PTR WINAPI CNamedPipe::GetContext()
{
	return m_ptrContext;
}

void WINAPI CNamedPipe::SetMonitor(BOOL bMonitor)
{
	m_bMonitor = bMonitor;
}

BOOL WINAPI CNamedPipe::IsMonitor()
{
	return m_bMonitor;
}


//连接管道，返回值详见"连接管道的返回值宏定义"
INT WINAPI CNamedPipe::Connect(LPCSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection)
{
	return 0;
}

//连接管道，返回值详见"连接管道的返回值宏定义"
INT WINAPI CNamedPipe::ConnectW(LPCWSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection)
{
	return 0;
}

//获取管道连接状态
BOOL WINAPI CNamedPipe::IsConnect()
{
	if (m_bClientPipe)
		return (BOOL)(m_hPipe != INVALID_HANDLE_VALUE);
	return m_bStartClientRecv;
}

//断开连接管道
VOID WINAPI CNamedPipe::Disconnect()
{
	if (m_bClientPipe)
	{
		DisconnectPipeInstance(FALSE);
	}
	else if (m_hPipe != INVALID_HANDLE_VALUE)
	{
		::FlushFileBuffers(m_hPipe);
		// Disconnect the pipe instance. 
		::DisconnectNamedPipe(m_hPipe);
	}
}

BOOL WINAPI CNamedPipe::SendData(LPCSTR lpszSendData,DWORD dwSendSize)
{
	//ASSERT(m_hPipe != INVALID_HANDLE_VALUE);
	if (m_hPipeCompletionPort)
		return SendDataEx(lpszSendData, dwSendSize);
	//// Allocate storage for this instance. 
	//LPSENDPIPE_OVERLAPPED pSendPipe = (LPSENDPIPE_OVERLAPPED) HeapAlloc(GetProcessHeap(),0,sizeof(SENDPIPE_OVERLAPPED)); 
	//if (pSendPipe == NULL) return FALSE;

	//pSendPipe->pszSendData = new TCHAR[dwSendSize];
	//memcpy(pSendPipe->pszSendData,lpszSendData,dwSendSize);
	//pSendPipe->Offset = 0;
	//pSendPipe->OffsetHigh = 0;
	//pSendPipe->hEvent = NULL;
	//pSendPipe->pNamedPipe = this; 
	//pSendPipe->dwSendSize = dwSendSize;

	//Start the read operation for this client. 
	//Note that this same routine is later used as a completion routine after a write operation. 
	//if (::WriteFileEx(m_hPipe,pSendPipe->pszSendData,
	//	pSendPipe->dwSendSize, (LPOVERLAPPED)pSendPipe, 
	//	(LPOVERLAPPED_COMPLETION_ROUTINE)CompletedWriteRoutine))
	//{
	//	return TRUE;
	//}

	//if (pSendPipe != NULL)
	//{
	//	if (pSendPipe->pszSendData != NULL)
	//		delete[] pSendPipe->pszSendData;
	//	HeapFree(GetProcessHeap(),0,pSendPipe);
	//}

	BOOL bResult = TRUE;
	DWORD dwWriteBytes=0,dwTotalWriteBytes=0,dwNeedSendSize=dwSendSize;
	LPSTR pszSendData = (LPSTR)lpszSendData;
	while (dwTotalWriteBytes < dwSendSize)
	{
		if (!::WriteFile(m_hPipe,pszSendData,dwNeedSendSize,&dwWriteBytes,NULL))
		{
			bResult = FALSE;
			break;
		}
		dwTotalWriteBytes += dwWriteBytes;
		pszSendData += dwWriteBytes;
		dwNeedSendSize -= dwWriteBytes;
	}
	return bResult;
}

BOOL WINAPI CNamedPipe::RecvData()
{
	if (m_hPipeCompletionPort)
		return RecvDataEx();

	//ASSERT(m_hPipe != INVALID_HANDLE_VALUE);
	m_recvOverlapped.pNamedPipe = this;
	if (::ReadFileEx(m_hPipe, m_recvOverlapped.chRecvData,
		NP_BUFSIZE-m_recvOverlapped.dwRecvSize, (LPOVERLAPPED)&m_recvOverlapped, 
		(LPOVERLAPPED_COMPLETION_ROUTINE)CompletedReadRoutine))
	{
		return TRUE;
	}
	return FALSE;

	//ASSERT(m_hPipe != INVALID_HANDLE_VALUE);
	//// Allocate storage for this instance. 
	//LPRECVPIPE_OVERLAPPED pRecvPipe = (LPRECVPIPE_OVERLAPPED) HeapAlloc(GetProcessHeap(),0,sizeof(RECVPIPE_OVERLAPPED)); 
	//if (pRecvPipe == NULL) return FALSE;

	//pRecvPipe->Offset = 0;
	//pRecvPipe->OffsetHigh = 0;
	//pRecvPipe->hEvent = NULL;
	//pRecvPipe->pNamedPipe = this; 
	//pRecvPipe->dwRecvSize = 0;
	//if (::ReadFileEx(m_hPipe, pRecvPipe->chRecvData,
	//	NP_BUFSIZE, (LPOVERLAPPED)pRecvPipe, 
	//	(LPOVERLAPPED_COMPLETION_ROUTINE)CompletedReadRoutine))
	//{
	//	return TRUE;
	//}

	//HeapFree(GetProcessHeap(),0,pRecvPipe);
	//return FALSE;
}

VOID CNamedPipe::CompletedCreate()
{
	if (m_pNamedPipeEvent != NULL)
		m_pNamedPipeEvent->OnCompletedCreate(this);
}

VOID CNamedPipe::CompletedConnect()
{
	m_bStartClientRecv = TRUE;
	if (m_pNamedPipeEvent != NULL)
		m_pNamedPipeEvent->OnCompletedConnect(this);
	RecvDataEx();
}

BOOL CNamedPipe::CompletedSend(LPCSTR lpszSendData, DWORD dwSendSize)
{
	BOOL bResult = FALSE;
	if (m_hPipeCompletionPort)
	{
		LPCOMPLETIONOVERLAPPEDDATA pSendData = (LPCOMPLETIONOVERLAPPEDDATA)lpszSendData;
		LPSTR szSendData = (LPSTR)pSendData->pCompletionData;

		if (m_pNamedPipeEvent != NULL)
			bResult = m_pNamedPipeEvent->OnCompletedSend(this, szSendData, dwSendSize);

		pSendData->dwTransferBytes += dwSendSize;
		if (pSendData->dwTransferBytes == pSendData->dwCompletionDataSize)
		{
			if (szSendData)
			{
				delete[] szSendData;
				pSendData->pCompletionData = NULL;
			}
			::HeapFree(GetProcessHeap(), 0, pSendData);
		}
		//继续发送剩余的数据
		else
		{
			DWORD dwWrite = 0;
			bResult = ::WriteFile(m_hPipe, pSendData->pCompletionData + pSendData->dwTransferBytes,
				pSendData->dwCompletionDataSize - pSendData->dwTransferBytes, &dwWrite, pSendData);
			DWORD dwErrCode = ::GetLastError();
			if (!bResult)
			{
				if (dwErrCode == ERROR_IO_PENDING)
					return bResult;

				if (szSendData)
					delete [] szSendData;
				::HeapFree(GetProcessHeap(), 0, pSendData);
			}
		}
	}
	else if (m_pNamedPipeEvent != NULL)
	{
		bResult = m_pNamedPipeEvent->OnCompletedSend(this, lpszSendData, dwSendSize);
	}
	return bResult;
}

DWORD CNamedPipe::CompletedRecv(LPCSTR lpszRecvData, DWORD dwRecvSize)
{
	BOOL bWrite = FALSE;
	DWORD dwRemainRecvDataSize = 0;
	if (m_hPipeCompletionPort)
	{
		LPCOMPLETIONOVERLAPPEDDATA pRecvData = (LPCOMPLETIONOVERLAPPEDDATA)lpszRecvData;
		//ASSERT(pRecvData == &m_recvData);
		dwRecvSize += pRecvData->dwTransferBytes;
		if (m_pNamedPipeEvent != NULL)
		{
			dwRemainRecvDataSize = m_pNamedPipeEvent->OnCompletedRecv(this, (LPCSTR)pRecvData->pCompletionData, dwRecvSize);
			if (dwRemainRecvDataSize > dwRecvSize)
				dwRemainRecvDataSize = dwRecvSize;
		}
		DWORD dwProcessDataSize = dwRecvSize - dwRemainRecvDataSize;
		if (dwProcessDataSize != dwRecvSize)
		{
			memmove(m_recvOverlapped.chRecvData, m_recvOverlapped.chRecvData + dwProcessDataSize, dwRemainRecvDataSize);
			pRecvData->dwTransferBytes += dwRemainRecvDataSize;
		}
		else
		{
			pRecvData->dwTransferBytes = 0;
		}
		if (!RecvDataEx())
		{
			DisconnectPipeInstance(FALSE);
		}
	}
	else
	{
		if (m_pNamedPipeEvent != NULL)
		{
			dwRemainRecvDataSize = m_pNamedPipeEvent->OnCompletedRecv(this, lpszRecvData, dwRecvSize);
		}
	}
	return dwRemainRecvDataSize;
}

INT CNamedPipe::CreateServerPipeInstance(LPCTSTR lpszPipeName, BOOL bFirstPipeInstance)
{
	if (m_hPipe != INVALID_HANDLE_VALUE)
		return PIPE_CREATE_ISEXIST;

	DWORD dwOpenMode = PIPE_ACCESS_DUPLEX |      // read/write access 
					   FILE_FLAG_OVERLAPPED;	 // overlapped mode
	if (bFirstPipeInstance)
		dwOpenMode |= FILE_FLAG_FIRST_PIPE_INSTANCE;

	BYTE sd[SECURITY_DESCRIPTOR_MIN_LENGTH];

	SECURITY_ATTRIBUTES sa;  
	sa.lpSecurityDescriptor = (PSECURITY_DESCRIPTOR)sd;  
	InitializeSecurityDescriptor(sa.lpSecurityDescriptor,   SECURITY_DESCRIPTOR_REVISION);  
	// ACL is set as NULL in order to allow all access to the object.  
	SetSecurityDescriptorDacl(sa.lpSecurityDescriptor, TRUE, NULL, FALSE);  
	sa.nLength = sizeof(sa);  
	sa.bInheritHandle = TRUE;  

	m_hPipe = ::CreateNamedPipe(
		lpszPipeName,             // pipe name 
		dwOpenMode,				  // Open mode	
		//PIPE_TYPE_MESSAGE |	      // message-type pipe 
		//PIPE_READMODE_MESSAGE |	  // message read mode 
		//PIPE_WAIT,				  // blocking mode
		PIPE_TYPE_BYTE |		  // byte-type pipe 	
		PIPE_READMODE_BYTE |	  // byte read mode
		PIPE_WAIT,				  // blocking mode
		PIPE_UNLIMITED_INSTANCES, // unlimited instances 
		NP_BUFSIZE,               // output buffer size 
		NP_BUFSIZE,               // input buffer size 
		NP_SERVER_TIMEOUT,        // client time-out 
		&sa);                    // default security attributes

	return m_hPipe != INVALID_HANDLE_VALUE ? PIPE_CREATE_SUCCEEDED : PIPE_CREATE_FAILED;
}

INT CNamedPipe::CreateClientPipeInstance(LPCTSTR lpszPipeName,DWORD dwWaitTimeOut)
{
	if (m_hPipe != INVALID_HANDLE_VALUE)
		return PIPE_CREATE_ISEXIST;

	// Try to open a named pipe; wait for it, if necessary. 
	while (m_hPipe == INVALID_HANDLE_VALUE) 
	{ 
		//CString strPipeName = TEXT("\\\\.\\pipe\\SNDA_");
		//strPipeName += lpszPipeName;

		m_hPipe = ::CreateFile(
			lpszPipeName,   // pipe name 
			GENERIC_READ | GENERIC_WRITE, // read and write access 
			0,              // no sharing 
			NULL,           // default security attributes
			OPEN_EXISTING,  // opens existing pipe 
			FILE_FLAG_OVERLAPPED,              // FILE_FLAG_OVERLAPPED attributes 
			NULL);          // no template file 

		// Break if the pipe handle is valid. 
		if (m_hPipe == INVALID_HANDLE_VALUE)
		{
			// Exit if an error other than ERROR_PIPE_BUSY occurs.
			DWORD dwErrorID = GetLastError();
			if (ERROR_PIPE_BUSY != dwErrorID) 
			{
				break;
			}

			// All pipe instances are busy, so wait for 20 seconds. 
			if (!WaitNamedPipe(lpszPipeName, dwWaitTimeOut)) 
			{ 
				break;
			}
		}
	} 

	return m_hPipe != INVALID_HANDLE_VALUE ? PIPE_CREATE_SUCCEEDED : PIPE_CREATE_FAILED;
}

BOOL CNamedPipe::ConnectToServer(LPCTSTR lpszPipeName,DWORD dwWaitTimeOut)
{
	INT iRet = CreateClientPipeInstance(lpszPipeName, dwWaitTimeOut);
	if (PIPE_CREATE_FAILED == iRet)
		return FALSE;

	if (!m_bStartClientRecv)
	{
		m_bStartClientRecv = TRUE;
		if (m_hPipe != INVALID_HANDLE_VALUE)
		{
			DWORD dwMode = PIPE_READMODE_BYTE|PIPE_WAIT;
			// The pipe connected; change to byte-read mode. 
			if (!SetNamedPipeHandleState( 
				m_hPipe,  // pipe handle 
				&dwMode,  // new pipe mode 
				NULL,     // don't set maximum bytes 
				NULL))    // don't set maximum time
			{
				DisconnectPipeInstance(FALSE);
			}
			else
			{
				RecvData();
			}
		}
		if (m_pNamedPipeEvent != NULL)
		{
			m_pNamedPipeEvent->OnCompletedCreate(this);
		}
	}
	return TRUE;
}

BOOL CNamedPipe::ConnectToClient(LPOVERLAPPED lpo)
{ 
//	ASSERT(m_hPipe != INVALID_HANDLE_VALUE);
	if (m_pNamedPipeEvent != NULL)
	{
		m_pNamedPipeEvent->OnCompletedCreate(this);
	}

	if (!lpo)
	{
		memset(&m_acceptData, 0, sizeof(COMPLETIONOVERLAPPEDDATA));
		m_acceptData.pCompletionKey = this;
		m_acceptData.dwCompletionType = NAMEDPIPE_IO_CONNECT;
		lpo = &m_acceptData;
	}
	
	// Start an overlapped connection for this pipe instance. 
	// Overlapped ConnectNamedPipe should return zero. 
	if (::ConnectNamedPipe(m_hPipe, lpo))
	{
		return FALSE;
	}

	BOOL bPendingIO = FALSE; 
	switch (GetLastError()) 
	{ 
	// The overlapped connection in progress. 
	case ERROR_IO_PENDING: 
		bPendingIO = TRUE; 
		break; 
	// Client is already connected, so signal an event. 
	case ERROR_PIPE_CONNECTED: 
		if (lpo->hEvent)
			SetEvent(lpo->hEvent); 
		else
			bPendingIO = TRUE;
		break;
	case ERROR_PIPE_LISTENING:
		bPendingIO = TRUE;
		break;
	// If an error occurs during the connect operation... 
	} 
	return bPendingIO; 
}

//closes its handle to the pipe. 
VOID CNamedPipe::DisconnectPipeInstance(BOOL bAutoDelete)
{
	if (m_hPipe != INVALID_HANDLE_VALUE)
	{
		HANDLE hPipe = m_hPipe;
		::FlushFileBuffers(hPipe);
		// Disconnect the pipe instance. 
		::DisconnectNamedPipe(hPipe);
		if (m_pNamedPipeEvent != NULL)
		{
			m_pNamedPipeEvent->OnCompletedDisconnect(this);
		}
		m_hPipe = INVALID_HANDLE_VALUE;
		// Close the handle to the pipe instance. 
		::CloseHandle(hPipe);
	}

	if (m_hPipeCompletionPort)
	{
		m_hPipeCompletionPort = NULL;
	}
	m_bStartClientRecv = FALSE;
	m_bMonitor = FALSE;

	if (bAutoDelete)
	{
		INamedPipeEvent* pNamedPipeEvent = m_pNamedPipeEvent;
		m_pNamedPipeEvent = NULL;
		if (pNamedPipeEvent && pNamedPipeEvent->OnBeforeRelease(this))
			delete this;
	}
}

BOOL CNamedPipe::SendDataEx(LPCSTR lpszSendData, DWORD dwSendSize)
{
	//ASSERT(m_hPipe != INVALID_HANDLE_VALUE);
	//PBYTE szSendData = new BYTE[dwSendSize];
	//if (!szSendData)
	//{
	//	return FALSE;
	//}

	//COMPLETIONOVERLAPPEDDATA sendPipe;
	//memset(&sendPipe, 0, sizeof (COMPLETIONOVERLAPPEDDATA));
	//sendPipe.pCompletionKey = this;
	//sendPipe.dwCompletionType = NAMEDPIPE_IO_SENDDATA;
	//sendPipe.pCompletionData = (LPVOID)szSendData;
	//sendPipe.dwTransferByte = dwSendSize;
	//memcpy(sendPipe.pCompletionData, lpszSendData, sendPipe.dwTransferByte);
	//DWORD dwWrite = 0;
	//BOOL bResult = ::WriteFile(m_hPipe, sendPipe.pCompletionData, sendPipe.dwTransferByte, &dwWrite, &sendPipe);
	//DWORD dwErrCode = ::GetLastError();
	//if (!bResult)
	//{
	//	if (dwErrCode == ERROR_IO_PENDING)
	//		return TRUE;

	//	if (szSendData)
	//		delete [] szSendData;
	//}
	//return bResult;

	// Allocate storage for this instance. 
	LPCOMPLETIONOVERLAPPEDDATA pSendPipe = (LPCOMPLETIONOVERLAPPEDDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(COMPLETIONOVERLAPPEDDATA));
	if (!pSendPipe) return FALSE;

	PBYTE szSendData = new BYTE[dwSendSize];
	if (!szSendData)
	{
		::HeapFree(GetProcessHeap(), 0, pSendPipe);
		return FALSE;
	}

	pSendPipe->pCompletionKey = this;
	pSendPipe->dwCompletionType = NAMEDPIPE_IO_SENDDATA;
	pSendPipe->pCompletionData = szSendData;
	pSendPipe->dwCompletionDataSize = dwSendSize;
	memcpy(pSendPipe->pCompletionData, lpszSendData, pSendPipe->dwCompletionDataSize);
	DWORD dwWrite = 0;
	BOOL bResult = ::WriteFile(m_hPipe, pSendPipe->pCompletionData, pSendPipe->dwCompletionDataSize, &dwWrite, pSendPipe);
	DWORD dwErrCode = ::GetLastError();
	if (!bResult)
	{
		if (dwErrCode == ERROR_IO_PENDING)
			return TRUE;

		if (szSendData)
			delete [] szSendData;
		::HeapFree(GetProcessHeap(), 0, pSendPipe);
	}
	return bResult;
}

BOOL CNamedPipe::RecvDataEx()
{
//	ASSERT(m_hPipe != INVALID_HANDLE_VALUE);
	memset(&m_recvData, 0, sizeof(COMPLETIONOVERLAPPEDDATA));
	m_recvData.pCompletionKey = this;
	m_recvData.dwCompletionType = NAMEDPIPE_IO_RECVDATA;
	m_recvData.pCompletionData = (PBYTE)(m_recvOverlapped.chRecvData + m_recvData.dwTransferBytes);
	m_recvData.dwCompletionDataSize = NP_BUFSIZE - m_recvData.dwTransferBytes;
	DWORD dwRead = 0;
	BOOL bResult = ::ReadFile(m_hPipe, m_recvData.pCompletionData, m_recvData.dwCompletionDataSize, &dwRead, &m_recvData);
	DWORD dwErrorCode = ::GetLastError();
	if (!bResult && (dwErrorCode == ERROR_IO_PENDING || dwErrorCode == ERROR_MORE_DATA))
	{
		return TRUE;
	}
	return bResult;
}

// This routine is called as a completion routine after writing to 
// the pipe, or when a new client has connected to a pipe instance. It 
// starts another read operation. 
VOID WINAPI CNamedPipe::CompletedWriteRoutine(DWORD dwErrorID, DWORD dwSendSize,LPOVERLAPPED lpo) 
{ 
	// lpOverlap points to storage for this instance. 
	LPSENDPIPE_OVERLAPPED pSendPipe = (LPSENDPIPE_OVERLAPPED)lpo;
	CNamedPipe* pNamedPipe = (CNamedPipe*)pSendPipe->pNamedPipe;
	BOOL bRead = FALSE;

//	ASSERT(pNamedPipe != NULL);
	// The write operation has finished, so read the next request (if there is no error). 
	if ((dwErrorID == 0) && (dwSendSize == pSendPipe->dwSendSize))
	{
		bRead = pNamedPipe->CompletedSend(pSendPipe->pszSendData,pSendPipe->dwSendSize);
	}

	// Disconnect if an error occurred. 
	if (!bRead)
	{
		pNamedPipe->DisconnectPipeInstance(TRUE);
	}
	
	if (pSendPipe != NULL)
	{
		if (pSendPipe->pszSendData != NULL)
			delete[] pSendPipe->pszSendData;
		HeapFree(GetProcessHeap(),0,pSendPipe);
	}
}
 
// This routine is called as an I/O completion routine after reading a 
// request from the client. It gets data and writes it to the pipe. 
VOID WINAPI CNamedPipe::CompletedReadRoutine(DWORD dwErrorID, DWORD dwRecvSize, LPOVERLAPPED lpo) 
{ 
	// lpOverlap points to storage for this instance. 
	LPRECVPIPE_OVERLAPPED pRecvPipe = (LPRECVPIPE_OVERLAPPED)lpo;
	CNamedPipe* pNamedPipe = (CNamedPipe*)pRecvPipe->pNamedPipe;

	DWORD dwRemainDataSize = 0;
//	ASSERT(pNamedPipe != NULL);
	// The read operation has finished, so write a response (if no error occurred). 
	if ((dwErrorID == 0) && (dwRecvSize != 0)) 
	{ 
		dwRecvSize += pRecvPipe->dwRecvSize;
		dwRemainDataSize = pNamedPipe->CompletedRecv(pRecvPipe->chRecvData, dwRecvSize);
		if (dwRemainDataSize > dwRecvSize)
			dwRemainDataSize = dwRecvSize;

		DWORD dwProcessDataSize = dwRecvSize - dwRemainDataSize;
		if (dwProcessDataSize != dwRecvSize)
		{
			memmove(pRecvPipe->chRecvData, pRecvPipe->chRecvData + dwProcessDataSize, dwRemainDataSize);
			pRecvPipe->dwRecvSize += dwRemainDataSize;
		}
		else
		{
			pRecvPipe->dwRecvSize = 0;
		}

		if (pNamedPipe->RecvData())
			return;
	}

	// Disconnect if an error occurred. 
	pNamedPipe->DisconnectPipeInstance(TRUE);

	//BOOL bWrite = FALSE;
	//ASSERT(pNamedPipe != NULL);
	//// The read operation has finished, so write a response (if no error occurred). 
	//if ((dwErrorID == 0) && (dwRecvSize != 0)) 
	//{ 
	//	pRecvPipe->dwRecvSize = dwRecvSize;
	//	bWrite = pNamedPipe->CompletedRecv(pRecvPipe->chRecvData,pRecvPipe->dwRecvSize);
	//}

	//// Disconnect if an error occurred. 
	//if (!bWrite)
	//{
	//	pNamedPipe->DisconnectPipeInstance();
	//}

	//if (pRecvPipe != NULL)
	//{
	//	//GlobalFree(pRecvPipe);
	//	HeapFree(GetProcessHeap(),0,pRecvPipe);
	//}
}
