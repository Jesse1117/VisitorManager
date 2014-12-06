// DoctorCallerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DoctorCaller.h"
#include "DoctorCallerDlg.h"
#include "Logindlg.h"
//#include "..\NurseStation\SocketServer.h"
//#include "..\NurseStation\SocketClient.h"
#include "../NurseStation/CommonStrMethod.h"
#include "../NurseStation/MyPort.h"
#include "../NurseStation/WriteLog.h"
//#include <Mmsystem.h>
//#pragma comment(lib, "WINMM.LIB")
#include "DownDiscardListDlg.h"

//////	��Ϣ����	//////////////////////
#define WM_MY_TRAYICON		(WM_USER+1)
///////////////////////////////////////////

#define TIMERID_UPDATE_PATIENT		1

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CDoctorCallerDlg �Ի���

CDoctorCallerDlg::CDoctorCallerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDoctorCallerDlg::IDD, pParent)
	, m_nEveryoneItem(-2)
	, m_bHaveCall(FALSE)
	, m_bHaveWait(FALSE)
	, m_pSoundThread(NULL)
	, m_pDoctorController(NULL)
	, m_bCanRefrush(TRUE)
	, m_pDownDiscardListDlg(NULL)
	, m_bReInlineDlg(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_strWavLibPath = CommonStrMethod::GetModuleDir() + _T("wavlib\\");

	//m_pSoundThread = AfxBeginThread(SoundThread, this);
}

void CDoctorCallerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PATIENT, m_lstPatientList);
	DDX_Control(pDX, IDC_BUTTON_CALL, m_btnCall);
	DDX_Control(pDX, IDC_BUTTON_RECALL, m_btnRecall);
	DDX_Control(pDX, IDC_BUTTON_DISCARD, m_btnDiscard);
	DDX_Control(pDX, IDC_BUTTON_WAIT, m_btnWait);
	//DDX_Control(pDX, IDC_BUTTON_WELCOME, m_btnWelcome);
	//DDX_Control(pDX, IDC_BUTTON_EVALUATE, m_btnEvaluate);
	//DDX_Control(pDX, IDC_BUTTON_THANKS, m_btnThanks);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, m_btnPause);
	//DDX_Control(pDX, IDC_STATIC_GREET, m_stDocName);
	//DDX_Control(pDX, IDC_STATIC_CURRENT_PATIENT, m_stCurPatient);
	//DDX_Control(pDX, IDC_STATIC_PATIENT_NAME, m_stCurPatientName);
	//DDX_Control(pDX, IDC_STATIC_NUMBER, m_staNum);
	DDX_Control(pDX, IDC_BUTTON_CHAT, m_btnChat);
	DDX_Control(pDX, IDC_STATIC_OPT_STATUS, m_stOptStatus);
}

BEGIN_MESSAGE_MAP(CDoctorCallerDlg, CDialog) 
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CALL, &CDoctorCallerDlg::OnBnClickedButtonCall)
	ON_BN_CLICKED(IDC_BUTTON_RECALL, &CDoctorCallerDlg::OnBnClickedButtonRecall)
	ON_BN_CLICKED(IDC_BUTTON_DISCARD, &CDoctorCallerDlg::OnBnClickedButtonDiscard)
	ON_BN_CLICKED(IDC_BUTTON_WAIT, &CDoctorCallerDlg::OnBnClickedButtonWait)
	ON_BN_CLICKED(IDC_BUTTON_WELCOME, &CDoctorCallerDlg::OnBnClickedButtonWelcome)
	ON_BN_CLICKED(IDC_BUTTON_EVALUATE, &CDoctorCallerDlg::OnBnClickedButtonEvaluate)
	ON_BN_CLICKED(IDC_BUTTON_THANKS, &CDoctorCallerDlg::OnBnClickedButtonThanks)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CDoctorCallerDlg::OnBnClickedButtonPause)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(WM_MY_TRAYICON, OnTrayIcon)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_SUBMENU_DISPLAY, &CDoctorCallerDlg::OnSubmenuDisplay)
	ON_COMMAND(ID_SUBMENU_QUIT, &CDoctorCallerDlg::OnSubmenuQuit)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PATIENT, &CDoctorCallerDlg::OnNMRClickListPatient)
	ON_COMMAND(ID_MENUITEM_DOCCALL, &CDoctorCallerDlg::OnMenuitemDoccall)
	ON_COMMAND(ID_MENUITEM_DOCWAIT, &CDoctorCallerDlg::OnMenuitemDocwait)
	ON_BN_CLICKED(IDC_BUTTON_CHAT, &CDoctorCallerDlg::OnBnClickedButtonChat)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_REFLUSH, &CDoctorCallerDlg::OnBnClickedButtonReflush)
	ON_BN_CLICKED(IDC_BUTTON_DONE_AND_DISCARD, &CDoctorCallerDlg::OnBnClickedButtonDoneAndDiscard)
