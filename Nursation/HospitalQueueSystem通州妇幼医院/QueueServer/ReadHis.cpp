// ReadHis.cpp : 实现文件
//

#include "stdafx.h"
#include "QueueServer.h"
#include "ReadHis.h"
#include "WriteLog.h"
#include "../NurseStation/BaseConfig.h"
#include "../NurseStation/CommonStrMethod.h"


// CReadHis


CReadHis::CReadHis()
: m_pReadPatientThread(NULL)
, m_pReadOtherDataThread(NULL)
, m_pAutoDeleteThread(NULL)
, m_bHisDbErr(FALSE)
, m_bMyDbErr(FALSE)
{
	m_strMyDbConnStr.Format(_T("Driver={%s};Server=%s;Uid=%s;Pwd=%s;Database=Nurse;"),
		CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("DRIVER"), _T("SQL Server"), _T("\\SYS\\mydb.ini")), 
		CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("SERVER"), _T("127.0.0.1"), _T("\\SYS\\mydb.ini")), 
		CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("UID"), _T("sa"), _T("\\SYS\\mydb.ini")), 
		CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("PWD"), _T("123456"), _T("\\SYS\\mydb.ini"))
		);
	//Provider=OraOLEDB.Oracle.1
	//Provider=MSDAORA.1
	//m_strHisDbConnStr.Format(_T("Provider=OraOLEDB.Oracle.1;Persist Security Info=False;User ID=%s;Password=%s;hos=%s;port=%s;Data Source=%s;"), 
	//	CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("USER_ID"), _T("hisforbjlb"), _T("\\SYS\\hisdb.ini")), 
	//	CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("PASSWORD"), _T("bjlb2014"), _T("\\SYS\\hisdb.ini")),
	//	CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("HOST"), _T("127.0.0.1"), _T("\\SYS\\hisdb.ini")),
	//	CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("PORT"), _T("1521"), _T("\\SYS\\hisdb.ini")),
	//	CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("SERVICE_NAME"), _T("orcl"), _T("\\SYS\\hisdb.ini"))
	//	);
	m_strHisDbConnStr.Format(_T("Provider=MSDAORA.1;Persist Security Info=False;User ID=%s;Password=%s;Data Source=(DESCRIPTION=(ADDRESS=(PROTOCOL=TCP)(HOST=%s)(PORT=%s))(CONNECT_DATA=(SERVER_NAME=%s)));"), 
		CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("USER_ID"), _T("hisforbjlb"), _T("\\SYS\\hisdb.ini")), 
		CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("PASSWORD"), _T("bjlb2014"), _T("\\SYS\\hisdb.ini")),
		CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("HOST"), _T("127.0.0.1"), _T("\\SYS\\hisdb.ini")),
		CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("PORT"), _T("1521"), _T("\\SYS\\hisdb.ini")),
		CommonStrMethod::GetPrivateProfileStringMy(_T("conn"), _T("SERVICE_NAME"), _T("orcl"), _T("\\SYS\\hisdb.ini"))
		);
	//WriteLog::Write(m_strHisDbConnStr);
	m_nHisDays = CommonStrMethod::GetPrivateProfileIntMy(
		_T("data"), _T("DATA_DAYS"), 0, _T("\\SYS\\hisdb.ini"));
	if(m_nHisDays < 0)
	{
		m_nHisDays = 0;
	}
}

CReadHis::~CReadHis()
{

}

BOOL CReadHis::Start()
{
	//ReadDepart();
	//ReadClinic();
	//ReadDoctor();

	//m_nHisDays = GetHisDays(5);
	BOOL bThread = StartPatientThread();

	BOOL b1 = TRUE, b2 = TRUE;
	if(!m_timerReadOtherData.IsActive())
	{
		b1 = m_timerReadOtherData.StartTimer(
			this, 60000, &CReadHis::ReadOtherDataTimerProc);//1分钟执行一次
	}
	if(!m_timerAutoDeletePatient.IsActive())
	{
		b2 = m_timerAutoDeletePatient.StartTimer(
			this, 600000, &CReadHis::AutoDeletePatientTimerProc);//6分钟执行一次
	}
	
	if(bThread && b1 && b2)
	{
		return TRUE;
	}
	else
	{
		if(!bThread)
		{
			WriteLog::WriteTimeErrLog(_T("启动读HIS病人数据线程失败"));
		}
		if(!b1)
		{
			WriteLog::WriteTimeErrLog(_T("启动读HIS基本数据定时器失败"));
		}
		if(!b2)
		{
			WriteLog::WriteTimeErrLog(_T("启动自动删除数据定时器失败"));
		}
		return FALSE;
	}
}

