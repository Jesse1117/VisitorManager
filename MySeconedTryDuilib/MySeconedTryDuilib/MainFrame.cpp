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
	
	m_pm.Init(m_hWnd);//���������봰�ھ������
	CDialogBuilder builder;
	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("first.xml"),(UINT)0,&cb,&m_pm);
	ASSERT(pRoot);
	m_pm.AttachDialog(pRoot);//�����ӿؼ����ݵ�HASH���У�
	m_pm.AddNotifier(this);//����֪ͨ��Ϣ
	Init();//��ʼ����������ť
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
	::GetMonitorInfo(::MonitorFromWindow(*this, MONITOR_DEFAULTTOPRIMARY), &oMonitor);//��ʾ�����,��ʾ����Ϣ
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
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
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
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg,wParam,lParam);//��ִ�и�������Ϣ���У�����syscommand
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
		OnCreate(uMsg, wParam, lParam, bHandled); //�����ڴ�����Ϣ
		break;
	case WM_CLOSE:
		OnClose(uMsg,wParam,lParam,bHandled);//�ر���Ϣ
		break;
	case WM_DESTROY:
		OnDestroy(uMsg,wParam,lParam,bHandled);//����������Ϣ
		break;
	case WM_NCACTIVATE:   //��������Ϣ�����˱�����
		lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); //�ͻ�������ĵط����Ʋ��������Ϣ�磺������
		break;
	case WM_NCCALCSIZE: 
		lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); //�ͻ�������ĵط����Ʋ��������Ϣ�磺������
		break;
	case WM_NCPAINT:////�ͻ�������ĵط����Ʋ��������Ϣ�磺������
		lRes = OnNcPaint(uMsg,wParam,lParam,bHandled);
		break;
	case WM_NCHITTEST://����������϶�
		/*
		Ϊ���ƶ�һ���ޱ������Ĵ��壬ʹ����WM_NCHITTEST��Ϣ�������Ϣ������£�
		ͨ���������϶��Ի��򴰿ڵı��������ƶ����ڣ�����ʱ��������ͨ������ڿͻ������϶����ƶ����ڡ�
		һ�������뵽�ķ����ǣ����������ϢWM_LBUTTONDOWN��WM_LBUTTONUP����OnLButtonUp�����м������λ�õı仯������MoveWindowʵ�ִ��ڵ��ƶ���
		ע�⣬�϶��������ƶ����ڵ�ʱ�򣬻����һ�����ο�����ʾ�˴����ƶ��ĵ�ǰλ�á����������ſ���ʱ�򣬴��ھ��ƶ������ο�����λ�á������ǵ�ʵ�ַ�����û��������ܡ�
		Ҫʵ�ִ˹��ܣ����Ǳ����Լ�������Щ���Ρ�
		��ʵ�ϣ�����û�б�Ҫ�Լ�����������飬��ΪWindows�Ѿ������������ˡ�
		���룬������ܹ���ƭWindows��������������������϶����Ǳ����������ǿͻ�������ô�����ƶ���������Windows�������ˡ�
		Ҫ��ƭWindows�����������е����ѣ������ǳ��򵥡�
		��������һ����Ϣ��WM_NCHITTEST��
		MSDN�����Ľ����ǣ�
		The WM_NCHITTEST message is sent to a window when the cursor moves, or when a mouse button is pressed or released. If the mouse is not captured, the message is sent to the window beneath the cursor. Otherwise, the message is sent to the window that has captured the mouse.
		�����Ϣ�ǵ�����ƶ���������������ʱ�򷢳��ġ�
		Windows�������Ϣ����ʲô�� ��HITTEST�����ǡ����в��ԡ�����˼��WM_NCHITTEST��Ϣ������ȡ��굱ǰ���е�λ�á�
		WM_NCHITTEST����Ϣ��Ӧ�����������굱ǰ���������ж���������˴��ڵ��ĸ���λ����Ϣ��Ӧ�����ķ���ֵָ���˲�λ�����������ܻ᷵��HTCAPTION������HTCLIENT�ȡ����䷵��ֵ�кܶ࣬�����MSDN����
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
	//��ȡ�������
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	if( !::IsZoomed(*this) ) //���û�����
	{
		RECT rcSizeBox = m_pm.GetSizeBox();//��ȡ��������С���Ǹ�sizebox(4,4,6,6);
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

	RECT rcCaption = m_pm.GetCaptionRect();//��ȡ���Ǳ�������rect
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