#include "StdAfx.h"
#include "TestFrameWnd.h"


CTestFrameWnd::CTestFrameWnd(void) : m_pCloseBtn(NULL)
	,m_pMaxBtn(NULL)
	,m_pMinBtn(NULL)
	,m_pRestoreBtn(NULL)
{
}


CTestFrameWnd::~CTestFrameWnd(void)
{
}

LRESULT CTestFrameWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch(uMsg)
	{
	case WM_CREATE:
		OnCreate(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_CLOSE:
		break;
	case WM_DESTROY:
		break;
	case WM_NCACTIVATE:   
		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_NCCALCSIZE: 
		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); 
		break;
	case WM_NCPAINT:
		lRes = OnNcPaint(uMsg,wParam,lParam,bHandled);
	break;
	default:
		bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CTestFrameWnd::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LONG styleValue = ::GetWindowLong(*this,GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(this->m_hWnd,GWL_STYLE,styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);//主窗口类与窗口句柄关联
	CDialogBuilder builder;
//	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("test.xml"),(UINT)0,NULL,&m_pm);
	ASSERT(pRoot);
	m_pm.AttachDialog(pRoot);//（附加控件数据到HASH表中）
	m_pm.AddNotifier(this);//增加通知消息
	InitCaptionButton();//初始化标题栏按钮
	return 0;
	/*
	m_pm.Init(m_hWnd);

	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("test.xml"), (UINT)0, NULL, &m_pm);   // duilib.xml需要放到exe目录下
	ASSERT(pRoot && "Failed to parse XML");

	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);   // 添加控件等消息响应，这样消息就会传达到duilib的消息循环，我们可以在Notify函数里做消息处理
	return 0;
	*/
	/*
	CControlUI *pWnd = new CButtonUI;
	pWnd->SetName(_T("btnHello"));      // 设置控件的名称，这个名称用于标识每一个控件，必须唯一，相当于MFC里面的控件ID
	pWnd->SetText(_T("Hello World"));   // 设置文字
	pWnd->SetBkColor(0xFF00FF00);       // 设置背景色
	pWnd->SetFloat(true);
	RECT rc;rc.left=0;rc.right=600;rc.bottom=0;rc.top=500;
	pWnd->SetMaxHeight(800);
	pWnd->SetMaxWidth(700);
	pWnd->SetMinHeight(700);
	pWnd->SetMinWidth(600);
	*/
// 	m_pm.Init(m_hWnd);
// 	m_pm.AttachDialog(CButtonUI*(this));
// 	m_pm.AddNotifier(this);   // 添加控件等消息响应，这样消息就会传达到duilib的消息循环，我们可以在Notify函数里做消息处理
	
	return 0;
}

void CTestFrameWnd::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("windowinit") ) OnPrepare();
	else if(msg.sType == _T("click"))
	{
		if(msg.pSender == m_pCloseBtn)
		{
			PostQuitMessage(0);
			return;
		}
		else if(msg.pSender == m_pMinBtn)
		{
			SendMessage(WM_SYSCOMMAND,SC_MINIMIZE,0);
		}
		else if(msg.pSender == m_pMaxBtn)
		{
			SendMessage(WM_SYSCOMMAND,SC_MAXIMIZE,0);
		}
		else if(msg.pSender == m_pRestoreBtn)
		{
			SendMessage(WM_SYSCOMMAND,SC_RESTORE,0);
		}
	}
}

LRESULT CTestFrameWnd::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CTestFrameWnd::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

void CTestFrameWnd::InitCaptionButton()
{
	m_pCloseBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")));
	m_pMaxBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("maxbtn")));
	m_pMinBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("minbtn")));
	m_pRestoreBtn = static_cast<CButtonUI*>(m_pm.FindControl(_T("restorebtn")));
		//static_cast<CButtonUI*>(m_pm.FindControl(_T("closebtn")))
		//CButtonUI*(m_pm.FindControl(_T("closebtn")));
}

LRESULT CTestFrameWnd::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}