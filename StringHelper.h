/**********************************************************
@copyright	(C)2012, huaao.cn
@file		StringHelper.h
@brief		字符串帮助函数的声明头文件
@details
@version
@author		
@date		2014-10-08
@changelog1:
@date
@version
@author
@brief
**********************************************************/
#pragma once

#include <string>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <sstream>
#include "GlobalMacro.h"

#pragma pack(push, _CRT_PACKING)

namespace NS_StringHelper
{
	/*
	* 从宽字符串转为ansi字符串
	* @param [in] in_str 为输入的源ansi字符
	* @return 返回值为宽字符串
	*/
	/*/*UGCUTILITY_API*/ std::string UnicodeToAscii(const std::wstring& in_str);

	/*
	* 从ansi字符串转为宽字符串
	* @param [in]  in_str 为输入的源ansi字符
	* @return 返回值为ansi字符串
	*/
	/*UGCUTILITY_API*/ std::wstring AsciiToUnicode(const std::string& in_str);

	/*
	* 从utf8字符串转为宽字符串
	* @param [in] in_utf8Str 输入UTF8字符串
	* @return 返回值为UNICODE字符串，如果转换失败，返回NULL
	*/
	/*UGCUTILITY_API*/ std::wstring UTF8ToUnicode(const std::string& in_utf8Str);

	/*
	* 从宽字符串转为utf8字符串
	* @param [in] in_wStr 输入宽字符串
	* @return 返回值为UTF8字符串，如果转换失败，返回NULL
	*/
	/*UGCUTILITY_API*/ std::string UnicodeToUTF8(const std::wstring& in_wStr);

	/*
	* 从ascii字符串转为utf8字符串
	* @param [in] in_asciiStr 输入ascii字符串
	* @return 返回值为UTF8字符串，如果转换失败，返回NULL
	*/
	/*UGCUTILITY_API*/ std::string AsciiToUTF8(const std::string &in_asciiStr);

	/*
	* 从utf8字符串转为ascii字符串
	* @param [in] in_utf8Str 输入utf8字符串
	* @return 返回值为ascii字符串，如果转换失败，返回NULL
	*/
	/*UGCUTILITY_API*/ std::string UTF8ToAscii(const std::string &in_utf8Str);

	/** @fn StringFormat
	@brief 格式化为std::string字符串
	@return std::string
	@ref 参照出处:http://fool.is-programmer.com/2011/3/18/use-printf-in-std-string.25407.html
	*/
	/*UGCUTILITY_API*/ std::string StringFormat(const char *fmt, ...);

	/** @fn StringFormat
	@brief 格式化为std::wstring字符串
	@return std::wstring
	@ref 参照出处:http://fool.is-programmer.com/2011/3/18/use-printf-in-std-string.25407.html
	*/
	/*UGCUTILITY_API*/ std::wstring StringFormat(const WCHAR *fmt, ...);

	/** @fn operator <<
	@brief 流式输出到std::wstring
	@param [in] std::wstring &strStream
	@param [in] const CDataType &data
	@return std::wstring.
	@example
	std::wstring str;
	str << L"My age is " << 8 << "\n";

	OutputDebugString(
	(
	std::wstring()
	<< L"My age is "
	<< 8
	<< "\n";
	).c_str()
	);
	*/
	template <class CDataType> inline
		std::wstring & operator << (std::wstring &strStream, const CDataType &data)
	{
		std::wstringstream ss;
		ss << data;

		strStream += ss.str();

		return strStream;
	}

	template <> inline
		std::wstring & operator << (std::wstring &strStream, const std::string &strWideData)
	{
		std::wstringstream ss;
		ss << NS_StringHelper::AsciiToUnicode(strWideData);

		strStream += ss.str();

		return strStream;
	}

	template <class CDataType> inline
		std::string & operator << (std::string &strStream, const CDataType &data)
	{
		std::stringstream ss;
		ss << data;

		strStream += ss.str();

		return strStream;
	}

	template <> inline
		std::string & operator << (std::string &strStream, const std::wstring &strWideData)
	{
		std::stringstream ss;
		ss << NS_StringHelper::UnicodeToAscii(strWideData);

		strStream += ss.str();

		return strStream;
	}

