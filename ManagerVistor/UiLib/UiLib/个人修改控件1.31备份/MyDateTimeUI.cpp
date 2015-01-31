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
		bool GetIsInit() const;
		void ModifyStyle(UINT addStyle,UINT removeStyle);
	protected:
		CMyDateTimeUI* m_pOwner;
		HBRUSH m_hBkBrush;
		bool m_bInit;
		UINT m_uStyle;
	};

	CMyDateTimeWnd::CMyDateTimeWnd() : m_bInit(false),m_hBkBrush(NULL),m_pOwner(NULL),m_uStyle(WS_CHILD)
	{
	}
	CMyDateTimeWnd::~CMyDateTimeWnd(){}

	RECT CMyDateTimeWnd::CalPos()
	{
		ASSERT(m_pOwner!=NULL);
		return m_pOwner->GetPos();
	}

	bool CMyDateTimeWnd::GetIsInit() const
	{
		return m_bInit;
	}

	void CMyDateTimeWnd::ModifyStyle(UINT addStyle,UINT removeStyle)
	{
		m_uStyle |= addStyle;
		m_uStyle &= ~removeStyle;
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
			Create(m_pOwner->GetManager()->GetPaintWindow(), NULL, m_uStyle, 0, rcPos);
			SetWindowFont(m_hWnd, m_pOwner->GetManager()->GetFontInfo(m_pOwner->GetFont())->hFont, TRUE);
		}

		if (m_pOwner->GetText().IsEmpty())
			::GetLocalTime(&m_pOwner->m_sysTime);

		::SendMessage(m_hWnd, DTM_SETSYSTEMTIME, 0, (LPARAM)&m_pOwner->m_sysTime);
		::ShowWindow(m_hWnd, SW_SHOWNOACTIVATE);
		m_bInit = true;
	}

	LRESULT CMyDateTimeWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
// 		LRESULT lRes = 0;
 		if( uMsg == WM_KILLFOCUS )
 		{
			::SendMessage(m_hWnd, DTM_GETSYSTEMTIME, 0, (LPARAM)&m_pOwner->m_sysTime);
 		}
// 		else if (uMsg == WM_KEYUP && (wParam == VK_DELETE || wParam == VK_BACK))
// 		{
// 			LRESULT lRes = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
// 			return lRes;
// 		}
// 		else if (uMsg == WM_KEYUP && wParam == VK_ESCAPE)
// 		{
// 			LRESULT lRes = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
// 			return lRes;
// 		}
// 		else
// 		{
// 			bHandled = FALSE;
//		}

//		if(!bHandled ) 
//		{
		return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
//		}
//		return lRes;
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
		m_pWindow->ModifyStyle(DTS_SHOWNONE,DTS_UPDOWN);
	}

	void CMyDateTimeUI::SetWindowUpDown()
	{
		m_pWindow->ModifyStyle(DTS_UPDOWN,DTS_SHOWNONE);
	}

	void CMyDateTimeUI::SetWindowShowExpanded()
	{
		m_pWindow->ModifyStyle(0,DTS_SHOWNONE | DTS_UPDOWN);
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

	void CMyDateTimeUI::PaintBkColor(HDC hDC)
	{
		if(!m_pWindow->GetIsInit())
			m_pWindow->Init(this);
//		RECT rc = GetPos();
//		::MoveWindow(m_pWindow->GetHWND(),rc.left,rc.top-2,rc.right-rc.left,rc.bottom-rc.top,TRUE);
		CLabelUI::PaintBkColor(hDC);
	}
}
