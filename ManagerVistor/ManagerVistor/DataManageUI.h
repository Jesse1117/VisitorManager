#pragma once

class CDataManageUI :
	public CContainerUI
	, public IDialogBuilderCallback
{
public:
	CDataManageUI(CPaintManagerUI* pManager);
	~CDataManageUI(void);

	CControlUI* CreateControl( LPCTSTR pstrClassName );
protected:
	CPaintManagerUI* m_pManager;
};
