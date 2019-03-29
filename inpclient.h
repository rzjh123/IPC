#ifndef __INPCLT_H__
#define __INPCLT_H__

#include "npdef.h"
//���ӹܵ��ķ���ֵ�궨��
//���ӿͻ��˹ܵ�ʧ��
#define CLIENTPIPE_START_FAILED			0
//���ӿͻ��˹ܵ��ɹ�
#define CLIENTPIPE_START_SUCCEEDED		1
//�ͻ��˹ܵ��ѳɹ�����
#define CLIENTPIPE_START_ISSTARTED		2
//�ͻ��˹ܵ�����������
#define CLIENTPIPE_START_ISSTARTING		3
//�ͻ��˹ܵ�����������
#define CLIENTPIPE_START_ISCONECTING	4

#ifdef __cplusplus
extern "C" {
#endif

	namespace NS_IPC
	{
		//�ͻ��˹ܵ��ص��¼�
		struct IOCP_IPC_CLS INamePipeClitEvent
		{
			//�ܵ����ӳɹ��¼�
			virtual BOOL WINAPI OnConnect() = 0;
			//�ܵ��Ͽ��¼�
			virtual BOOL WINAPI OnDisconnect() = 0;
			//�ܵ����������¼�
			//����FALSE���رչܵ������򲻹رչܵ�
			virtual BOOL WINAPI OnSendData(LPCSTR lpszSendData, DWORD dwSendSize) = 0;
			//�ܵ����������¼�
			//����δ��������ݴ�С: ������0����ʾ�������ݶ��Ѵ������; ����ͷ���ʵ��δ����������ݴ�С
			virtual DWORD WINAPI OnRecvData(LPCSTR lpszRecvData, DWORD dwRecvSize) = 0;
			virtual BOOL WINAPI OnRelease(INamedPipe* pNamedPipe) = 0;
		};
		//�ͻ��˹ܵ��ഴ������
		IOCP_IPC_API INamedPipe* WINAPI CreateNamePipeClient(INamePipeClitEvent* pClientEvent);
	};

#ifdef __cplusplus
}
#endif


#endif
