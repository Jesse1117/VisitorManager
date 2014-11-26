#include "StdAfx.h"
#include "MainFrame.h"
#include "ControlEx.h"
#include <string>
using namespace std;

CMainFrame::CMainFrame(void) : m_pMaxBtn(NULL)
	,m_pRestoreBtn(NULL)
	,m_pMinBtn(NULL)
	,m_pCloseBtn(NULL)
{
}


CMainFrame::~CMainFrame(void)
{
}

LRESULT CMainFrame::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*
	LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	::SetWindowLong(this->m_hWnd, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

	m_pm.Init(m_hWnd);
	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("first.xml"), (UINT)0,  NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);

	Init();
	return 0;
	*/
	
	LONG styleValue = ::GetWindowLong(*this,GWL_STYLE);
	styleValue &= ~WS_CAPTION;
	styleValue |= WS_SIZEBOX;
	::SetWindowLong(this->m_hWnd,GWL_STYLE,styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
	
	m_pm.Init(m_hWnd);//主窗口类与窗口句柄关联
	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("first.xml"),(UINT)0,&cb,&m_pm);
	ASSERT(pRoot);
	m_pm.AttachDialog(pRoot);//（附加控件数据到HASH表中）
	m_pm.AddNotifier(this);//增加通知消息
	Init();//初始化标题栏按钮
	return 0;
}

LRESULT CMainFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CMainFrame::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	bHandled = FALSE;
	::PostQuitMessage(0L);
	return 0;
}

LRESULT CMainFrame::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CMainFrame::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CMainFrame::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CMainFrame::OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	/*
	SIZE szRoundCorner = m_pm.GetRoundCorner();
	if( !::IsIconic(*this) && (szRoundCorner.cx != 0 || szRoundCorner.cy != 0) ) {
		CDuiRect rcWnd;
		::GetWindowRect(*this, &rcWnd);
		rcWnd.Offset(-rcWnd.left, -rcWnd.top);
		rcWnd.right++; rcWnd.bottom++;
		HRGN hRgn = ::CreateRoundRectRgn(rcWnd.left, rcWnd.top, rcWnd.right, rcWnd.bottom, szRoundCorner.cx, szRoundCorner.cy);
		::SetWindowRgn(*this, hRgn, TRUE);
		::DeleteObject(hRgn);
	}
	*/
	bHandled = FALSE;
	//	return CWindowWnd::HandleMessage(uMsg,wParam,lParam);
	return 0;
}

LRESULT CMainFrame::OnGetMinMaxInfo(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	MONITORINFO oMonitor = {};//
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);//显示器句柄,显示器信息
	CDuiRect rcWork = oMonitor.rcWork;
	rcWork.Offset(-oMonitor.rcMonitor.left, -oMonitor.rcMonitor.top);

	LPMINMAXINFO lpMMI = (LPMINMAXINFO) lParam;
	lpMMI->ptMaxPosition.x	= rcWork.left;
	lpMMI->ptMaxPosition.y	= rcWork.top;
	lpMMI->ptMaxSize.x		= rcWork.right;
	lpMMI->ptMaxSize.y		= rcWork.bottom;

	bHandled = FALSE;
	return 0;
}

LRESULT CMainFrame::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
// 	if( wParam == SC_CLOSE ) {
// 		::PostQuitMessage(0L);
// 		bHandled = TRUE;
// 		return 0;
// 	}
// 	BOOL bZoomed = ::IsZoomed(*this);
// 	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
// 	if( ::IsZoomed(*this) != bZoomed ) {
// 		if( !bZoomed ) {
// 			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
// 			if( pControl ) pControl->SetVisible(false);
// 			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
// 			if( pControl ) pControl->SetVisible(true);
// 		}
// 		else {
// 			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));
// 			if( pControl ) pControl->SetVisible(true);
// 			pControl = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn")));
// 			if( pControl ) pControl->SetVisible(false);
// 		}
// 	}
// 	return lRes;
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg,wParam,lParam);//先执行父窗口消息队列，处理syscommand
	if( ::IsZoomed(*this) != bZoomed )
	{
		//		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl())
		if(!bZoomed)
		{
			if(m_pMaxBtn)m_pMaxBtn->SetVisible(false);
			if(m_pRestoreBtn)m_pRestoreBtn->SetVisible(true);
		}
		else
		{
			if(m_pMaxBtn)m_pMaxBtn->SetVisible(true);
			if(m_pRestoreBtn)m_pRestoreBtn->SetVisible(false);
		}
	}
