#include "stdafx.h"
#include "LockCode.h"

CLock::CLock()
{
	::InitializeCriticalSection(&m_csObject);
}

CLock::~CLock()
{
	::DeleteCriticalSection(&m_csObject);
}

void CLock::Lock()
{
	::EnterCriticalSection(&m_csObject);
}

void CLock::Unlock()
{
	::LeaveCriticalSection(&m_csObject);
}

BOOL CLock::TryLock(BOOL bFlag/* = TRUE*/)
{
	BOOL bRet = ::TryEnterCriticalSection(&m_csObject);
	if (bRet && bFlag)
	{
		::LeaveCriticalSection(&m_csObject);
	}

	return bRet;
}
