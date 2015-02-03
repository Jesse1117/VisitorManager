#include "stdafx.h"
#include "UIDateTime.h"

namespace UiLib
{
	//CDateTimeUI::m_nDTUpdateFlag
#define DT_NONE   0
#define DT_UPDATE 1
#define DT_DELETE 2
#define DT_KEEP   3

	class CDateTimeWnd : public CWindowWnd
	{
	public:
		CDateTimeWnd();

		void Init(CDateTimeUI* pOwner);
		RECT CalPos();

		LPCTSTR GetWindowClassName() const;
		LPCTSTR GetSuperClassName() const;
		void OnFinalMessage(HWND hWnd);

		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		//LRESULT OnEditChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		bool GetIsInit() const;
		void ModifyStyle(UINT addStyle,UINT removeStyle);
		BOOL GetIsTimeformat();
	protected:
		CDateTimeUI* m_pOwner;
		HBRUSH m_hBkBrush;
		bool m_bInit;
		UINT m_uStyle;
	};

	CDateTimeWnd::CDateTimeWnd() : m_pOwner(NULL), m_hBkBrush(NULL), m_bInit(false),m_uStyle(WS_CHILD)
	{
	}
	
	void CDateTimeWnd::ModifyStyle(UINT addStyle,UINT removeStyle)
	{
		m_uStyle |= addStyle;
		m_uStyle &= ~removeStyle;
	}

	BOOL CDateTimeWnd::GetIsTimeformat()
	{
		return m_uStyle & DTS_TIMEFORMAT;
	}

	void CDateTimeWnd::Init(CDateTimeUI* pOwner)
	{
		m_pOwner = pOwner;
		m_pOwner->m_nDTUpdateFlag = GDT_NONE;
		if (m_hWnd == NULL)
		{
			RECT rcPos = CalPos();
//			UINT uStyle = WS_CHILD;
			Create(m_pOwner->GetManager()->GetPaintWindow(), NULL, m_uStyle, 0, rcPos);
			SetWindowFont(m_hWnd, m_pOwner->GetManager()->GetFontInfo(m_pOwner->GetFont())->hFont, TRUE);
		}
		if (m_pOwner->GetText().IsEmpty())
			::GetLocalTime(&m_pOwner->m_sysTime);
		::SendMessage(m_hWnd, DTM_SETSYSTEMTIME, 0, (LPARAM)&m_pOwner->m_sysTime);
		::ShowWindow(m_hWnd, SW_SHOWNOACTIVATE);
		::SetFocus(m_hWnd);
		m_bInit = true;    
	}
	
	bool CDateTimeWnd::GetIsInit() const
	{
		return m_bInit;
	}

	RECT CDateTimeWnd::CalPos()
	{
		CDuiRect rcPos = m_pOwner->GetPos();
		return rcPos;
	}

	LPCTSTR CDateTimeWnd::GetWindowClassName() const
	{
		return _T("DateTimeWnd");
	}

	LPCTSTR CDateTimeWnd::GetSuperClassName() const
	{
		return DATETIMEPICK_CLASS;
	}

	void CDateTimeWnd::OnFinalMessage(HWND /*hWnd*/)
	{
		if( m_hBkBrush != NULL ) ::DeleteObject(m_hBkBrush);
		m_pOwner->m_pWindow = NULL;
		delete this;
	}