	/* @fn StringICompare
	@brief 对stl中的字符串对象进行忽略大小写的比较操作
	@param [in] const std::string& strLeft 比较时左字符串
	@param [in] const std::string& strRight 比较时右字符串
	@return int 比较值
	@retval 和stricmp函数返回值类似
	*/
	/*UGCUTILITY_API*/ int StringICompare(const std::string& strLeft, const std::string& strRight);
	/*UGCUTILITY_API*/ int StringICompare(const std::wstring& strLeft, const std::wstring& strRight);

	/** @fn StringIEqual
	@brief 对stl中的字符串对象进行忽略大小写的比较操作,判断是否相等
	@param [in] const std::string& strLeft 比较时左字符串
	@param [in] const std::string& strRight 比较时右字符串
	@return bool.
	@retval true 相等
	@retval false 不相等
	*/
	/*UGCUTILITY_API*/ bool StringIEqual(const std::string &strLeft, const std::string &strRight);
	/*UGCUTILITY_API*/ bool StringIEqual(const std::wstring &strLeft, const std::wstring &strRight);

	/** 对std::wstring进行Replace操作
	* @param [in][out] std::wstring &str,待替换的字符串
	* @param [in] const std::wstring &strSrc,要被替换的源字符子串
	* @param [in] const std::wstring &strDst,要被替换的目的字符子串
	* @return void.
	*/
	/*UGCUTILITY_API*/ void Replace(
		std::wstring &str,
		const std::wstring &strSrc,
		const std::wstring &strDst
		);

	/** 对std::wstring进行Replace操作
	* @param [in][out] std::string &str,待替换的字符串
	* @param [in] const std::string &strSrc,要被替换的源字符子串
	* @param [in] const std::string &strDst,要被替换的目的字符子串
	* @return void.
	*/
	/*UGCUTILITY_API*/ void Replace(
		std::string &str,
		const std::string &strSrc,
		const std::string &strDst
		);

	/** @fn IsNumeric
	@brief 判断str中的字符是否都为数字字符或'.'
	@return bool.
	@retval true 是数字。
	@retval false 不是数字。
	*/
	/*UGCUTILITY_API*/ bool IsNumeric(const std::wstring &str);

	/** 对std::wstring进行ltrim操作
	@return void.
	*/
	/*UGCUTILITY_API*/ void TrimLeft(std::wstring& str);
	/*UGCUTILITY_API*/ void TrimLeft(std::string& str);

	/** 对std::wstring进行rtrim操作
	@return void.
	*/
	/*UGCUTILITY_API*/ void TrimRight(std::wstring& str);
	/*UGCUTILITY_API*/ void TrimRight(std::string& str);

	/** @fn Trim
	@brief 对std::wstring进行trim操作
	@return void.
	*/
	template<class StringType>
	void Trim(StringType& str)
	{
		TrimLeft(str);
		TrimRight(str);
	}

	/** @fn Trim
	@brief 返回一个Trim处理后的std::wstring
	@details 不修改str参数
	@parma [in] const std::wstring &str
	@return std::wstring.
	*/
	template<class StringType>
	StringType TrimCopy(const StringType &str)
	{
		StringType strTrim = str;
		Trim(strTrim);

		return strTrim;
	}

	/** 对std::wstring进行trim操作,删除最左边的wChar字符
	@return void.
	*/
	///UTILITY_API void TrimLeft(std::wstring& str, const WCHAR &wChar);
	///UTILITY_API void TrimLeft(std::string& str, const CHAR &wChar);
	template <class StringType, class CharType>
	void TrimLeft(StringType& str, const CharType &charToBeTrimed)
	{
		StringType::size_type iPos = 0;
		while (iPos < str.size() && charToBeTrimed == str[iPos])
		{
			iPos++;
		}

		if (iPos < str.size())
		{
			str.erase(0, iPos);
		}
		else
		{
			str.erase(str.begin(), str.end());
		}
	}

	/** 对std::wstring进行trim操作,删除最右边的wChar字符
	@return void.
	*/
	///UTILITY_API void TrimRight(std::wstring& str, const WCHAR &wChar);
	///UTILITY_API void TrimRight(std::string& str, const CHAR &wChar);
	template <class StringType, class CharType>
	void TrimRight(StringType & str, const CharType &charToBeTrimed)
	{
		///PAssert_Return(str.size() > 0);
		if (str.empty())
		{
			return;
		}

		int iPos = str.size() - 1;
		while (iPos >= 0 && charToBeTrimed == str[iPos])
		{
			iPos--;
		}

		if (iPos >= 0)
		{
			str.erase(iPos + 1, str.size() - iPos - 1);
		}
		else
		{
			str.erase(str.begin(), str.end());
		}
	}

