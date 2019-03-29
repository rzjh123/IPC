#ifndef __INPSRV_H__
#define __INPSRV_H__

#include "npdef.h"

/////////////////////////////////////////////////////////////////////////////////
#ifdef __cplusplus
extern "C" {
#endif

struct IOCP_IPC_CLS INamedPipeServerRoutine
{
	virtual void WINAPI Routine(INamedPipe* pNamedPipe) = 0;
};
/////////////////////////////////////////////////////////////////////////////////
//服务段端管道类接口函数
struct IOCP_IPC_CLS  INamedPipeServer
{
	//释放管道服务端
	virtual VOID WINAPI Release() = 0;
	//连接管道，返回值详见"连接管道的返回值宏定义"
	virtual INamedPipe* WINAPI Create(LPCSTR szPipeName, INamedPipeEvent* pNamedPipeEvent, DWORD dwTimeout) = 0;
	//连接管道，返回值详见"连接管道的返回值宏定义"
	virtual INamedPipe* WINAPI CreateW(LPCWSTR szPipeName, INamedPipeEvent* pNamedPipeEvent, DWORD dwTimeout) = 0;
	//管道服务端是否正在运行
	virtual BOOL WINAPI IsRunning() = 0;
	//停止管道服务端
	virtual BOOL WINAPI Stop() = 0;
	//获取管道数
	virtual DWORD WINAPI GetNamedPipeCount() = 0;
	//获取管道接口
	virtual INamedPipe* WINAPI GetNamedPipe(HANDLE hPipe) = 0;
	//移除管道接口
	virtual VOID WINAPI RemoveNamedPipe(HANDLE hPipe) = 0;

	//循环每个管道
	virtual void WINAPI ForEachNamedPipe(INamedPipeServerRoutine* pRoutine) = 0;
};

//服务端管道类创建函数
IOCP_IPC_API INamedPipeServer* WINAPI CreateNamedPipeServer();

#ifdef __cplusplus
}
#endif

#endif
