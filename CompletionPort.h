#ifndef __COMPLETIONPORT_H__
#define __COMPLETIONPORT_H__

#include "npdef.h"
#include "ThreadCode.h"


//////////////////////////////////////////////////////////
//信息打印，带时间戳
extern int __cdecl ConsolePrintf(LPCTSTR lpszFormat, ...);
//////////////////////////////////////////////////////////
class CCompletionPort;
class CCompletionThread : public CThread
{
public:
	CCompletionThread();

	BOOL StartCompletionPort(CCompletionPort* pCompletionPort);
public:
	virtual ~CCompletionThread();
protected:
	virtual void	Run();
	virtual BOOL	BeforeRun();
	virtual void	AfterRun();
	virtual void	Debug(DWORD dwErrCode);

private:
	CCompletionPort* m_pCompletionPort;
};

typedef std::vector<CCompletionThread*>	CompletionThreadList;

class CCompletionPort
{
	friend class CCompletionThread;

public:
	CCompletionPort();

	DWORD Start(DWORD dwThreadCount = 0);
	void Stop();
	HANDLE BindIoHandle(HANDLE hIoHandle, LPVOID pCompletionKey);
	VOID GetCompletionQueued();
	BOOL PostCompletionData(PCOMPLETIONOVERLAPPEDDATA pCompletionData);

	VOID SetContext(ULONG_PTR ptrContext);
	HANDLE GetSafeHandle();
	operator HANDLE() const;

	BOOL IsWorking() { return m_bWork; }

public:
	virtual ~CCompletionPort();

private:
	HANDLE	m_hCompletionPort;
	CompletionThreadList m_vecCompletionThread;
	BOOL m_bWork;
	ULONG_PTR m_ptrContext;
};

__inline VOID CCompletionPort::SetContext(ULONG_PTR ptrContext)
{m_ptrContext = ptrContext;}

__inline HANDLE CCompletionPort::GetSafeHandle()
{return this != NULL ? m_hCompletionPort : NULL;}

__inline CCompletionPort::operator HANDLE() const
{return m_hCompletionPort;}

#endif
