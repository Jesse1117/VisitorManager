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
	case WM_SYSCOMMAND:
		lRes = OnSysCommand(uMsg,wParam,lParam,bHandled);
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

	m_pm.Init(m_hWnd);//���������봰�ھ������
	CDialogBuilder builder;
//	CDialogBuilderCallbackEx cb;
	CControlUI* pRoot = builder.Create(_T("test.xml"),(UINT)0,NULL,&m_pm);
	ASSERT(pRoot);
	m_pm.AttachDialog(pRoot);//�����ӿؼ����ݵ�HASH���У�
	m_pm.AddNotifier(this);//����֪ͨ��Ϣ
	InitCaptionButton();//��ʼ����������ť
	return 0;
	/*
	m_pm.Init(m_hWnd);

	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("test.xml"), (UINT)0, NULL, &m_pm);   // duilib.xml��Ҫ�ŵ�exeĿ¼��
	ASSERT(pRoot && "Failed to parse XML");

	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);   // ��ӿؼ�����Ϣ��Ӧ��������Ϣ�ͻᴫ�ﵽduilib����Ϣѭ�������ǿ�����Notify����������Ϣ����
	return 0;
	*/
	/*
	CControlUI *pWnd = new CButtonUI;
	pWnd->SetName(_T("btnHello"));      // ���ÿؼ������ƣ�����������ڱ�ʶÿһ���ؼ�������Ψһ���൱��MFC����Ŀؼ�ID
	pWnd->SetText(_T("Hello World"));   // ��������
	pWnd->SetBkColor(0xFF00FF00);       // ���ñ���ɫ
	pWnd->SetFloat(true);
	RECT rc;rc.left=0;rc.right=600;rc.bottom=0;rc.top=500;
	pWnd->SetMaxHeight(800);
	pWnd->SetMaxWidth(700);
	pWnd->SetMinHeight(700);
	pWnd->SetMinWidth(600);
	*/
// 	m_pm.Init(m_hWnd);
// 	m_pm.AttachDialog(CButtonUI*(this));
// 	m_pm.AddNotifier(this);   // ��ӿؼ�����Ϣ��Ӧ��������Ϣ�ͻᴫ�ﵽduilib����Ϣѭ�������ǿ�����Notify����������Ϣ����
	
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
	return lRes;
}
/*
��������϶�������
*/
LRESULT CTestFrameWnd::OnNcHitTest(UINT uMsg,WPARAM wParam,LPARAM lParam,BOOL bHandled)
{
	//��ȡ�������
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