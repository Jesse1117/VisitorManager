// RecordsetDoctor.h : CRecordsetDoctor ���ʵ��



// CRecordsetDoctor ʵ��

// ���������� 2014��7��18��, 16:57

#include "stdafx.h"
#include "RecordsetDoctor.h"
IMPLEMENT_DYNAMIC(CRecordsetDoctor, CRecordset)

CRecordsetDoctor::CRecordsetDoctor(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = "";
	m_NAME = "";
	m_GENDER = 0.0;
	m_TITLE = "";
	m_EXPERT_FLAG = 0.0;
	m_ID_DEPART = 0;
	m_ID_CLINIC = "";
	m_nFields = 7;
	//m_nDefaultType = dynaset;
	m_nDefaultType = forwardOnly;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetDoctor::GetDefaultConnect()
{
	return _T("DSN=NurseHisDb;UID=hisforbjlb;PWD=bjlb2014;DBQ=NURSEHISDB ;DBA=W;APA=T;EXC=F;FEN=T;QTO=T;FRC=10;FDL=10;LOB=T;RST=T;BTD=F;BNF=F;BAM=IfAllSuccessful;NUM=NLS;DPM=F;MTS=T;MDI=F;CSR=F;FWC=F;FBS=64000;TLO=O;MLD=0;ODA=F;");
}

CString CRecordsetDoctor::GetDefaultSQL()
{
	return _T("[HISFORBJLB].[HISFORBJLB_DOCTOR]");
}

void CRecordsetDoctor::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Double(pFX, _T("[GENDER]"), m_GENDER);
	RFX_Text(pFX, _T("[TITLE]"), m_TITLE);
	RFX_Double(pFX, _T("[EXPERT_FLAG]"), m_EXPERT_FLAG);
	RFX_Double(pFX, _T("[ID_DEPART]"), m_ID_DEPART);
	RFX_Text(pFX, _T("[ID_CLINIC]"), m_ID_CLINIC);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetDoctor ���

#ifdef _DEBUG
void CRecordsetDoctor::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetDoctor::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