	LRESULT CDateTimeWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL bHandled = TRUE;
		if(WM_NOTIFY==uMsg)
		{
			::SetFocus(m_hWnd);
		}
		if( uMsg == WM_KILLFOCUS )
		{
			HWND hh= DateTime_GetMonthCal(GetHWND());
			//::FindWindow(_T("SysMonthCal32"),NULL);
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
					m_pOwner->m_nDTUpdateFlag = DT_NONE;
					lRes= OnKillFocus(uMsg,wParam, lParam,bHandled);
				}
			}			
		}
		else if (uMsg == WM_KEYUP && (wParam == VK_DELETE || wParam == VK_BACK))
		{
			LRESULT lRes = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
			m_pOwner->m_nDTUpdateFlag = DT_DELETE;
			m_pOwner->UpdateText();
			::ShowWindow(GetHWND(),SW_HIDE);
			return lRes;
		}
		else if (uMsg == WM_KEYUP && wParam == VK_ESCAPE)
		{
			LRESULT lRes = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
			m_pOwner->m_nDTUpdateFlag = DT_KEEP;
			::ShowWindow(GetHWND(),SW_HIDE);
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

	LRESULT CDateTimeWnd::OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
		if (m_pOwner->m_nDTUpdateFlag == DT_NONE)
		{
			::SendMessage(m_hWnd, DTM_GETSYSTEMTIME, 0, (LPARAM)&m_pOwner->m_sysTime);
			m_pOwner->m_nDTUpdateFlag = DT_UPDATE;
			m_pOwner->UpdateText();
		}
		::ShowWindow(GetHWND(),SW_HIDE);
		return lRes;
	}

	CDateTimeUI::CDateTimeUI() : m_pWindow(NULL),m_bReadOnly(false)
	{
		m_pWindow = new CDateTimeWnd();
		ASSERT(m_pWindow);
		::GetLocalTime(&m_sysTime);
		m_nDTUpdateFlag = DT_NONE;
	}

	LPCTSTR CDateTimeUI::GetClass() const
	{
		return _T("DateTimeUI");
	}

	LPVOID CDateTimeUI::GetInterface(LPCTSTR pstrName)
	{
		if( _tcscmp(pstrName, DUI_CTR_DATETIME) == 0 ) return static_cast<CDateTimeUI*>(this);
		return CLabelUI::GetInterface(pstrName);
	}

	SYSTEMTIME& CDateTimeUI::GetTime()
	{
		return m_sysTime;
	}

	void CDateTimeUI::SetTime(SYSTEMTIME* pst)
	{
		m_sysTime = *pst;
		Invalidate();
	}

	void CDateTimeUI::SetReadOnly(bool bReadOnly)
	{
		m_bReadOnly = bReadOnly;
		Invalidate();
	}

	bool CDateTimeUI::IsReadOnly() const
	{
		return m_bReadOnly;
	}

	void CDateTimeUI::UpdateText()
	{
		if (m_nDTUpdateFlag == DT_DELETE)
			SetText(_T(""));
		else if (m_nDTUpdateFlag == DT_UPDATE)
		{
			CDuiString sText;
			if(!GetWindowTimeFormat())
				sText.SmallFormat(_T("%4d-%02d-%02d"),
					m_sysTime.wYear, m_sysTime.wMonth, m_sysTime.wDay);
			else
				sText.SmallFormat(_T("%02d:%02d:%02d"),
					m_sysTime.wHour, m_sysTime.wMinute, m_sysTime.wSecond);
			SetText(sText);
		}
	}

	void CDateTimeUI::DoEvent(TEventUI& event)
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
				if(!m_pWindow->GetIsInit())
					m_pWindow->Init(this);
				m_pWindow->ShowWindow();
				::SetFocus(m_pWindow->GetHWND());
				return;
		}
		if( event.Type == UIEVENT_KILLFOCUS && IsEnabled() ) 
		{
			::ShowWindow(m_pWindow->GetHWND(),SW_HIDE);
			Invalidate();
		}
		if( event.Type == UIEVENT_BUTTONDOWN || event.Type == UIEVENT_DBLCLICK || event.Type == UIEVENT_RBUTTONDOWN) 
		{
			if( IsEnabled() ) {
				GetManager()->ReleaseCapture();
				if( IsFocused() && m_pWindow == NULL )
				{
					m_pWindow = new CDateTimeWnd();
					ASSERT(m_pWindow);
				}
				if( m_pWindow != NULL )
				{
					if(!m_pWindow->GetIsInit())
						m_pWindow->Init(this);
					m_pWindow->ShowWindow();
				}
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

	void CDateTimeUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
	{
		if(_tcscmp(pstrName,_T("timestyle"))==0) 
		{
			if(_tcscmp(pstrValue,_T("shownone"))==0) SetWindowShowNone();
			if(_tcscmp(pstrValue,_T("updown"))==0) SetWindowUpDown();
			if(_tcscmp(pstrValue,_T("expand"))==0) SetWindowShowExpanded();
			m_nDTUpdateFlag=DT_UPDATE;
			UpdateText();
		}
		else if(_tcscmp(pstrName,_T("timeformat"))==0)
		{
			if(_tcscmp(pstrValue,_T("true"))==0)
			{
				SetWindowTimeFormat();
				SetWindowUpDown();
				m_nDTUpdateFlag=DT_UPDATE;
				UpdateText();
			}
		}
		else
			CLabelUI::SetAttribute(pstrName,pstrValue);
	}

	void CDateTimeUI::SetWindowShowNone()
	{
		m_pWindow->ModifyStyle(DTS_SHOWNONE,DTS_UPDOWN);
	}

	void CDateTimeUI::SetWindowUpDown()
	{
		m_pWindow->ModifyStyle(DTS_UPDOWN,DTS_SHOWNONE);
	}

	void CDateTimeUI::SetWindowShowExpanded()
	{
		m_pWindow->ModifyStyle(0,DTS_SHOWNONE | DTS_UPDOWN);
	}

	void CDateTimeUI::SetWindowTimeFormat()
	{
		m_pWindow->ModifyStyle(DTS_TIMEFORMAT,0);
	}

	BOOL CDateTimeUI::GetWindowTimeFormat()
	{
		return m_pWindow->GetIsTimeformat();
	}
}
