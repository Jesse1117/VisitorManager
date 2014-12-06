#include "StdAfx.h"
#include "MyPort.h"
#include "CommonStrMethod.h"

MyPort::MyPort(void)
{
}

MyPort::~MyPort(void)
{
}

USHORT MyPort::GetLocalPort(USHORT uDefaultPort)
{
	return GetPort(_T("LOCAL_PORT"), uDefaultPort);
}

USHORT MyPort::GetOpenPort(USHORT uDefaultPort)
{
	return GetPort(_T("OPEN_PORT"), uDefaultPort);
}

BOOL MyPort::SetLocalPort(CString strPort)
{
	return SetPort(_T("LOCAL_PORT"), CommonStrMethod::Str2Int(strPort));
}

BOOL MyPort::SetOpenPort(CString strPort)
{
	return SetPort(_T("OPEN_PORT"), CommonStrMethod::Str2Int(strPort));
}




//////////////////////////////	private		//////////////////////////////////



USHORT MyPort::GetPort(CString strKeyName, USHORT uDefaultPort)
{
	CString strAbsName = CommonStrMethod::GetModuleDir() + _T("SYS\\port.ini");

	return CommonStrMethod::Str2Int(
		CommonStrMethod::GetPrivateProfileStringMy(
		_T("sys"), strKeyName, 
		CommonStrMethod::Int2Str(uDefaultPort),
		strAbsName));
}

BOOL MyPort::SetPort(CString strKeyName, USHORT uPort)
{
	CString strAbsName = CommonStrMethod::GetModuleDir() + _T("SYS\\port.ini");

	return CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), strKeyName,
		CommonStrMethod::Int2Str(uPort), strAbsName);
}

