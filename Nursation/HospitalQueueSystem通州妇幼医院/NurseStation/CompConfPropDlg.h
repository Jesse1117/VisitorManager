#pragma once
#include "resource.h"
#include "afxwin.h"

// CCompConfPropDlg 对话框

//class CCompConfPropDlg : public CPropertyPage
class CCompConfPropDlg : public CDialog
{
	DECLARE_DYNAMIC(CCompConfPropDlg)

public:
	//CCompConfPropDlg();
	CCompConfPropDlg(CWnd* pParent = NULL);
	virtual ~CCompConfPropDlg();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_COMP_CONF };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//virtual BOOL OnApply();
	CString m_strTimes;
	virtual BOOL OnInitDialog();
	afx_msg void OnEnChangeEditTimes();
	CString m_strPageItemCount;
	CString m_strSwitchPageTime;
	CString m_strShowCallTime;
	afx_msg void OnEnChangeEditItemcount();
	afx_msg void OnEnChangeEditSwitchMinute();
	afx_msg void OnEnChangeEditShowCallMinute();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();

	void Save();
	void EnableOk();
	CButton m_btnOk;
	int m_nRadioDisableTakingNum;
	CString m_strRefreshTime;
	CString m_strDataDays;
	int m_nReadIn;
	int m_nShowType;
	CButton m_ckShowQueueNum;
	CButton m_ckSwitchPage;
	CString m_strPageColCount;
	CButton m_ckShowLineNum;
};
