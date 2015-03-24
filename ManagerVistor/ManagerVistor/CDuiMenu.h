using namespace UiLib;

class CDuiMenu :public WindowImplBase
{
public:
	explicit CDuiMenu(LPCTSTR pszXMLPath): m_strXMLPath(pszXMLPath){}
	virtual LPCTSTR    GetWindowClassName()const{ return _T("CDuiMenu "); }
	virtual CDuiString GetSkinFolder()          { return _T("");            }
	virtual CDuiString GetSkinFile()            { return m_strXMLPath;      }
	virtual void       OnFinalMessage(HWND hWnd){ delete this;              }

	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		Close();
		bHandled = FALSE;
		return 0;
	}

	void Init(HWND hWndParent, POINT ptPos)
	{
		Create(hWndParent, _T("MenuWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
		::ClientToScreen(hWndParent, &ptPos);
		::SetWindowPos(*this, NULL, ptPos.x, ptPos.y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
	}

	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		LRESULT lRes = 0;
		BOOL    bHandled = TRUE;

		switch( uMsg )
		{
		case WM_KILLFOCUS:    
			lRes = OnKillFocus(uMsg, wParam, lParam, bHandled); 
			break; 
		default:
			bHandled = FALSE;
		}

		if(bHandled || m_PaintManager.MessageHandler(uMsg, wParam, lParam, lRes)) 
		{
			return lRes;
		}

		return __super::HandleMessage(uMsg, wParam, lParam);
	}

protected:
	virtual ~CDuiMenu(){};        
	CDuiString  m_strXMLPath;
};