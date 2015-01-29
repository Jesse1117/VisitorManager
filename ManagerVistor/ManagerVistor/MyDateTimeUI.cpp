#include "StdAfx.h"
#include "MyDateTimeUI.h"

namespace UiLib
{
	class CMyDateTimeWnd : public CWindowWnd
	{
	public:
		CMyDateTimeWnd();
		~CMyDateTimeWnd();
		void Init(CMyDateTimeUI* pOwner);
		RECT CalPos();
		LPCTSTR GetWindowClassName() const;
		LPCTSTR GetSuperClassName() const;
		void OnFinalMessage(HWND hWnd);
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	protected:
		CMyDateTimeUI* m_pOwner;
		HBRUSH m_hBkBrush;
		bool m_bInit;
	};

	CMyDateTimeWnd::CMyDateTimeWnd() : m_bInit(false),m_hBkBrush(NULL),m_pOwner(NULL)
	{
	}
	CMyDateTimeWnd::~CMyDateTimeWnd(){}

	RECT CMyDateTimeWnd::CalPos()
	{
		ASSERT(m_pOwner!=NULL);
		return m_pOwner->GetPos();
	}

	LPCTSTR CMyDateTimeWnd::GetWindowClassName() const
	{
		return _T("MyDateTimeWnd");
	}

	LPCTSTR CMyDateTimeWnd::GetSuperClassName() const
	{
		return DATETIMEPICK_CLASS;
	}

	void CMyDateTimeWnd::OnFinalMessage(HWND /*hWnd*/)
	{
		// Clear reference and die
		if( m_hBkBrush != NULL ) ::DeleteObject(m_hBkBrush);
		delete this;
	}

	void CMyDateTimeWnd::Init(CMyDateTimeUI* pOwner)
	{
		m_pOwner = pOwner;
//		m_pOwner->m_nDTUpdateFlag = GDT_NONE;
		if (m_hWnd == NULL)
		{
			RECT rcPos = CalPos();
			UINT uStyle = WS_CHILD;
			Create(m_pOwner->GetManager()->GetPaintWindow(), NULL, uStyle, 0, rcPos);
			SetWindowFont(m_hWnd, m_pOwner->GetManager()->GetFontInfo(m_pOwner->GetFont())->hFont, TRUE);
		}

		if (m_pOwner->GetText().IsEmpty())
			::GetLocalTime(&m_pOwner->m_sysTime);

		::SendMessage(m_hWnd, DTM_SETSYSTEMTIME, 0, (LPARAM)&m_pOwner->m_sysTime);
		::ShowWindow(m_hWnd, SW_SHOWNOACTIVATE);
		::SetFocus(m_hWnd);
		m_bInit = true;
	}

	LRESULT CMyDateTimeWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL bHandled = TRUE;
		if(WM_SETFOCUS==uMsg)
		{
			::OutputDebugString(L"WM_SETFOCUS\n");
		}
		if(WM_NOTIFY==uMsg)
		{
			::SetFocus(m_hWnd);
			::OutputDebugString(L"WM_NOTIFY\n");
		}
		if( uMsg == WM_KILLFOCUS /**/)
		{
			//这里肯可能需要优化，因为FindWindow找出来的窗口不一定是本进程的窗口
			HWND hh=::FindWindow(_T("SysMonthCal32"),NULL);
			//Isdel=true;
			if(::IsWindow(hh))
			{
				MCHITTESTINFO pp;
				memset(&pp,0,sizeof(pp));
				GetCursorPos(&pp.pt);
				::ScreenToClient(hh,&pp.pt);
				pp.cbSize=sizeof(pp);
				MonthCal_HitTest(hh,&pp);
				//下一个月
				if(pp.uHit==MCHT_TITLEBTNNEXT)
				{
					return 1;
				}
				//上一个月
				if(pp.uHit==MCHT_TITLEBTNPREV)
				{
					return 1;
				}
			}
			else
			{
				POINT pt;
				::GetCursorPos(&pt); 
				RECT rt;
				::GetWindowRect(m_hWnd,&rt);
				if(!(pt.x>=rt.left&&pt.x<=rt.right)||
					!(pt.x>=rt.top&&pt.x<=rt.bottom))
				{
//					m_pOwner->m_nDTUpdateFlag = DT_NONE;
					lRes= OnKillFocus(uMsg,wParam, lParam,bHandled);
				}
			}
		}
		else/**/ if (uMsg == WM_KEYUP && (wParam == VK_DELETE || wParam == VK_BACK))
		{
			LRESULT lRes = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
//			m_pOwner->m_nDTUpdateFlag = DT_DELETE;
			//			m_pOwner->UpdateText();
			//			PostMessage(WM_CLOSE);
			return lRes;
		}
		else if (uMsg == WM_KEYUP && wParam == VK_ESCAPE)
		{
			LRESULT lRes = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
//			m_pOwner->m_nDTUpdateFlag = DT_KEEP;
			//			PostMessage(WM_CLOSE);
			return lRes;
		}
		else
		{
			bHandled = FALSE;
		}

