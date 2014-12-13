#pragma once


class CPage1 : public CNotifyPump
{
public:
	CPage1();
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);

	DUI_DECLARE_MESSAGE_MAP()
		virtual void OnClick(TNotifyUI& msg);
	virtual void OnSelectChanged( TNotifyUI &msg );
	virtual void OnItemClick( TNotifyUI &msg );
private:
	CPaintManagerUI* m_pPaintManager;
};


//////////////////////////////////////////////////////////////////////////
///

class CPage2 : public CNotifyPump
{
public:
	CPage2();
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);

	DUI_DECLARE_MESSAGE_MAP()
		virtual void OnClick(TNotifyUI& msg);
	virtual void OnSelectChanged( TNotifyUI &msg );
	virtual void OnItemClick( TNotifyUI &msg );
private:
	CPaintManagerUI* m_pPaintManager;
};

class CRichListWnd : public WindowImplBase
{
public:
	CRichListWnd(void);
	~CRichListWnd(void);
	virtual void OnFinalMessage( HWND hWnd );
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual UILIB_RESOURCETYPE GetResourceType() const;
	virtual CDuiString GetZIPFileName() const;
	virtual LPCTSTR GetWindowClassName( void ) const;
	DUI_DECLARE_MESSAGE_MAP()
private:
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;
	CPage1 m_Page1;
	CPage2 m_Page2;
};
