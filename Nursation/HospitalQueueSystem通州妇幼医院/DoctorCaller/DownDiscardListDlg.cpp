// DownDiscardListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "DoctorCaller.h"
#include "DownDiscardListDlg.h"
#include "../NurseStation/WriteLog.h"
#include "../NurseStation/NurseDef.h"

// CDownDiscardListDlg 对话框

IMPLEMENT_DYNAMIC(CDownDiscardListDlg, CDialog)

CDownDiscardListDlg::CDownDiscardListDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDownDiscardListDlg::IDD, pParent)
{

}

CDownDiscardListDlg::~CDownDiscardListDlg()
{
}

void CDownDiscardListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PATIENT, m_lstPatientList);
	DDX_Control(pDX, IDC_STATIC_OPT_STATUS, m_stOptStatus);
}


BEGIN_MESSAGE_MAP(CDownDiscardListDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REFLUSH, &CDownDiscardListDlg::OnBnClickedButtonReflush)
	ON_COMMAND(ID_REINLINE, &CDownDiscardListDlg::OnReinline)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PATIENT, &CDownDiscardListDlg::OnNMRClickListPatient)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CDownDiscardListDlg 消息处理程序

BOOL CDownDiscardListDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	CRect rectParent;
	m_pParentWnd->GetWindowRect(&rectParent);

	CRect rect;
	GetWindowRect(&rect);

	int iScreenX = ::GetSystemMetrics(SM_CXSCREEN);
	int iScreenY = ::GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(m_pParentWnd, rectParent.left - rect.Width(), 
		rectParent.top, rect.Width(), rect.Height(), NULL);

	m_lstPatientList.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);

	m_lstPatientList.GetClientRect(&rect);
	m_lstPatientList.InsertColumn(0, _T("排号"), LVCFMT_CENTER, rect.Width()/100.0*30);
	m_lstPatientList.InsertColumn(1, _T("姓名"), LVCFMT_CENTER, rect.Width()/100.0*40);
	m_lstPatientList.InsertColumn(2, _T("状态"), LVCFMT_CENTER, rect.Width()/100.0*20);

	m_lstPatientList.SetHeaderFontHW(18,9);
	m_lstPatientList.SetFontHW(16,8);

	OnUpdatePatient();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDownDiscardListDlg::OnBnClickedButtonReflush()
{
	OnUpdatePatient();
}

void CDownDiscardListDlg::OnUpdatePatient()
{
	try
	{
		CADODatabase db;
		db.SetConnectionString(((CDoctorCallerDlg*)m_pParentWnd)->m_pDoctorController->m_strConn);
		db.Open();
		CADORecordset rset(&db);
		//刷新病人数据
		rset.Open(((CDoctorCallerDlg*)m_pParentWnd)->m_pDoctorController->m_strSelectDoneDiscard, CADORecordset::openQuery);
		OnShowPatients(rset);
		rset.Close();
		db.Close();
	}
	catch (_com_error& e)
	{
		CString strErr;
		strErr.Format(_T("CDownDiscardListDlg::OnUpdatePatient: %s"), e.ErrorMessage());
		WriteLog::WriteDbErrLog(strErr);
		return;
	}
}

void CDownDiscardListDlg::OnShowPatients(CADORecordset& rset)
{
	m_lstPatientList.DeleteAllItems();
	m_mapPatientList.RemoveAll();
	try
	{
		for(int i = 0; !rset.IsEOF(); i++, rset.MoveNext())
		{
			//m_lstPatientList.SetItemTextColor(0, i, 0x000000);
			//m_lstPatientList.SetItemTextColor(1, i, 0x000000);
			//m_lstPatientList.SetItemTextColor(2, i, 0x000000);

			CString strSerialId, strQueueNum, strPatientName;
			int nStatus, nGender;
			rset.GetFieldValue(_T("log_id"), strSerialId);
			rset.GetFieldValue(_T("queue_id_call"), strQueueNum);
			rset.GetFieldValue(_T("patient_name"), strPatientName);
			rset.GetFieldValue(_T("status"), nStatus);
			rset.GetFieldValue(_T("patient_gender"), nGender);
			/*
			switch((QueueStatusEnum)nStatus)
			{
			case qsDoing:
				{
					m_lstPatientList.SetItemTextColor(0, i, 0x006600);
					m_lstPatientList.SetItemTextColor(1, i, 0x006600);
					m_lstPatientList.SetItemTextColor(2, i, 0x006600);
				}
				break;
			case qsPrepare:
				{
					m_lstPatientList.SetItemTextColor(0, i, 0xFF6600);
					m_lstPatientList.SetItemTextColor(1, i, 0xFF6600);
					m_lstPatientList.SetItemTextColor(2, i, 0xFF6600);
				}
				break;
			default:
				;
			}
			*/
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

CString CDownDiscardListDlg::GetStatus(QueueStatusEnum qs)
{
	switch(qs)
	{
	case qsDone:
		return _T("完成");
	case qsDiscard:
		return _T("过号");
	case qsDoing:
		return _T("就诊");
	case qsPrepare:
		return _T("准备");
	case qsInLine:
		return _T("排队");
	default:
		return _T("");
	}
}

void CDownDiscardListDlg::OnReinline()
{
	m_stOptStatus.SetWindowText(_T(""));
	int nSel = -1;
	POSITION pos = m_lstPatientList.GetFirstSelectedItemPosition();
	if(pos)
	{
		nSel = m_lstPatientList.GetNextSelectedItem(pos);
	}
	if(nSel == -1) return;
	try
	{
		CADODatabase db;
		db.SetConnectionString(((CDoctorCallerDlg*)m_pParentWnd)->m_pDoctorController->m_strConn);
		db.Open();
		
		CString strUpdate;
		strUpdate.Format(_T("update queue set status=%d,priority=%d where log_id='%s';"),
			qsInLine, priThree, m_mapPatientList[nSel].strQueSerialId);

		db.Execute(strUpdate);
		db.Close();
		m_bOptStatusSuccess = TRUE;
		m_stOptStatus.SetWindowText(_T("召回操作成功"));
	}
	catch (_com_error& e)
	{
		m_bOptStatusSuccess = FALSE;
		m_stOptStatus.SetWindowText(_T("召回操作失败"));
		CString strErr;
		strErr.Format(_T("CDownDiscardListDlg::OnReinline: %s"), e.ErrorMessage());
		WriteLog::WriteDbErrLog(strErr);
		return;
	}

	OnUpdatePatient();
	((CDoctorCallerDlg*)m_pParentWnd)->OnUpdatePatient();
}

void CDownDiscardListDlg::OnNMRClickListPatient(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if(pNMItemActivate->iItem == -1) return;

	CMenu menu;
	menu.LoadMenu(IDR_MENU_REINLINE);
	CMenu* pMenu = menu.GetSubMenu(0);
	m_lstPatientList.ClientToScreen(&pNMItemActivate->ptAction);
	pMenu->TrackPopupMenu(TPM_LEFTBUTTON, 
		pNMItemActivate->ptAction.x, pNMItemActivate->ptAction.y, this);
	pMenu->Detach();
	pMenu->DestroyMenu();
	menu.Detach();
	menu.DestroyMenu();

	*pResult = 0;
}

HBRUSH CDownDiscardListDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

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
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

void CDownDiscardListDlg::OnDestroy()
{
	CDialog::OnDestroy();

	((CDoctorCallerDlg*)m_pParentWnd)->m_bReInlineDlg = FALSE;
}
