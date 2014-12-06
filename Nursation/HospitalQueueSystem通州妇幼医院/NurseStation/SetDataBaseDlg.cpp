// SetDataBaseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NurseStation.h"
#include "SetDataBaseDlg.h"


// CSetDataBaseDlg 对话框

IMPLEMENT_DYNAMIC(CSetDataBaseDlg, CDialog)

CSetDataBaseDlg::CSetDataBaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSetDataBaseDlg::IDD, pParent)
	, m_set_account(_T(""))
	, m_set_pass(_T(""))
	, m_set_serverip(_T(""))
	, m_selectbase(0)
{

}

CSetDataBaseDlg::~CSetDataBaseDlg()
{
}

void CSetDataBaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ED_SETACCOUNT, m_set_account);
	DDX_Text(pDX, IDC_ED_SETPASS, m_set_pass);
	DDX_Text(pDX, IDC_ED_SETSERVERIP, m_set_serverip);
	DDX_Radio(pDX, IDC_RADIO_ORACLE, m_selectbase);
}


BEGIN_MESSAGE_MAP(CSetDataBaseDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CSetDataBaseDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CSetDataBaseDlg 消息处理程序

BOOL CSetDataBaseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_set_account=m_baseconfig.GetServerAcount();
	m_set_pass=m_baseconfig.GetServerPassword();
	m_set_serverip=m_baseconfig.GetServerIP();
	m_set_database=m_baseconfig.GetDataDrive();
	if(m_set_database==_T("SQL Server"))
	{
		m_selectbase=1;
	}
	if(m_set_database==_T("Oracle"))
	{
		m_selectbase=0;
	}
	if(m_set_database==_T("MySQL"))
	{
		m_selectbase=2;
	}
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CSetDataBaseDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	m_baseconfig.SetServerAcount(m_set_account);
	m_baseconfig.SetServerIP(m_set_serverip);
	m_baseconfig.SetServerPassword(m_set_pass);
	CString name=_T("");
	if(m_selectbase==0)
	{
		name=_T("Oracle");
	}
	else if(m_selectbase==1)
	{
		name=_T("SQL Server");
	}
	else if(m_selectbase==2)
	{
		name=_T("MySQL");
	}
	m_baseconfig.SetDataDrive(name);
	m_baseconfig.Save();
	OnOK();
}
