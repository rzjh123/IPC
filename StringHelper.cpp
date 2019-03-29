#include "stdafx.h"
#include "StringHelper.h"
#include <strstream>

namespace NS_StringHelper
{
	std::string StringFormat(const char *fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		const size_t SIZE = 4096;
		char buffer[SIZE] = { 0 };
		///vsnprintf(buffer, SIZE, fmt, ap);
		///int nSize = vsnprintf_s( buffer, sizeof(buffer), _TRUNCATE, fmt, ap);
		vsnprintf_s(buffer, SIZE, _TRUNCATE, fmt, ap);
		va_end(ap);

		return std::string(buffer);
	}

	std::wstring StringFormat(const WCHAR *fmt, ...)
	{
		va_list ap;
		va_start(ap, fmt);
		const size_t SIZE = 4096;
		WCHAR buffer[SIZE] = { 0 };
		///_vsnwprintf(buffer, SIZE, fmt, ap);
		_vsnwprintf_s(buffer, SIZE, _TRUNCATE, fmt, ap);
		va_end(ap);

		return std::wstring(buffer);
	}

	int StringICompare(const std::string& strLeft, const std::string& strRight)
	{
		int iResult = _stricmp(strLeft.c_str(), strRight.c_str());
		return iResult;
	}

	int StringICompare(const std::wstring& strLeft, const std::wstring& strRight)
	{
		int iResult = _wcsicmp(strLeft.c_str(), strRight.c_str());
		return iResult;
	}

	bool StringIEqual(const std::string &strLeft, const std::string &strRight)
	{
		bool bResult = (0 == StringICompare(strLeft, strRight));
		return bResult;
	}

	bool StringIEqual(const std::wstring &strLeft, const std::wstring &strRight)
	{
		bool bResult = (0 == StringICompare(strLeft, strRight));
		return bResult;
	}

	std::string UnicodeToAscii(const std::wstring& in_str)
	{
		int nNeedChars = WideCharToMultiByte(CP_ACP, 0, in_str.c_str(), -1, 0, 0, 0, 0);
		if (nNeedChars > 0)//再次判断一下
		{
			std::vector<char> temp(nNeedChars);
			::WideCharToMultiByte(CP_ACP, 0, in_str.c_str(), -1, &temp[0], nNeedChars, 0, 0);
			return std::string(&temp[0]);
		}

		return std::string();
	}

	std::wstring AsciiToUnicode(const std::string& in_str)
	{
		int nNeedWchars = MultiByteToWideChar(CP_ACP, 0, in_str.c_str(), -1, NULL, 0);
		if (nNeedWchars > 0)
		{
			std::vector<wchar_t> temp(nNeedWchars);
			::MultiByteToWideChar(CP_ACP, 0, in_str.c_str(), -1, &temp[0], nNeedWchars);
			return std::wstring(&temp[0]);
		}

		return std::wstring();
	}

	std::wstring UTF8ToUnicode(const std::string& in_utf8Str)
	{
		int nNeedWchars = MultiByteToWideChar(CP_UTF8, 0, in_utf8Str.c_str(), -1, NULL, 0);
		if (nNeedWchars > 0)
		{
			std::vector<wchar_t> temp(nNeedWchars);
			::MultiByteToWideChar(CP_UTF8, 0, in_utf8Str.c_str(), -1, &temp[0], nNeedWchars);
			return std::wstring(&temp[0]);
		}

		return std::wstring();
	}

	std::string UnicodeToUTF8(const std::wstring& in_wStr) 
	{ 
		int nNeedChars = WideCharToMultiByte(CP_UTF8, 0, in_wStr.c_str(), -1, 0, 0, 0, 0);
		if (nNeedChars > 0)//再次判断一下
		{
			std::vector<char> temp(nNeedChars);
			::WideCharToMultiByte(CP_UTF8, 0, in_wStr.c_str(), -1, &temp[0], nNeedChars, 0, 0);
			return std::string(&temp[0]);
		}

		return std::string();
	}

	std::string AsciiToUTF8(const std::string &in_asciiStr)
	{
		return UnicodeToUTF8(AsciiToUnicode(in_asciiStr));
	}

	std::string UTF8ToAscii(const std::string &in_utf8Str)
	{
		return UnicodeToAscii(UTF8ToUnicode(in_utf8Str));
	}

	void Replace(
		std::wstring &str,
		const std::wstring &strSrc,
		const std::wstring &strDst
		)
	{
		std::wstring::size_type iPos = 0;
		while ((iPos = str.find(strSrc, iPos)) != std::wstring::npos)
		{
			str.replace(iPos, strSrc.size(), strDst);
			iPos += strDst.size();
		}
	}

	void Replace(
		std::string &str,
		const std::string &strSrc,
		const std::string &strDst
		)
	{
		std::string::size_type iPos = 0;
		while ((iPos = str.find(strSrc, iPos)) != std::string::npos)
		{
			str.replace(iPos, strSrc.size(), strDst);
			iPos += strDst.size();
		}
	}

