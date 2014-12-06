#pragma once

// CPropSetting
#include "PropConnectToMyDbDlg.h"
#include "PropSocket.h"
#include "PropConnectToHisDbDlg.h"

class CPropSetting : public CPropertySheet
{
	DECLARE_DYNAMIC(CPropSetting)

public:
	CPropSetting(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CPropSetting(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CPropSetting();
	
protected:
	CPropConnectToMyDbDlg m_PropConnectToMyDbDlg;
	CPropSocket m_PropSocket;
	CPropConnectToHisDbDlg m_PropConnectToHisDbDlg;


	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	HICON    m_hIcon;
};