		if(!bHandled ) 
		{
			return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		}
		return lRes;
	}

	LRESULT CMyDateTimeWnd::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = ::DefWindowProc(m_hWnd,uMsg,wParam,lParam);
		::SendMessage(m_hWnd, DTM_GETSYSTEMTIME, 0, (LPARAM)&m_pOwner->m_sysTime);
		return lRes;
	}

	CMyDateTimeUI::CMyDateTimeUI(void) : m_pWindow(NULL)
	, m_bReadOnly(false)
	{
		::GetLocalTime(&m_sysTime);
		m_pWindow = new CMyDateTimeWnd;
		ASSERT(m_pWindow);
	}

	CMyDateTimeUI::~CMyDateTimeUI(void)
	{
		if(m_pWindow)
		{
			delete m_pWindow;
			m_pWindow = NULL;
		}
	}

	LPCTSTR CMyDateTimeUI::GetClass() const
	{
		return _T("MyDateTimeUI"); 
	}

	LPVOID CMyDateTimeUI::GetInterface(LPCTSTR pstrName)
	{
		if( _tcscmp(pstrName, DUI_CTR_MYDATETIME) == 0 ) return static_cast<CMyDateTimeUI*>(this);
		return CLabelUI::GetInterface(pstrName);
	}

	SYSTEMTIME& CMyDateTimeUI::GetTime()
	{
		return m_sysTime;
	}

	void CMyDateTimeUI::SetTime(SYSTEMTIME* pst)
	{
		m_sysTime = *pst;
		Invalidate();
	}

	void CMyDateTimeUI::SetReadOnly(bool bReadOnly)
	{
		m_bReadOnly = bReadOnly;
		Invalidate();
	}

	bool CMyDateTimeUI::IsReadOnly() const
	{
		return m_bReadOnly;
	}

	void CMyDateTimeUI::UpdateText()
	{
		
	}
	
	void CMyDateTimeUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if(_tcscmp(pstrName,_T("timestyle"))==0) 
		{
			if(_tcscmp(pstrValue,_T("shownone"))==0) SetWindowShowNone();
			if(_tcscmp(pstrValue,_T("updown"))==0) SetWindowUpDown();
			if(_tcscmp(pstrValue,_T("expand"))==0) SetWindowShowExpanded();
		}
		else
			CLabelUI::SetAttribute(pstrName,pstrValue);
	}

	void CMyDateTimeUI::SetWindowShowNone()
	{
		DWORD dStyle = ::GetWindowLong(m_pWindow->GetHWND(),GWL_STYLE);
		dStyle |= DTS_SHOWNONE;
		dStyle &= ~DTS_UPDOWN;
		::SetWindowLong(m_pWindow->GetHWND(),GWL_STYLE,dStyle);
		m_pWindow->ShowWindow();
	}

	void CMyDateTimeUI::SetWindowUpDown()
	{
		DWORD dStyle = ::GetWindowLong(m_pWindow->GetHWND(),GWL_STYLE);
		dStyle |= DTS_UPDOWN;
		dStyle &= ~DTS_SHOWNONE;
		::SetWindowLong(m_pWindow->GetHWND(),GWL_STYLE,dStyle);
		m_pWindow->ShowWindow();
	}

	void CMyDateTimeUI::SetWindowShowExpanded()
	{
		DWORD dStyle = ::GetWindowLong(m_pWindow->GetHWND(),GWL_STYLE);
		dStyle &= ~DTS_UPDOWN;
		dStyle &= ~DTS_SHOWNONE;
		::SetWindowLong(m_pWindow->GetHWND(),GWL_STYLE,dStyle);
		m_pWindow->ShowWindow();
	}

	void CMyDateTimeUI::DoEvent(TEventUI& event)
	{
		if( !IsMouseEnabled() && event.Type > UIEVENT__MOUSEBEGIN && event.Type < UIEVENT__MOUSEEND ) {
			if( m_pParent != NULL ) m_pParent->DoEvent(event);
			else CLabelUI::DoEvent(event);
			return;
		}
		if( event.Type == UIEVENT_SETCURSOR && IsEnabled() )
		{
			::SetCursor(::LoadCursor(NULL, MAKEINTRESOURCE(IDC_IBEAM)));
			return;
		}
		if( event.Type == UIEVENT_WINDOWSIZE )
		{
			if( m_pWindow != NULL ) m_pManager->SetFocusNeeded(this);
		}
		if( event.Type == UIEVENT_SCROLLWHEEL )
		{
			if( m_pWindow != NULL ) return;
		}
		if( event.Type == UIEVENT_SETFOCUS && IsEnabled() ) 
		{
			if( m_pWindow )
				::SetFocus(m_pWindow->GetHWND());
				return;
			// 			m_pWindow = new CDateTimeWnd();
			// 			ASSERT(m_pWindow);
			// 			m_pWindow->Init(this);
			// 			m_pWindow->ShowWindow();
		}
		if( event.Type == UIEVENT_KILLFOCUS && IsEnabled() ) 
		{
			Invalidate();
		}
		if( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK || event.Type == UIEVENT_RBUTTONDOWN) 
		{
			if( IsEnabled() ) {
				GetManager()->ReleaseCapture();
				// 				if( IsFocused() && m_pWindow == NULL )
				// 				{
				// 					m_pWindow = new CDateTimeWnd();
				// 					ASSERT(m_pWindow);
				// 				}
				// 				if( m_pWindow != NULL )
				// 				{
				// 					m_pWindow->Init(this);
				// 					m_pWindow->ShowWindow();
				// 				}
			}
			return;
		}
		if( event.Type == UIEVENT_MOUSEMOVE ) 
		{
			return;
		}
		if( event.Type == UIEVENT_BUTTONUP ) 
		{
			return;
		}
		if( event.Type == UIEVENT_CONTEXTMENU )
		{
			return;
		}
		if( event.Type == UIEVENT_MOUSEENTER )
		{
			return;
		}
		if( event.Type == UIEVENT_MOUSELEAVE )
		{
			return;
		}

		CLabelUI::DoEvent(event);
	}
}
