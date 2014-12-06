// RecordsetPatient.h : CRecordsetPatient ���ʵ��



// CRecordsetPatient ʵ��

// ���������� 2014��7��18��, 8:26

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
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
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
// CRecordsetPatient ���

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