	/** 对std::wstring进行trim操作,删除左右两边的wChar字符
	@return void.
	*/
	///UTILITY_API void Trim(std::wstring& str, const WCHAR &wChar);
	template <class StringType, class CharType>
	void Trim(StringType &str, const CharType &charToBeTrimed)
	{
		TrimLeft(str, charToBeTrimed);
		TrimRight(str, charToBeTrimed);
	}

	/** @fn Trim
	@brief 返回一个Trim处理后的std::wstring
	@parma [in] const std::wstring &str
	@param [in] const WCHAR &wChar
	@return std::wstring.
	*/
	///UTILITY_API std::wstring TrimCopy(const std::wstring &str, const WCHAR &wChar);
	template <class StringType, class CharType>
	StringType TrimCopy(const StringType & str, const CharType &charToBeTrimed)
	{
		StringType strTrim = str;
		Trim(strTrim, charToBeTrimed);

		return strTrim;
	}

	/*
	* 从字符串中根据截断字符进行截断（注意：删除了首尾的空白字符）
	* @param [in] in_str 输入字符串
	* @param [in] cSplit 输入的截断字符
	* @return 返回值截断的各个字串，如果字符串中没有截断字符的话，vector大小为0
	*/
	/*UGCUTILITY_API*/ std::vector<std::string> Split_String_by_DelimiterA(const std::string& in_str, char cSplit);

	/*
	* 从宽字符串中根据截断字符进行截断（注意：删除了首尾的空白字符）
	* @param [in] in_wStr 输入宽字符串
	* @param [in] cSplit 输入的截断宽字符
	* @return 返回值截断的各个子宽字符串，如果字符串中没有截断字符的话，vector大小为0
	*/
	/*UGCUTILITY_API*/ std::vector<std::wstring> Split_String_by_Delimiter(const std::wstring& in_wStr, wchar_t cSplit);

	//////////////////////////////////////////////////////////////////////////
	///下面为一些通用的模板函数

	/** @fn StringToType
	@brief 模板函数，将相应字符串类型值转换为T类型元素返回(数字)
	@return T
	*/
	template <class T>
	void StringToType(const std::string &s, T &value)
	{
		std::stringstream ss(s);
		ss >> value;
	}

	template <class T>
	void StringToType(const std::wstring &s, T &value)
	{
		std::wstringstream ss(s);
		ss >> value;
	}

	template <class T>
	T StringToType(const std::string &s)
	{
		T value;
		std::stringstream ss(s);
		ss >> value;

		return value;
	}

	template <class T>
	T StringToType(const std::wstring &s)
	{
		T value;
		std::wstringstream ss(s);
		ss >> value;

		return value;
	}

	/** @fn ToNumber
	@brief 模板函数，将相应类型值转换为T类型元素返回(数字)
	@return string
	作者:温辉敏 日期:2008.07.26
	*/
	template<typename T, int iDefaultValue>
	T ToNumber(const std::string  & s)
	{
		try
		{
			T tReturnValue = 0;
			///sscanf(s.c_str(), "%d", &tReturnValue);
			sscanf_s(s.c_str(), "%d", &tReturnValue);

			return tReturnValue;
		}
		catch (...)
		{
			return iDefaultValue;
		}
	}

	template<typename T, int iDefaultValue>
	T ToNumberU(const std::string  & s)
	{
		try
		{
			T tReturnValue = 0;
			///sscanf(s.c_str(), "%d", &tReturnValue);
			sscanf_s(s.c_str(), "%u", &tReturnValue);

			return tReturnValue;
		}
		catch (...)
		{
			return iDefaultValue;
		}
	}

	/** @fn ToNumber
	@brief 模板函数，将相应类型值转换为T类型元素返回(数字)
	@return int
	作者:温辉敏 日期:2009-9-11
	*/
	template<typename T, int iDefaultValue>
	T ToNumber(const std::wstring  & s)
	{
		try
		{
			T tReturnValue = 0;
			///sscanf(s.c_str(), "%d", &tReturnValue);
			swscanf_s(s.c_str(), L"%d", &tReturnValue);

			return tReturnValue;
		}
		catch (...)
		{
			return iDefaultValue;
		}
	}

