// PropConnectToHisSet.cpp : 实现文件
//

#include "stdafx.h"
//#include "NurseStation.h"
#include "PropConnectToMyDbDlg.h"
#include "../NurseStation/CommonStrMethod.h"


// CPropConnectToMyDbDlg 对话框

IMPLEMENT_DYNAMIC(CPropConnectToMyDbDlg, CPropertyPage)

CPropConnectToMyDbDlg::CPropConnectToMyDbDlg()
	: CPropertyPage(CPropConnectToMyDbDlg::IDD)
	, m_strUID(_T(""))
	, m_strPWD(_T(""))
	, m_strHostIP(_T(""))
{

}

CPropConnectToMyDbDlg::~CPropConnectToMyDbDlg()
{
}

void CPropConnectToMyDbDlg::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UID, m_strUID);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPWD);
	DDX_Text(pDX, IDC_EDIT_HOST, m_strHostIP);
}


BEGIN_MESSAGE_MAP(CPropConnectToMyDbDlg, CPropertyPage)
	ON_EN_CHANGE(IDC_EDIT_UID, &CPropConnectToMyDbDlg::OnEnChangeEditMyaccount)
	ON_EN_CHANGE(IDC_EDIT_PWD, &CPropConnectToMyDbDlg::OnEnChangeEditMypass)
	ON_EN_CHANGE(IDC_EDIT_HOST, &CPropConnectToMyDbDlg::OnEnChangeEditMyip)
	ON_BN_CLICKED(IDC_BUTTON1, &CPropConnectToMyDbDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CPropConnectToMyDbDlg 消息处理程序

BOOL CPropConnectToMyDbDlg::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	//
	m_strUID = CommonStrMethod::GetPrivateProfileStringMy(
		_T("conn"), _T("UID"), _T("sa"), _T("\\SYS\\mydb.ini"));
	m_strPWD = CommonStrMethod::GetPrivateProfileStringMy(
		_T("conn"), _T("PWD"), _T("123456"), _T("\\SYS\\mydb.ini"));
	m_strHostIP = CommonStrMethod::GetPrivateProfileStringMy(
		_T("conn"), _T("SERVER"), _T("127.0.0.1"), _T("\\SYS\\mydb.ini"));

	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CPropConnectToMyDbDlg::OnEnChangeEditMyaccount()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	SetModified();
	// TODO:  在此添加控件通知处理程序代码
}

void CPropConnectToMyDbDlg::OnEnChangeEditMypass()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	SetModified();
	// TODO:  在此添加控件通知处理程序代码
}

void CPropConnectToMyDbDlg::OnEnChangeEditMyip()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	SetModified();
	// TODO:  在此添加控件通知处理程序代码
}

BOOL CPropConnectToMyDbDlg::OnApply()
{
	// TODO: 在此添加专用代码和/或调用基类
	UpdateData();

	CommonStrMethod::WritePrivateProfileStringMy(
		_T("conn"), _T("UID"), m_strUID, _T("\\SYS\\mydb.ini"));
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("conn"), _T("SERVER"), m_strHostIP, _T("\\SYS\\mydb.ini"));
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("conn"), _T("PWD"), m_strPWD, _T("\\SYS\\mydb.ini"));

	return CPropertyPage::OnApply();
}


void CPropConnectToMyDbDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}
