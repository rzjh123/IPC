#ifndef _IPC_H_
#define _IPC_H_

#ifdef IPC_EXPORTS
#define IOCP_IPC_CLS   __declspec(dllexport)
#define IOCP_IPC_API   __declspec(dllexport)
#else
#define IOCP_IPC_CLS   __declspec(dllimport)
#define IOCP_IPC_API   __declspec(dllimport)
#endif // IPC_EXPORTS

#endif // _IPC_H_

