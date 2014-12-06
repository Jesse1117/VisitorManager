#pragma once

#include "../NurseStation/ServiceController.h"
#include "ServerOpenController.h"

class CServerController : public CServiceController
{
public:
	CServerController(void);
	~CServerController(void);

private:
	virtual BOOL OnStartControl();
	virtual BOOL OnEndControl();

	virtual void OnRecvReqLogin(LPREQLOGIN pReqLogin, LPSOCKADDR_IN psockddr){}
	virtual void OnRecvDoctorCmd(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr){}
	virtual void OnRecvCmdResult(LPCMDRESULT pCmdResult, LPSOCKADDR_IN psockddr){}
	virtual void OnRecvChatMsg(LPCHATMSG pChatMsg, LPSOCKADDR_IN psockddr){}

	virtual void AddDoctor(LPBROADCAST pLogin, LPSOCKADDR_IN psockddr){}


	virtual void OnDoctorLogin(CDoctor* pDoctor, BOOL bLogin){}
	virtual void OnDoctorOutLine(CDoctor* pDoctor){}

	virtual void OnNurseOutLine(CNurse* pNurse);
	virtual void OnNurseLogin(CNurse* pNurse, BOOL bLogin);

	CServerOpenController m_ServerOpenController;
};
