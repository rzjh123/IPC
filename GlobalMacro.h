/**********************************************************
@copyright	(C)2012, 
@file		GlobalMacro.h
@brief		ȫ�ֺ궨���ͷ�ļ�
@details	���ļ�����������Ҫ�õ���ȫ�ֺ�Ķ���
@version 
@author		������
@date		2012-2-16
@changelog1:
	@date
	@version
	@author
	@brief
**********************************************************/

#if !defined(AFX_GLOBALMACRO_H__DD58A78D_C125_410F_B4C8_F0067B797121__INCLUDED_)
#define AFX_GLOBALMACRO_H__DD58A78D_C125_410F_B4C8_F0067B797121__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma   warning(push)  
#pragma   warning(disable:4996 4090 4018) 

/// ��ȡ�����ά�� 
#ifndef PARRAYSIZE
	#define PARRAYSIZE(array) ((sizeof(array)/sizeof(array[0])))
#endif

/* �������ػ���״̬��Ϣ  */
#ifdef OK
#undef OK
#endif /* #ifdef OK */
#ifndef OK
#define OK               (0)    /* �ɹ�����	*/
#endif /* #ifndef OK */

/* �������ػ���״̬��Ϣ  */
#ifdef FAILURE
#undef FAILURE
#endif /* #ifdef FAILURE */
#ifndef FAILURE
#define FAILURE           (-1)    /* ʧ�ܷ���	*/
#endif /* #ifndef FAILURE */

//////////////////////////////////////////////////////////////////////////
///һЩ�궨��

///ɾ��һ������ָ��ĺ궨��
//lint -emacro(774, DELETEA)
#ifndef DELETEA
#define DELETEA(ptr)	\
	if(NULL != ptr)		\
	{					\
		delete[] ptr;	\
		ptr = NULL;		\
	}
#endif

///ɾ��һ��ָ��ĺ궨��
#ifndef FREEP
#define FREEP(ptr)		\
	if(NULL != ptr)		\
	{					\
		free(ptr) ;		\
		ptr = NULL;		\
	}
#endif

///ɾ��һ��ָ��ĺ궨��
#ifndef GLOBALFREEP
#define GLOBALFREEP(ptr)	\
	if(NULL != ptr)			\
	{						\
		GlobalFree(ptr) ;	\
		ptr = NULL;			\
	}
#endif

///ɾ��һ��ָ��ĺ궨��
//lint -emacro(774, DELETEP)
#ifndef DELETEP
#define DELETEP(ptr)	\
	if(NULL != (ptr))	\
	{					\
		delete (ptr);	\
		(ptr) = NULL;	\
	}
#endif

///ɾ��һ��GDI����ĺ궨��
//lint -emacro(774, DELETEOBJECT)
#ifndef DELETEOBJECT
#define DELETEOBJECT(ptr)	\
	if(NULL != (ptr))		\
	{						\
		::DeleteObject(ptr);\
		(ptr) = NULL;		\
	}
#endif

///Destroyһ��Window
//lint -emacro(774, DESTROYWINDOW)
#ifndef DESTROYWINDOW
#define DESTROYWINDOW(hWnd)		\
	if (IsWindow(hWnd))			\
	{							\
		DestroyWindow(hWnd);	\
	}
#endif

///�ر�һ��Handle
//lint -emacro(774, CLOSEHANDLE)
#ifndef CLOSEHANDLE
#define CLOSEHANDLE(handle)		\
	if(NULL != (handle))		\
	{							\
		::CloseHandle (handle);	\
		(handle) = NULL;		\
	}
#endif

///ʹ��FreeLibraryж��һ����ĺ궨��
#ifndef FREELIBRARY
#define FREELIBRARY(hModule)	\
	if(NULL != hModule)			\
	{							\
		FreeLibrary(hModule) ;	\
		hModule = NULL;			\
	}
#endif

///ʹ��AfxFreeLibraryж��һ����ĺ궨��
#ifndef AFXFREELIBRARY
#define AFXFREELIBRARY(hModule)	\
	if(NULL != hModule)			\
	{							\
		AfxFreeLibrary(hModule);\
		hModule = NULL;			\
	}
#endif

///ɾ��һ��ָ��ĺ궨��
//lint -emacro(774, FREEP)
#ifndef FREEP
#undef  FREEP
#define FREEP(ptr)		\
	if(NULL != ptr)		\
	{					\
		free(ptr) ;		\
		ptr = NULL;		\
	}
