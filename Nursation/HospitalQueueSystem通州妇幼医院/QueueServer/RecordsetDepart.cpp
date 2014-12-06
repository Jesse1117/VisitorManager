// RecordsetDepart.h : CRecordsetDepart 类的实现



// CRecordsetDepart 实现

// 代码生成在 2014年7月18日, 16:55

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
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Double(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Double(pFX, _T("[ID_PARENT]"), m_ID_PARENT);

}
/////////////////////////////////////////////////////////////////////////////
// CRecordsetDepart 诊断

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