void CReadHis::Close()
{
	m_timerReadOtherData.KillTimer();
	m_timerAutoDeletePatient.KillTimer();
	EndPatientThread();
}

BOOL CReadHis::StartPatientThread()
{
	if(m_pReadPatientThread == NULL)
	{
		m_pReadPatientThread = AfxBeginThread(ReadPatientThreadProc, this);
	}
	
	return m_pReadPatientThread != NULL;
}

void CReadHis::EndPatientThread()
{
	if(m_pReadPatientThread)
	{
		m_bReadPatientThread = FALSE;
		::WaitForSingleObject(m_pReadPatientThread->m_hThread, 20);
		delete m_pReadPatientThread;
		m_pReadPatientThread = NULL;
	}
}

UINT CReadHis::ReadPatientThreadProc(LPVOID pParam)
{
	CReadHis* pThis = (CReadHis*)pParam;
	pThis->m_bReadPatientThread = TRUE;
	while(pThis->m_bReadPatientThread)
	{
		pThis->ReadPatient();
		Sleep(2000);
	}
	::ExitThread(0);
	return 0;
}

void CReadHis::ReadOtherDataTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if(!m_pReadOtherDataThread)
	{
		m_pReadOtherDataThread = AfxBeginThread(ReadOtherDataThreadProc, this);
	}
}

UINT CReadHis::ReadOtherDataThreadProc(LPVOID pParam)
{
	CReadHis* pThis = (CReadHis*)pParam;
	pThis->ReadDepart();
	pThis->ReadClinic();
	pThis->ReadDoctor();

	pThis->m_pReadOtherDataThread = NULL;

	return 0;
}

void CReadHis::AutoDeletePatientTimerProc(HWND hWnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	if(!m_pAutoDeleteThread)
	{
		m_pAutoDeleteThread = AfxBeginThread(AutoDeleteThreadProc, this);
	}
}

UINT CReadHis::AutoDeleteThreadProc(LPVOID pParam)
{
	CReadHis* pThis = (CReadHis*)pParam;
	pThis->AutoDeletePatient();

	pThis->m_pAutoDeleteThread = NULL;

	return 0;
}

