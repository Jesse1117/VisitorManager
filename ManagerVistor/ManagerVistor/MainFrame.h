#pragma once

class CMainFrame : public WindowImplBase
{
public:
	explicit CMainFrame(LPCTSTR pszXMLName);
	~CMainFrame(void);
	virtual LPCTSTR GetWindowClassName() const
	{
		return _T("XMLWnd");
	}

	virtual CDuiString GetSkinFile()
	{
		return m_strXMLName;
	}

	virtual CDuiString GetSkinFolder()
	{
		return _T("");
	}
public:
	CControlUI* CreateControl( LPCTSTR pstrClassName );
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
//	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void InitWindow();//重载父类函数
	void Notify(TNotifyUI& msg);
protected:
	CDuiString m_strXMLName;    // XML的名字
	CControlUI* m_pCloseBtn;
	CControlUI* m_pMinBtn;
	CControlUI* m_pMaxBtn;
	CControlUI* m_pRestoreBtn;
private:
	//recordUI控件
	CComboUI* m_pCertiTypeCombo;
	CEditUI* m_pCertiNumEdit;
	CEditUI* m_pVistorNameEdit;
	CComboUI* m_pSexCombo;
	CEditUI* m_pCardNumEdit;
	CEditUI* m_pAddressEdit;
	CComboUI* m_pCarNumCombo;
	CEditUI* m_pCarNumEdit;
	CComboUI* m_pCarTypeCombo;
	CButtonUI* m_pAddCarTypeBtn;
	CEditUI* m_pVistorUnitEdit;
	CEditUI* m_pVistorPhoneNumEdit;
	CComboUI* m_pVistorNumCombo;
	CButtonUI* m_pAddVistorBtn;
	CDateTimeUI* m_pLeaveDate;
	CDateTimeUI* m_pLeaveTime;
	CComboUI* m_pBatchCombo;
	CButtonUI* m_pAddBatchBtn;
private:
	void InitSearchCtrl();
	void AddCertitypeMsg();
private:
	CDialogBuilder m_dlgBuilder;
	CListPlusContainerElement* m_LastElement;
};

