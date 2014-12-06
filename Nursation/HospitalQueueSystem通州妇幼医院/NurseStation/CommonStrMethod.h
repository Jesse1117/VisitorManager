/************************************************************************/
/*     Author:	Songyz                                                  */
/*     Time:	2013.11.14                                              */
/************************************************************************/

#pragma once
#include "afx.h"
#include "WinSock2.h"

class CommonStrMethod
{
public:
	CommonStrMethod(void);
	~CommonStrMethod(void);
public:

	/**
	desc:		���ֽ��ַ��� ת ���ֽ��ַ���

	dstBuf:		Ŀ���ַ���������
	src:		Դ�ַ���

	return:		�ɹ������� TRUE;���򣬷��� FALSE
	*/
	static BOOL WChar2Char(char* dstBuf, size_t len, const wchar_t* src);

	/**
	desc:		���ֽ��ַ��� ת ���ֽ��ַ���

	dstBuf:		Ŀ���ַ���������
	src:		Դ�ַ���

	return:		�ɹ������� TRUE;���򣬷��� FALSE
	*/
	static BOOL Char2WChar(wchar_t* dstBuf,size_t len,const char *src);

	/**
	desc:		���ַ����в������ַ�����һ�γ��ֵ��±�
	strSrc:		Դ�ַ���
	strFind:	Ҫ���ҵ��ַ���

	return:		���ҳɹ��������������ַ�����һ�γ��ֵ��±ꣻ
	���򣬷��� -1
	*/
	static int StrFind(CString strSrc, CString strFind);

	/**
	desc:		���ַ����в������ַ�����һ�γ��ֵ��±�, �����ִ�Сд
	strSrc:		Դ�ַ���
	strFind:	Ҫ���ҵ��ַ���

	return:		���ҳɹ��������������ַ�����һ�γ��ֵ��±ꣻ
	���򣬷��� -1
	*/
	static int StrFindNoCase(CString strSrc, CString strFind);

	/**
	desc:		��Դ�ַ����е��ַ����滻�����ַ���

	strSrc:		Դ�ַ���
	strFrom:	Ҫ�滻���ַ���
	strTo:		�����滻�����ַ���

	return:		�����滻������ַ���
	*/
	static CString StrReplace(CString strSrc, CString strFrom, CString strTo);

	/**
	desc:			���ַ������ݷָ����ָ���ַ�������, 
					�ָ���������һ���ַ���Ҳ�����Ƕ���ַ���
					���磬_T("\n") �� _T(" ") �� _T(" \n,.��")

	strSrc:			Դ�ַ���
	arrStrDest:		�ַ������飬����ָ�õ��ַ���
	strDivisionSet:	�ָ�����

	return:			�ɹ������� TRUE�����򣬷��� FALSE
	*/
	static BOOL StrSplit(CString strSrc, CStringArray& arrStrDest, CString strDivisionSet);

	
	static int FindWcharNoCase(CString& strSrc, TCHAR chFind);

	/**
	desc:		�Ƚ��������ַ��Ƿ����, �����ִ�Сд

	return:		��ȣ����� TRUE�����򣬷��� FALSE
	*/
	static BOOL CompareWcharNoCase(WCHAR ch1, WCHAR ch2);

	/**
	desc:				���ַ����л�ȡ����ֵ

	strSrc:				Դ�ַ���
	strProfileName:		Ҫ��ȡ��������
	strProfileValue:	�����ȡ��������ֵ

	return:				�ɹ������� TRUE�����򣬷��� FALSE
	*/
	static BOOL StrGetProfileStr(CString strSrc, CString strProfileName, 
		CString& strProfileValue, WCHAR wchSplitNameValue, WCHAR wchSplitProfile);

	/**
	desc:				���ַ����л�ȡ����ֵ����������������Сд

	strSrc:				Դ�ַ���
	strProfileName:		Ҫ��ȡ��������
	strProfileValue:	�����ȡ��������ֵ

	return:				�ɹ������� TRUE�����򣬷��� FALSE
	*/
	static BOOL StrGetProfileStrNoCase(CString strSrc, CString strProfileName, 
		CString& strProfileValue, WCHAR wchSplitNameValue, WCHAR wchSplitProfile);

	/**
	desc:		���������ַ��� ת�� ��������

	strNum:		�����ַ���

	return:		���� ת���õ���������
	*/
	static int Str2Int(CString strNum);

	/**
	desc:		�������� ת�� ���������ַ��� 

	iNum:		��������

	return:		���� ת���õ����������ַ���
	*/
	static CString Int2Str(int iNum);


	//////////////////////////////////////////////////////////////

	/**
	desc:		��ȡ��ǰ��������·��,������'\'

	return:		���� ��ǰ��������·��
	*/
	static CString GetModuleDir(void);

	static CString GetModuleFileName(void);

	/**
	desc:			��ȡĳ�ļ����µ��ļ�ȫ·����

	strPath:		�ļ���·��
	strarrFileList: �����ļ��б���ַ�������

	return:			���� ��ǰ��������·��
	*/
	static int GetAbsNameListOfDir(CString strPath, CStringArray& strarrFileList);

	/**
	desc:			��ȡĳ�ļ����µ��ļ�ȫ·����

	strPath:		�ļ���·��
	strarrFileList: �����ļ��б���ַ�������

	return:			���� ��ǰ��������·��
	*/
	static int GetNameListOfDir(CString strPath, CStringArray& strarrFileList);

	static BOOL GetLocalHostNameAndIP(CString& strHostName, CString& strHostIP);

	static CString GetLocalHostName();

	static CString GetLocalIP();

	static BOOL StrIsNumbers(CString strNum);

	static CString StrClearUnvisibleChar(CString& strSrc);

	static BOOL PathFileExist(CString strPath);

	static BOOL CreatePathMy(CString strPath);

	static BOOL CreateFileMy(CString strFile);

	static CString GetPathFromAbsName(CString strAbsName);

	static CString GetNameFromAbsName(CString strAbsName);

	static BOOL IsAbsPath(CString strAbsPath);

	static CString GetPrivateProfileStringMy(CString strAppName, CString strKeyName, 
		CString strDefault, CString strFileName);

	static int GetPrivateProfileIntMy(CString strAppName, CString strKeyName, 
		int nDefault, CString strFileName);

	static BOOL WritePrivateProfileStringMy(CString strAppName, CString strKeyName, 
		CString strProfile, CString strFileName);

	static USHORT NetToHostShort(USHORT uNetShort);

	static CString NetToHostIP(IN_ADDR& in_addrNet);

	static CString GetAbsName(CString strName);

	static BOOL AddAutoRun(CString strValueName);

	static BOOL WriteRegString(HKEY hKeyRoot, CString strSubKey, 
		CString strValueName, CString strData);

	static BOOL GetRegString(HKEY hKeyRoot, CString strSubKey, 
		CString strValueName, CString& strData);

	static CString GetRegString(HKEY hKeyRoot, CString strSubKey, 
		CString strValueName);





///////////////////////////////		private method		/////////////////////////////////
private:
	static BOOL _CreatePath(CString strPath);
};
