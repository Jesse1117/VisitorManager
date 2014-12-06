#include "StdAfx.h"
#include "ServerOpenController.h"
#include "../NurseStation/OpenDatabase.h"
#include "../NurseStation/CommonStrMethod.h"
#include "../NurseStation/MyPort.h"
#include "../NurseStation/WriteLog.h"

CServerOpenController::CServerOpenController()
{
	m_mapCmdStrEnum[_T("LOGIN")] = ntiLogin;
	m_mapCmdStrEnum[_T("LOGOUT")] = ntiQuit;

	m_mapCmdEnumStr[ntiLogin] = _T("LOGIN");
	m_mapCmdEnumStr[ntiQuit] = _T("LOGOUT");

	m_mapDocCmdStrEnum[_T("CALL")] = dcCmdCall;
	m_mapDocCmdStrEnum[_T("RECALL")] = dcCmdRecall;
	m_mapDocCmdStrEnum[_T("DISCARD")] = dcCmdDiscard;
	m_mapDocCmdStrEnum[_T("WAIT")] = dcCmdWait;
	m_mapDocCmdStrEnum[_T("REQEVA")] = dcCmdEva;
	m_mapDocCmdStrEnum[_T("PAUSE")] = dcCmdPause;
	m_mapDocCmdStrEnum[_T("RESUME")] = dcCmdResume;

	m_mapDocCmdEnumStr[dcCmdCall] = _T("CALL");
	m_mapDocCmdEnumStr[dcCmdRecall] = _T("RECALL");
	m_mapDocCmdEnumStr[dcCmdDiscard] = _T("DISCARD");
	m_mapDocCmdEnumStr[dcCmdWait] = _T("WAIT");
	m_mapDocCmdEnumStr[dcCmdEva] = _T("REQEVA");
	m_mapDocCmdEnumStr[dcCmdPause] = _T("PAUSE");
	m_mapDocCmdEnumStr[dcCmdResume] = _T("RESUME");

	m_strMyDbConnStr.Format(_T("Driver={%s};Server=%s;Uid=%s;Pwd=%s;Database=Nurse;"),
		CommonStrMethod::GetPrivateProfileStringMy(_T("sys"), _T("DRIVER"), _T("SQL Server"), _T("sys.ini")), 
		CommonStrMethod::GetPrivateProfileStringMy(_T("sys"), _T("SERVER"), _T("127.0.0.1"), _T("sys.ini")), 
		CommonStrMethod::GetPrivateProfileStringMy(_T("sys"), _T("UID"), _T("sa"), _T("sys.ini")), 
		CommonStrMethod::GetPrivateProfileStringMy(_T("sys"), _T("PWD"), _T("123456"), _T("sys.ini"))
		);
}

CServerOpenController::~CServerOpenController()
{
}

BOOL CServerOpenController::OnStartControl()
{
	UpdateDoctorOffice();

	return CController::OnStartControl();
}

BOOL CServerOpenController::OnEndControl()
{
	return CController::OnEndControl();
}

void CServerOpenController::DispatchCmd(LPUDPPACKEGE pUDPPackege,
										LPSOCKADDR_IN psockddr)
{
	WCHAR wszCmd[64] = {0};
	CommonStrMethod::Char2WChar(wszCmd, 128, (CHAR*)pUDPPackege);
	//CString strCmd(wszCmd);
	//CString strHead = strCmd.Left(3);
	WCHAR wszHead[4];
	wszHead[0] = wszCmd[0];
	wszHead[1] = wszCmd[1];
	wszHead[2] = wszCmd[2];
	wszHead[3] = '\0';
	//if(strHead.CompareNoCase(_T("CMD")) == 0)
	if(wcscmp(wszHead, _T("CMD")) == 0)
	{
		//#ifdef _DEBUG
		CString strRecv;
		strRecv.Format(_T("Recived from %s:%d\r\n%s\r\n"), 
			NetToHostIP(psockddr->sin_addr), 
			NetToHostShort(psockddr->sin_port), wszCmd);
		WriteLogWithTime(strRecv);
		//#endif
		//DOCTORCMD doctorcmd;
		//memset(&doctorcmd, 0, sizeof(DOCTORCMD));
		//if(TranslateCmd(wszBuf, &doctorcmd))
		//{
		//	RetransmitCmd(&doctorcmd, psockddr);
		//}
		//else
		//{
		//	return;
		//}
		RetransmitCmd(wszCmd, psockddr);
	}
	else
	{
		switch( ((LPUDPPACKEGE)pUDPPackege)->header.eTypeID )
		{
		case ntiCmdResult:
			OnRecvCmdResult((LPCMDRESULT)pUDPPackege, psockddr);
			break;
		default:
			CController::DispatchCmd(pUDPPackege, psockddr);
			break;
		}
	}
}

