#include "StdAfx.h"
#include "DataManage.h"
#include "VisitorInfo.h"
#include "ConectToMySql.h"
CDataManage::CDataManage(void)
{
	m_MySql = new CConectToMySql();
	/*m_MySql->ConnectToDB();*/
}

CDataManage::~CDataManage(void)
{
}

BOOL CDataManage::IsAppointment (const CVisitorInfo& info)
{
	return TRUE;
}

BOOL CDataManage::UpdateVisitorInfo(const CVisitorInfo& info)
{
	return TRUE;
}