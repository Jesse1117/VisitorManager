#pragma once
//#include "../NurseStation/BaseConfig.h"
#include "afxwin.h"
#include "resource.h"

// CPropConnectToMyDbDlg �Ի���

class CPropConnectToMyDbDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CPropConnectToMyDbDlg)

public:
	CPropConnectToMyDbDlg();
	virtual ~CPropConnectToMyDbDlg();

// �Ի�������
	enum { IDD = IDD_PROP_LOCAL_DB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnApply();

	virtual BOOL OnInitDialog();

	CString m_strUID;
	CString m_strPWD;
	CString m_strHostIP;
	afx_msg void OnEnChangeEditMyaccount();
	afx_msg void OnEnChangeEditMypass();
	afx_msg void OnEnChangeEditMyip();
	afx_msg void OnBnClickedButton1();
};
