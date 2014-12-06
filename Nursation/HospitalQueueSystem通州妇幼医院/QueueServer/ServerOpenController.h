#pragma once

#include "../NurseStation/Controller.h"

// CServerOpenController ÃüÁîÄ¿±ê

class CServerOpenController : public CController
{
	typedef CMap<CString, LPCTSTR, SOCKADDR_IN, SOCKADDR_IN&> OfficeSockMap;
	typedef CMap<CString, LPCTSTR, CString, LPCTSTR> DoctorOfficeMap;

public:
	CServerOpenController();
	virtual ~CServerOpenController();
public:

	OfficeSockMap& GetOfficeSockMap()
	{
		return m_mapOfficeSock;
	}

private:

	virtual BOOL OnStartControl();
	virtual BOOL OnEndControl();

	virtual void DispatchCmd(LPUDPPACKEGE pUDPPackege, LPSOCKADDR_IN psockddr);

	///////		CMD dispatch function	/////////////////////////////
	virtual void OnRecvReqLogin(LPREQLOGIN pReqLogin, LPSOCKADDR_IN psockddr){}
	virtual void OnRecvLogin(LPBROADCAST pLogin, LPSOCKADDR_IN psockddr){}
	virtual void OnRecvQuit(LPQUIT pQuit, LPSOCKADDR_IN psockddr){}
	virtual void OnRecvHeartBeat(LPBROADCAST pHeartbeat, LPSOCKADDR_IN psockddr){}
	virtual void OnRecvDoctorCmd(LPDOCTORCMD pDoctorCmd, LPSOCKADDR_IN psockddr){}
	virtual void OnRecvCmdResult(LPCMDRESULT pCmdResult, LPSOCKADDR_IN psockddr);
	virtual void OnRecvChatMsg(LPCHATMSG pChatMsg, LPSOCKADDR_IN psockddr){}
	///////		End	CMD dispatch function	/////////////////////////

	virtual void OnSetPort();

private:
	BOOL RetransmitCmd(CString strCmd, LPSOCKADDR_IN psockaddrin);
	LPSOCKADDR_IN GetSock(CString strDoctorId);
	void UpdateDoctorOffice();

private:
	CMap<CString, LPCTSTR, DoctorCmdEnum, DoctorCmdEnum> m_mapDocCmdStrEnum;
	CMap<DoctorCmdEnum, DoctorCmdEnum, CString, LPCTSTR> m_mapDocCmdEnumStr;

	CMap<CString, LPCTSTR, NetTypeIDEnum, NetTypeIDEnum> m_mapCmdStrEnum;
	CMap<NetTypeIDEnum, NetTypeIDEnum, CString, LPCTSTR> m_mapCmdEnumStr;

	OfficeSockMap m_mapOfficeSock;
	DoctorOfficeMap m_mapDoctorOffice;

	CString m_strMyDbConnStr;
};

