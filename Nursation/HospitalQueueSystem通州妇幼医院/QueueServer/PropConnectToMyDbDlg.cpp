// PropConnectToHisSet.cpp : ʵ���ļ�
//

#include "stdafx.h"
//#include "NurseStation.h"
#include "PropConnectToMyDbDlg.h"
#include "../NurseStation/CommonStrMethod.h"


// CPropConnectToMyDbDlg �Ի���

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


// CPropConnectToMyDbDlg ��Ϣ�������

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
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CPropConnectToMyDbDlg::OnEnChangeEditMyaccount()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	SetModified();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CPropConnectToMyDbDlg::OnEnChangeEditMypass()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	SetModified();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CPropConnectToMyDbDlg::OnEnChangeEditMyip()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�
	SetModified();
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

BOOL CPropConnectToMyDbDlg::OnApply()
{
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