END_MESSAGE_MAP()


// CDoctorCallerDlg ��Ϣ�������

BOOL CDoctorCallerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	// 
	AddTrayIcon();

	//Init Patient ListCtrl 
	m_lstPatientList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	//m_lstPatientList.DeleteAllItems();

	CRect rect;
	m_lstPatientList.GetClientRect(&rect);
	//while(m_lstPatientList.DeleteColumn(0));
	//m_lstPatientList.InsertColumn(0, _T("���"), LVCFMT_CENTER, rect.Width()/100.0*20);
	//m_lstPatientList.InsertColumn(1, _T("�ź�"), LVCFMT_CENTER, rect.Width()/100.0*25);
	//m_lstPatientList.InsertColumn(2, _T("����"), LVCFMT_CENTER, rect.Width()/100.0*35);
	//m_lstPatientList.InsertColumn(3, _T("״̬"), LVCFMT_CENTER, rect.Width()/100.0*20);
	m_lstPatientList.InsertColumn(0, _T("����"), LVCFMT_CENTER, rect.Width()/100.0*30);
	m_lstPatientList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width()/100.0*40);
	m_lstPatientList.InsertColumn(2, _T("״̬"), LVCFMT_CENTER, rect.Width()/100.0*20);

	m_lstPatientList.SetHeaderFontHW(18,9);
	m_lstPatientList.SetFontHW(16,8);

	CLoginDlg* pLoginDlg = ((CDoctorCallerApp*)AfxGetApp())->GetLoginDlg();

	//InitCtrls();

	//::SetWindowLong(m_pDoctorController->GetChat()->m_hWnd, GWL_STYLE, 
	//	::GetWindowLong(m_pDoctorController->GetChat()->m_hWnd, GWL_STYLE) & ~WS_BORDER);

	//::SetWindowLong(m_pDoctorController->GetChat()->m_hWnd, GWL_STYLE, 
	//	::GetWindowLong(m_pDoctorController->GetChat()->m_hWnd, GWL_STYLE) & ~WS_CAPTION);
	//::SetWindowLong(m_pDoctorController->GetChat()->m_hWnd, GWL_STYLE, 
	//	::GetWindowLong(m_pDoctorController->GetChat()->m_hWnd, GWL_EXSTYLE) & ~(WS_EX_WINDOWEDGE & WS_EX_DLGMODALFRAME));
	m_pDoctorController = new CDoctorController(this);
	m_pDoctorController->SetUserId(pLoginDlg->GetUserId());
	m_pDoctorController->SetUserName(pLoginDlg->GetUserName());
	m_pDoctorController->SetUserType(pLoginDlg->GetUserType());
	m_pDoctorController->SetOffices(pLoginDlg->GetOffices());
	m_pDoctorController->SetNurseSock(pLoginDlg->GetPNurseSock());
	m_pDoctorController->SetCallSpecial(pLoginDlg->GetCallSpecial());
	delete pLoginDlg;

	CString strTitle;
	strTitle.Format(_T("%s"), m_pDoctorController->GetUserName());
	SetWindowText(strTitle);

	m_pDoctorController->StartControl();

	int iScreenX = ::GetSystemMetrics(SM_CXSCREEN);
	int iScreenY = ::GetSystemMetrics(SM_CYSCREEN);

	GetWindowRect(&rect);

	::SetWindowPos(this->m_hWnd, HWND_TOPMOST, iScreenX - rect.Width(), 
		30, rect.Width(), rect.Height(), NULL);

	GetWindowRect(&rect);

	CRect rectChat;
	CDialog* pChatDlg = m_pDoctorController->GetChat();
	pChatDlg->GetWindowRect(&rectChat);

	pChatDlg->SetWindowPos(this, iScreenX - rectChat.Width(), 
		rect.bottom, rectChat.Width(), rectChat.Height(), NULL);

	//m_pDoctorController->MoveChatControls();
	//m_pDoctorController->ShowChat();

	//SetTimer(TIMERID_UPDATE_PATIENT, 5000, NULL);

	OnUpdatePatient();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CDoctorCallerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDoctorCallerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CDoctorCallerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CDoctorCallerDlg::OnBnClickedButtonCall()
{
	//if(SendCmd(dcCmdResume))
	//{
	//	m_btnPause.SetWindowText(_T("��ͣ"));
	//}
	SendCmd(dcCmdCall);
}

