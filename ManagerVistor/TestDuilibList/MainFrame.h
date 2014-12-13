#pragma once

class CMainFrame : public WindowImplBase,public IListCallbackUI
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
	void InitWindow();//���ظ��ຯ��

	void Notify(TNotifyUI& msg);

	void OnSearch();

	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//�ص�����,�μ�CListUIԴ��
	LPCTSTR GetItemText(CControlUI* pControl, int iIndex, int iSubItem);
protected:
	CDuiString m_strXMLName;    // XML������
	CControlUI* m_pCloseBtn;
	CControlUI* m_pMinBtn;
	CControlUI* m_pMaxBtn;
	CControlUI* m_pSearch;
//	CControlUI* m_pRestoreBtn;
};
