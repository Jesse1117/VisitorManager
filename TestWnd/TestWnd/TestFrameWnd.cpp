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