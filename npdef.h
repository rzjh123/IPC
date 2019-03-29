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
//�ܵ���ӿں���
struct  IOCP_IPC_CLS INamedPipe
{
	//�Ͽ����Ӳ��ͷŸùܵ�
	virtual VOID WINAPI Release() = 0;
	//��ȡ�ܵ����
	virtual HANDLE WINAPI GetHandle() = 0;
	//�Ƿ��ǿͻ��˹ܵ�
	virtual BOOL WINAPI IsClientPipe() = 0;
	//��������������
	virtual VOID WINAPI SetContext(ULONG_PTR ptrContext) = 0;
	//��ȡ����������
	virtual ULONG_PTR WINAPI GetContext() = 0;
	//���ü��ӹܵ�
	virtual void WINAPI SetMonitor(BOOL bMonitor) = 0;
	//�Ƿ��Ǽ��ӹܵ�
	virtual BOOL WINAPI IsMonitor() = 0;
	//���ӹܵ�������ֵ���"���ӹܵ��ķ���ֵ�궨��"
	virtual INT WINAPI Connect(LPCSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection) = 0;
	//���ӹܵ�������ֵ���"���ӹܵ��ķ���ֵ�궨��"
	virtual INT WINAPI ConnectW(LPCWSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection) = 0;
	//��ȡ�ܵ�����״̬
	virtual BOOL WINAPI IsConnect() = 0;
	//�Ͽ����ӹܵ�
	virtual VOID WINAPI Disconnect() = 0;
	//��������
	virtual BOOL WINAPI SendData(LPCSTR lpszSendData, DWORD dwSendSize) = 0;
	//��������
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