#endif

/** ����ĸ�������������ɾ����ͬ���͵�ָ��ĺ궨��
*/
#ifndef DELETE_TYPE_P
#define DELETE_TYPE_P(Type, ptrEvent)			\
	{											\
		Type *ptrEventLocal = (Type *)ptrEvent; \
		DELETEP(ptrEventLocal);					\
		ptrEvent = NULL;						\
	}
#endif

/** ����ĸ�������������ɾ����ͬ���͵�ָ��ĺ궨��
*/
#ifndef DELETE_TYPE_A
#define DELETE_TYPE_A(Type, ptrEvent) \
	{\
		Type *ptrEventLocal = (Type *)ptrEvent; \
		DELETEA(ptrEventLocal); \
		ptrEvent = NULL; \
	}
#endif

#ifndef VOS_DELETE_SEM
#define VOS_DELETE_SEM(semId)	\
	if (NULL != semId)			\
	{							\
		VOS_DeleteSem(semId);	\
		semId = NULL;			\
	}
#endif

#ifndef VOS_DELETE_THREAD_MUTEX
#define VOS_DELETE_THREAD_MUTEX(semId)	\
	if (NULL != semId)					\
	{									\
		VOS_DeleteThreadMutex(semId);	\
		semId = NULL;					\
	}
#endif

/** This macro is used to assert that a condition must be TRUE.
��condition������������ִ��statement��䣬Ȼ����return_valueֵreturn
*/
#ifndef PAssert_ReturnValue
#define PAssert_ReturnValue(condition, return_value) \
	{  \
		if (!(condition)) \
		{ \
			return (return_value); \
		} \
	}
#endif

/** This macro is used to assert that a condition must be TRUE.
��condition������������ִ��statement��䣬Ȼ��return
*/
#ifndef PAssert_Return
#define PAssert_Return(condition) \
	{  \
		if (!(condition)) \
		{ \
			return ; \
		} \
	}
#endif

/** This macro is used to assert that a condition must be TRUE.
��condition������������ִ��statement��䣬Ȼ����return_valueֵreturn
*/
#ifndef PAssert_Statement_ReturnValue
#define PAssert_Statement_ReturnValue(condition, statement, return_value) \
	{  \
		if (!(condition)) \
		{ \
			statement; \
			return (return_value); \
		} \
	}
#endif

/** This macro is used to assert that a condition must be TRUE.
��condition������������ִ��statement��䣬Ȼ��return
*/
#ifndef PAssert_Statement_Return
#define PAssert_Statement_Return(condition, statement) \
	{  \
		if (!(condition)) \
		{ \
			statement; \
			return ; \
		} \
	}
#endif

/** This macro is used to assert that a pointer must be non-null.
��ָ��ptrΪNULL��ִ��statement��䣬Ȼ����return_valueֵreturn
*/
#ifndef PAssertNotNull_Statement_ReturnValue
#define PAssertNotNull_Statement_ReturnValue(ptr, statement, return_value) \
	{ \
		if( (ptr) == NULL) \
		{ \
			statement; \
			return (return_value); \
		} \
	}
#endif

/** This macro is used to assert that a pointer must be non-null.
��ָ��ptrΪNULL��ִ��statement��䣬Ȼ��return
*/
#ifndef PAssertNotNull_Statement_Return
#define PAssertNotNull_Statement_Return(ptr, statement) \
	{ \
		if( (ptr) == NULL) \
		{ \
			statement; \
			return ; \
		} \
	}
#endif

/** This macro is used to assert that a pointer must be non-null.
��ָ��ptrΪNULL��ִ��statement��䣬Ȼ����return_valueֵreturn
*/
#ifndef PAssertNotNull_ReturnValue
#define PAssertNotNull_ReturnValue(ptr, return_value) \
	{ \
		if( (ptr) == NULL) \
		{ \
			return (return_value); \
		} \
	}
#endif

/** This macro is used to assert that a pointer must be non-null.
��ָ��ptrΪNULL��ִ��statement��䣬Ȼ��return
*/
#ifndef PAssertNotNull_Return
#define PAssertNotNull_Return(ptr) \
	{ \
		if( (ptr) == NULL) \
		{ \
			return ; \
		} \
	}
