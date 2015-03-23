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
	void InitWindow();//���ظ��ຯ��
	void Notify(TNotifyUI& msg);
protected:
	CDuiString m_strXMLName;    // XML������
	CControlUI* m_pCloseBtn;
	CControlUI* m_pMinBtn;
	CControlUI* m_pMaxBtn;
	CControlUI* m_pRestoreBtn;

private:
	CDialogBuilder m_dlgBuilder;

	CListPlusContainerElement* m_LastElement;
};

