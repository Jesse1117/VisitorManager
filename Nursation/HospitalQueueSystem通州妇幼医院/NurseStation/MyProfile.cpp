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
desc:				在字符串中获取属性值

strSrc:				源字符串
strProfileName:		要获取的属性名
strProfileValue:	保存获取到的属性值

return:				成功，返回 TRUE；否则，返回 FALSE
*/
BOOL MyProfile::MyGetProfileString(CString strSrc, 
										 CString strProfileName, 
										 CString& strProfileValue)
{
	return CommonStrMethod::StrGetProfileStr(strSrc, strProfileName, strProfileValue, '=', ';');
}

/**
desc:				在字符串中获取属性值，不区分属性名大小写

strSrc:				源字符串
strProfileName:		要获取的属性名
strProfileValue:	保存获取到的属性值

return:				成功，返回 TRUE；否则，返回 FALSE
*/
BOOL MyProfile::MyGetProfileStringNoCase(CString strSrc, 
											   CString strProfileName, 
											   CString& strProfileValue)
{
	return CommonStrMethod::StrGetProfileStrNoCase(strSrc, strProfileName, strProfileValue, '=', ';');
}

/**
desc:				在字符串中获取属性值

strSrc:				源字符串
strProfileName:		要获取的属性名

return:				成功，返回 属性值字符串；否则，返回 空字符串
*/
CString MyProfile::MyGetProfileString(CString strSrc, 
											CString strProfileName)
{
	CString strProfileValue;
	CommonStrMethod::StrGetProfileStr(strSrc, strProfileName, strProfileValue, '=', ';');
	return strProfileValue;
}

/**
desc:				在字符串中获取属性值，不区分属性名大小写

strSrc:				源字符串
strProfileName:		要获取的属性名

return:				成功，返回 属性值字符串；否则，返回 空字符串
*/
CString MyProfile::MyGetProfileStringNoCase(CString strSrc, 
												  CString strProfileName)
{
	CString strProfileValue;
	CommonStrMethod::StrGetProfileStrNoCase(strSrc, strProfileName, strProfileValue, '=', ';');
	return strProfileValue;
}

/**
desc:		比较两个宽字符是否相等, 不区分大小写

strSrc:		源字符串

return:		返回 报文头字符串
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
