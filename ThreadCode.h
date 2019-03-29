#ifndef __THREADCODE_H__
#define __THREADCODE_H__

class CThread
{
public:
	CThread();
	virtual ~CThread();

	BOOL Start(BOOL bSuspend = FALSE, DWORD dwStackSize = 0);
	BOOL Stop(DWORD dwTimeOut = INFINITE);
	DWORD Suspend()
	{
		if (m_hThread)
			return ::SuspendThread(m_hThread);
		return (DWORD)(-1);
	}
	DWORD Resume()
	{
		if (m_hThread)
			return ::ResumeThread(m_hThread);
		return (DWORD)(-1);
	}
	HANDLE GetHandle()
	{
		return m_hThread;
	}
	DWORD GetID()
	{
		return m_dwThreadId;
	}
	BOOL IsRunning()
	{
		return m_bRunning;
	}
	void SetRunning(BOOL bRunning)
	{
		m_bRunning = bRunning;
	}
protected:
	virtual void	Run() = 0;
	virtual BOOL	BeforeRun() = 0;
	virtual void	AfterRun() = 0;
	virtual void	Debug(DWORD dwErrCode) = 0;

private:
	static DWORD WINAPI ThreadStartRoutine(LPVOID lpParameter);

private:
	HANDLE	m_hThread;
	DWORD	m_dwThreadId;
	BOOL	m_bRunning;
};

#endif
