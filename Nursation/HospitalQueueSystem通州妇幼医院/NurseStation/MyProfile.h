#pragma once

class MyProfile
{
public:
	MyProfile(void);
	~MyProfile(void);

	/**
	desc:				���ַ����л�ȡ����ֵ

	strSrc:				Դ�ַ���
	strProfileName:		Ҫ��ȡ��������
	strProfileValue:	�����ȡ��������ֵ

	return:				�ɹ������� TRUE�����򣬷��� FALSE
	*/
	static BOOL MyGetProfileString(CString strSrc, CString strProfileName, CString& strProfileValue);

	/**
	desc:				���ַ����л�ȡ����ֵ����������������Сд

	strSrc:				Դ�ַ���
	strProfileName:		Ҫ��ȡ��������
	strProfileValue:	�����ȡ��������ֵ

	return:				�ɹ������� TRUE�����򣬷��� FALSE
	*/
	static BOOL MyGetProfileStringNoCase(CString strSrc, CString strProfileName, CString& strProfileValue);

	/**
	desc:				���ַ����л�ȡ����ֵ

	strSrc:				Դ�ַ���
	strProfileName:		Ҫ��ȡ��������

	return:				�ɹ������� ����ֵ�ַ��������򣬷��� ���ַ���
	*/
	static CString MyGetProfileString(CString strSrc, CString strProfileName);

	/**
	desc:				���ַ����л�ȡ����ֵ����������������Сд

	strSrc:				Դ�ַ���
	strProfileName:		Ҫ��ȡ��������

	return:				�ɹ������� ����ֵ�ַ��������򣬷��� ���ַ���
	*/
	static CString MyGetProfileStringNoCase(CString strSrc, CString strProfileName);

	/**
	desc:		���ַ����в���һ�����ַ���һ�γ��ֵ��±�, �����ִ�Сд

	strSrc:		Դ�ַ���
	chFind:		Ҫ���ҵ��ַ�

	return:		���ҳɹ��������������ַ�����һ�γ��ֵ��±ꣻ
	���򣬷��� -1
	*/

	/**
	desc:		�Ƚ��������ַ��Ƿ����, �����ִ�Сд

	strSrc:		Դ�ַ���

	return:		���� ����ͷ�ַ���
	*/
	static CString GetHeaderString(CString& strSrc);

	static BOOL GetCmdTypeDataString(
		CString& strSrc, 
		CString& strCmdTypeStr, 
		CString& strCmdDataStr);
};
