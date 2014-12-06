#include "StdAfx.h"
#include "MyProfile.h"
#include "CommonStrMethod.h"

MyProfile::MyProfile(void)
{
}

MyProfile::~MyProfile(void)
{
}

/**
desc:				���ַ����л�ȡ����ֵ

strSrc:				Դ�ַ���
strProfileName:		Ҫ��ȡ��������
strProfileValue:	�����ȡ��������ֵ

return:				�ɹ������� TRUE�����򣬷��� FALSE
*/
BOOL MyProfile::MyGetProfileString(CString strSrc, 
										 CString strProfileName, 
										 CString& strProfileValue)
{
	return CommonStrMethod::StrGetProfileStr(strSrc, strProfileName, strProfileValue, '=', ';');
}

/**
desc:				���ַ����л�ȡ����ֵ����������������Сд

strSrc:				Դ�ַ���
strProfileName:		Ҫ��ȡ��������
strProfileValue:	�����ȡ��������ֵ

return:				�ɹ������� TRUE�����򣬷��� FALSE
*/
BOOL MyProfile::MyGetProfileStringNoCase(CString strSrc, 
											   CString strProfileName, 
											   CString& strProfileValue)
{
	return CommonStrMethod::StrGetProfileStrNoCase(strSrc, strProfileName, strProfileValue, '=', ';');
}

/**
desc:				���ַ����л�ȡ����ֵ

strSrc:				Դ�ַ���
strProfileName:		Ҫ��ȡ��������

return:				�ɹ������� ����ֵ�ַ��������򣬷��� ���ַ���
*/
CString MyProfile::MyGetProfileString(CString strSrc, 
											CString strProfileName)
{
	CString strProfileValue;
	CommonStrMethod::StrGetProfileStr(strSrc, strProfileName, strProfileValue, '=', ';');
	return strProfileValue;
}

/**
desc:				���ַ����л�ȡ����ֵ����������������Сд

strSrc:				Դ�ַ���
strProfileName:		Ҫ��ȡ��������

return:				�ɹ������� ����ֵ�ַ��������򣬷��� ���ַ���
*/
CString MyProfile::MyGetProfileStringNoCase(CString strSrc, 
												  CString strProfileName)
{
	CString strProfileValue;
	CommonStrMethod::StrGetProfileStrNoCase(strSrc, strProfileName, strProfileValue, '=', ';');
	return strProfileValue;
}

/**
desc:		�Ƚ��������ַ��Ƿ����, �����ִ�Сд

strSrc:		Դ�ַ���

return:		���� ����ͷ�ַ���
*/
CString MyProfile::GetHeaderString(CString& strSrc)
{
	int nIndex = strSrc.Find(_T(";"));
	if(nIndex == -1)
	{
		return _T("");
	}
	CString str = strSrc.Left(nIndex);
	return str.MakeLower();
}

BOOL MyProfile::GetCmdTypeDataString(CString& strSrc, 
										CString& strCmdTypeStr, 
										CString& strCmdDataStr)
{
	CString strSrcTemp = strSrc;
	int nStart = strSrcTemp.ReverseFind(';');
	strSrcTemp = strSrcTemp.Left(nStart);
	//strSrcTemp = strSrc.Left(strSrc.GetLength()-1);
	nStart = strSrcTemp.ReverseFind(';');
	strSrcTemp = strSrcTemp.Mid(nStart+1);
	nStart = strSrcTemp.Find('=');
	strCmdTypeStr = strSrcTemp.Left(nStart);
	strCmdDataStr = strSrcTemp.Mid(nStart+1);

	if(!strCmdTypeStr.IsEmpty())
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