void CDoctorCallerDlg::OnBnClickedButtonRecall()
{
	//if(SendCmd(dcCmdResume))
	//{
	//	m_btnPause.SetWindowText(_T("��ͣ"));
	//}
	SendCmd(dcCmdRecall);
}

void CDoctorCallerDlg::OnBnClickedButtonDiscard()
{
	//if(SendCmd(dcCmdResume))
	//{
	//	m_btnPause.SetWindowText(_T("��ͣ"));
	//}
	SendCmd(dcCmdDiscard);
}

void CDoctorCallerDlg::OnBnClickedButtonWait()
{
	//if(SendCmd(dcCmdResume))
	//{
	//	m_btnPause.SetWindowText(_T("��ͣ"));
	//}
	SendCmd(dcCmdWait);
}

void CDoctorCallerDlg::OnBnClickedButtonWelcome()
{
	//MessageBox(_T("���ã��ܸ���Ϊ������"));
	SoundAdd(_T("welcome"));
}

void CDoctorCallerDlg::OnBnClickedButtonEvaluate()
{
	//MessageBox(_T("����Ϊ�ҵķ���������ۣ�"));
	SoundAdd(_T("evaluate"));
	SendCmd(dcCmdEva);
	//srand(time(NULL));
	//SendEvaluate((EvaluateLevelEnum)(rand()%4+1));
}

void CDoctorCallerDlg::OnBnClickedButtonThanks()
{
	//MessageBox(_T("лл��"));
	SoundAdd(_T("thanks"));
}

void CDoctorCallerDlg::OnBnClickedButtonPause()
{
	CString str;
	m_btnPause.GetWindowText(str);
	//if(str.Compare(MAKEINTRESOURCE(IDS_STRING_PAUSE)) == 0)
	if(str.Compare(_T("��ͣ")) == 0)
	{
		if(SendCmd(dcCmdPause))
		{
			//m_btnPause.SetWindowText(MAKEINTRESOURCE(IDS_STRING_RESUME));
			m_btnPause.SetWindowText(_T("�ָ�"));
		}
	}
	else
	{
		if(SendCmd(dcCmdResume))
		{
			//m_btnPause.SetWindowText(MAKEINTRESOURCE(IDS_STRING_PAUSE));
			m_btnPause.SetWindowText(_T("��ͣ"));
		}
	}
	//SendCmd(dcCmdPause);
}