#endif

/** This macro is used to assert that a pointer must be non-null.
��ָ��ptrΪNULL��ִ��continue���
*/
#define PAssertNotNull_Continue(ptr) \
	{ \
		if( (ptr) == NULL) \
		{ \
			continue ; \
		} \
	}

/** This macro is used to assert that a pointer must be non-null.
��ָ��ptrΪNULL��ִ��statement,Ȼ��ִ��continue���
*/
#define PAssertNotNull_Statement_Continue(ptr, statement) \
	{ \
		if( (ptr) == NULL) \
		{ \
			statement; \
			continue ; \
		} \
	}

/** This macro is used to assert that a pointer must be non-null.
��ָ��ptrΪNULL��ִ��break���
*/
#define PAssertNotNull_Break(ptr) \
	{ \
		if( (ptr) == NULL) \
		{ \
			break ; \
		} \
	}

/** This macro is used to assert that a pointer must be non-null.
��ָ��ptrΪNULL��ִ��statement,Ȼ��ִ��break���
*/
#define PAssertNotNull_Statement_Break(ptr, statement) \
	{ \
		if( (ptr) == NULL) \
		{ \
			statement; \
			break ; \
		} \
	}

/** This macro is used to do something and return 
ִ��һ�����statement��Ȼ��return return_value
*/
#ifndef PStatement_Return
#define PStatement_Return(statement) \
{ \
	statement; \
	return ; \
}
#endif

/** This macro is used to do something and return 
ִ��һ�����statement��Ȼ��return return_value
*/
#ifndef PStatement_ReturnValue
#define PStatement_ReturnValue(statement, return_value) \
{ \
	statement; \
	return return_value; \
}
#endif

/** This macro is used to assert that a condition must be TRUE.
��condition������������ִ��break���
*/
#ifndef PAssert_Break
#define PAssert_Break(condition) \
{  \
	if (!(condition)) \
	{ \
		break ; \
	} \
}
#endif

/** This macro is used to do something and break 
ִ��һ�����statement��Ȼ��break
*/
#ifndef PStatement_Break
#define PStatement_Break(statement) \
{ \
	statement; \
	break; \
}
#endif

/** This macro is used to assert that a condition must be TRUE.
��condition������������ִ��statement��䣬Ȼ��ִ��break���
*/
#ifndef PAssert_Statement_Break
#define PAssert_Statement_Break(condition, statement) \
{  \
	if (!(condition)) \
	{ \
		statement; \
		break ; \
	} \
}
#endif

/** This macro is used to assert that a condition must be TRUE.
��condition������������ִ��continue���
*/
#ifndef PAssert_Continue
#define PAssert_Continue(condition) \
{  \
	if (!(condition)) \
	{ \
		continue ; \
	} \
}
#endif

/** This macro is used to do something and continue 
ִ��һ�����statement��Ȼ��continue
*/
#ifndef PStatement_Continue
#define PStatement_Continue(statement) \
{ \
	statement; \
	continue; \
}
#endif

/** This macro is used to assert that a condition must be TRUE.
��condition������������ִ��statement��䣬Ȼ��ִ��continue���
*/
#ifndef PAssert_Statement_Continue
#define PAssert_Statement_Continue(condition, statement) \
{  \
	if (!(condition)) \
	{ \
		statement; \
		continue ; \
	} \
}
#endif

/** �ղ���
*/
#ifndef NULL_OPERATION
	#define NULL_OPERATION
#endif

///memsetȱʡ���캯��
#ifndef MEMSET_CONSTRUCTOR
#define MEMSET_CONSTRUCTOR(ClassType) \
	ClassType() \
	{ \
		memset(this, 0, sizeof(ClassType)); \
	}
#endif

#if 1
#ifdef __cplusplus
/** 
�����ض���������ɾ�����������͵�����ָ��
*/
#ifndef DELETE_ARRAY_TEMPLATE
#define DELETE_ARRAY_TEMPLATE
template <class classType>
void DeleteArray(void *&ptr)
{
	classType *ptrClassType = (classType *)ptr;
	DELETEA(ptrClassType);
	ptr = NULL;
}
#endif

