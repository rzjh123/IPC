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
//����ζ˹ܵ���ӿں���
struct IOCP_IPC_CLS  INamedPipeServer
{
	//�ͷŹܵ������
	virtual VOID WINAPI Release() = 0;
	//���ӹܵ�������ֵ���"���ӹܵ��ķ���ֵ�궨��"
	virtual INamedPipe* WINAPI Create(LPCSTR szPipeName, INamedPipeEvent* pNamedPipeEvent, DWORD dwTimeout) = 0;
	//���ӹܵ�������ֵ���"���ӹܵ��ķ���ֵ�궨��"
	virtual INamedPipe* WINAPI CreateW(LPCWSTR szPipeName, INamedPipeEvent* pNamedPipeEvent, DWORD dwTimeout) = 0;
	//�ܵ�������Ƿ���������
	virtual BOOL WINAPI IsRunning() = 0;
	//ֹͣ�ܵ������
	virtual BOOL WINAPI Stop() = 0;
	//��ȡ�ܵ���
	virtual DWORD WINAPI GetNamedPipeCount() = 0;
	//��ȡ�ܵ��ӿ�
	virtual INamedPipe* WINAPI GetNamedPipe(HANDLE hPipe) = 0;
	//�Ƴ��ܵ��ӿ�
	virtual VOID WINAPI RemoveNamedPipe(HANDLE hPipe) = 0;

	//ѭ��ÿ���ܵ�
	virtual void WINAPI ForEachNamedPipe(INamedPipeServerRoutine* pRoutine) = 0;
};

//����˹ܵ��ഴ������
IOCP_IPC_API INamedPipeServer* WINAPI CreateNamedPipeServer();

#ifdef __cplusplus
}
#endif

#endif
