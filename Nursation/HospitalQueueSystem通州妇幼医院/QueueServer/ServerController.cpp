#include "StdAfx.h"
#include "ServerController.h"

CServerController::CServerController(void)
{

}

CServerController::~CServerController(void)
{
}

BOOL CServerController::OnStartControl()
{
	BOOL bRet = m_ServerOpenController.StartControl();

	return CServiceController::OnStartControl() && bRet;
}

BOOL CServerController::OnEndControl()
{
	BOOL bRet = m_ServerOpenController.EndControl();

	return  CServiceController::OnEndControl() && bRet;
}

void CServerController::OnNurseOutLine(CNurse* pNurse)
{
	const CNurse::OfficeArray& officeArray = pNurse->GetOfficeList();
	for(int i = 0; i < officeArray.GetCount(); i++)
	{
		m_ServerOpenController.GetOfficeSockMap()[officeArray[i].GetOfficeId()] 
		= pNurse->GetSockAddrIn();
	}
}

void CServerController::OnNurseLogin(CNurse* pNurse, BOOL bLogin)
{
	const CNurse::OfficeArray& officeArray = pNurse->GetOfficeList();
	for(int i = 0; i < officeArray.GetCount(); i++)
	{
		m_ServerOpenController.GetOfficeSockMap().RemoveKey(officeArray[i].GetOfficeId());
	}
}
