#include "StdAfx.h"
#include "MainFrame.h"
#include <sstream>

CMainFrame::CMainFrame(LPCTSTR pszXMLName) : m_strXMLName(pszXMLName)
, m_pCloseBtn(NULL)
, m_pMaxBtn(NULL)
, m_pMinBtn(NULL)
, m_pSearch(NULL)
//, m_pRestoreBtn(NULL)
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
//	m_pRestoreBtn = static_cast<CControlUI*>(m_PaintManager.FindControl(_T("restorebtn")));
	m_pSearch = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn")));
}


void CMainFrame::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("click") ) {
		if( msg.pSender == m_pCloseBtn ) {
			PostQuitMessage(0);
			return; 
		}
		else if( msg.pSender == m_pMinBtn ) { 
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
		else if( msg.pSender == m_pMaxBtn ) { 
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
// 		else if( msg.pSender == m_pRestoreBtn ) { 
// 			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
		else if(msg.pSender == m_pSearch)
			OnSearch();
	}
}

void CMainFrame::OnSearch()
{
	CListUI* pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("domainlist")));
	pList->SetTextCallback(this);
	for(int i=0; i<100; i++)
	{
		std::stringstream ss;
		ss << "www." << i << ".com";
//		domain.push_back(ss.str());
		ss.clear();
		ss << "it's " << i;
//		desc.push_back(ss.str());
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(i);
		
		if( pList ) pList->Add(pListElement);
	}
	return ;
}

LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = __super::HandleMessage(uMsg, wParam, lParam);
	return lRes;
}

LPCTSTR CMainFrame::GetItemText(CControlUI* pControl,int iIndex,int iSubItem)
{
	TCHAR szBuf[255]={0};
	switch(iSubItem)
	{
	case 0:
		swprintf_s(szBuf,_T("%d"),iIndex);
		break;
	case 1:
		break;
	case 2:
		break;
	}
	pControl->SetUserData(szBuf);
	return pControl->GetUserData();
}