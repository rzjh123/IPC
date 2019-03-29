#ifndef __INPCLT_H__
#define __INPCLT_H__

#include "npdef.h"
//连接管道的返回值宏定义
//连接客户端管道失败
#define CLIENTPIPE_START_FAILED			0
//连接客户端管道成功
#define CLIENTPIPE_START_SUCCEEDED		1
//客户端管道已成功启动
#define CLIENTPIPE_START_ISSTARTED		2
//客户端管道正在启动中
#define CLIENTPIPE_START_ISSTARTING		3
//客户端管道正在连接中
#define CLIENTPIPE_START_ISCONECTING	4

#ifdef __cplusplus
extern "C" {
#endif

	namespace NS_IPC
	{
		//客户端管道回调事件
		struct IOCP_IPC_CLS INamePipeClitEvent
		{
			//管道连接成功事件
			virtual BOOL WINAPI OnConnect() = 0;
			//管道断开事件
			virtual BOOL WINAPI OnDisconnect() = 0;
			//管道发送数据事件
			//返回FALSE将关闭管道，否则不关闭管道
			virtual BOOL WINAPI OnSendData(LPCSTR lpszSendData, DWORD dwSendSize) = 0;
			//管道接受数据事件
			//返回未处理的数据大小: 若返回0，表示接受数据都已处理完毕; 否则就返回实际未处理完的数据大小
			virtual DWORD WINAPI OnRecvData(LPCSTR lpszRecvData, DWORD dwRecvSize) = 0;
			virtual BOOL WINAPI OnRelease(INamedPipe* pNamedPipe) = 0;
		};
		//客户端管道类创建函数
		IOCP_IPC_API INamedPipe* WINAPI CreateNamePipeClient(INamePipeClitEvent* pClientEvent);
	};

#ifdef __cplusplus
}
#endif


#endif
