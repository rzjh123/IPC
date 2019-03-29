#ifndef __NAMEDPIPECLIENT_H__
#define __NAMEDPIPECLIENT_H__

#include "inpclient.h"
#include "namedpipe.h"
#include "ipc.h"

	/////////////////////////////////////////////////////////////////////////////////
	class IOCP_IPC_CLS CNamedPipeClientEvent : public INamedPipeEvent
	{
	public:
		CNamedPipeClientEvent(NS_IPC::INamePipeClitEvent* pNamedPipeEvent)
		{
			m_pNamedPipeEvent = pNamedPipeEvent;
		}
		~CNamedPipeClientEvent()
		{
			m_pNamedPipeEvent = NULL;
		}
		void SetNamedPipeEvent(NS_IPC::INamePipeClitEvent* pNamedPipeEvent)
		{
			m_pNamedPipeEvent = pNamedPipeEvent;
		}
	public:
		//INamedPipeEvent
		virtual VOID WINAPI OnCompletedCreate(INamedPipe* pNamedPipe)
		{
			if (m_pNamedPipeEvent)
				m_pNamedPipeEvent->OnConnect();
		}
		virtual VOID WINAPI OnCompletedConnect(INamedPipe* pNamedPipe)
		{
			//if (m_pNamedPipeEvent)
			//	m_pNamedPipeEvent->OnConnect();
		}
		virtual BOOL WINAPI OnCompletedDisconnect(INamedPipe* pNamedPipe)
		{
			if (m_pNamedPipeEvent)
				m_pNamedPipeEvent->OnDisconnect();
			return FALSE;
		}
		virtual BOOL WINAPI OnCompletedSend(INamedPipe* pNamedPipe, LPCSTR lpszSendData, DWORD dwSendSize)
		{
			if (m_pNamedPipeEvent)
				return m_pNamedPipeEvent->OnSendData(lpszSendData, dwSendSize);
			return TRUE;
		}
		virtual DWORD WINAPI OnCompletedRecv(INamedPipe* pNamedPipe, LPCSTR lpszRecvData, DWORD dwRecvSize)
		{
			if (m_pNamedPipeEvent)
				return m_pNamedPipeEvent->OnRecvData(lpszRecvData, dwRecvSize);
			return 0;
		}
		virtual BOOL WINAPI OnBeforeRelease(INamedPipe* pNamedPipe)
		{
			return FALSE;
		}
	private:
		NS_IPC::INamePipeClitEvent* m_pNamedPipeEvent;
	};

	class IOCP_IPC_CLS CNamedPipeClient : public CNamedPipe
	{
	public:
		CNamedPipeClient(NS_IPC::INamePipeClitEvent* pNamedPipeEvent);

		BOOL SetConnectEvent();
		BOOL IsReconnection();
		INT StartNamedPipeClient(LPCTSTR lpszPipeName, DWORD dwWaitTimeOut);
		VOID StopNamedPipeClient();
		void SetNamedPipeEvent(NS_IPC::INamePipeClitEvent* pNamedPipeEvent);
	public:
		virtual ~CNamedPipeClient();
		virtual VOID DisconnectPipeInstance(BOOL bAutoDelete);

		//INamedPipe
		//断开连接并释放该管道
		virtual VOID WINAPI Release();
		//连接管道，返回值详见"连接管道的返回值宏定义"
		virtual INT WINAPI Connect(LPCSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection);
		//连接管道，返回值详见"连接管道的返回值宏定义"
		virtual INT WINAPI ConnectW(LPCWSTR szPipeName, DWORD dwWaitTimeOut, BOOL bReconnection);

	public:
		HANDLE m_hThread;
		HANDLE m_hConnectEvent;

	private:
		CNamedPipeClientEvent m_npEvent;
		//是否断线重连
		BOOL m_bReconnection;
	};

	__inline void CNamedPipeClient::SetNamedPipeEvent(NS_IPC::INamePipeClitEvent* pNamedPipeEvent)
	{
		m_npEvent.SetNamedPipeEvent(pNamedPipeEvent);
	}

	__inline BOOL CNamedPipeClient::IsReconnection()
	{
		return m_bReconnection;
	}


#endif
