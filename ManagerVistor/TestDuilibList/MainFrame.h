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
	void InitWindow();//重载父类函数

	void Notify(TNotifyUI& msg);

	void OnSearch();

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
protected:
	CDuiString m_strXMLName;    // XML的名字
	CControlUI* m_pCloseBtn;
	CControlUI* m_pMinBtn;
	CControlUI* m_pMaxBtn;
	CControlUI* m_pSearch;
//	CControlUI* m_pRestoreBtn;
};