	bool IsNumeric(const std::wstring &str)
	{
		PAssert_ReturnValue(!str.empty(), false);

		bool bResult = true;

		for (std::wstring::const_iterator iter = str.begin(); iter != str.end(); iter++)
		{
			const WCHAR & charLocal = *iter;
			if (iswdigit(charLocal) || charLocal == L'.')
			{
				continue;
			}
			else
			{
				bResult = false;
				break;
			}
		}

		return bResult;
	}

	//////////////////////////////////////////////////////////////////////////
	///Trim系列函数	
	void TrimLeft(std::wstring& str)
	{
		PAssert_Return(str.size() > 0);

		std::wstring::size_type iPos = 0;
		while (iPos < str.size() && iswspace(str[iPos]))
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

	void TrimLeft(std::string& str)
	{
		PAssert_Return(str.size() > 0);

		std::string::size_type iPos = 0;
		while (iPos < str.size() && isspace(str[iPos]))
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

	void TrimRight(std::wstring& str)
	{
		PAssert_Return(str.size() > 0);

		int iPos = str.size() - 1;
		while (iPos >= 0 && iswspace(str[iPos]))
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

	void TrimRight(std::string& str)
	{
		PAssert_Return(str.size() > 0);

		int iPos = str.size() - 1;
		while (iPos >= 0 && isspace(str[iPos]))
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

	//////////////////////////////////////////////////////////////////////////
	///SplitString系列函数
	template<typename STR>
	static void SplitStringT(const STR& str, const typename STR::value_type s, bool trim_whitespace, std::vector<STR>* r)
	{
		size_t last = 0;
		size_t i;
		size_t c = str.size();
		for (i = 0; i <= c; ++i)
		{
			if (i == c || str[i] == s)
			{
				size_t len = i - last;
				STR tmp = str.substr(last, len);
				if (trim_whitespace)
				{
					STR t_tmp = TrimCopy(tmp);
					r->push_back(t_tmp);
				}
				else
				{
					r->push_back(tmp);
				}
				last = i + 1;
			}
		}
	}

	//ansi版本
	std::vector<std::string> Split_String_by_DelimiterA(const std::string& in_str, char cSplit)
	{
		std::vector<std::string> vecRet;
		SplitStringT(in_str, cSplit, true, &vecRet);

		return vecRet;
	}

	//unicode版本
	std::vector<std::wstring> Split_String_by_Delimiter(const std::wstring& in_wStr, wchar_t cSplit)
	{
		std::vector<std::wstring> vecRet;
		SplitStringT(in_wStr, cSplit, true, &vecRet);

		return vecRet;
	}

	std::string FormatHexDataA(const ByteBuf &byteBuf)
	{
		return FormatHexDataA(byteBuf.second, byteBuf.first);
	}

	std::string FormatHexDataA(const byte *ptrBuffer, const int &iSize)
	{
		PAssertNotNull_ReturnValue(ptrBuffer, "");
		PAssert_ReturnValue((iSize > 0), "");
		int i = 0;
		int j = 0;
		int c = 0;
		int printnext = 1;
		///由于这里要进行格式输出如"%.4x "等，这里给出10个字符作为格式输出冗余
		char str[10] = { 0 };
		//使用ostrstream的代码，但ostrstream.str()传出去要使用者负责清除ostrstream.str()指向的内存了
		std::ostrstream ostr;
		if (iSize)
		{
			if (iSize % 16)
			{
				c = iSize + (16 - iSize % 16);
			}
			else
			{
				c = iSize;
			}
		}
		else
		{
			c = iSize;
		}

		for (i = 0; i < c; i++)
		{
			if (printnext)
			{
				printnext--;
				sprintf_s(str, sizeof(str), "%.4x ", i & 0xffff);
				ostr << str;
			}

			if (i<iSize)
			{
				sprintf_s(str, sizeof(str), "%3.2x", ptrBuffer[i] & 0xff);
				ostr << str;
			}
			else
			{
				sprintf_s(str, sizeof(str), "   ");
				ostr << str;
			}

			if (!((i + 1) % 8))
			{
				if ((i + 1) % 16)
				{
					sprintf_s(str, sizeof(str), " -");
					ostr << str;
				}
				else
				{
					sprintf_s(str, sizeof(str), "   ");
					ostr << str;
					for (j = i - 15; j <= i; j++)
					{
						if (j<iSize)
						{
							if ((ptrBuffer[j] & 0xff) >= 0x20 &&
								(ptrBuffer[j] & 0xff) <= 0x7e)
							{
								sprintf_s(str, sizeof(str), "%c", ptrBuffer[j] & 0xff);
								ostr << str;
							}
							else
							{
								sprintf_s(str, sizeof(str), ".");

								ostr << str;
							}
						}
						else
						{
							sprintf_s(str, sizeof(str), " ");
							ostr << str;
						}
					}

					sprintf_s(str, sizeof(str), "\n");

					ostr << str;
					printnext = 1;
				}
			}
		}

		/**
		ostrstreams 没有为我们插入一般在字符数组末尾所需要的零终止符，
		当我们准备好零终止符时，用特别操作算子ends。
		*/
		ostr << std::ends;

		std::string strReturn = ostr.str();

		///释放资源
		ostr.rdbuf()->freeze(0);

		return strReturn;
		/*
		strncpy(str, ostr.str(), iSize );
		str[iSize ] = '\0';
		ostr.rdbuf()->freeze(0);
		*/
	}

	std::wstring FormatHexDataW(const ByteBuf &byteBuf)
	{
		return FormatHexDataW(byteBuf.second, byteBuf.first);
	}

	std::wstring FormatHexDataW(const byte *ptrBuffer, const int &iSize)
	{
		return AsciiToUnicode(FormatHexDataA(ptrBuffer, iSize));
	}

	std::wstring FormatStringForXml(const std::wstring& str)
	{
		std::wstring strRslt = str;
		Replace(strRslt, L"&", L"&amp;");
		Replace(strRslt, L"<", L"&lt;");
		Replace(strRslt, L">", L"&gt;");
		Replace(strRslt, L"\"", L"&quot;");
		Replace(strRslt, L"\'", L"&apos;");
		//Replace(strRslt, L" ", L"&#x0020;");

		return strRslt;
	}

	std::wstring UnformatStringForXml(const std::wstring& str)
	{
		std::wstring strRslt = str;
		Replace(strRslt, L"&lt;", L"<");
		Replace(strRslt, L"&gt;", L">");
		Replace(strRslt, L"&quot;", L"\"");
		Replace(strRslt, L"&apos;", L"\'");
		Replace(strRslt, L"&amp;", L"&");
		//Replace(strRslt, L"&#x0020;", L" ");
		return strRslt;
	}

	std::wstring FormatStringForHtml(const std::wstring& str)
	{
		std::wstring strRslt = str;
		Replace(strRslt, L"&", L"&amp;");
		Replace(strRslt, L" ", L"&nbsp;");
		Replace(strRslt, L"<", L"&lt;");
		Replace(strRslt, L">", L"&gt;");
		Replace(strRslt, L"\r", L"<br>");
		Replace(strRslt, L"\"", L"&quot;");
		return strRslt;
	}

	std::wstring UnformatStringForHtml(const std::wstring& str)
	{
		std::wstring strRslt = str;
		Replace(strRslt, L"&quot;", L"\"");
		Replace(strRslt, L"<br>", L"\r\n");
		Replace(strRslt, L"&lt;", L"<");
		Replace(strRslt, L"&gt;", L">");
		Replace(strRslt, L"&nbsp;", L" ");
		Replace(strRslt, L"&amp;", L"&");
		return strRslt;
	}

	std::string Binary2String(const CHAR* szBuf, UINT uBufLen)
	{
		return std::string(szBuf, uBufLen);
	}

	BOOL String2Binary(const std::string& str, UINT uBufLen, CHAR* szBuf, UINT& uRealLen)
	{
		uRealLen = (uBufLen > str.length()) ? str.length() : uBufLen;
		memcpy(szBuf, str.c_str(), uRealLen);

		// str被截断了
		if (uRealLen < str.length())
			return FALSE;
		// 正常
		else
			return TRUE;
	}

	BYTE ToHex(const BYTE &x)
	{
		return x > 9 ? x + 55 : x + 48;
	}

	unsigned char FromHex(unsigned char x)
	{
		unsigned char y;

		if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
		else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
		else if (x >= '0' && x <= '9') y = x - '0';

		return y;
	}

	std::string UrlEncode(const std::string& str)
	{
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++)
		{
			if (isalnum((unsigned char)str[i]) ||
				(str[i] == '-') ||
				(str[i] == '_') ||
				(str[i] == '.') ||
				(str[i] == '~'))
				strTemp += str[i];
			else if (str[i] == ' ')
				strTemp += "+";
			else
			{
				strTemp += '%';
				strTemp += ToHex((unsigned char)str[i] >> 4);
				strTemp += ToHex((unsigned char)str[i] % 16);
			}
		}

		return strTemp;
	}

	std::string UrlDecode(const std::string& str)
	{
		std::string strTemp = "";
		size_t length = str.length();
		for (size_t i = 0; i < length; i++)
		{
			if (str[i] == '+') strTemp += ' ';
			else if (str[i] == '%')
			{
				unsigned char high = FromHex((unsigned char)str[++i]);
				unsigned char low = FromHex((unsigned char)str[++i]);
				strTemp += high * 16 + low;
			}
			else strTemp += str[i];
		}

		return strTemp;
	}
};

