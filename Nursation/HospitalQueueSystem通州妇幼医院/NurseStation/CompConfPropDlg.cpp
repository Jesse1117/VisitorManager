// CompConfPropDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "NurseStation.h"
#include "CompConfPropDlg.h"
#include "CommonStrMethod.h"


// CCompConfPropDlg 对话框

//IMPLEMENT_DYNAMIC(CCompConfPropDlg, CPropertyPage)
IMPLEMENT_DYNAMIC(CCompConfPropDlg, CDialog)

//CCompConfPropDlg::CCompConfPropDlg()
	//: CPropertyPage(CCompConfPropDlg::IDD)
CCompConfPropDlg::CCompConfPropDlg(CWnd* pParent)
	: CDialog(CCompConfPropDlg::IDD,  pParent)
	, m_strTimes(_T(""))
	, m_strPageItemCount(_T(""))
	, m_strSwitchPageTime(_T(""))
	, m_strShowCallTime(_T(""))
	, m_nRadioDisableTakingNum(0)
	, m_strRefreshTime(_T(""))
	, m_strDataDays(_T(""))
	, m_nReadIn(0)
	, m_nShowType(0)
	, m_strPageColCount(_T(""))
{

}

CCompConfPropDlg::~CCompConfPropDlg()
{
}

void CCompConfPropDlg::DoDataExchange(CDataExchange* pDX)
{
	//CPropertyPage::DoDataExchange(pDX);
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_TIMES, m_strTimes);
	DDX_Text(pDX, IDC_EDIT_ITEMCOUNT, m_strPageItemCount);
	DDX_Text(pDX, IDC_EDIT_SWITCH_MINUTE, m_strSwitchPageTime);
	DDX_Text(pDX, IDC_EDIT_SHOW_CALL_MINUTE, m_strShowCallTime);
	DDX_Control(pDX, IDC_BUTTON_OK, m_btnOk);
	DDX_Radio(pDX, IDC_RADIO_DISABLE_TAKING, m_nRadioDisableTakingNum);
	DDX_Text(pDX, IDC_EDIT_REFRESH_TIME, m_strRefreshTime);
	DDX_Text(pDX, IDC_EDIT_DATA_DAYS, m_strDataDays);
	DDX_Radio(pDX, IDC_RADIO_READ_IN, m_nReadIn);
	DDX_Radio(pDX, IDC_RADIO_SHOW_ROW, m_nShowType);
	DDX_Control(pDX, IDC_CHECK_SHOW_NUM, m_ckShowQueueNum);
	DDX_Control(pDX, IDC_CHECK_SWITCH_PAGE, m_ckSwitchPage);
	DDX_Text(pDX, IDC_EDIT_PAGE_COL_COUNT, m_strPageColCount);
	DDX_Control(pDX, IDC_CHECK_SHOW_LINE_NUM, m_ckShowLineNum);
}