BOOL CReadHis::OpenHisDb(CADODatabase& hisDb)
{
	//打开HIS数据库
	try
	//TRY
	{
		hisDb.Open(_T("DSN=NurseHisDb;"));
		//hisDb.Open(m_strHisDbConnStr);
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("连接HIS数据库失败: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}

		return FALSE;
	}
	//END_CATCH_ALL
	//m_bHisDbErr = FALSE;
	return TRUE;
}

BOOL CReadHis::OpenMyDb(CADODatabase& myDb)
{
	//打开本系统数据库
	try
	{
		myDb.Open(m_strMyDbConnStr);
	}
	catch (_com_error& e)
	{
		if(!m_bMyDbErr)
		{
			m_bMyDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("连接排队系统数据库失败: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}

		return FALSE;
	}
	//m_bMyDbErr = FALSE;
	return TRUE;
}


BOOL CReadHis::ReadPatient()
{
	//连接HIS数据库采用ODBC，连接内部数据库采用ADO
	CADODatabase hisDb;

	//打开HIS数据库
	if(!OpenHisDb(hisDb))
	{
		return FALSE;
	}

	//打开本系统数据库
	CADODatabase myDb;
	if(!OpenMyDb(myDb))
	{
		hisDb.Close();
		return FALSE;
	}

	CString strQuerySerialId;
	//strQuerySerialId.Format(_T("SELECT SERIAL_ID,ID_CARD,QUEUE_NUM,PATIENT_NAME,PATIENT_GENDER,ID_DEPART,TIME,ID_DOCTOR,ID_PAY,PAY_FLAG,PAY_DESC,MONEY,IN_FLAG FROM HisForBjlb_Patient WHERE TIME>to_date(to_char(sysdate-%d,'yyyymmdd'),'yyyymmdd') ORDER BY time DESC"), 
	strQuerySerialId.Format(_T("SELECT serial_id,id_card,queue_num,patient_name,patient_gender,id_depart,time,id_doctor,id_pay,pay_flag,pay_desc,money,in_flag FROM HisForBjlb_Patient WHERE time>to_date(to_char(sysdate-%d,'yyyymmdd'),'yyyymmdd') ORDER BY time DESC"), 
		m_nHisDays);

	//获取HIS数据
	CADORecordset hisRset(&hisDb);
	try
	{
		//hisRset.SetRowsetSize(2);
		if(!hisRset.Open(strQuerySerialId))
		{
			hisDb.Close();
			myDb.Close();
			return FALSE;
		}

		//if(hisRset.GetFieldCount() != 13)
		//{
		//	CString strErr;
		//	strErr.Format(_T("ReadPatient:HIS数据库病人排队视图表[HISFORBJLB_PATIENT]的字段数目不正确: 应为13，实为%d"),hisRset.GetFieldCount());
		//	WriteLog::WriteTimeErrLog(strErr);
		//	return FALSE;
		//}
		if(hisRset.IsBOF())
		{
			hisDb.Close();
			myDb.Close();
			return TRUE;
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadPatient:读取HIS数据库病人排队视图表[HISFORBJLB_PATIENT]失败: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	//将HIS数据写入本系统数据库
	CADORecordset myRset(&myDb);
	CString strInsert;
	try
	{
		for(; !hisRset.IsEOF(); hisRset.MoveNext())
		{
			CString strSerialId;
			
			hisRset.GetFieldValue((short)0, strSerialId);

			CString strQuery;
			strQuery.Format(_T("SELECT serial_id FROM HisForBjlb_Patient WHERE serial_id='%s'"),
				strSerialId);
			try
			{
				myRset.Open(strQuery);
				if(!myRset.IsBOF())
				{
					myRset.Close();
					continue;
				}
				myRset.Close();
			}
			catch (_com_error& e)
			{
				if(!m_bMyDbErr)
				{
					m_bMyDbErr = TRUE;
					CString strErr;
					strErr.Format(_T("ReadPatient:读取病人表[HisForBjlb_Patient].[serial_id]时出错: %s"), e.ErrorMessage());
					WriteLog::WriteTimeErrLog(strErr);
				}
				myRset.Close();
				continue;
			}
			
			int nPatientGender,nPayFlag,nInFlag,nIdDepart,nQueueNum,nIdPay,nIdDoctor;
			CString strIdCard,strQueueNum,strPatientName,strPatientGender,
				strIdDepart,strTime,strIdDoctor,strIdPay,strPayDesc,strPayMoney, strPayFlag, strInFlag;

			hisRset.GetFieldValue(_T("id_card"), strIdCard);
			hisRset.GetFieldValue(_T("queue_num"), strQueueNum);
			nQueueNum = CommonStrMethod::Str2Int(strQueueNum);
			//hisRset.GetFieldValue(_T("queue_num"), nQueueNum);
			strQueueNum = CommonStrMethod::Int2Str(nQueueNum);
			hisRset.GetFieldValue(_T("patient_name"), strPatientName);
			hisRset.GetFieldValue(_T("patient_gender"), strPatientGender);
			nPatientGender = CommonStrMethod::Str2Int(strPatientGender);
			hisRset.GetFieldValue(_T("id_depart"), strIdDepart);
			//hisRset.GetFieldValue(_T("id_depart"), nIdDepart);
			nIdDepart = CommonStrMethod::Str2Int(strIdDepart);
			strIdDepart = CommonStrMethod::Int2Str(nIdDepart);
			hisRset.GetFieldValue(_T("time"), strTime);
			hisRset.GetFieldValue(_T("id_doctor"), strIdDoctor);
			if(strIdDoctor.IsEmpty())
			{
				strIdDoctor = _T("0");
			}
			nIdDoctor = CommonStrMethod::Str2Int(strIdDoctor);
			strIdDoctor = CommonStrMethod::Int2Str(nIdDoctor);
			hisRset.GetFieldValue(_T("id_pay"), strIdPay);
			//hisRset.GetFieldValue(_T("id_pay"), nIdPay);
			//strIdPay = CommonStrMethod::Int2Str(nIdPay);
			hisRset.GetFieldValue(_T("pay_flag"), strPayFlag);
			nPayFlag = CommonStrMethod::Str2Int(strPayFlag);
			hisRset.GetFieldValue(_T("pay_desc"), strPayDesc);
			hisRset.GetFieldValue(_T("money"), strPayMoney);
			hisRset.GetFieldValue(_T("in_flag"), strInFlag);
			nInFlag = CommonStrMethod::Str2Int(strInFlag);

			strInsert.Format(_T("INSERT INTO HisForBjlb_Patient(serial_id,id_card,queue_num,patient_name,patient_gender,id_depart,time,id_doctor,pay_flag,id_pay,pay_desc,money,in_flag) VALUES('%s','%s','%s','%s',%d,'%s','%s',%s,%d,'%s','%s','%s',%d);"),
				strSerialId,strIdCard,strQueueNum,strPatientName,nPatientGender,
				strIdDepart,strTime,strIdDoctor == _T("0")? _T("null"):_T("'")+strIdDoctor+_T("'"),nPayFlag,strIdPay,strPayDesc,strPayMoney,nInFlag);

			try
			{
				if(!strInsert.IsEmpty())
				{
					//WriteLog::Write(strInsert);
					myDb.Execute(strInsert);
				}
				else
				{
					//WriteLog::Write(_T("Insert null"));
				}
			}
			catch (_com_error& e)
			{
				if(!m_bMyDbErr)
				{
					m_bMyDbErr = TRUE;
					CString strErr;
					strErr.Format(_T("ReadPatient:将HIS排队病人数据写入排队系统数据库时出错: %s"), e.ErrorMessage());
					WriteLog::WriteTimeErrLog(strErr);
				}

				//return FALSE;
				continue;
			}
			//m_bMyDbErr = FALSE;
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadPatient:遍历HIS排队病人数据时出错: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	try
	{
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
	}
	catch (CException* e)
	{
	}
	return TRUE;
}

BOOL CReadHis::ReadDepart()
{
	//连接HIS数据库采用ODBC，连接内部数据库采用ADO
	CADODatabase hisDb;

	//打开HIS数据库
	if(!OpenHisDb(hisDb))
	{
		return FALSE;
	}

	//打开本系统数据库
	CADODatabase myDb;
	if(!OpenMyDb(myDb))
	{
		hisDb.Close();
		return FALSE;
	}

	//获取HIS数据
	CADORecordset hisRset(&hisDb);
	try
	{
		//WriteLog::Write(_T("SELECT ID,NAME,ID_PARENT FROM HISFORBJLB_DEPART;"));
		hisRset.Open(_T("SELECT ID,NAME,ID_PARENT FROM HISFORBJLB_DEPART"));
		//if(hisRset.GetFieldCount() != 3)
		//{
		//	CString strErr;
		//	strErr.Format(_T("ReadDepart:HIS数据库部门视图表[HISFORBJLB_DEPART]的字段数目不正确: 应为3，实为%d"),hisRset.GetFieldCount());
		//	WriteLog::WriteTimeErrLog(strErr);
		//	return FALSE;
		//}
		if(hisRset.IsBOF())
		{
			hisRset.Close();
			hisDb.Close();
			myDb.Close();
			return FALSE;
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDepart:读取HIS数据库部门视图表[HISFORBJLB_DEPART]失败: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	//获取本系统数据库部门表已存在的部门ID列表
	CStringArray strArrId;
	CADORecordset myRset(&myDb);
	try
	{
		myRset.Open(_T("SELECT office_id FROM Office;"));
		for(;!myRset.IsEOF(); myRset.MoveNext())
		{
			CString strId;
			myRset.GetFieldValue((int)0, strId);
			strArrId.Add(strId);
		}
		myRset.Close();
	}
	catch (_com_error& e)
	{
		if(!m_bMyDbErr)
		{
			m_bMyDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDepart:读取排队系统数据库部门表[Office].[office_id]失败: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bMyDbErr = FALSE;

	//将HIS数据写入本系统数据库
	CString strSql;
	try
	{
		for(; !hisRset.IsEOF(); hisRset.MoveNext())
		{
			int nId,nIdParent;
			CString strId, strName, strIdParent;

			hisRset.GetFieldValue(_T("ID"), strId);
			nId = CommonStrMethod::Str2Int(strId);
			strId = CommonStrMethod::Int2Str(nId);
			hisRset.GetFieldValue(_T("NAME"), strName);
			hisRset.GetFieldValue(_T("ID_PARENT"), strIdParent);
			nIdParent = CommonStrMethod::Str2Int(strIdParent);
			strIdParent = CommonStrMethod::Int2Str(nIdParent);

			if(StringExistInStringArray(strId, strArrId))
			{
				strSql.AppendFormat(_T("UPDATE Office SET name='%s',parent_id='%s' WHERE office_id='%s';"),
					strName, strIdParent, strId);
			}
			else
			{
				strSql.AppendFormat(_T("INSERT INTO Office(office_id,name,call_name,parent_id,his_flag) VALUES('%s','%s','%s','%s',1);"),
					strId,strName,strName,strIdParent);
			}
		}
		//AfxMessageBox(strInsert);
		//WriteLog::Write(strSql);
		
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDepart:遍历部门数据时出错: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	try
	{
		myDb.Execute(strSql);
	}
	catch (_com_error& e)
	{
		//if(!m_bMyDbErr)
		//{
		//	m_bMyDbErr = TRUE;
		//	CString strErr;
		//	strErr.Format(_T("ReadDepart:将HIS部门数据写入排队系统数据库时出错: %s"), e.ErrorMessage());
		//	WriteLog::WriteTimeErrLog(strErr);
		//}
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bMyDbErr = FALSE;

	try
	{
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
	}
	catch (CException* e)
	{
	}

	return TRUE;
}

BOOL CReadHis::ReadClinic()
{
	//连接HIS数据库采用ODBC，连接内部数据库采用ADO
	CADODatabase hisDb;

	//打开HIS数据库
	if(!OpenHisDb(hisDb))
	{
		return FALSE;
	}

	//打开本系统数据库
	CADODatabase myDb;
	if(!OpenMyDb(myDb))
	{
		hisDb.Close();
		return FALSE;
	}

	//获取HIS数据
	CADORecordset hisRset(&hisDb);
	try
	{
		//WriteLog::Write(_T("SELECT ID,NAME,POSITION,ID_DEPART FROM HISFORBJLB_CLINIC;"));
		hisRset.Open(_T("SELECT ID,NAME,POSITION,ID_DEPART FROM HISFORBJLB_CLINIC"));
		//if(hisRset.GetFieldCount() != 4)
		//{
		//	CString strErr;
		//	strErr.Format(_T("ReadClinic:HIS数据库诊室视图表[HISFORBJLB_CLINIC]的字段数目不正确: 应为4，实为%d"),hisRset.GetFieldCount());
		//	WriteLog::WriteTimeErrLog(strErr);
		//	return FALSE;
		//}
		if(hisRset.IsBOF())
		{
			hisRset.Close();
			hisDb.Close();
			myDb.Close();
			return FALSE;
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadClinic:读取HIS数据库诊室视图表[HISFORBJLB_CLINIC]失败: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	//获取本系统数据库部门表已存在的部门ID列表
	CStringArray strArrId;
	CADORecordset myRset(&myDb);
	try
	{
		myRset.Open(_T("SELECT consult_id FROM Consult;"));
		for(;!myRset.IsEOF(); myRset.MoveNext())
		{
			CString strId;
			myRset.GetFieldValue((int)0, strId);
			strArrId.Add(strId);
		}
		myRset.Close();
	}
	catch (_com_error& e)
	{
		if(!m_bMyDbErr)
		{
			m_bMyDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadClinic:读取排队系统数据库诊室表[Consult].[consult_id]失败: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bMyDbErr = FALSE;

	//将HIS数据写入本系统数据库
	CString strSql;
	try
	{
		for(; !hisRset.IsEOF(); hisRset.MoveNext())
		{
			CString strId,strName,strPosition;
			int nIdDepart;

			hisRset.GetFieldValue(_T("ID"), strId);
			hisRset.GetFieldValue(_T("NAME"), strName);
			hisRset.GetFieldValue(_T("POSITION"), strPosition);
			hisRset.GetFieldValue(_T("ID_DEPART"), nIdDepart);

			if(StringExistInStringArray(strId, strArrId))
			{
				strSql.AppendFormat(_T("UPDATE Consult SET name='%s',position='%s',office_id='%d' WHERE consult_id='%s';"),
					strName, strPosition, nIdDepart, strId);
			}
			else
			{
				strSql.AppendFormat(_T("INSERT INTO Consult(consult_id,name,call_name,position,office_id,his_flag) VALUES('%s','%s','%s','%s','%d',1);"),
					strId, strName, strName, strPosition, nIdDepart);
			}
		}
		//AfxMessageBox(strInsert);
		//WriteLog::Write(strSql);
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadClinic:遍历HIS诊室数据时出错: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	try
	{
		myDb.Execute(strSql);
	}
	catch (_com_error& e)
	{
		if(!m_bMyDbErr)
		{
			m_bMyDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadClinic:将HIS诊室数据写入排队系统数据库时出错: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bMyDbErr = FALSE;

	try
	{
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
	}
	catch (CException* e)
	{
	}

	return TRUE;
}

BOOL CReadHis::ReadDoctor()
{
	//连接HIS数据库采用ODBC，连接内部数据库采用ADO
	CADODatabase hisDb;

	//打开HIS数据库
	if(!OpenHisDb(hisDb))
	{
		return FALSE;
	}

	//打开本系统数据库
	CADODatabase myDb;
	if(!OpenMyDb(myDb))
	{
		hisDb.Close();
		return FALSE;
	}

	//获取HIS数据
	CADORecordset hisRset(&hisDb);
	try
	{
		//WriteLog::Write(_T("SELECT ID,NAME,GENDER,TITLE,EXPERT_FLAG,ID_DEPART,ID_CLINIC FROM HISFORBJLB_DOCTOR;"));
		hisRset.Open(_T("SELECT ID,NAME,GENDER,TITLE,EXPERT_FLAG,ID_DEPART,ID_CLINIC FROM HISFORBJLB_DOCTOR"));
		//if(hisRset.GetFieldCount() != 7)
		//{
		//	CString strErr;
		//	strErr.Format(_T("ReadDoctor:HIS数据库医生视图表[HISFORBJLB_DOCTOR]的字段数目不正确: 应为7，实为%d"),hisRset.GetFieldCount());
		//	WriteLog::WriteTimeErrLog(strErr);
		//	return FALSE;
		//}
		if(hisRset.IsBOF())
		{
			hisRset.Close();
			hisDb.Close();
			myDb.Close();
			return FALSE;
		}
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDoctor:读取HIS数据库医生视图表[HISFORBJLB_DOCTOR]失败: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	//获取本系统数据库部门表已存在的部门ID列表
	CStringArray strArrId;
	CADORecordset myRset(&myDb);
	try
	{
		myRset.Open(_T("SELECT doctor_id FROM Doctor;"));
		for(;!myRset.IsEOF(); myRset.MoveNext())
		{
			CString strId;
			myRset.GetFieldValue((int)0, strId);
			strArrId.Add(strId);
		}
		myRset.Close();
	}
	catch (_com_error& e)
	{
		if(!m_bMyDbErr)
		{
			m_bMyDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDoctor:读取排队系统数据库医生表[Doctor].[doctor_id]失败: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bMyDbErr = FALSE;

	//将HIS数据写入本系统数据库
	CString strSql;
	try
	{
		for(; !hisRset.IsEOF(); hisRset.MoveNext())
		{
			CString strId,strName,strTitle,strIdClinic, strGender,strExpertFlag, strIdDepart;
			int nId, nGender,nExpertFlag,nIdDepart;
//ID,NAME,GENDER,TITLE,EXPERT_FLAG,ID_DEPART,ID_CLINIC
			hisRset.GetFieldValue(_T("ID"), strId);
			nId = CommonStrMethod::Str2Int(strId);
			strId = CommonStrMethod::Int2Str(nId);
			hisRset.GetFieldValue(_T("NAME"), strName);
			hisRset.GetFieldValue(_T("GENDER"), strGender);
			nGender = CommonStrMethod::Str2Int(strGender);
			hisRset.GetFieldValue(_T("TITLE"), strTitle);
			hisRset.GetFieldValue(_T("EXPERT_FLAG"), strExpertFlag);
			nExpertFlag = CommonStrMethod::Str2Int(strExpertFlag);
			hisRset.GetFieldValue(_T("ID_DEPART"), strIdDepart);
			nIdDepart = CommonStrMethod::Str2Int(strIdDepart);
			strIdDepart = CommonStrMethod::Int2Str(nIdDepart);
			hisRset.GetFieldValue(_T("ID_CLINIC"), strIdClinic);

			if(StringExistInStringArray(strId, strArrId))
			{
				strSql.AppendFormat(_T("UPDATE Doctor SET name='%s',gender=%d,title='%s',expert_flag=%d,office_id='%s' WHERE doctor_id='%s';"),
					strName, nGender, strTitle, nExpertFlag, strIdDepart, strId);
			}
			else
			{
				strSql.AppendFormat(_T("INSERT INTO Doctor(doctor_id,name,gender,title,expert_flag,office_id,consult_id,password,his_flag) VALUES('%s','%s',%d,'%s',%d,'%s','%s','123',1);"),
					strId, strName, nGender, strTitle, nExpertFlag, strIdDepart, strIdClinic);
			}
		}
		//WriteLog::Write(strSql);
		
	}
	catch (_com_error& e)
	{
		if(!m_bHisDbErr)
		{
			m_bHisDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("ReadDoctor:遍历HIS医生数据时出错: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bHisDbErr = FALSE;

	try
	{
		myDb.Execute(strSql);
	}
	catch (_com_error& e)
	{
		//if(!m_bMyDbErr)
		//{
		//	m_bMyDbErr = TRUE;
		//	CString strErr;
		//	strErr.Format(_T("ReadDoctor:将HIS医生数据写入排队系统数据库时出错: %s"), e.ErrorMessage());
		//	WriteLog::WriteTimeErrLog(strErr);
		//}
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
		return FALSE;
	}
	//m_bMyDbErr = FALSE;

	try
	{
		myRset.Close();
		hisRset.Close();
		hisDb.Close();
		myDb.Close();
	}
	catch (CException* e)
	{
	}

	return TRUE;
}

BOOL CReadHis::AutoDeletePatient()
{
	CADODatabase myDb;
	static BOOL bDbErr = FALSE;
	if(!OpenMyDb(myDb))
	{
		if(!bDbErr)
		{
			bDbErr = TRUE;
			WriteLog::WriteTimeErrLog(_T("AutoDeletePatient:定时删除排队系统数据库[HisForBjlb_Patient]时出错:打开数据库失败"));
		}
		return FALSE;
	}
	CString strDel;
	//strDel.Format(_T("DELETE FROM HisForBjlb_Patient WHERE time < DATEADD(day,-%d,getdate())"), m_nHisDays + 1);
	strDel.Format(_T("DELETE FROM HisForBjlb_Patient WHERE time < CONVERT(varchar(100), DATEADD(day,-%d,getdate()), 23)"), m_nHisDays + 1);
	try
	{
		myDb.Execute(strDel);
		myDb.Close();
	}
	catch (_com_error& e)
	{
		if(!bDbErr)
		{
			bDbErr = TRUE;
			CString strErr;
			strErr.Format(_T("AutoDeletePatient:定时删除排队系统数据库[HisForBjlb_Patient]时出错: %s"), e.ErrorMessage());
			WriteLog::WriteTimeErrLog(strErr);
		}
		myDb.Close();
		return FALSE;
	}

	return TRUE;
}

BOOL CReadHis::StringExistInStringArray(CString str, CStringArray& arr)
{
	if(arr.IsEmpty()) return FALSE;
	for(int i = 0; i < arr.GetCount(); i++)
	{
		if(arr[i].Compare(str) == 0)
		{
			return TRUE;
		}
	}
	return FALSE;
}


// CReadHis 成员函数
