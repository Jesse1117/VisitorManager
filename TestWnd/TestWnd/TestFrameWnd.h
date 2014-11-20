#pragma once
#include "ControlEx.h"
class CTestFrameWnd : public CWindowWnd,public INotifyUI
{
public:
	CTestFrameWnd(void);
	~CTestFrameWnd(void);
	LPCTSTR GetWindowClassName() const {return _T("UIMainFrame");}
	UINT GetClassStyle() const {return CS_DBLCLKS;}
	void OnFinalMessage(HWND hWnd){delete this;}
	void OnPrepare(){}
	void Notify(TNotifyUI& msg);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);//消息循环
	LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClose(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& bHandled);
	LRESULT OnDestroy(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& bHandled);
	LRESULT OnSysCommand(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& bHandled);
	LRESULT OnNcHitTest(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL bHandled);
	LRESULT OnSize(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL bHandled);
	LRESULT OnGetMinMaxInfo(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL bHandled);
	void InitCaptionButton();
public:
	CPaintManagerUI m_pm;
private:
	//按钮
	CButtonUI* m_pCloseBtn;
	CButtonUI* m_pMaxBtn;
	CButtonUI* m_pRestoreBtn;
	CButtonUI* m_pMinBtn;
};

