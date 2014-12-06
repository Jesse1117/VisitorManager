// RecordsetPatient.h : CRecordsetPatient 类的实现



// CRecordsetPatient 实现

// 代码生成在 2014年7月18日, 8:26

#include "stdafx.h"
#include "RecordsetPatient.h"
IMPLEMENT_DYNAMIC(CRecordsetPatient, CRecordset)

CRecordsetPatient::CRecordsetPatient(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_SERIAL_ID = "";
	m_ID_CARD = "";
	m_QUEUE_NUM = 0.0;
	m_PATIENT_NAME = "";
	m_PATIENT_GENDER = 0.0;
	m_ID_DEPART = 0.0;
	m_TIME;
	m_ID_DOCTOR = "";
	m_PAY_FLAG = 0.0;
	m_PAY_DESC = "";
	m_PAY_MONEY = "";
	m_nFields = 11;
	//m_nDefaultType = dynaset;
	m_nDefaultType = forwardOnly;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CRecordsetPatient::GetDefaultConnect()
{
	return _T("DSN=NurseHisDb;UID=hisforbjlb;PWD=bjlb2014;DBQ=NURSEHISDB ;DBA=W;APA=T;EXC=F;FEN=T;QTO=T;FRC=10;FDL=10;LOB=T;RST=T;BTD=F;BNF=F;BAM=IfAllSuccessful;NUM=NLS;DPM=F;MTS=T;MDI=F;CSR=F;FWC=F;FBS=64000;TLO=O;MLD=0;ODA=F;");
}

CString CRecordsetPatient::GetDefaultSQL()
{
	return _T("[HISFORBJLB].[HISFORBJLB_PATIENT]");
}

void CRecordsetPatient::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[SERIAL_ID]"), m_SERIAL_ID);
	RFX_Text(pFX, _T("[ID_CARD]"), m_ID_CARD);
	RFX_Double(pFX, _T("[QUEUE_NUM]"), m_QUEUE_NUM);
	RFX_Text(pFX, _T("[PATIENT_NAME]"), m_PATIENT_NAME);
	RFX_Double(pFX, _T("[PATIENT_GENDER]"), m_PATIENT_GENDER);
	RFX_Double(pFX, _T("[ID_DEPART]"), m_ID_DEPART);
	RFX_Date(pFX, _T("[TIME]"), m_TIME);
	RFX_Text(pFX, _T("[ID_DOCTOR]"), m_ID_DOCTOR);
	RFX_Double(pFX, _T("[PAY_FLAG]"), m_PAY_FLAG);
	RFX_Text(pFX, _T("[PAY_DESC]"), m_PAY_DESC);
	RFX_Text(pFX, _T("[MONEY]"), m_PAY_MONEY);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetPatient 诊断

#ifdef _DEBUG
void CRecordsetPatient::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetPatient::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