/** 
�����ض���������ɾ�����������͵�ָ��
*/
#ifndef DELETE_TEMPLATE
#define DELETE_TEMPLATE
template <class classType>
void Delete(void *&ptr)
{
	classType *ptrClassType = (classType *)ptr;
	DELETEP(ptrClassType);
	ptr = NULL;
}
#endif
#endif
#endif

///���ƺ궨��
#ifndef LEFT_SHIFT

#define LEFT_SHIFT(uiData) \
	( (uiData) * 2)
#endif

//////////////////////////////////////////////////////////////////////////
///NEWϵ�к궨��
/** @macro MACRO_NEW_RETURNVALUE
@brief new CONSTRUCTOR�������Ӧָ��POINTER��ʧ����return RET_VAL
@details ����ACE ��ACE_NEW_RETURN�궨��
	1.POINTERָ������ڱ��궨�����ʱ�ȶ���á�
	2.���ݹ��캯��CONSTRUCTOR newһ�����󸳸�POINTER��
	3.ʧ��return RET_VAL.
*/
#ifndef MACRO_NEW_RETURNVALUE
#define MACRO_NEW_RETURNVALUE(POINTER, CONSTRUCTOR, RET_VAL) \
	do \
	{ \
		POINTER = new  CONSTRUCTOR; \
		if (POINTER == 0) \
		{ \
			return RET_VAL; \
		} \
	} while (0);
#endif

#ifndef MACRO_NEW_RETURN
#define MACRO_NEW_RETURN(POINTER, CONSTRUCTOR) \
	do \
	{ \
		POINTER = new CONSTRUCTOR; \
		if (POINTER == 0) \
		{ \
			return; \
		} \
	} while (0);
#endif

#ifndef MACRO_NEW_NORETURN
#define MACRO_NEW_NORETURN(POINTER, CONSTRUCTOR) \
	do \
	{ \
		POINTER = new CONSTRUCTOR; \
		if (POINTER == 0) \
		{ } \
	} while (0);
#endif