//	bHandled = FALSE;
	return lRes;
}

LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	/*
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg ) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_CLOSE:         lRes = OnClose(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
//	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_SIZE:          lRes = OnSize(uMsg, wParam, lParam, bHandled); break;
	case WM_GETMINMAXINFO: lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled); break;
	case WM_SYSCOMMAND:    lRes = OnSysCommand(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	*/
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch(uMsg)
	{
	case WM_CREATE:
		OnCreate(uMsg, wParam, lParam, bHandled); //处理窗口创建消息
		break;
	case WM_CLOSE:
		OnClose(uMsg,wParam,lParam,bHandled);//关闭消息
		break;
	case WM_DESTROY:
		OnDestroy(uMsg,wParam,lParam,bHandled);//窗口销毁消息
		break;
	case WM_NCACTIVATE:   //这三个消息屏蔽了标题栏
		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); //客户区以外的地方绘制产生这个消息如：标题栏
		break;
	case WM_NCCALCSIZE: 
		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); //客户区以外的地方绘制产生这个消息如：标题栏
		break;
	case WM_NCPAINT:////客户区以外的地方绘制产生这个消息如：标题栏
		lRes = OnNcPaint(uMsg,wParam,lParam,bHandled);
		break;
	case WM_NCHITTEST://处理标题栏拖动
		/*
		为了移动一个无标题栏的窗体，使用了WM_NCHITTEST消息，这个消息大概如下：
		通常，我们拖动对话框窗口的标题栏来移动窗口，但有时候，我们想通过鼠标在客户区上拖动来移动窗口。
		一个容易想到的方案是，处理鼠标消息WM_LBUTTONDOWN和WM_LBUTTONUP。在OnLButtonUp函数中计算鼠标位置的变化，调用MoveWindow实现窗口的移动。
		注意，拖动标题栏移动窗口的时候，会出现一个矩形框，它提示了窗口移动的当前位置。当鼠标左键放开的时候，窗口就移动到矩形框所在位置。而我们的实现方案中没有这个功能。
		要实现此功能，我们必须自己来画这些矩形。
		事实上，我们没有必要自己来做这件事情，因为Windows已经给我们做好了。
		试想，如果我能够欺骗Windows，告诉它现在鼠标正在拖动的是标题栏而不是客户区，那么窗口移动操作就由Windows来代劳了。
		要欺骗Windows并不像想像中的困难，甚至非常简单。
		我们利用一个消息：WM_NCHITTEST。
		MSDN对它的解释是：
		The WM_NCHITTEST message is sent to a window when the cursor moves, or when a mouse button is pressed or released. If the mouse is not captured, the message is sent to the window beneath the cursor. Otherwise, the message is sent to the window that has captured the mouse.
		这个消息是当鼠标移动或者有鼠标键按下时候发出的。
		Windows用这个消息来做什么？ “HITTEST”就是“命中测试”的意思，WM_NCHITTEST消息用来获取鼠标当前命中的位置。
		WM_NCHITTEST的消息响应函数会根据鼠标当前的坐标来判断鼠标命中了窗口的哪个部位，消息响应函数的返回值指出了部位，例如它可能会返回HTCAPTION，或者HTCLIENT等。（其返回值有很多，请查阅MSDN）。
		*/
		lRes = OnNcHitTest(uMsg,wParam,lParam,bHandled);
		break;
 	case WM_SIZE:
 		lRes = OnSize(uMsg,wParam,lParam,bHandled);
 		break;
  	case WM_GETMINMAXINFO: 
  		lRes = OnGetMinMaxInfo(uMsg, wParam, lParam, bHandled);
  		break;
	case WM_SYSCOMMAND:
		lRes = OnSysCommand(uMsg,wParam,lParam,bHandled);
		break;
	default:
		bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