//BEGIN_MESSAGE_MAP(CCompConfPropDlg, CPropertyPage)
BEGIN_MESSAGE_MAP(CCompConfPropDlg, CDialog)
	ON_EN_CHANGE(IDC_EDIT_TIMES, &CCompConfPropDlg::OnEnChangeEditTimes)
	ON_EN_CHANGE(IDC_EDIT_ITEMCOUNT, &CCompConfPropDlg::OnEnChangeEditItemcount)
	ON_EN_CHANGE(IDC_EDIT_SWITCH_MINUTE, &CCompConfPropDlg::OnEnChangeEditSwitchMinute)
	ON_EN_CHANGE(IDC_EDIT_SHOW_CALL_MINUTE, &CCompConfPropDlg::OnEnChangeEditShowCallMinute)
	ON_BN_CLICKED(IDC_BUTTON_OK, &CCompConfPropDlg::OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CCompConfPropDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


BOOL CCompConfPropDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CString strPath = CommonStrMethod::GetModuleDir() + _T("sys\\sysconfig.ini");

	m_strTimes = CommonStrMethod::GetPrivateProfileStringMy(
		_T("sys"),_T("SOUND_REPLAY_TIMES"), _T("1"), strPath);
	m_strPageItemCount = CommonStrMethod::GetPrivateProfileStringMy(
		_T("sys"),_T("PAGE_ITEM_COUNT"), _T("8"), strPath);
	m_strSwitchPageTime = CommonStrMethod::GetPrivateProfileStringMy(
		_T("sys"),_T("PAGE_SWITCH_TIME"), _T("8"), strPath);
	m_strShowCallTime = CommonStrMethod::GetPrivateProfileStringMy(
		_T("sys"),_T("SHOW_CALL_TIME"), _T("8"), strPath);

	m_nRadioDisableTakingNum = CommonStrMethod::GetPrivateProfileIntMy(
		_T("sys"), _T("ENABLE_TAKING_NUM"), 0, strPath);

	m_strRefreshTime = CommonStrMethod::GetPrivateProfileStringMy(
		_T("time"),_T("FLUSHTIMESEC"),_T("30"),strPath);

	m_strDataDays = CommonStrMethod::GetPrivateProfileStringMy(
		_T("sys"), _T("DATA_DAYS"), _T("0"), strPath);

	m_nReadIn = CommonStrMethod::GetPrivateProfileIntMy(
		_T("sys"), _T("READ_INPATIENT"), 0, strPath);

	m_nShowType = CommonStrMethod::GetPrivateProfileIntMy(
		_T("sys"), _T("SHOW_TYPE"), 0, strPath);

	int nShowQueueNum = CommonStrMethod::GetPrivateProfileIntMy(
		_T("sys"), _T("SHOW_QUEUE_NUM"), 1, _T("\\SYS\\sysconfig.ini"));
	if(nShowQueueNum)
	{
		m_ckShowQueueNum.SetCheck(BST_CHECKED);
	}
	else
	{
		m_ckShowQueueNum.SetCheck(BST_UNCHECKED);
	}

	int nSwitchPage = CommonStrMethod::GetPrivateProfileIntMy(
		_T("sys"), _T("SWITCH_PAGE"), 1, _T("\\SYS\\sysconfig.ini"));
	if(nSwitchPage)
	{
		m_ckSwitchPage.SetCheck(BST_CHECKED);
	}
	else
	{
		m_ckSwitchPage.SetCheck(BST_UNCHECKED);
	}

	m_strPageColCount = CommonStrMethod::GetPrivateProfileStringMy(
		_T("sys"), _T("PAGE_COL_COUNT"), _T("3"), strPath);

	int nShowLineNum = CommonStrMethod::GetPrivateProfileIntMy(
		_T("sys"), _T("SHOW_LINE_NUM"), 1, _T("\\SYS\\sysconfig.ini"));
	if(nShowLineNum)
	{
		m_ckShowLineNum.SetCheck(BST_CHECKED);
	}
	else
	{
		m_ckShowLineNum.SetCheck(BST_UNCHECKED);
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

// CCompConfPropDlg 消息处理程序


void CCompConfPropDlg::OnEnChangeEditTimes()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	EnableOk();
}

void CCompConfPropDlg::OnEnChangeEditItemcount()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	EnableOk();
}

void CCompConfPropDlg::OnEnChangeEditSwitchMinute()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	EnableOk();
}

void CCompConfPropDlg::OnEnChangeEditShowCallMinute()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	EnableOk();
}

//BOOL CCompConfPropDlg::OnApply()
//{
//	Save();
//	((CNurseStationApp*)AfxGetApp())->GetController()->ReLoadConf();
//	return CPropertyPage::OnApply();
//}

void CCompConfPropDlg::OnBnClickedButtonOk()
{
	Save();
	m_btnOk.EnableWindow(FALSE);
	CDialog::OnOK();
}

void CCompConfPropDlg::OnBnClickedButtonCancel()
{
	CDialog::OnCancel();
}