/** @macro CHECK_RUN_ONCE_BEGIN
@brief ��֤����ֻ����һ��
@details ��֤Ƕ��CHECK_RUN_ONCE_BEGIN��CHECK_RUN_ONCE_END֮��Ĵ���ֻ����һ��
@example
	CHECK_RUN_ONCE_BEING();
	{
		///�������ִֻ��һ�εĴ���
		int i++;
		...
	}
	CHECK_RUN_ONCE_BEGIN();
*/
#ifndef CHECK_RUN_ONCE_BEGIN
#define CHECK_RUN_ONCE_BEGIN() \
	do \
	{ \
		static UINT s_uiNumRun##NAME = 0; \
		if (0 == s_uiNumRun##NAME) \
		{ \
			s_uiNumRun##NAME ++;
#endif

#ifndef CHECK_RUN_ONCE_END
#define CHECK_RUN_ONCE_END() \
		} \
	} \
	while (0);
#endif

/** @macro CHECK_RUN_COUNT_BEGIN
@brief CHECK_RUN_COUNT_BEGIN()��CHECK_RUN_COUNT_END֮����뱣ִ֤�д�������Ϊmax_count��
@details 
	1.ÿ�����е�CHECK_RUN_COUNT_BEGIN��CHECK_RUN_COUNT_END֮�����ʱ����ִ�д���û�ﵽmax_count����ִ��һ�Ρ�
	2.��֤CHECK_RUN_COUNT_BEGIN��CHECK_RUN_COUNT_END֮��������д���������max_count�Ρ�
@param max_count ִ�е�������
@example 
	CHECK_RUN_COUNT_BEGIN(max_count);
	{
		///����Ĵ��뽫����ִ��max_count��
		///do something...
	}
	CHECK_RUN_COUNT_END();
*/
#ifndef CHECK_RUN_COUNT_BEGIN
	#define CHECK_RUN_COUNT_BEGIN(max_count) \
		do \
		{ \
			static UINT s_uiCount = 0; \
			if (s_uiCount < max_count) \
			{
#endif

#ifndef CHECK_RUN_COUNT_END
	#define CHECK_RUN_COUNT_END() \
				s_uiCount ++; \
			} \
		} \
		while (0);
#endif

/** @macro CHECK_CONDITION_RUN_ONCE_BEGIN
@brief ������ִ�б�֤��������ʱ,Ƕ��CHECK_CONDITION_RUN_ONCE_BEGIN��CHECK_CONDITION_RUN_ONCE_END֮��Ĵ���ֻ����һ��
@param condition ������������ʽ
@example
	CHECK_CONDITION_RUN_ONCE_BEGIN(8>7);
	{
		///��������ı��ʽ(8>7)Ϊtrue�Ż�ִ�б��δ���
		///�������ִֻ��һ�εĴ���
		int i++;
		...
	}
	CHECK_CONDITION_RUN_ONCE_END();
*/
//#ifndef CHECK_CONDITION_RUN_ONCE_BEGIN
//#define CHECK_CONDITION_RUN_ONCE_BEGIN(condition) \
//		do \
//		{ \
//			if (condition) \
//			{ \
//				CHECK_RUN_ONCE_BEGIN(); \
//				{
//#endif
//
//#ifndef CHECK_CONDITION_RUN_ONCE_END
//#define CHECK_CONDITION_RUN_ONCE_END() \
//				} \
//				CHECK_RUN_ONCE_END(); \
//			} \
//		} while (0);
//#endif

#ifndef CHECK_CONDITION_RUN_ONCE_BEGIN
#define CHECK_CONDITION_RUN_ONCE_BEGIN(condition) \
		do \
		{ \
			static UINT s_uiRunCount = 0; \
			if (0 == s_uiRunCount) \
			{ \
				if (condition) \
				{
#endif

#ifndef CHECK_CONDITION_RUN_ONCE_END
#define CHECK_CONDITION_RUN_ONCE_END() \
					s_uiRunCount ++;\
				} \
			} \
		} while (0);
#endif

/** @macro CHECK_CONDITION_RUN_COUNT_BEGIN
@brief ������ִ�б�֤��������ʱ,Ƕ��CHECK_CONDITION_RUN_COUNT_BEGIN��CHECK_CONDITION_RUN_COUNT_END֮��Ĵ���ֻ����һ��
@param condition ������������ʽ
@example
	CHECK_CONDITION_RUN_COUNT_BEGIN(8>7, 5);
	{
		///��������ı��ʽ(8>7)Ϊtrue�Ż�ִ�б��δ���
		///�������ִֻ��5�εĴ���
		int i++;
		...
	}
	CHECK_CONDITION_RUN_COUNT_END();
*/
//#ifndef CHECK_CONDITION_RUN_COUNT_BEGIN
//#define CHECK_CONDITION_RUN_COUNT_BEGIN(condition, max_count) \
//		do \
//		{ \
//			if (condition) \
//			{ \
//				CHECK_RUN_COUNT_BEGIN(max_count); \
//				{
//#endif
//
//#ifndef CHECK_CONDITION_RUN_COUNT_END
//#define CHECK_CONDITION_RUN_COUNT_END() \
//				} \
//				CHECK_RUN_COUNT_END(); \
//			} \
//		} while (0);
//#endif

#ifndef CHECK_CONDITION_RUN_COUNT_BEGIN
#define CHECK_CONDITION_RUN_COUNT_BEGIN(condition, max_count) \
		do \
		{ \
			static UINT s_uiRunCount = 0; \
			if (s_uiRunCount < max_count ) \
			{ \
				if (condition) \
				{
#endif

#ifndef CHECK_CONDITION_RUN_COUNT_END
#define CHECK_CONDITION_RUN_COUNT_END() \
					s_uiRunCount ++;\
				} \
			} \
		} while (0);
#endif

/** @macro DEBUG_ENABLE_ONLY_BEGIN
@brief DEBUG_ENABLE_ONLY_BEGIN()��DEBUG_ENABLE_ONLY_END()֮�����ֻ��DEBUG�²���Ч
@details 
	1.ͨ��debug��if(1){...}���������������.��ʵ���Կ���#if 1
	2.ͨ��release��if(0){...}���������������.��ʵ���Կ���#if 0
	3.����Ĵ����Ż��Ϳ��������Ĵ����ˡ�
@example 
	DEBUG_ENABLE_ONLY_BEGIN();
	{
		printf("I just work in debug mode.");
	}
	DEBUG_ENABLE_ONLY_END();
*/
#ifdef _DEBUG
	#ifndef DEBUG_ENABLE_ONLY_BEGIN
	#define DEBUG_ENABLE_ONLY_BEGIN() \
		if(1) \
		{ 
	#endif

	#ifndef DEBUG_ENABLE_ONLY_END
	#define DEBUG_ENABLE_ONLY_END() \
		}
	#endif
#else
	#ifndef DEBUG_ENABLE_ONLY_BEGIN
	#define DEBUG_ENABLE_ONLY_BEGIN() \
		if(0) \
		{ 
	#endif

	#ifndef DEBUG_ENABLE_ONLY_END
	#define DEBUG_ENABLE_ONLY_END() \
		}
	#endif
#endif

/** @macro TIMER_TRIGGER_BEGIN
@brief ÿ��millionsecondsInterval����ʱ����,Ƕ��TIMER_TRIGGER_BEGIN��TIMER_TRIGGER_END֮��Ĵ�������һ��
@details 
	1.����TIMER_TRIGGER_BEGIN��TIMER_TRIGGER_END�������ں���Ҫ�ܲ��ϱ����õ���
	2.���õ���ÿ��millionsecondsInterval����Ż����ִ��TIMER_TRIGGER_BEGIN��TIMER_TRIGGER_END֮����롣
@param millionsecondsInterval ������
@example
	TIMER_TRIGGER_BEGIN(2000);
	{
		///�������ÿ��2000����ִ��һ�εĴ���
		int i++;
		...
	}
	TIMER_TRIGGER_END();
*/
#ifndef TIMER_TRIGGER_BEGIN
#define TIMER_TRIGGER_BEGIN(millionsecondsInterval) \
	do \
	{ \
		static UINT s_uiTickCount = GetTickCount(); \
		UINT uiTickCount = GetTickCount(); \
		if ( (uiTickCount - s_uiTickCount) > millionsecondsInterval ) \
		{
#endif

#ifndef TIMER_TRIGGER_END
#define TIMER_TRIGGER_END() \
			s_uiTickCount = uiTickCount; \
		} \
	} while (0);
#endif

/** @macro OUTPUTDEBUGSTRING_DEBUG
@brief ֻ��DEBUG�汾�����õ�OutputDebugString����궨��
*/
#ifndef OUTPUTDEBUGSTRING_DEBUG
	#ifdef _DEBUG
		#define OUTPUTDEBUGSTRING_DEBUG(str) OutputDebugString(str)
	#else
		#define OUTPUTDEBUGSTRING_DEBUG(str)
	#endif
#endif


/** Declare all the standard PWlib class information.
This macro is used to provide the basic run-time typing capability needed
by the library. All descendent classes from the #PObject# class require
these functions for correct operation. Either use this macro or the
#PDECLARE_CLASS# macro.

The use of the #PDECLARE_CLASS# macro is no longer recommended for reasons
of compatibility with documentation systems.
*/
#ifndef CLASSINFO
#define CLASSINFO(cls, par) \
  public: \
  static const char * Class() \
	{ return #cls; } \
	virtual const char * GetClass(unsigned ancestor = 0) const \
	{ return ancestor > 0 ? par::GetClass(ancestor-1) : cls::Class(); } \
	virtual BOOL IsClass(const char * clsName) const \
	{ return strcmp(clsName, cls::Class()) == 0; } \
	virtual BOOL IsDescendant(const char * clsName) const \
	{ return strcmp(clsName, cls::Class()) == 0 || \
	par::IsDescendant(clsName); } 
#endif

/** Declare all the standard PWlib class information.
This macro is used to provide the basic run-time typing capability needed
by the library. All descendent classes from the #PObject# class require
these functions for correct operation. Either use this macro or the
#PDECLARE_CLASS# macro.

The use of the #PDECLARE_CLASS# macro is no longer recommended for reasons
of compatibility with documentation systems.
*/
#ifndef CLASSINFO_BASE
#define CLASSINFO_BASE(cls) \
  public: \
  static const char * Class() \
	{ return #cls; } \
	virtual const char * GetClass(unsigned ancestor = 0) const \
	{ return cls::Class(); } \
	virtual BOOL IsClass(const char * clsName) const \
	{ return strcmp(clsName, cls::Class()) == 0; } \
	virtual BOOL IsDescendant(const char * clsName) const \
	{ return strcmp(clsName, cls::Class()) == 0; } 
#endif

#pragma   warning(pop)

#endif // !defined(AFX_GLOBALMACRO_H__DD58A78D_C125_410F_B4C8_F0067B797121__INCLUDED_)