	template<typename T, int iDefaultValue>
	T ToNumberU(const std::wstring  & s)
	{
		try
		{
			T tReturnValue = 0;
			///sscanf(s.c_str(), "%d", &tReturnValue);
			swscanf_s(s.c_str(), L"%u", &tReturnValue);

			return tReturnValue;
		}
		catch (...)
		{
			return iDefaultValue;
		}
	}

	/** @fn ToString
	@brief 模板函数，将相应类型值转换为字符串
	@return string
	作者:温辉敏 日期:2008.07.26
	*/
	template<typename T>
	std::string ToString(const T & t)
	{
		try
		{
			std::stringstream   ss;
			ss << t;
			return   ss.str();
		}
		catch (...)
		{
			return "";
		}
	}

	/** @fn ToWString
	@brief 模板函数，将相应类型值转换为字符串
	@return wstring
	作者:温辉敏 日期:2009-9-5
	*/
	template<typename T>
	std::wstring ToWString(const T & t)
	{
		try
		{
			std::wstringstream ss;
			ss << t;
			return ss.str();
		}
		catch (...)
		{
			return L"";
		}
	}

	/** @fn HasAlpha
	@brief 模板函数，判断是否含有英文字母
	@return bool
	*/
	template<typename T>
	static bool HasAlpha(T const & src)
	{
		return (std::find_if(src.begin(), src.end(), &isalpha) == src.end()) ? false : true;
	}

	/** @fn ToNumber64Bit
	@brief 模板函数，将相应类型值转换为T类型元素返回(数字)
	@return INT64
	*/
	template<typename T, INT64 iDefaultValue>
	T ToNumber64Bit(const std::wstring  & s)
	{
		try
		{
			T tReturnValue = iDefaultValue;
			///sscanf(s.c_str(), "%d", &tReturnValue);
			swscanf_s(s.c_str(), L"%I64d", &tReturnValue);

			return tReturnValue;
		}
		catch (...)
		{
			return iDefaultValue;
		}
	}

	template<typename T, INT64 iDefaultValue>
	T ToNumber64BitU(const std::wstring  & s)
	{
		try
		{
			T tReturnValue = iDefaultValue;
			///sscanf(s.c_str(), "%d", &tReturnValue);
			swscanf_s(s.c_str(), L"%I64u", &tReturnValue);

			return tReturnValue;
		}
		catch (...)
		{
			return iDefaultValue;
		}
	}

	/** @fn ToNumber64Bit
	@brief 模板函数，将相应类型值转换为T类型元素返回(数字)
	@return string
	作者:温辉敏 日期:2009-5-22
	*/
	template<typename T, INT64 iDefaultValue>
	T ToNumber64Bit(const std::string  & s)
	{
		try
		{
			T tReturnValue = 0;
			///sscanf(s.c_str(), "%I64d", &tReturnValue);
			sscanf_s(s.c_str(), "%I64d", &tReturnValue);

			return tReturnValue;
		}
		catch (...)
		{
			return iDefaultValue;
		}
	}

	template<typename T, INT64 iDefaultValue>
	T ToNumber64BitU(const std::string  & s)
	{
		try
		{
			T tReturnValue = 0;
			///sscanf(s.c_str(), "%I64d", &tReturnValue);
			sscanf_s(s.c_str(), "%I64u", &tReturnValue);

			return tReturnValue;
		}
		catch (...)
		{
			return iDefaultValue;
		}
	}

	/** @fn HexStringToNumber64Bit
	@brief 模板函数，将十六进制字符串转换为T类型元素返回(数字)
	@return INT64
	*/
	template<typename T, INT64 iDefaultValue>
	T HexStringToNumber64Bit(const std::wstring  & s)
	{
		try
		{
			T tReturnValue = iDefaultValue;
			///sscanf(s.c_str(), "%d", &tReturnValue);
			swscanf_s(s.c_str(), L"%I64x", &tReturnValue);

			return tReturnValue;
		}
		catch (...)
		{
			return iDefaultValue;
		}
	}

	/** @fn HexStringToNumber64Bit
	@brief 模板函数，将十六进制字符串转换为T类型元素返回(数字)
	@return string
	作者:温辉敏 日期:2011-7-13
	*/
	template<typename T, INT64 iDefaultValue>
	T HexStringToNumber64Bit(const std::string  & s)
	{
		try
		{
			T tReturnValue = 0;
			///sscanf(s.c_str(), "%I64d", &tReturnValue);
			sscanf_s(s.c_str(), "%I64x", &tReturnValue);

			return tReturnValue;
		}
		catch (...)
		{
			return iDefaultValue;
		}
	}