void CCompConfPropDlg::Save()
{
	UpdateData();

	CString strPath = CommonStrMethod::GetModuleDir() + _T("sys\\sysconfig.ini");

	if(m_strTimes.IsEmpty() || CommonStrMethod::Str2Int(m_strTimes) < 0)
	{
		m_strTimes = _T("0");
	}
	if(m_strPageItemCount.IsEmpty() || CommonStrMethod::Str2Int(m_strPageItemCount) < 1)
	{
		m_strPageItemCount = _T("8");
	}
	if(m_strSwitchPageTime.IsEmpty() || CommonStrMethod::Str2Int(m_strSwitchPageTime) < 1)
	{
		m_strSwitchPageTime = _T("8");
	}
	if(m_strShowCallTime.IsEmpty() || CommonStrMethod::Str2Int(m_strShowCallTime) < 1)
	{
		m_strShowCallTime = _T("8");
	}
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("SOUND_REPLAY_TIMES"), m_strTimes, strPath);
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("PAGE_ITEM_COUNT"), m_strPageItemCount, strPath);
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("PAGE_SWITCH_TIME"), m_strSwitchPageTime, strPath);
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("SHOW_CALL_TIME"), m_strShowCallTime, strPath);

	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("ENABLE_TAKING_NUM"), 
		CommonStrMethod::Int2Str(m_nRadioDisableTakingNum), strPath);
	((CNurseStationApp*)AfxGetApp())->m_pNurseView
		->EnableTakingNum(m_nRadioDisableTakingNum == 1 ? TRUE : FALSE);

	int nRefreshTime = CommonStrMethod::Str2Int(m_strRefreshTime);
	if(CommonStrMethod::Str2Int(m_strRefreshTime) < 0)
	{
		nRefreshTime = 0;
		m_strRefreshTime = _T("0");
	}
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("time"),_T("FLUSHTIMESEC"),m_strRefreshTime,strPath);

	theApp.m_pNurseWnd->m_fushsec=nRefreshTime;
	theApp.m_pNurseWnd->m_originFlushTime=nRefreshTime;

	int nDataDays = CommonStrMethod::Str2Int(m_strDataDays);
	if(nDataDays < 0)
	{
		nDataDays = 0;
		m_strDataDays = _T("0");
	}
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("DATA_DAYS"), m_strDataDays, strPath);
	//((CNurseStationApp*)AfxGetApp())->m_pNurseWnd->SetDataDays(nDataDays);
	//((CNurseStationApp*)AfxGetApp())->m_pNurseWnd->GetOfficeQueView()->SetDataDays(nDataDays);
	((CNurseStationApp*)AfxGetApp())->GetController()->SetDataDays(nDataDays);
	
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("READ_INPATIENT"), 
		CommonStrMethod::Int2Str(m_nReadIn), strPath);
	((CNurseStationApp*)AfxGetApp())->m_pNurseWnd->m_bReadInPatient = 1 == m_nReadIn;
	((CNurseStationApp*)AfxGetApp())->m_pNurseWnd->GetOfficeQueView()->m_bReadInPatient = 1 == m_nReadIn;

	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("SHOW_TYPE"), 
		CommonStrMethod::Int2Str(m_nShowType), strPath);

	int nShowQueNum;
	if(m_ckShowQueueNum.GetCheck() == BST_CHECKED)
	{
		nShowQueNum = 1;
	}
	else
	{
		nShowQueNum = 0;
	}
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("SHOW_QUEUE_NUM"), 
		CommonStrMethod::Int2Str(nShowQueNum),
		_T("\\SYS\\sysconfig.ini"));

	int nSwitchPage;
	if(m_ckSwitchPage.GetCheck() == BST_CHECKED)
	{
		nSwitchPage = 1;
	}
	else
	{
		nSwitchPage = 0;
	}
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("SWITCH_PAGE"), 
		CommonStrMethod::Int2Str(nSwitchPage),
		_T("\\SYS\\sysconfig.ini"));

	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("PAGE_COL_COUNT"), m_strPageColCount, strPath);

	int nShowLineNum;
	if(m_ckShowLineNum.GetCheck() == BST_CHECKED)
	{
		nShowLineNum = 1;
	}
	else
	{
		nShowLineNum = 0;
	}
	CommonStrMethod::WritePrivateProfileStringMy(
		_T("sys"), _T("SHOW_LINE_NUM"), 
		CommonStrMethod::Int2Str(nShowLineNum),
		_T("\\SYS\\sysconfig.ini"));

	((CNurseStationApp*)AfxGetApp())->GetController()->ReLoadConf();
}

void CCompConfPropDlg::EnableOk()
{
	m_btnOk.EnableWindow();
}