HBRUSH CDoctorCallerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	//if(pWnd->GetDlgCtrlID() == IDC_EDIT_CHATREC && nCtlColor == CTLCOLOR_EDIT )

	switch(pWnd->GetDlgCtrlID())
	{
	case IDC_STATIC_OPT_STATUS:
		{
			if(m_bOptStatusSuccess)
			{
				pDC->SetTextColor(0xFF0000);
			}
			else
			{
				pDC->SetTextColor(0x0000FF);
			}
		}
		break;
	//case IDC_STATIC_CURRENT_PATIENT:
	//	{
	//		COLORREF clr = 0x4DB34D;
	//		pDC->SetTextColor(clr);
	//	}
	//	break;
	//case IDC_STATIC_PATIENT_NAME:
	//	{
	//		COLORREF clr = 0x0000FF;
	//		pDC->SetTextColor(clr);
	//	}
	//	break;
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

LRESULT CDoctorCallerDlg::DefWindowProc(UINT message, 
										WPARAM wParam, 
										LPARAM lParam) 
{
	LONG lRes = CDialog::DefWindowProc(message, wParam, lParam);
	switch(message)
	{
	case WM_SYSCOMMAND:
		if(wParam == SC_MINIMIZE)
		{
			ShowWindow(SW_HIDE);
			//ShowTip();
		}
		break;
	}
	return lRes;
}

BOOL CDoctorCallerDlg::TaskBarAddIcon(HWND hwnd, 
									  UINT uID, 
									  HICON hIcon, 
									  LPCWSTR lpszTip)
{
	BOOL res;
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = uID;
	nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_INFO;
	nid.uCallbackMessage = WM_MY_TRAYICON;
	nid.hIcon = hIcon;
	if (lpszTip)
	{
		lstrcpyn(nid.szTip, lpszTip, sizeof(nid.szTip));
	}
	else
	{
		nid.szTip[0] = '\0';
	}
	res = Shell_NotifyIcon(NIM_ADD, &nid);

	if (hIcon)
	{
		DestroyIcon(hIcon);
	}
	return res;
}

void CDoctorCallerDlg::AddTrayIcon(void)
{
	HICON hIcon = LoadIcon(AfxGetApp()->m_hInstance, 
		MAKEINTRESOURCE(IDR_MAINFRAME));
	wchar_t tip[128] = {0};
	wsprintf(tip, _T("ҽ��������"));
	TaskBarAddIcon(this->m_hWnd, IDR_MAINFRAME, hIcon, tip);
}

LRESULT CDoctorCallerDlg::OnTrayIcon(WPARAM wParam, LPARAM lParam)
{
	if(wParam != IDR_MAINFRAME)
	{
		return 1;
	}
	switch(lParam)
	{
	case WM_LBUTTONUP:
	case WM_LBUTTONDBLCLK:
		{
			this->ShowWindow(SW_SHOW);
			this->ShowWindow(SW_NORMAL);
			//this->ShowWindow(SW_SHOWNORMAL);
			//this->SetFocus();
			this->UpdateWindow();
		}
		break;
	case WM_RBUTTONUP:
		{
			SetForegroundWindow();//�����������λ�����½ǵ����˵���ʧ
			CPoint pt;
			::GetCursorPos(&pt);
			CMenu menu;
			menu.LoadMenu(IDR_MENU_ICON);
			//menu.CreatePopupMenu();
			//menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�˳�"));
			//menu.AppendMenu(MF_STRING, WM_MY_CLOSEWINDOW, _T("�˳�"));
			//menu.TrackPopupMenu(TPM_BOTTOMALIGN, pt.x, pt.y, this);
			CMenu* subMenu = menu.GetSubMenu(0);
			subMenu->TrackPopupMenu(TPM_CENTERALIGN, pt.x, pt.y, this);
			subMenu->Detach();
			subMenu->DestroyMenu();
			menu.Detach();
			menu.DestroyMenu();
		}
		break;
	}
	return 0;
}

BOOL CDoctorCallerDlg::TaskBarDeleteIcon(HWND hwnd, UINT uID)
{
	NOTIFYICONDATA nid;
	nid.cbSize = sizeof(NOTIFYICONDATA);
	nid.hWnd = hwnd;
	nid.uID = uID;
	return Shell_NotifyIcon(NIM_DELETE, &nid);
}

void CDoctorCallerDlg::RemoveTrayIcon()
{
	TaskBarDeleteIcon(this->m_hWnd, IDR_MAINFRAME);
}

void CDoctorCallerDlg::OnClose()
{
	//if(IDCANCEL == MessageBox(_T("ȷ���˳���"), _T("ҽ��������"), MB_OKCANCEL))
	//{
	//	return;
	//}
	if(!BeforeUserQuit()) return;

	CDialog::OnClose();
}

void CDoctorCallerDlg::OnDestroy()
{
	if(m_pDoctorController)
	{
		m_pDoctorController->EndControl();
		delete m_pDoctorController;
		m_pDoctorController = NULL;
	}

	RemoveTrayIcon();

	CDialog::OnDestroy();
}
/*
void CDoctorCallerDlg::OnShowPatients(LPCMDRESULT pPatients)
{
	m_lstPatientList.DeleteAllItems();
	m_mapPatientList.RemoveAll();
	m_bHaveCall = FALSE;
	m_bHaveWait = FALSE;
	//m_lstPatientList.SetTextColor(0x000000);
	CString strPatientName;
	if(pPatients->nSentCount == 0)
	{
		strPatientName = _T("�޻���");
	}
	else
	{
		for(int i = 0; i < pPatients->nSentCount; i++)
		{
			//CString strNo;
			//strNo.Format(_T("%d"), i+1);
			//m_lstPatientList.InsertItem(i, strNo);
			m_lstPatientList.SetItemTextColor(0, i, 0x000000);
			m_lstPatientList.SetItemTextColor(1, i, 0x000000);
			m_lstPatientList.SetItemTextColor(2, i, 0x000000);

			switch(pPatients->patientsArray[i].eStatus)
			{
			case qsDoing:
				{
					m_lstPatientList.SetItemTextColor(0, i, 0x006600);
					m_lstPatientList.SetItemTextColor(1, i, 0x006600);
					m_lstPatientList.SetItemTextColor(2, i, 0x006600);
					m_bHaveCall = TRUE;
					strPatientName = pPatients->patientsArray[i].wszPatientName;
				}
				break;
			case qsPrepare:
				{
					m_lstPatientList.SetItemTextColor(0, i, 0xFF6600);
					m_lstPatientList.SetItemTextColor(1, i, 0xFF6600);
					m_lstPatientList.SetItemTextColor(2, i, 0xFF6600);
					m_bHaveWait = TRUE;
				}
				break;
			default:
				;
			}
			m_lstPatientList.InsertItem(i, pPatients->patientsArray[i].wszQueueID);
			m_lstPatientList.SetItemText(i, 1, pPatients->patientsArray[i].wszPatientName);
			m_lstPatientList.SetItemText(i, 2, GetStatus(pPatients->patientsArray[i].eStatus));

			PATIENTINFO info;
			info.strQueSerialId = pPatients->patientsArray[i].wszSerialID;
			info.eStatus = pPatients->patientsArray[i].eStatus;
			m_mapPatientList[i] = info;
		}
	}

	CString strTitle;
	strTitle.Format(_T("%s ����:%d"), 
		m_pDoctorController->GetUserName(), pPatients->nPatientCount);
	SetWindowText(strTitle);
}
*/
void CDoctorCallerDlg::OnShowPatients(CADORecordset& rset)
{
	m_lstPatientList.DeleteAllItems();
	m_mapPatientList.RemoveAll();
	m_bHaveCall = FALSE;
	m_bHaveWait = FALSE;
	//m_lstPatientList.SetTextColor(0x000000);
	try
	{
		CString strTitle;
		strTitle.Format(_T("%s ����:%d"), 
			m_pDoctorController->GetUserName(), rset.GetRecordCount());
		SetWindowText(strTitle);

		for(int i = 0; !rset.IsEOF(); i++, rset.MoveNext())
		{
			//CString strNo;
			//strNo.Format(_T("%d"), i+1);
			//m_lstPatientList.InsertItem(i, strNo);
			m_lstPatientList.SetItemTextColor(0, i, 0x000000);
			m_lstPatientList.SetItemTextColor(1, i, 0x000000);
			m_lstPatientList.SetItemTextColor(2, i, 0x000000);

			CString strSerialId, strQueueNum, strPatientName;
			int nStatus, nGender;
			rset.GetFieldValue(_T("log_id"), strSerialId);
			rset.GetFieldValue(_T("queue_id_call"), strQueueNum);
			rset.GetFieldValue(_T("patient_name"), strPatientName);
			rset.GetFieldValue(_T("status"), nStatus);
			rset.GetFieldValue(_T("patient_gender"), nGender);

			switch((QueueStatusEnum)nStatus)
			{
			case qsDoing:
				{
					m_lstPatientList.SetItemTextColor(0, i, 0x006600);
					m_lstPatientList.SetItemTextColor(1, i, 0x006600);
					m_lstPatientList.SetItemTextColor(2, i, 0x006600);
					m_bHaveCall = TRUE;
				}
				break;
			case qsPrepare:
				{
					m_lstPatientList.SetItemTextColor(0, i, 0xFF6600);
					m_lstPatientList.SetItemTextColor(1, i, 0xFF6600);
					m_lstPatientList.SetItemTextColor(2, i, 0xFF6600);
					m_bHaveWait = TRUE;
				}
				break;
			default:
				;
			}
			m_lstPatientList.InsertItem(i, strQueueNum);
			m_lstPatientList.SetItemText(i, 1, strPatientName);
			m_lstPatientList.SetItemText(i, 2, GetStatus((QueueStatusEnum)nStatus));

			PATIENTINFO info;
			info.strQueSerialId = strSerialId;
			info.eStatus = (QueueStatusEnum)nStatus;
			m_mapPatientList[i] = info;
		}
	}
	catch (_com_error& e)
	{
	}
}

BOOL CDoctorCallerDlg::SendCmd(DoctorCmdEnum eDoctorCmdEnum, CString strQueSerialId)
{
	if(!m_pDoctorController) return FALSE;
	return m_pDoctorController->SendCmd(eDoctorCmdEnum, strQueSerialId);
}

//BOOL CDoctorCallerDlg::UserQuit()
//{
//	//
//	//int nRetainCall = IDNO, nRetainWait = IDNO;
//	//if(m_bHaveCall)
//	//{
//	//	nRetainCall = MessageBox(_T("�Ƿ�����ǰ���л��ߣ�\r\nѡ\"��\",�����µ�¼ʱ�ɼ�������û���\r\nѡ\"��\",��û�������ɾ���"), _T("ע��"), MB_YESNOCANCEL);
//	//}
//	//if(IDCANCEL == nRetainCall) return FALSE;
//	//if(m_bHaveWait)
//	//{
//	//	nRetainWait = MessageBox(_T("�Ƿ����ȴ����ߣ�\r\nѡ\"��\",�����µ�¼ʱ���øû��߼����������ȴ�\r\nѡ\"��\",��û��߽����·����Ŷӿ���ǰ��"), _T("ע��"), MB_YESNOCANCEL);
//	//}
//	//if(IDCANCEL == nRetainWait) return FALSE;
//
//	//::KillTimer(this->m_hWnd, TIMERID_SEND_HEARTBEAT);
//	//::KillTimer(this->m_hWnd, TIMERID_UPDATE_USER);
//	//if(nRetainCall == IDYES && nRetainWait == IDYES)
//	//{
//	//	SendUserQuit(EXITCODE_UPDATE_NONE);
//	//}
//	//else if(nRetainCall == IDYES && nRetainWait == IDNO)
//	//{
//	//	SendUserQuit(EXITCODE_UPDATE_WAIT);
//	//}
//	//else if(nRetainCall == IDNO && nRetainWait == IDYES)
//	//{
//	//	SendUserQuit(EXITCODE_UPDATE_CALL);
//	//}
//	//else
//	//{
//	//	SendUserQuit(EXITCODE_UPDATE_ALL);
//	//}
//	SendUserQuit(EXITCODE_UPDATE_ALL);
//
//	//SocketClose();
//	return TRUE;
//}

BOOL  CDoctorCallerDlg::BeforeUserQuit()
{
	//
	int nUpdateCall = IDNO, nRetainWait = IDNO;
	if(m_bHaveCall)
	{
		nUpdateCall = MessageBox(_T("��ǰ�����Ƿ���ɾ��"), _T("ҽ��������"), MB_YESNOCANCEL);
	}
	if(IDCANCEL == nUpdateCall) return FALSE;
	if(m_bHaveWait)
	{
		nRetainWait = MessageBox(_T("�Ƿ����ȴ����ߣ�"), _T("ҽ��������"), MB_YESNOCANCEL);
	}
	if(IDCANCEL == nRetainWait) return FALSE;
	if(!m_bHaveCall && !m_bHaveWait)
	{
		if(IDCANCEL == MessageBox(_T("ȷ���˳���"), _T("ҽ��������"), MB_OKCANCEL))
		{
			return FALSE;
		}
		nUpdateCall = IDNO;
		nRetainWait = IDYES;
	}

	//::KillTimer(this->m_hWnd, TIMERID_SEND_HEARTBEAT);
	//::KillTimer(this->m_hWnd, TIMERID_UPDATE_USER);

	if(nUpdateCall == IDNO && nRetainWait == IDYES)
	{
		m_pDoctorController->SetExitCode(EXITCODE_UPDATE_NONE);
	}
	else if(nUpdateCall == IDNO && nRetainWait == IDNO)
	{
		m_pDoctorController->SetExitCode(EXITCODE_UPDATE_WAIT);
	}
	else if(nUpdateCall == IDYES && nRetainWait == IDYES)
	{
		m_pDoctorController->SetExitCode(EXITCODE_UPDATE_CALL);
	}
	else if(nUpdateCall == IDYES && nRetainWait == IDNO)
	{
		m_pDoctorController->SetExitCode(EXITCODE_UPDATE_ALL);
	}

	return TRUE;
}

void CDoctorCallerDlg::OnSubmenuDisplay()
{
	this->ShowWindow(SW_SHOW);
	this->ShowWindow(SW_NORMAL);
	this->UpdateWindow();
}

void CDoctorCallerDlg::OnSubmenuQuit()
{
	OnClose();
}
/*
void CDoctorCallerDlg::InitCtrls()
{
	//Init Patient ListCtrl 
	m_lstPatientList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lstPatientList.DeleteAllItems();

	CRect rect;
	m_lstPatientList.GetClientRect(&rect);
	while(m_lstPatientList.DeleteColumn(0));
	//m_lstPatientList.InsertColumn(0, _T("���"), LVCFMT_CENTER, rect.Width()/100.0*20);
	//m_lstPatientList.InsertColumn(1, _T("�ź�"), LVCFMT_CENTER, rect.Width()/100.0*25);
	//m_lstPatientList.InsertColumn(2, _T("����"), LVCFMT_CENTER, rect.Width()/100.0*35);
	//m_lstPatientList.InsertColumn(3, _T("״̬"), LVCFMT_CENTER, rect.Width()/100.0*20);
	m_lstPatientList.InsertColumn(0, _T("�ź�"), LVCFMT_CENTER, rect.Width()/100.0*30);
	m_lstPatientList.InsertColumn(1, _T("����"), LVCFMT_CENTER, rect.Width()/100.0*45);
	m_lstPatientList.InsertColumn(2, _T("״̬"), LVCFMT_CENTER, rect.Width()/100.0*16);

	m_lstPatientList.SetHeaderFontHW(18,9);
	m_lstPatientList.SetFontHW(16,8);

	//Set font
	//CFont font;
	//font.CreatePointFont(120, _T("����"));
	//m_stCurPatientName.SetFont(&font);
	//m_stCurPatient.SetFont(&font);
	//m_staNum.SetFont(&font);

	//m_btnCall.SetFont(&font);
	//m_btnRecall.SetFont(&font);
	//m_btnDiscard.SetFont(&font);
	//m_btnWait.SetFont(&font);
	//m_btnWelcome.SetFont(&font);
	//m_btnEvaluate.SetFont(&font);
	//m_btnThanks.SetFont(&font);
	//m_btnPause.SetFont(&font);
	//m_btnChat.SetFont(&font);

	//m_stDocName.SetWindowText(m_pDoctorController->GetUserName());
}
*/
UINT CDoctorCallerDlg::SoundThread(LPVOID pParam)
{
	CDoctorCallerDlg* pThis = (CDoctorCallerDlg*)pParam;
	pThis->m_bSoundThread = TRUE;

	while(pThis->m_bSoundThread)
	{
		if(pThis->m_lstStr.IsEmpty())
		{
			//Sleep(20);
			if(pThis->m_pSoundThread)
			{
				SuspendThread(pThis->m_pSoundThread->m_hThread);
			}
		}
		else
		{
			pThis->m_Mutex.Lock();
			CString str = pThis->m_lstStr.GetHead();
			pThis->m_lstStr.RemoveHead();
			pThis->m_Mutex.Unlock();
			//::sndPlaySound(pThis->m_strWavLibPath + str + _T(".wav"), SND_NODEFAULT | SND_SYNC);
		}
	}

	return TRUE;
}

void CDoctorCallerDlg::StopSoundThread()
{
	m_bSoundThread = FALSE;
}

void CDoctorCallerDlg::SoundAdd(CString str)
{
	m_Mutex.Lock();
	if(!m_lstStr.IsEmpty())
	{
		if(str.Compare(m_lstStr.GetTail()) == 0)
		{
			m_Mutex.Unlock();
			return;
		}
	}
	m_lstStr.AddTail(str);
	m_Mutex.Unlock();
	if(m_pSoundThread)
	{
		for(;m_pSoundThread->ResumeThread(););
	}
}

void CDoctorCallerDlg::OnNMRClickListPatient(NMHDR *pNMHDR, LRESULT *pResult)
{
	//if(!m_bCallSpecial)
	//{
	//	return;
	//}

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if(pNMItemActivate->iItem == -1) return;

	CMenu menu;
	menu.LoadMenu(IDR_MENU_DOCCMD);
	CMenu* pMenu = menu.GetSubMenu(0);
	m_lstPatientList.ClientToScreen(&pNMItemActivate->ptAction);

	switch(m_mapPatientList[pNMItemActivate->iItem].eStatus)
	{
	case qsDoing:
		{
			pMenu->EnableMenuItem(ID_MENUITEM_DOCCALL, MF_GRAYED);
			pMenu->EnableMenuItem(ID_MENUITEM_DOCWAIT, MF_GRAYED);
		}
		break;
	case qsPrepare:
		{
			pMenu->EnableMenuItem(ID_MENUITEM_DOCWAIT, MF_GRAYED);
		}
		break;
	case qsInLine:
		{
		}
		break;
	}
	if(m_pDoctorController && !m_pDoctorController->GetCallSpecial())
	{
		pMenu->EnableMenuItem(ID_MENUITEM_DOCCALL, MF_GRAYED);
		pMenu->EnableMenuItem(ID_MENUITEM_DOCWAIT, MF_GRAYED);
	}
	m_bCanRefrush = FALSE;
	pMenu->TrackPopupMenu(TPM_LEFTBUTTON, 
		pNMItemActivate->ptAction.x, pNMItemActivate->ptAction.y, this);
	pMenu->Detach();
	pMenu->DestroyMenu();
	menu.Detach();
	menu.DestroyMenu();
	m_bCanRefrush = TRUE;

	*pResult = 0;
}

int CDoctorCallerDlg::GetCurSel()
{
	int nSel = -1;
	POSITION pos = m_lstPatientList.GetFirstSelectedItemPosition();
	if(pos)
	{
		nSel = m_lstPatientList.GetNextSelectedItem(pos);
	}

	return nSel;
}

void CDoctorCallerDlg::OnMenuitemDoccall()
{
	int nSel = GetCurSel();
	if(nSel != -1)
	{
		SendCmd(dcCmdCall, m_mapPatientList[nSel].strQueSerialId);
	}
}

void CDoctorCallerDlg::OnMenuitemDocwait()
{
	int nSel = GetCurSel();
	if(nSel != -1)
	{
		SendCmd(dcCmdWait, m_mapPatientList[nSel].strQueSerialId);
	}
}

void CDoctorCallerDlg::OnBnClickedButtonChat()
{
	if(!m_pDoctorController) return;
	m_pDoctorController->ShowOrHideChat();
}

CString CDoctorCallerDlg::GetStatus(QueueStatusEnum qs)
{
	switch(qs)
	{
	case qsDoing:
		return _T("����");
	case qsPrepare:
		return _T("׼��");
	case qsInLine:
		return _T("�Ŷ�");
	case qsDone:
		return _T("���");
	case qsDiscard:
		return _T("����");
	default:
		return _T("");
	}
}


void CDoctorCallerDlg::OnTimer(UINT_PTR nIDEvent)
{
	switch(nIDEvent)
	{
	case TIMERID_UPDATE_PATIENT:
		{
			//OnUpdatePatient();
		}
		break;
	}

	CDialog::OnTimer(nIDEvent);
}

void CDoctorCallerDlg::OnUpdatePatient()
{
	if(!m_bCanRefrush) return;
	if(!m_pDoctorController) return;
	try
	{
		CADODatabase db;
		db.SetConnectionString(m_pDoctorController->m_strConn);
		db.Open();
		CADORecordset rset(&db);
		//ˢ�²�������
		rset.Open(m_pDoctorController->m_strSelect, CADORecordset::openQuery);
		OnShowPatients(rset);
		rset.Close();
		db.Close();
	}
	catch (_com_error& e)
	{
		CString strErr;
		strErr.Format(_T("CDoctorCallerDlg::OnUpdatePatient: %s"), e.ErrorMessage());
		WriteLog::WriteDbErrLog(strErr);
		return;
	}
}

void CDoctorCallerDlg::OnBnClickedButtonReflush()
{
	OnUpdatePatient();
}

void CDoctorCallerDlg::SetOptStatus(DoctorCmdEnum eDocCmd, BOOL bSuccess)
{
	m_stOptStatus.SetWindowText(_T(""));
	CString strStatus;
	switch(eDocCmd)
	{
	case dcCmdCall:
		{
			strStatus = _T("���в���");
		}
		break;
	case dcCmdWait:
		{
			strStatus = _T("׼������");
		}
		break;
	case dcCmdDiscard:
		{
			strStatus = _T("���Ų���");
		}
		break;
	case dcCmdRecall:
		{
			strStatus = _T("�غ�����");
		}
		break;
	case dcCmdPause:
		{
			strStatus = _T("��ͣ����");
		}
		break;
	case dcCmdResume:
		{
			strStatus = _T("�ָ�����");
		}
		break;
	default:
		{
			strStatus = _T("");
		}
	}
	if(strStatus.IsEmpty()) return;
	if(bSuccess)
	{
		strStatus += _T("�ɹ�");
	}
	else
	{
		strStatus += _T("ʧ��");
	}
	m_bOptStatusSuccess = bSuccess;
	m_stOptStatus.SetWindowText(strStatus);
}

void CDoctorCallerDlg::OnBnClickedButtonDoneAndDiscard()
{
	//CDownDiscardListDlg dlg(this);
	//dlg.DoModal();
	if(!m_bReInlineDlg)
	{
		m_pDownDiscardListDlg = new CDownDiscardListDlg(this);
		m_pDownDiscardListDlg->Create(CDownDiscardListDlg::IDD, this);
		m_bReInlineDlg = TRUE;
	}
	m_pDownDiscardListDlg->ShowWindow(SW_NORMAL);
}