	typedef unsigned char byte;
	typedef std::pair<std::size_t, byte*> ByteBuf;
	/** @fn FormatHexDataA
	@brief 将大小为iSize的缓冲区中内容按字节以16进制字符串格式化成std::string返回
	@param [in] const byte *ptrBuffer
	@parma [in] const int &iSize
	@return std::string.
	*/
	/*UGCUTILITY_API*/ std::string FormatHexDataA(const byte *ptrBuffer, const int &iSize);

	/** @fn FormatHexDataA
	@brief 将大小为iSize的缓冲区中内容按字节以16进制字符串格式化成std::string返回
	@param [in] const ByteBuf &byteBuf
	@return std::string.
	*/
	/*UGCUTILITY_API*/ std::string FormatHexDataA(const ByteBuf &byteBuf);

	/** @fn FormatHexDataW
	@brief 将大小为iSize的缓冲区中内容按字节以16进制字符串格式化成std::wstring返回
	@param [in] const byte *ptrBuffer
	@parma [in] const int &iSize
	@return std::wstring.
	*/
	/*UGCUTILITY_API*/ std::wstring FormatHexDataW(const byte *ptrBuffer, const int &iSize);

	/** @fn FormatHexDataW
	@brief 将大小为iSize的缓冲区中内容按字节以16进制字符串格式化成std::wstring返回
	@param [in] const ByteBuf &byteBuf
	@return std::wstring.
	*/
	/*UGCUTILITY_API*/ std::wstring FormatHexDataW(const ByteBuf &byteBuf);

	/** @fn ToLower
	@brief 将字符串str变成小写
	@tparam CStringType 字符串类型，支持std::string和std::wstring
	@param [in][out] CStringType &str
	@return void.
	*/
	template <class CStringType>
	void ToLower(CStringType &str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
	}

	/** @fn ToLowerCopy
	@brief 返回输入字符串str的小写拷贝，不改变str中内容
	@tparam CStringType 字符串类型，支持std::string和std::wstring
	@param [in] const CStringType &str
	@return CStringType.
	*/
	template <class CStringType>
	CStringType ToLowerCopy(const CStringType &str)
	{
		CStringType strLocal = str;
		std::transform(strLocal.begin(), strLocal.end(), strLocal.begin(), tolower);
		return strLocal;
	}

	/** @fn ToUpper
	@brief 将字符串str变成大写
	@tparam CStringType 字符串类型，支持std::string和std::wstring
	@param [in][out] CStringType &str
	@return void.
	*/
	template <class CStringType>
	void ToUpper(CStringType &str)
	{
		std::transform(str.begin(), str.end(), str.begin(), toupper);
	}

	/** @fn ToUpperCopy
	@brief 返回输入字符串str的大写拷贝，不改变str中内容
	@tparam CStringType 字符串类型，支持std::string和std::wstring
	@param [in] const CStringType &str
	@return CStringType.
	*/
	template <class CStringType>
	CStringType ToUpperCopy(const CStringType &str)
	{
		CStringType strLocal = str;
		std::transform(strLocal.begin(), strLocal.end(), strLocal.begin(), toupper);
		return strLocal;
	}

	// 为xml替换/恢复字符串中的特殊字符：&,<,>,",'等
	/*UGCUTILITY_API*/ std::wstring FormatStringForXml(const std::wstring& str);
	/*UGCUTILITY_API*/ std::wstring UnformatStringForXml(const std::wstring& str);

	// 为html替换/恢复字符串中的特殊字符：&,<,>,",'等
	/*UGCUTILITY_API*/ std::wstring FormatStringForHtml(const std::wstring& str);
	/*UGCUTILITY_API*/ std::wstring UnformatStringForHtml(const std::wstring& str);

	// 将二进制格式转换成std::string
	/*UGCUTILITY_API*/ std::string Binary2String(const CHAR* szBuf, UINT uBufLen);
	// 将std::string转换成二进制格式
	/*UGCUTILITY_API*/ BOOL String2Binary(const std::string& str, UINT uBufLen, CHAR* szBuf, UINT& uRealLen);


	/*UGCUTILITY_API*/ std::string UrlEncode(const std::string& str);
	/*UGCUTILITY_API*/ std::string UrlDecode(const std::string& str);
};

///让全局能使用模板函数template <class CDataType> std::wstring &operator (std::wstring &str, ...
using NS_StringHelper::operator <<;


#pragma pack(pop)