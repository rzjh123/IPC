#ifndef __NAMEDPIPEDEFINE_H__
#define __NAMEDPIPEDEFINE_H__

#define MAX_PIPENAME_LEN	256
#define NP_BUFSIZE			(64*1024)
/////////////////////////////////////////////////////////////////////////////////
#define NP_SERVER_TIMEOUT	5000
#define NP_CLIENT_TIMEOUT	100
/////////////////////////////////////////////////////////////////////////////////
#define PIPE_CREATE_FAILED			0
#define PIPE_CREATE_SUCCEEDED		1
#define PIPE_CREATE_ISEXIST			2
/////////////////////////////////////////////////////////////////////////////////

#include "IPC.h"
//管道类接口函数
struct  IOCP_IPC_CLS INamedPipe
{
	//断开连接并释放该管道
	virtual VOID WINAPI Release() = 0;
	//获取管道句柄
	virtual HANDLE WINAPI GetHandle() = 0;
	//是否是客户端管道
	virtual BOOL WINAPI IsClientPipe() = 0;
	//设置上下文内容
	virtual VOID WINAPI SetContext(ULONG_PTR ptrContext) = 0;
	//获取上下文内容
	virtual ULONG_PTR WINAPI GetContext() = 0;
	//设置监视管道
	virtual void WINAPI SetMonitor(BOOL bMonitor) = 0;
	//是否是监视管道
	virtual BOOL WINAPI IsMonitor() = 0;
	//连接管道，返回值详见"连接管道的返回值宏定义"
	virtual INT WINAPI Connect(LPCSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection) = 0;
	//连接管道，返回值详见"连接管道的返回值宏定义"
	virtual INT WINAPI ConnectW(LPCWSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection) = 0;
	//获取管道连接状态
	virtual BOOL WINAPI IsConnect() = 0;
	//断开连接管道
	virtual VOID WINAPI Disconnect() = 0;
	//发送数据
	virtual BOOL WINAPI SendData(LPCSTR lpszSendData, DWORD dwSendSize) = 0;
	//接受数据
	virtual BOOL WINAPI RecvData() = 0;
};

/////////////////////////////////////////////////////////////////////////////////
struct IOCP_IPC_CLS INamedPipeEvent
{
	virtual VOID WINAPI OnCompletedCreate(INamedPipe* pNamedPipe) = 0;
	virtual VOID WINAPI OnCompletedConnect(INamedPipe* pNamedPipe) = 0;
	virtual BOOL WINAPI OnCompletedDisconnect(INamedPipe* pNamedPipe) = 0;
	virtual BOOL WINAPI OnCompletedSend(INamedPipe* pNamedPipe,LPCSTR lpszSendData,DWORD dwSendSize) = 0;
	virtual DWORD WINAPI OnCompletedRecv(INamedPipe* pNamedPipe,LPCSTR lpszRecvData,DWORD dwRecvSize) = 0;
	virtual BOOL WINAPI OnBeforeRelease(INamedPipe* pNamedPipe) = 0;
};

#endif