void CMainFrame::Notify(TNotifyUI& msg)
{
	
	if( msg.sType == _T("windowinit") )
	{// OnPrepare();
	}
	else if( msg.sType == _T("click") ) {
		if( msg.pSender == m_pCloseBtn ) {
			PostQuitMessage(0);
			return; 
		}
		else if( msg.pSender == m_pMinBtn ) { 
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
		else if( msg.pSender == m_pMaxBtn ) { 
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
		else if( msg.pSender == m_pRestoreBtn ) { 
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
	}
	else if(msg.sType==_T("selectchanged"))
	{
		CDuiString name = msg.pSender->GetName();
		CTabLayoutUI* pTabLayoutUI = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("myaddtest")));
		if(name==_T("common"))
		{
			pTabLayoutUI->SelectItem(0);
		}
		else if(name==_T("firwall"))
		{
			pTabLayoutUI->SelectItem(1);
		}
		else if(name==_T("antivius"))
		{
			pTabLayoutUI->SelectItem(2);
		}
		else if(name==_T("network"))
		{
			pTabLayoutUI->SelectItem(3);
		}
	}
	/*
	else if(msg.sType==_T("selectchanged"))
	{
		CDuiString name = msg.pSender->GetName();
		CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("switch")));
		if(name==_T("examine"))
			pControl->SelectItem(0);
		else if(name==_T("trojan"))
			pControl->SelectItem(1);
		else if(name==_T("plugins"))
			pControl->SelectItem(2);
		else if(name==_T("vulnerability"))
			pControl->SelectItem(3);
		else if(name==_T("rubbish"))
			pControl->SelectItem(4);
		else if(name==_T("cleanup"))
			pControl->SelectItem(5);
		else if(name==_T("fix"))
			pControl->SelectItem(6);
		else if(name==_T("tool"))
			pControl->SelectItem(7);
	}
	*/
	/*
	if( msg.sType == _T("windowinit") )
	{

	}
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
	*/
}

LRESULT CMainFrame::OnNcHitTest(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL bHandled)
{
	//获取鼠标坐标
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if( !::IsZoomed(*this) ) //如果没有最大化
	{
		RECT rcSizeBox = m_pm.GetSizeBox();//获取的拉大拉小的那个sizebox(4,4,6,6);
		if( pt.y < rcClient.top + rcSizeBox.top ) 
		{
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTTOPLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTTOPRIGHT;
			return HTTOP;
		}
		else if( pt.y > rcClient.bottom - rcSizeBox.bottom ) 
		{
			if( pt.x < rcClient.left + rcSizeBox.left ) return HTBOTTOMLEFT;
			if( pt.x > rcClient.right - rcSizeBox.right ) return HTBOTTOMRIGHT;
			return HTBOTTOM;
		}

		if( pt.x < rcClient.left + rcSizeBox.left ) return HTLEFT;
		if( pt.x > rcClient.right - rcSizeBox.right ) return HTRIGHT;
	}

	RECT rcCaption = m_pm.GetCaptionRect();//获取的是标题栏的rect
	if( pt.x > rcCaption.left+rcClient.left && pt.x < rcClient.right - rcCaption.right 
		&& pt.y > rcCaption.top && pt.y < rcCaption.bottom ) 
	{
		CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
		if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0
			&& _tcscmp(pControl->GetClass(),_T("OptionUI"))!=0)
			return HTCAPTION;
	}
	return HTCLIENT;
}