#include "StdAfx.h"
#include "MainFrame.h"
#include <string.h>
#include "VisitorRecordUI.h"
#include "DataManageUI.h"
#include "VisitorList.h"
#include "DataDef.h"
using namespace std;

CMainFrame::CMainFrame(LPCTSTR pszXMLName) : m_strXMLName(pszXMLName)
	, m_pCloseBtn(NULL)
	, m_pMaxBtn(NULL)
	, m_pMinBtn(NULL)
	, m_pRestoreBtn(NULL)
	,m_LastElement(NULL)
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
	PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	CVisitorList* pList = static_cast<CVisitorList*>(m_PaintManager.FindControl(_T("Visitors")));	
	VisitorListInfo info2;
	CListPlusContainerElement* pListItem = NULL;
	pListItem = static_cast<CListPlusContainerElement*>(m_dlgBuilder.Create(_T("xmls\\VisitorList_item.xml"),(UINT)0,NULL,&m_PaintManager));
	pList->InsertItem(pList->GetCount(),70,pListItem);
	info2.strName=_T("ÄãÀÏÆÅ");
	info2.strGender=_T("Å®");
	info2.strPhotoPath=_T("file='Image/woman.jpg' source='50,0,270,280' dest='5,5,50,50'");

	//CListPlusContainerElement* pListItem1= new CListPlusContainerElement;
	//pList->InsertItem(pList->GetCount(),70,pListItem1);
	for (int i=0;i<100;i++)
	{
		pList->AddVisitorInfo(info2,_T("xmls\\VisitorList_item.xml"));
	}
}	

CControlUI* CMainFrame::CreateControl( LPCTSTR pstrClassName )
{
	if(_tcscmp(pstrClassName,_T("VistorRecord"))==0)
		return new CVisitorRecordUI(&m_PaintManager);
	if(_tcscmp(pstrClassName,_T("DataManage"))==0)
		return new CDataManageUI(&m_PaintManager);
	return NULL;
}

LRESULT CMainFrame::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = __super::HandleMessage(uMsg, wParam, lParam);
	return lRes;
}

void CMainFrame::Notify( TNotifyUI& msg )
{
	if(msg.sType == DUI_MSGTYPE_SELECTCHANGED){
		CDuiString name = msg.pSender->GetName();
		CTabLayoutUI* pTabLayoutModule = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabModule")));
		if(pTabLayoutModule){
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
		if(pTabLayoutRecord){
			if(name==_T("NoRecord"))
				pTabLayoutRecord->SelectItem(0);
			else if(name==_T("LeaveRecord"))
				pTabLayoutRecord->SelectItem(1);
		}
		CTabLayoutUI* pTabLayoutDataManage = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabDataManage")));
		if (pTabLayoutDataManage)
		{
			if (name==L"Visitor")
			{
				pTabLayoutDataManage->SelectItem(0);
			}
			else if (name==L"Stay")
			{
				pTabLayoutDataManage->SelectItem(1);
			}
			else if (name==L"Visited")
			{
				pTabLayoutDataManage->SelectItem(2);
			}
			else if (name==L"Blacklist")
			{
				pTabLayoutDataManage->SelectItem(3);
			}
			else if (name==L"Staffcard")
			{
				pTabLayoutDataManage->SelectItem(4);
			}
			else if (name==L"Usualcard")
			{
				pTabLayoutDataManage->SelectItem(5);
			}
			else if (name==L"Doorkeeper")
			{
				pTabLayoutDataManage->SelectItem(6);
			}

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
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; 
		}

	}
	else if (msg.sType==DUI_MSGTYPE_ITEMCLICK)
	{
		if (m_LastElement&&m_LastElement!=msg.pSender)
		{
			m_LastElement->SetFixedHeight(70);
		}
		m_LastElement = (CListPlusContainerElement*)msg.pSender;
		m_LastElement->SetFixedHeight(m_LastElement->m_BigCy);
	}
}