void CServerOpenController::OnSetPort()
{
	MyPort myPort;
	SetPort(myPort.GetOpenPort(4020));
}

void CServerOpenController::OnRecvCmdResult(LPCMDRESULT pCmdResult, LPSOCKADDR_IN psockddr)
{
	CString strCmd;
	CString strPatient;
	CString strNum;

	if(pCmdResult->eTypeIDFrom != ntiDoctorCmd)
	{
		strCmd = m_mapCmdEnumStr[pCmdResult->eTypeIDFrom];
	}
	else
	{
		DoctorCmdEnum eCmd = pCmdResult->eDoctorCmd;
		strCmd = m_mapDocCmdEnumStr[eCmd];
		if(eCmd == dcCmdCall)
		{
			//for(int i = 0; i < MAX_PATIENTS_SHOW; i++)
			//{
			//	if(pCmdResult->patientsArray[i].eStatus == qsDoing)
			//	{
			//		strPatient.Format(_T("%s|%s|%s|%s"), 
			//			pCmdResult->patientsArray[i].wszQueueID, 
			//			pCmdResult->patientsArray[i].wszPatientName,
			//			pCmdResult->patientsArray[i].wszPatientGender,
			//			pCmdResult->patientsArray[i].wszPatientAge);
			//	}
			//	break;
			//}
		}
		else if(eCmd == dcCmdWait)
		{
			//for(int i = 0; i < MAX_PATIENTS_SHOW; i++)
			//{
			//	if(pCmdResult->patientsArray[i].eStatus == qsPrepare)
			//	{
			//		strPatient.Format(_T("%s|%s|%s|%s"), 
			//			pCmdResult->patientsArray[i].wszQueueID, 
			//			pCmdResult->patientsArray[i].wszPatientName,
			//			pCmdResult->patientsArray[i].wszPatientGender,
			//			pCmdResult->patientsArray[i].wszPatientAge);
			//	}
			//	break;
			//}
		}
		//strNum.Format(_T("%d"), pCmdResult->nPatientCount);
		//if(!(eCmd == dcCmdCall || eCmd == dcCmdWait 
		//	|| eCmd == dcCmdDiscard))
		//{
		//	strNum.Empty();
		//}
	}

	strNum.Format(_T("%d"), pCmdResult->nPatientCount);


	CString strRet;
	strRet.Format(_T("RET@%s@%s@%s@%s@%s@ED"), 
		pCmdResult->header.sUserInfo.wszUserID, strCmd,
		pCmdResult->bSucceed ? _T("1") : _T("0"), strNum, strPatient);

	int iLength = strRet.GetLength()*2 + 1;
	CHAR* pbuf = (CHAR*)malloc(iLength);
	memset(pbuf, 0, iLength);
	CommonStrMethod::WChar2Char(pbuf, iLength, strRet.GetBuffer());

	if(SendTo(pbuf, strlen(pbuf), &pCmdResult->header.sSockAddrIn))
	{
		CString strLog;
		strLog.Format(_T("Sent to %s:%d\r\n%s"), 
			NetToHostIP(pCmdResult->header.sSockAddrIn.sin_addr),
			NetToHostShort(pCmdResult->header.sSockAddrIn.sin_port),
			strRet);
		WriteLogWithTime(strLog);
	}
}

