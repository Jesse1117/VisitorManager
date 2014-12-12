#include "StdAfx.h"
#include "MainFrame.h"
#include <string.h>
#include "VisitorRecordUI.h"

using namespace std;

CMainFrame::CMainFrame(LPCTSTR pszXMLName) : m_strXMLName(pszXMLName)
	, m_pCloseBtn(NULL)
	, m_pMaxBtn(NULL)
	, m_pMinBtn(NULL)
	, m_pRestoreBtn(NULL)
{
}

CMainFrame::~CMainFrame(void)
{
}

void CMainFrame::InitWindow()
{
	CenterWindow();
	m_pCloseBtn = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("closebtn")));
	m_pMaxBtn = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("maxbtn")));
	m_pMinBtn = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("minbtn")));
	m_pRestoreBtn = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
}

CControlUI* CMainFrame::CreateControl( LPCTSTR pstrClassName )
{
	if(_tcscmp(pstrClassName,_T("VistorRecord"))==0)
		return new CVisitorRecordUI(&m_PaintManager);
	return NULL;
}

LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = __super::HandleMessage(uMsg, wParam, lParam);
	return lRes;
}

void CMainFrame::Notify( TNotifyUI& msg )
{
	if(msg.sType == DUI_MSGTYPE_SELECTCHANGED)
	{
		CDuiString name = msg.pSender->GetName();
		CTabLayoutUI* pTabLayoutModule = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabModule")));
		if(pTabLayoutModule)
		{
			if(name==_T("record"))
				pTabLayoutModule->SelectItem(0);
			else if(name==_T("datamanage"))
				pTabLayoutModule->SelectItem(1);
			else if(name==_T("check"))
				pTabLayoutModule->SelectItem(2);
			else if(name==_T("appointment"))
				pTabLayoutModule->SelectItem(3);
			else if(name==_T("user"))
				pTabLayoutModule->SelectItem(4);
			else if(name==_T("email"))
				pTabLayoutModule->SelectItem(5);
		}
		CTabLayoutUI* pTabLayoutRecord = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabRecord")));
		if(pTabLayoutRecord)
		{
			if(name==_T("NoRecord"))
				pTabLayoutRecord->SelectItem(0);
			else if(name==_T("LeaveRecord"))
				pTabLayoutRecord->SelectItem(1);
		}
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
}
