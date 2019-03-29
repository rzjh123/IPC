/**********************************************************
@copyright	(C)2012, huaao.cn
@file		StringHelper.h
@brief		�ַ�����������������ͷ�ļ�
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
	* �ӿ��ַ���תΪansi�ַ���
	* @param [in] in_str Ϊ�����Դansi�ַ�
	* @return ����ֵΪ���ַ���
	*/
	/*/*UGCUTILITY_API*/ std::string UnicodeToAscii(const std::wstring& in_str);

	/*
	* ��ansi�ַ���תΪ���ַ���
	* @param [in]  in_str Ϊ�����Դansi�ַ�
	* @return ����ֵΪansi�ַ���
	*/
	/*UGCUTILITY_API*/ std::wstring AsciiToUnicode(const std::string& in_str);

	/*
	* ��utf8�ַ���תΪ���ַ���
	* @param [in] in_utf8Str ����UTF8�ַ���
	* @return ����ֵΪUNICODE�ַ��������ת��ʧ�ܣ�����NULL
	*/
	/*UGCUTILITY_API*/ std::wstring UTF8ToUnicode(const std::string& in_utf8Str);

	/*
	* �ӿ��ַ���תΪutf8�ַ���
	* @param [in] in_wStr ������ַ���
	* @return ����ֵΪUTF8�ַ��������ת��ʧ�ܣ�����NULL
	*/
	/*UGCUTILITY_API*/ std::string UnicodeToUTF8(const std::wstring& in_wStr);

	/*
	* ��ascii�ַ���תΪutf8�ַ���
	* @param [in] in_asciiStr ����ascii�ַ���
	* @return ����ֵΪUTF8�ַ��������ת��ʧ�ܣ�����NULL
	*/
	/*UGCUTILITY_API*/ std::string AsciiToUTF8(const std::string &in_asciiStr);

	/*
	* ��utf8�ַ���תΪascii�ַ���
	* @param [in] in_utf8Str ����utf8�ַ���
	* @return ����ֵΪascii�ַ��������ת��ʧ�ܣ�����NULL
	*/
	/*UGCUTILITY_API*/ std::string UTF8ToAscii(const std::string &in_utf8Str);

	/** @fn StringFormat
	@brief ��ʽ��Ϊstd::string�ַ���
	@return std::string
	@ref ���ճ���:http://fool.is-programmer.com/2011/3/18/use-printf-in-std-string.25407.html
	*/
	/*UGCUTILITY_API*/ std::string StringFormat(const char *fmt, ...);

	/** @fn StringFormat
	@brief ��ʽ��Ϊstd::wstring�ַ���
	@return std::wstring
	@ref ���ճ���:http://fool.is-programmer.com/2011/3/18/use-printf-in-std-string.25407.html
	*/
	/*UGCUTILITY_API*/ std::wstring StringFormat(const WCHAR *fmt, ...);

	/** @fn operator <<
	@brief ��ʽ�����std::wstring
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
	@brief ��stl�е��ַ���������к��Դ�Сд�ıȽϲ���
	@param [in] const std::string& strLeft �Ƚ�ʱ���ַ���
	@param [in] const std::string& strRight �Ƚ�ʱ���ַ���
	@return int �Ƚ�ֵ
	@retval ��stricmp��������ֵ����
	*/
	/*UGCUTILITY_API*/ int StringICompare(const std::string& strLeft, const std::string& strRight);
	/*UGCUTILITY_API*/ int StringICompare(const std::wstring& strLeft, const std::wstring& strRight);

	/** @fn StringIEqual
	@brief ��stl�е��ַ���������к��Դ�Сд�ıȽϲ���,�ж��Ƿ����
	@param [in] const std::string& strLeft �Ƚ�ʱ���ַ���
	@param [in] const std::string& strRight �Ƚ�ʱ���ַ���
	@return bool.
	@retval true ���
	@retval false �����
	*/
	/*UGCUTILITY_API*/ bool StringIEqual(const std::string &strLeft, const std::string &strRight);
	/*UGCUTILITY_API*/ bool StringIEqual(const std::wstring &strLeft, const std::wstring &strRight);

	/** ��std::wstring����Replace����
	* @param [in][out] std::wstring &str,���滻���ַ���
	* @param [in] const std::wstring &strSrc,Ҫ���滻��Դ�ַ��Ӵ�
	* @param [in] const std::wstring &strDst,Ҫ���滻��Ŀ���ַ��Ӵ�
	* @return void.
	*/
	/*UGCUTILITY_API*/ void Replace(
		std::wstring &str,
		const std::wstring &strSrc,
		const std::wstring &strDst
		);

	/** ��std::wstring����Replace����
	* @param [in][out] std::string &str,���滻���ַ���
	* @param [in] const std::string &strSrc,Ҫ���滻��Դ�ַ��Ӵ�
	* @param [in] const std::string &strDst,Ҫ���滻��Ŀ���ַ��Ӵ�
	* @return void.
	*/
	/*UGCUTILITY_API*/ void Replace(
		std::string &str,
		const std::string &strSrc,
		const std::string &strDst
		);

	/** @fn IsNumeric
	@brief �ж�str�е��ַ��Ƿ�Ϊ�����ַ���'.'
	@return bool.
	@retval true �����֡�
	@retval false �������֡�
	*/
	/*UGCUTILITY_API*/ bool IsNumeric(const std::wstring &str);

	/** ��std::wstring����ltrim����
	@return void.
	*/
	/*UGCUTILITY_API*/ void TrimLeft(std::wstring& str);
	/*UGCUTILITY_API*/ void TrimLeft(std::string& str);

	/** ��std::wstring����rtrim����
	@return void.
	*/
	/*UGCUTILITY_API*/ void TrimRight(std::wstring& str);
	/*UGCUTILITY_API*/ void TrimRight(std::string& str);

	/** @fn Trim
	@brief ��std::wstring����trim����
	@return void.
	*/
	template<class StringType>
	void Trim(StringType& str)
	{
		TrimLeft(str);
		TrimRight(str);
	}

	/** @fn Trim
	@brief ����һ��Trim������std::wstring
	@details ���޸�str����
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

	/** ��std::wstring����trim����,ɾ������ߵ�wChar�ַ�
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

	/** ��std::wstring����trim����,ɾ�����ұߵ�wChar�ַ�
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

	/** ��std::wstring����trim����,ɾ���������ߵ�wChar�ַ�
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
	@brief ����һ��Trim������std::wstring
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
	* ���ַ����и��ݽض��ַ����нضϣ�ע�⣺ɾ������β�Ŀհ��ַ���
	* @param [in] in_str �����ַ���
	* @param [in] cSplit ����Ľض��ַ�
	* @return ����ֵ�ضϵĸ����ִ�������ַ�����û�нض��ַ��Ļ���vector��СΪ0
	*/
	/*UGCUTILITY_API*/ std::vector<std::string> Split_String_by_DelimiterA(const std::string& in_str, char cSplit);

	/*
	* �ӿ��ַ����и��ݽض��ַ����нضϣ�ע�⣺ɾ������β�Ŀհ��ַ���
	* @param [in] in_wStr ������ַ���
	* @param [in] cSplit ����ĽضϿ��ַ�
	* @return ����ֵ�ضϵĸ����ӿ��ַ���������ַ�����û�нض��ַ��Ļ���vector��СΪ0
	*/
	/*UGCUTILITY_API*/ std::vector<std::wstring> Split_String_by_Delimiter(const std::wstring& in_wStr, wchar_t cSplit);

	//////////////////////////////////////////////////////////////////////////
	///����ΪһЩͨ�õ�ģ�庯��

	/** @fn StringToType
	@brief ģ�庯��������Ӧ�ַ�������ֵת��ΪT����Ԫ�ط���(����)
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
	@brief ģ�庯��������Ӧ����ֵת��ΪT����Ԫ�ط���(����)
	@return string
	����:�»��� ����:2008.07.26
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
	@brief ģ�庯��������Ӧ����ֵת��ΪT����Ԫ�ط���(����)
	@return int
	����:�»��� ����:2009-9-11
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
	@brief ģ�庯��������Ӧ����ֵת��Ϊ�ַ���
	@return string
	����:�»��� ����:2008.07.26
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
	@brief ģ�庯��������Ӧ����ֵת��Ϊ�ַ���
	@return wstring
	����:�»��� ����:2009-9-5
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
	@brief ģ�庯�����ж��Ƿ���Ӣ����ĸ
	@return bool
	*/
	template<typename T>
	static bool HasAlpha(T const & src)
	{
		return (std::find_if(src.begin(), src.end(), &isalpha) == src.end()) ? false : true;
	}

	/** @fn ToNumber64Bit
	@brief ģ�庯��������Ӧ����ֵת��ΪT����Ԫ�ط���(����)
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
	@brief ģ�庯��������Ӧ����ֵת��ΪT����Ԫ�ط���(����)
	@return string
	����:�»��� ����:2009-5-22
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
	@brief ģ�庯������ʮ�������ַ���ת��ΪT����Ԫ�ط���(����)
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
	@brief ģ�庯������ʮ�������ַ���ת��ΪT����Ԫ�ط���(����)
	@return string
	����:�»��� ����:2011-7-13
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
	@brief ����СΪiSize�Ļ����������ݰ��ֽ���16�����ַ�����ʽ����std::string����
	@param [in] const byte *ptrBuffer
	@parma [in] const int &iSize
	@return std::string.
	*/
	/*UGCUTILITY_API*/ std::string FormatHexDataA(const byte *ptrBuffer, const int &iSize);

	/** @fn FormatHexDataA
	@brief ����СΪiSize�Ļ����������ݰ��ֽ���16�����ַ�����ʽ����std::string����
	@param [in] const ByteBuf &byteBuf
	@return std::string.
	*/
	/*UGCUTILITY_API*/ std::string FormatHexDataA(const ByteBuf &byteBuf);

	/** @fn FormatHexDataW
	@brief ����СΪiSize�Ļ����������ݰ��ֽ���16�����ַ�����ʽ����std::wstring����
	@param [in] const byte *ptrBuffer
	@parma [in] const int &iSize
	@return std::wstring.
	*/
	/*UGCUTILITY_API*/ std::wstring FormatHexDataW(const byte *ptrBuffer, const int &iSize);

	/** @fn FormatHexDataW
	@brief ����СΪiSize�Ļ����������ݰ��ֽ���16�����ַ�����ʽ����std::wstring����
	@param [in] const ByteBuf &byteBuf
	@return std::wstring.
	*/
	/*UGCUTILITY_API*/ std::wstring FormatHexDataW(const ByteBuf &byteBuf);

	/** @fn ToLower
	@brief ���ַ���str���Сд
	@tparam CStringType �ַ������ͣ�֧��std::string��std::wstring
	@param [in][out] CStringType &str
	@return void.
	*/
	template <class CStringType>
	void ToLower(CStringType &str)
	{
		std::transform(str.begin(), str.end(), str.begin(), tolower);
	}

	/** @fn ToLowerCopy
	@brief ���������ַ���str��Сд���������ı�str������
	@tparam CStringType �ַ������ͣ�֧��std::string��std::wstring
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
	@brief ���ַ���str��ɴ�д
	@tparam CStringType �ַ������ͣ�֧��std::string��std::wstring
	@param [in][out] CStringType &str
	@return void.
	*/
	template <class CStringType>
	void ToUpper(CStringType &str)
	{
		std::transform(str.begin(), str.end(), str.begin(), toupper);
	}

	/** @fn ToUpperCopy
	@brief ���������ַ���str�Ĵ�д���������ı�str������
	@tparam CStringType �ַ������ͣ�֧��std::string��std::wstring
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

	// Ϊxml�滻/�ָ��ַ����е������ַ���&,<,>,",'��
	/*UGCUTILITY_API*/ std::wstring FormatStringForXml(const std::wstring& str);
	/*UGCUTILITY_API*/ std::wstring UnformatStringForXml(const std::wstring& str);

	// Ϊhtml�滻/�ָ��ַ����е������ַ���&,<,>,",'��
	/*UGCUTILITY_API*/ std::wstring FormatStringForHtml(const std::wstring& str);
	/*UGCUTILITY_API*/ std::wstring UnformatStringForHtml(const std::wstring& str);

	// �������Ƹ�ʽת����std::string
	/*UGCUTILITY_API*/ std::string Binary2String(const CHAR* szBuf, UINT uBufLen);
	// ��std::stringת���ɶ����Ƹ�ʽ
	/*UGCUTILITY_API*/ BOOL String2Binary(const std::string& str, UINT uBufLen, CHAR* szBuf, UINT& uRealLen);


	/*UGCUTILITY_API*/ std::string UrlEncode(const std::string& str);
	/*UGCUTILITY_API*/ std::string UrlDecode(const std::string& str);
};

///��ȫ����ʹ��ģ�庯��template <class CDataType> std::wstring &operator (std::wstring &str, ...
using NS_StringHelper::operator <<;


#pragma pack(pop)