BOOL CServerOpenController::RetransmitCmd(CString strCmd, LPSOCKADDR_IN psockaddrin)
{
	//return SendTo((CHAR*)pDoctorCmd, sizeof(DOCTORCMD), _T("192.168.1.200"), 4020);
	CHAR szFailedRet[32] = {0};
	strcpy_s(szFailedRet, 32, "RET@@@0@@@ED");

	CString strErr;
	int iIndex = CommonStrMethod::StrFindNoCase(strCmd, _T("ED"));
	if(iIndex == -1)
	{
		strErr = _T("指令报文错误：无法检索到指令报文结束标志ED");
		WriteErrLog(strErr);
		SendTo(szFailedRet, strlen(szFailedRet), psockaddrin);
		return FALSE;
	}
	strCmd = strCmd.Left(iIndex+2);
	CStringArray arrstrCmd;
	CommonStrMethod::StrSplit(strCmd,arrstrCmd, _T("@"));

	if(arrstrCmd.GetCount() > 3)
	{
		sprintf_s(szFailedRet, 32, "RET@%s@%s@0@@@ED", arrstrCmd[1], arrstrCmd[2]);
	}

	if(arrstrCmd.GetCount() < 6)
	{
		strErr = _T("指令报文错误：指令报文项数目小于最低项数目");
		WriteErrLog(strErr);
		SendTo(szFailedRet, strlen(szFailedRet), psockaddrin);
		return FALSE;
	}

	LPSOCKADDR_IN pNurseSock = GetSock(arrstrCmd[1]);
	if(!pNurseSock)
	{
		strErr = _T("系统返回错误：护士站系统尚未启动");
		WriteErrLog(strErr);
		SendTo(szFailedRet, strlen(szFailedRet), psockaddrin);
		return FALSE;
	}

	arrstrCmd[2] = arrstrCmd[2].MakeUpper();
	DoctorCmdEnum eDocCmd;
	BOOL bFound = FALSE;
	bFound = m_mapDocCmdStrEnum.Lookup(arrstrCmd[2], eDocCmd);
	if(bFound)
	{
		DOCTORCMD docCmd;
		ZeroMemory(&docCmd, sizeof(docCmd));
		docCmd.header.eTypeID = ntiDoctorCmd;
		docCmd.header.nDataLength = sizeof(docCmd);
		docCmd.header.sSockAddrIn = *psockaddrin;
		wcscpy_s(docCmd.header.sUserInfo.wszUserID, MAX_ID_LENGTH, arrstrCmd[1].GetBuffer());
		docCmd.header.sUserInfo.eUserType = utDoctor;
		docCmd.eDoctorCmd = eDocCmd;
		return SendTo((CHAR*)&docCmd, sizeof(docCmd), pNurseSock);
	}
	else
	{
		NetTypeIDEnum eCmd;
		bFound = m_mapCmdStrEnum.Lookup(arrstrCmd[2], eCmd);
		if(bFound)
		{
			switch(eCmd)
			{
			case ntiLogin:
				{
					BROADCAST login;
					ZeroMemory(&login, sizeof(login));
					login.header.nDataLength = sizeof(login);
					login.header.sSockAddrIn = *psockaddrin;
					login.header.eTypeID = ntiLogin;
					wcscpy_s(login.header.sUserInfo.wszUserID, MAX_ID_LENGTH, arrstrCmd[1].GetBuffer());
					login.header.sUserInfo.eUserType = utDoctor;
					return SendTo((CHAR*)&login, sizeof(login), pNurseSock);
				}
				break;
			case ntiQuit:
				{
					QUIT quit;
					ZeroMemory(&quit, sizeof(quit));
					quit.header.nDataLength = sizeof(quit);
					quit.header.sSockAddrIn = *psockaddrin;
					quit.header.eTypeID = ntiQuit;
					wcscpy_s(quit.header.sUserInfo.wszUserID, MAX_ID_LENGTH, arrstrCmd[1].GetBuffer());
					quit.header.sUserInfo.eUserType = utDoctor;
					return SendTo((CHAR*)&quit, sizeof(quit), pNurseSock);
				}
				break;
			default:
				{
					strErr.Format(_T("指令报文提示：排队系统尚未启用 %s 命令"), arrstrCmd[2]);
					WriteErrLog(strErr);
					SendTo(szFailedRet, strlen(szFailedRet), psockaddrin);
					return FALSE;
				}
				break;
			}
		}
		else
		{
			strErr.Format(_T("指令报文错误：%s 不是预设命令类型"), arrstrCmd[2]);
			WriteErrLog(strErr);
			SendTo(szFailedRet, strlen(szFailedRet), psockaddrin);
			return FALSE;
		}
	}

	return FALSE;
}

LPSOCKADDR_IN CServerOpenController::GetSock(CString strDoctorId)
{
	DoctorOfficeMap::CPair* pPairDO;
	pPairDO = m_mapDoctorOffice.PLookup(strDoctorId);
	if(!pPairDO)
	{
		return NULL;
	}
	OfficeSockMap::CPair* pPairOS;
	pPairOS = m_mapOfficeSock.PLookup(pPairDO->value);
	if(!pPairOS)
	{
		return NULL;
	}

	return &pPairOS->value;
}

void CServerOpenController::UpdateDoctorOffice()
{
	try
	{
		CADODatabase db;
		db.SetConnectionString(m_strMyDbConnStr);
		db.Open();
		CADORecordset rset(&db);
		CString strSql(_T("select doctor_id,office_id from Doctor;"));
		rset.Open(strSql, CADORecordset::openQuery);
		if(!rset.IsBOF())
		{
			for(; !rset.IsEOF(); rset.MoveNext())
			{
				CString strOfficeId, strDoctorId;
				rset.GetFieldValue(0, strDoctorId);
				rset.GetFieldValue(1, strOfficeId);
				m_mapDoctorOffice[strDoctorId] = strOfficeId;
			}
		}
		rset.Close();
		db.Close();
	}
	catch (_com_error& e)
	{
		CString strErr;
		strErr.Format(_T("CServerOpenController::UpdateDoctorOffice: %s"), e.ErrorMessage());
		WriteLog::WriteDbErrLog(strErr);
	}
}

// CServerOpenController 成员函数
