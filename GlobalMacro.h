/**********************************************************
@copyright	(C)2012, 
@file		GlobalMacro.h
@brief		全局宏定义的头文件
@details	本文件包含了所有要用到的全局宏的定义
@version 
@author		李万曦
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

/// 获取数组的维数 
#ifndef PARRAYSIZE
	#define PARRAYSIZE(array) ((sizeof(array)/sizeof(array[0])))
#endif

/* 函数返回基本状态信息  */
#ifdef OK
#undef OK
#endif /* #ifdef OK */
#ifndef OK
#define OK               (0)    /* 成功返回	*/
#endif /* #ifndef OK */

/* 函数返回基本状态信息  */
#ifdef FAILURE
#undef FAILURE
#endif /* #ifdef FAILURE */
#ifndef FAILURE
#define FAILURE           (-1)    /* 失败返回	*/
#endif /* #ifndef FAILURE */

//////////////////////////////////////////////////////////////////////////
///一些宏定义

///删除一个数组指针的宏定义
//lint -emacro(774, DELETEA)
#ifndef DELETEA
#define DELETEA(ptr)	\
	if(NULL != ptr)		\
	{					\
		delete[] ptr;	\
		ptr = NULL;		\
	}
#endif

///删除一个指针的宏定义
#ifndef FREEP
#define FREEP(ptr)		\
	if(NULL != ptr)		\
	{					\
		free(ptr) ;		\
		ptr = NULL;		\
	}
#endif

///删除一个指针的宏定义
#ifndef GLOBALFREEP
#define GLOBALFREEP(ptr)	\
	if(NULL != ptr)			\
	{						\
		GlobalFree(ptr) ;	\
		ptr = NULL;			\
	}
#endif

///删除一个指针的宏定义
//lint -emacro(774, DELETEP)
#ifndef DELETEP
#define DELETEP(ptr)	\
	if(NULL != (ptr))	\
	{					\
		delete (ptr);	\
		(ptr) = NULL;	\
	}
#endif

///删除一个GDI对象的宏定义
//lint -emacro(774, DELETEOBJECT)
#ifndef DELETEOBJECT
#define DELETEOBJECT(ptr)	\
	if(NULL != (ptr))		\
	{						\
		::DeleteObject(ptr);\
		(ptr) = NULL;		\
	}
#endif

///Destroy一个Window
//lint -emacro(774, DESTROYWINDOW)
#ifndef DESTROYWINDOW
#define DESTROYWINDOW(hWnd)		\
	if (IsWindow(hWnd))			\
	{							\
		DestroyWindow(hWnd);	\
	}
#endif

///关闭一个Handle
//lint -emacro(774, CLOSEHANDLE)
#ifndef CLOSEHANDLE
#define CLOSEHANDLE(handle)		\
	if(NULL != (handle))		\
	{							\
		::CloseHandle (handle);	\
		(handle) = NULL;		\
	}
#endif

///使用FreeLibrary卸载一个库的宏定义
#ifndef FREELIBRARY
#define FREELIBRARY(hModule)	\
	if(NULL != hModule)			\
	{							\
		FreeLibrary(hModule) ;	\
		hModule = NULL;			\
	}
#endif

///使用AfxFreeLibrary卸载一个库的宏定义
#ifndef AFXFREELIBRARY
#define AFXFREELIBRARY(hModule)	\
	if(NULL != hModule)			\
	{							\
		AfxFreeLibrary(hModule);\
		hModule = NULL;			\
	}
#endif

///删除一个指针的宏定义
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

/** 定义的根据输入类型来删除不同类型的指针的宏定义
*/
#ifndef DELETE_TYPE_P
#define DELETE_TYPE_P(Type, ptrEvent)			\
	{											\
		Type *ptrEventLocal = (Type *)ptrEvent; \
		DELETEP(ptrEventLocal);					\
		ptrEvent = NULL;						\
	}
#endif

/** 定义的根据输入类型来删除不同类型的指针的宏定义
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
若condition条件不成立则执行statement语句，然后以return_value值return
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
若condition条件不成立则执行statement语句，然后return
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
若condition条件不成立则执行statement语句，然后以return_value值return
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
若condition条件不成立则执行statement语句，然后return
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
若指针ptr为NULL则执行statement语句，然后以return_value值return
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
若指针ptr为NULL则执行statement语句，然后return
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
若指针ptr为NULL则执行statement语句，然后以return_value值return
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
若指针ptr为NULL则执行statement语句，然后return
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
若指针ptr为NULL则执行continue语句
*/
#define PAssertNotNull_Continue(ptr) \
	{ \
		if( (ptr) == NULL) \
		{ \
			continue ; \
		} \
	}

/** This macro is used to assert that a pointer must be non-null.
若指针ptr为NULL则执行statement,然后执行continue语句
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
若指针ptr为NULL则执行break语句
*/
#define PAssertNotNull_Break(ptr) \
	{ \
		if( (ptr) == NULL) \
		{ \
			break ; \
		} \
	}

