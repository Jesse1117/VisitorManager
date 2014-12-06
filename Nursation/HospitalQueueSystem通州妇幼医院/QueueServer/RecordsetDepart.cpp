// RecordsetDepart.h : CRecordsetDepart ���ʵ��



// CRecordsetDepart ʵ��

// ���������� 2014��7��18��, 16:55

#include "stdafx.h"
#include "RecordsetDepart.h"
IMPLEMENT_DYNAMIC(CRecordsetDepart, CRecordset)

CRecordsetDepart::CRecordsetDepart(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = 0;
	m_NAME = "";
	m_ID_PARENT = 0;
	m_nFields = 3;
	//m_nDefaultType = dynaset;
	m_nDefaultType = forwardOnly;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CRecordsetDepart::GetDefaultConnect()
{
	return _T("DSN=NurseHisDb;UID=hisforbjlb;PWD=bjlb2014;DBQ=NURSEHISDB ;DBA=W;APA=T;EXC=F;FEN=T;QTO=T;FRC=10;FDL=10;LOB=T;RST=T;BTD=F;BNF=F;BAM=IfAllSuccessful;NUM=NLS;DPM=F;MTS=T;MDI=F;CSR=F;FWC=F;FBS=64000;TLO=O;MLD=0;ODA=F;");
}

CString CRecordsetDepart::GetDefaultSQL()
{
	return _T("[HISFORBJLB].[HISFORBJLB_DEPART]");
}

void CRecordsetDepart::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Double(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Double(pFX, _T("[ID_PARENT]"), m_ID_PARENT);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetDepart ���

#ifdef _DEBUG
void CRecordsetDepart::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRecordsetDepart::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


