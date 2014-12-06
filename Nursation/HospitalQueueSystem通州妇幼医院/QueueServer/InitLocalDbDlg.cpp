// InitLocalDbDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QueueServer.h"
#include "InitLocalDbDlg.h"
#include "../NurseStation/ado2.h"


// CInitLocalDbDlg 对话框

IMPLEMENT_DYNAMIC(CInitLocalDbDlg, CDialog)

CInitLocalDbDlg::CInitLocalDbDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInitLocalDbDlg::IDD, pParent)
	, m_strUID(_T(""))
	, m_strPWD(_T(""))
	, m_strHostIP(_T(""))
{

}

CInitLocalDbDlg::~CInitLocalDbDlg()
{
}

void CInitLocalDbDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UID, m_strUID);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPWD);
	DDX_Text(pDX, IDC_EDIT_HOST, m_strHostIP);
}


BEGIN_MESSAGE_MAP(CInitLocalDbDlg, CDialog)

	ON_BN_CLICKED(IDOK, &CInitLocalDbDlg::OnBnClickedOk)
END_MESSAGE_MAP()



BOOL CInitLocalDbDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_strHostIP = _T("127.0.0.1");
	m_strUID = _T("sa");
	m_strPWD = _T("123456");

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CInitLocalDbDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	CString strConn;
	strConn.Format(_T("Driver={SQL Server};Server=%s;Uid=%s;Pwd=%s;Database=master;"),
		m_strHostIP, m_strUID, m_strPWD);

	CADODatabase myDb;
	try
	{
		myDb.Open(strConn);
	}
	catch (_com_error& e)
	{
		CString strErr;
		strErr.Format(_T("初始化失败：无法连接到SQL Server数据库: %s"), e.ErrorMessage());
		MessageBox(strErr, _T("初始化数据库"));
		return;
	}
	CFile file;
	if(!file.Open(_T("nurse.sql"), CFile::modeRead))
	{
		MessageBox(_T("初始化失败：nurse.sql文件缺失"), _T("初始化数据库"));
		return;
	}

	MessageBox(_T("初始化数据库成功"), _T("初始化数据库"));
	OnOK();
}
