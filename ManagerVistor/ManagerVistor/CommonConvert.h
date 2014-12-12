#pragma once
////����ת���ַ�������
#include <string>
using namespace std;
class CCommonConvert
{
public:
	CCommonConvert(void);
	~CCommonConvert(void);
	static int WStringToChar(const std::wstring str,char c_str[],int length);
	static int CharToWString(std::wstring& str,const char c_str[]);
	static void intToWString(int i,std::wstring& str);
	static void WStringToint(int& i,const std::wstring str);
	static BOOL WChar2Char(char* dstBuf, size_t len, const wchar_t* src);
	static int Char2WChar(const char* source,size_t len,wchar_t* dest);
	static string WStringToString(const std::wstring str);
	static wstring StringToWString(const std::string str);
	//��ȡ����IP
//	CString GetComputerIP();
	//��ȡ����ִ��·��
//	CString GetExeFullFilePath();
	////UTF8תstd::string
	static std::string UTF8_To_string(const std::string & str);
	////std::stringתutf8�ַ���
	static std::string string_To_UTF8(const std::string & str); 
};
