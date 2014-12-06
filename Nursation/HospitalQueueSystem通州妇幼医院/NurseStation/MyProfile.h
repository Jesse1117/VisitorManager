#pragma once

class MyProfile
{
public:
	MyProfile(void);
	~MyProfile(void);

	/**
	desc:				在字符串中获取属性值

	strSrc:				源字符串
	strProfileName:		要获取的属性名
	strProfileValue:	保存获取到的属性值

	return:				成功，返回 TRUE；否则，返回 FALSE
	*/
	static BOOL MyGetProfileString(CString strSrc, CString strProfileName, CString& strProfileValue);

	/**
	desc:				在字符串中获取属性值，不区分属性名大小写

	strSrc:				源字符串
	strProfileName:		要获取的属性名
	strProfileValue:	保存获取到的属性值

	return:				成功，返回 TRUE；否则，返回 FALSE
	*/
	static BOOL MyGetProfileStringNoCase(CString strSrc, CString strProfileName, CString& strProfileValue);

	/**
	desc:				在字符串中获取属性值

	strSrc:				源字符串
	strProfileName:		要获取的属性名

	return:				成功，返回 属性值字符串；否则，返回 空字符串
	*/
	static CString MyGetProfileString(CString strSrc, CString strProfileName);

	/**
	desc:				在字符串中获取属性值，不区分属性名大小写

	strSrc:				源字符串
	strProfileName:		要获取的属性名

	return:				成功，返回 属性值字符串；否则，返回 空字符串
	*/
	static CString MyGetProfileStringNoCase(CString strSrc, CString strProfileName);

	/**
	desc:		在字符串中查找一个宽字符第一次出现的下标, 不区分大小写

	strSrc:		源字符串
	chFind:		要查找的字符

	return:		查找成功，返回所查找字符串第一次出现的下标；
	否则，返回 -1
	*/

	/**
	desc:		比较两个宽字符是否相等, 不区分大小写

	strSrc:		源字符串

	return:		返回 报文头字符串
	*/
	static CString GetHeaderString(CString& strSrc);

	static BOOL GetCmdTypeDataString(
		CString& strSrc, 
		CString& strCmdTypeStr, 
		CString& strCmdDataStr);
};
