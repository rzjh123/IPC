#ifndef __LOCKCODE_H__
#define __LOCKCODE_H__

class CLock
{
public:
	CLock();
	~CLock();
	void	Lock();
	BOOL	TryLock(BOOL bFlag = TRUE);
	void	Unlock();
private:
	CRITICAL_SECTION	m_csObject;
};

template <typename T>
class CScopeLock
{
public:
	CScopeLock(T& tObject)
		:m_tObject(tObject)
	{
		m_tObject.Lock();
	}
	~CScopeLock()
	{
		m_tObject.Unlock();
	}
private:
	T& m_tObject;
};

#endif