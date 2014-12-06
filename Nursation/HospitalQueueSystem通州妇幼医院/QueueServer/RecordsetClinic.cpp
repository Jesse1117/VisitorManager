// RecordsetClinic.h : CRecordsetClinic ���ʵ��



// CRecordsetClinic ʵ��

// ���������� 2014��7��18��, 16:56

#include "stdafx.h"
#include "RecordsetClinic.h"
IMPLEMENT_DYNAMIC(CRecordsetClinic, CRecordset)

CRecordsetClinic::CRecordsetClinic(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = "";
	m_NAME = "";
	m_POSITION = "";
	m_ID_DEPART = 0;
	m_nFields = 4;
	//m_nDefaultType = dynaset;
	m_nDefaultType = forwardOnly;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetClinic::GetDefaultConnect()
{
	return _T("DSN=NurseHisDb;UID=hisforbjlb;PWD=bjlb2014;DBQ=NURSEHISDB ;DBA=W;APA=T;EXC=F;FEN=T;QTO=T;FRC=10;FDL=10;LOB=T;RST=T;BTD=F;BNF=F;BAM=IfAllSuccessful;NUM=NLS;DPM=F;MTS=T;MDI=F;CSR=F;FWC=F;FBS=64000;TLO=O;MLD=0;ODA=F;");
}

CString CRecordsetClinic::GetDefaultSQL()
{
	return _T("[HISFORBJLB].[HISFORBJLB_CLINIC]");
}

void CRecordsetClinic::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Text(pFX, _T("[POSITION]"), m_POSITION);
	//RFX_Text(pFX, _T("[ID_DEPART]"), m_ID_DEPART);
	RFX_Double(pFX, _T("[ID_DEPART]"), m_ID_DEPART);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetClinic ���

#ifdef _DEBUG
void CRecordsetClinic::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetClinic::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