/** This macro is used to assert that a pointer must be non-null.
若指针ptr为NULL则执行statement,然后执行break语句
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
执行一个语句statement，然后return return_value
*/
#ifndef PStatement_Return
#define PStatement_Return(statement) \
{ \
	statement; \
	return ; \
}
#endif

/** This macro is used to do something and return 
执行一个语句statement，然后return return_value
*/
#ifndef PStatement_ReturnValue
#define PStatement_ReturnValue(statement, return_value) \
{ \
	statement; \
	return return_value; \
}
#endif

/** This macro is used to assert that a condition must be TRUE.
若condition条件不成立则执行break语句
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
执行一个语句statement，然后break
*/
#ifndef PStatement_Break
#define PStatement_Break(statement) \
{ \
	statement; \
	break; \
}
#endif

/** This macro is used to assert that a condition must be TRUE.
若condition条件不成立则执行statement语句，然后执行break语句
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
若condition条件不成立则执行continue语句
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
执行一个语句statement，然后continue
*/
#ifndef PStatement_Continue
#define PStatement_Continue(statement) \
{ \
	statement; \
	continue; \
}
#endif

/** This macro is used to assert that a condition must be TRUE.
若condition条件不成立则执行statement语句，然后执行continue语句
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

/** 空操作
*/
#ifndef NULL_OPERATION
	#define NULL_OPERATION
#endif

///memset缺省构造函数
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
按照特定数据类型删除该数据类型的数组指针
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
按照特定数据类型删除该数据类型的指针
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

///左移宏定义
#ifndef LEFT_SHIFT

#define LEFT_SHIFT(uiData) \
	( (uiData) * 2)
#endif

//////////////////////////////////////////////////////////////////////////
///NEW系列宏定义
/** @macro MACRO_NEW_RETURNVALUE
@brief new CONSTRUCTOR对象给相应指针POINTER，失败则return RET_VAL
@details 参照ACE 中ACE_NEW_RETURN宏定义
	1.POINTER指针必须在本宏定义调用时先定义好。
	2.根据构造函数CONSTRUCTOR new一个对象赋给POINTER。
	3.失败return RET_VAL.
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
@brief 保证代码只运行一次
@details 保证嵌在CHECK_RUN_ONCE_BEGIN和CHECK_RUN_ONCE_END之间的代码只运行一次
@example
	CHECK_RUN_ONCE_BEING();
	{
		///下面添加只执行一次的代码
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
@brief CHECK_RUN_COUNT_BEGIN()和CHECK_RUN_COUNT_END之间代码保证执行次数至多为max_count次
@details 
	1.每次运行到CHECK_RUN_COUNT_BEGIN和CHECK_RUN_COUNT_END之间代码时，若执行次数没达到max_count次则执行一次。
	2.保证CHECK_RUN_COUNT_BEGIN和CHECK_RUN_COUNT_END之间代码运行次数不超过max_count次。
@param max_count 执行的最大次数
@example 
	CHECK_RUN_COUNT_BEGIN(max_count);
	{
		///下面的代码将至多执行max_count次
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
@brief 带条件执行保证满足条件时,嵌在CHECK_CONDITION_RUN_ONCE_BEGIN和CHECK_CONDITION_RUN_ONCE_END之间的代码只运行一次
@param condition 满足的条件表达式
@example
	CHECK_CONDITION_RUN_ONCE_BEGIN(8>7);
	{
		///必须上面的表达式(8>7)为true才会执行本段代码
		///下面添加只执行一次的代码
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
@brief 带条件执行保证满足条件时,嵌在CHECK_CONDITION_RUN_COUNT_BEGIN和CHECK_CONDITION_RUN_COUNT_END之间的代码只运行一次
@param condition 满足的条件表达式
@example
	CHECK_CONDITION_RUN_COUNT_BEGIN(8>7, 5);
	{
		///必须上面的表达式(8>7)为true才会执行本段代码
		///下面添加只执行5次的代码
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
@brief DEBUG_ENABLE_ONLY_BEGIN()和DEBUG_ENABLE_ONLY_END()之间代码只在DEBUG下才有效
@details 
	1.通过debug下if(1){...}来包含所处理代码.其实可以考虑#if 1
	2.通过release下if(0){...}来包含所处理代码.其实可以考虑#if 0
	3.具体的代码优化就看编译器的处理了。
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
@brief 每隔millionsecondsInterval毫秒时间间隔,嵌在TIMER_TRIGGER_BEGIN和TIMER_TRIGGER_END之间的代码运行一次
@details 
	1.首先TIMER_TRIGGER_BEGIN和TIMER_TRIGGER_END代码所在函数要能不断被调用到。
	2.调用到后，每隔millionsecondsInterval毫秒才会进入执行TIMER_TRIGGER_BEGIN和TIMER_TRIGGER_END之间代码。
@param millionsecondsInterval 毫秒数
@example
	TIMER_TRIGGER_BEGIN(2000);
	{
		///下面添加每隔2000毫秒执行一次的代码
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
@brief 只在DEBUG版本起作用的OutputDebugString输出宏定义
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
