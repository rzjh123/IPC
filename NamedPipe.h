#pragma once

#include "npdef.h"

typedef struct tagSENDPIPE_OVERLAPPED : public OVERLAPPED
{ 
	LPVOID pNamedPipe;
	//TCHAR chSendData[NP_BUFSIZE];
	LPSTR pszSendData;
	DWORD dwSendSize; 
}SENDPIPE_OVERLAPPED,* PSENDPIPE_OVERLAPPED,FAR* LPSENDPIPE_OVERLAPPED;

typedef struct tagRECVPIPE_OVERLAPPED : public OVERLAPPED
{ 
	LPVOID pNamedPipe;
	CHAR chRecvData[NP_BUFSIZE]; 
	DWORD dwRecvSize;
}RECVPIPE_OVERLAPPED,* PRECVPIPE_OVERLAPPED,FAR* LPRECVPIPE_OVERLAPPED;

typedef struct tagPIPETHREADPARAMS
{
	LPVOID pNamedPipe;
	LPVOID pContent;
	HANDLE hStartEvent;
	DWORD dwTimeOut;
	TCHAR szNamePipe[MAX_PIPENAME_LEN];
}PIPETHREADPARAMS, * PPIPETHREADPARAMS,FAR* LPPIPETHREADPARAMS;

#define NAMEDPIPE_IO_END			0
#define NAMEDPIPE_IO_CONNECT		1
#define NAMEDPIPE_IO_DISCONNECT		2
#define NAMEDPIPE_IO_RECVDATA		3
#define NAMEDPIPE_IO_SENDDATA		4

typedef struct tagCompletionOverlappedData : public OVERLAPPED
{
	LPVOID pCompletionKey;		// ??
	DWORD dwCompletionType;		// 数据类型
	DWORD dwCompletionDataSize;	// pCompletionData的数据大小
	PBYTE pCompletionData;		// 用于存储自定义关联数据
	DWORD dwTransferBytes;		// 已读取或发送的字节数
	DWORD dwErrorCode;			// 完成端口返回错误码
}COMPLETIONOVERLAPPEDDATA, * PCOMPLETIONOVERLAPPEDDATA, FAR* LPCOMPLETIONOVERLAPPEDDATA;

/////////////////////////////////////////////////////////////////////////////////
class IOCP_IPC_CLS CNamedPipe : public INamedPipe
{
public:
	CNamedPipe(INamedPipeEvent* pNamedPipeEvent=NULL);
	virtual ~CNamedPipe();

public:
	//INamedPipe
	//断开连接并释放该管道
	virtual VOID WINAPI Release();
	//获取管道句柄
	virtual HANDLE WINAPI GetHandle();
	//是否是客户端管道
	virtual BOOL WINAPI IsClientPipe();
	//设置上下文内容
	virtual VOID WINAPI SetContext(ULONG_PTR ptrContext);
	//获取上下文内容
	virtual ULONG_PTR WINAPI GetContext();
	//设置监视管道
	virtual void WINAPI SetMonitor(BOOL bMonitor);
	//是否是监视管道
	virtual BOOL WINAPI IsMonitor();
	//连接管道，返回值详见"连接管道的返回值宏定义"
	virtual INT WINAPI Connect(LPCSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection);
	//连接管道，返回值详见"连接管道的返回值宏定义"
	virtual INT WINAPI ConnectW(LPCWSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection);
	//获取管道连接状态
	virtual BOOL WINAPI IsConnect();
	//断开连接管道
	virtual VOID WINAPI Disconnect();
	//发送数据
	virtual BOOL WINAPI SendData(LPCSTR lpszSendData, DWORD dwSendSize);
	//接受数据
	virtual BOOL WINAPI RecvData();
public:
	virtual VOID CompletedCreate();
	virtual VOID CompletedConnect();
	virtual BOOL CompletedSend(LPCSTR lpszSendData,DWORD dwSendSize);
	virtual DWORD CompletedRecv(LPCSTR lpszRecvData,DWORD dwRecvSize);
	virtual VOID DisconnectPipeInstance(BOOL bAutoDelete);

	INT CreateServerPipeInstance(LPCTSTR lpszPipeName, BOOL bFirstPipeInstance = FALSE);
	INT CreateClientPipeInstance(LPCTSTR lpszPipeName,DWORD dwWaitTimeOut=NP_CLIENT_TIMEOUT);
	BOOL ConnectToServer(LPCTSTR lpszPipeName,DWORD dwWaitTimeOut=NP_CLIENT_TIMEOUT);
	BOOL ConnectToClient(LPOVERLAPPED lpo = NULL);

	//重叠I/O
	BOOL SendDataEx(LPCSTR lpszSendData,DWORD dwSendSize);
	BOOL RecvDataEx();

	void SetPipeCompletionPort(HANDLE hPipeCompletionPort);
	void SetNamedPipeInterface(INamedPipeEvent* pNamedPipeEvent);
	HANDLE GetSafeHandle();
	operator HANDLE() const;

	static VOID WINAPI CompletedWriteRoutine(DWORD, DWORD, LPOVERLAPPED);
	static VOID WINAPI CompletedReadRoutine(DWORD, DWORD, LPOVERLAPPED);

protected:
	HANDLE m_hPipe;
	HANDLE m_hPipeCompletionPort;
	INamedPipeEvent* m_pNamedPipeEvent;
	ULONG_PTR m_ptrContext;
	BOOL m_bMonitor;
	BOOL m_bStartClientRecv;
	BOOL m_bClientPipe;
	//DWORD m_dwRecvDataOffset;
	//CHAR m_chRecvData[NP_BUFSIZE];
	RECVPIPE_OVERLAPPED m_recvOverlapped;
	COMPLETIONOVERLAPPEDDATA m_recvData;
	COMPLETIONOVERLAPPEDDATA m_acceptData;
};

__inline void CNamedPipe::SetPipeCompletionPort(HANDLE hPipeCompletionPort)
{m_hPipeCompletionPort = hPipeCompletionPort;}

__inline void CNamedPipe::SetNamedPipeInterface(INamedPipeEvent* pNamedPipeEvent)
	{m_pNamedPipeEvent = pNamedPipeEvent;}

__inline HANDLE CNamedPipe::GetSafeHandle()
	{return this != NULL ? m_hPipe : INVALID_HANDLE_VALUE;}

__inline CNamedPipe::operator HANDLE() const
	{return m_hPipe;}
