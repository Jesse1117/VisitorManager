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
	case WM_SYSCOMMAND:
		lRes = OnSysCommand(uMsg,wParam,lParam,bHandled);
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

LRESULT CTestFrameWnd::OnClose(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& bHandled)
{
	bHandled = FALSE;
	return 0;
}

LRESULT CTestFrameWnd::OnDestroy(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& bHandled)
{
	bHandled = FALSE;
	::PostQuitMessage(0L);
	return 0;
}

LRESULT CTestFrameWnd::OnSysCommand(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL& bHandled)
{
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
	return lRes;
}
/*
处理鼠标拖动标题栏
*/
LRESULT CTestFrameWnd::OnNcHitTest(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL bHandled)
{
	//获取鼠标坐标
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	RECT rcCaption = m_pm.GetCaptionRect();
	if( pt.x > rcCaption.left+rcClient.left && pt.x < rcClient.right - rcCaption.right 
		&& pt.y > rcCaption.top && pt.y < 90 ) 
	{
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
			if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0)
				return HTCAPTION;
	}
	return HTCLIENT;
}

LRESULT CTestFrameWnd::OnSize(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL bHandled)
{
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

	bHandled = FALSE;
	return 0;
}

LRESULT CTestFrameWnd::OnGetMinMaxInfo(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL bHandled)
{
	MONITORINFO oMonitor = {};
	oMonitor.cbSize = sizeof(oMonitor);
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);
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