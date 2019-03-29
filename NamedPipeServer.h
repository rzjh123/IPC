#ifndef __NAMEDPIPESERVER_H__
#define __NAMEDPIPESERVER_H__

#include "LockCode.h"
#include "NamedPipe.h"
#include "CompletionPort.h"
#include "inpsrv.h"


typedef std::map<HANDLE, CNamedPipe*>	NAMEDPIPE_MAP;
class  IOCP_IPC_CLS CNamedPipeServer : public INamedPipeServer
{
public:
	CNamedPipeServer();
	CNamedPipe* Start(LPCTSTR lpszPipeName, INamedPipeEvent* pNamedPipeEvent, DWORD dwTimeout);
	CNamedPipe* CreatePipeInstance(LPCTSTR lpszPipeName, INamedPipeEvent* pNamedPipeEvent, BOOL bFirstPipeInstance = FALSE);
	CNamedPipe* CreateNextPipeInstance();
	VOID RemoveNamedPipeClient(HANDLE hPipe);
	CNamedPipe* GetNamedPipeClient(HANDLE hPipe);
	CCompletionPort* GetCompletionPort();

	template<class _Fn>
	inline void For_Each_NamedPipe(_Fn _Func)
	{
		NAMEDPIPE_MAP::iterator it;
		m_csLock.Lock();
		try
		{
			it = m_mapNamedPipe.begin();
			for(; it != m_mapNamedPipe.end(); it++)
			{
				_Func(it->second);			
			}
		}
		catch(...)
		{
			ConsolePrintf(_T("For_Each_NamedPipe Exception\r\n"));
		}
		m_csLock.Unlock();
	}

	BOOL IsWorking() { return m_completionPort.IsWorking(); }

public:
	virtual ~CNamedPipeServer();
	//INamedPipeServer
	//�ͷŹܵ������
	virtual VOID WINAPI Release();
	//���ӹܵ�������ֵ���"���ӹܵ��ķ���ֵ�궨��"
	virtual INamedPipe* WINAPI Create(LPCSTR szPipeName, INamedPipeEvent* pNamedPipeEvent, DWORD dwTimeout);
	//���ӹܵ�������ֵ���"���ӹܵ��ķ���ֵ�궨��"
	virtual INamedPipe* WINAPI CreateW(LPCWSTR szPipeName, INamedPipeEvent* pNamedPipeEvent, DWORD dwTimeout);
	//�ܵ�������Ƿ���������
	virtual BOOL WINAPI IsRunning();
	//ֹͣ�ܵ������
	virtual BOOL WINAPI Stop();
	//��ȡ�ܵ���
	virtual DWORD WINAPI GetNamedPipeCount();
	//��ȡ�ܵ��ӿ�
	virtual INamedPipe* WINAPI GetNamedPipe(HANDLE hPipe);
	//�Ƴ��ܵ��ӿ�
	virtual VOID WINAPI RemoveNamedPipe(HANDLE hPipe);
	//ѭ��ÿ���ܵ�
	virtual void WINAPI ForEachNamedPipe(INamedPipeServerRoutine* pRoutine);
private:
	CCompletionPort	 m_completionPort;

public:
	NAMEDPIPE_MAP m_mapNamedPipe;
	TCHAR m_szPipeName[MAX_PIPENAME_LEN];
	INamedPipeEvent* m_pNamedPipeEvent;
	CNamedPipe* m_pCurrNamedPipe;
	CLock m_csLock;
};

__inline CCompletionPort* CNamedPipeServer::GetCompletionPort()
{
	return &m_completionPort;
}

#endif

