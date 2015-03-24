#include "StdAfx.h"
#include "DataManageUI.h"
#include "VisitorList.h"

using namespace UiLib;
CDataManageUI::CDataManageUI(CPaintManagerUI* pManager)
{
	CDialogBuilder builder;
	CContainerUI* pDataManageUI = static_cast<CContainerUI*>(builder.Create(_T("xmls\\DataManage.xml"),NULL,this,pManager,NULL));
	if( pDataManageUI ) 
	{
		m_pManager = pManager;
		this->Add(pDataManageUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}	

	////CListContainerElementUI* pListItem=new CListContainerElementUI;
	//CListContainerElementUI* pListItem = NULL;
	//CDialogBuilder m_dlgBuilder;
	//pListItem = static_cast<CListContainerElementUI*>(m_dlgBuilder.Create(_T("xmls\\VisitorList_item.xml"),(UINT)0,this,m_pManager));
	//pList->InsertItem(0,70,pListItem);
}

CDataManageUI::~CDataManageUI(void)
{
}

CControlUI* CDataManageUI::CreateControl( LPCTSTR pstrClassName )
{
	if(_tcscmp(pstrClassName,_T("VisitorList"))==0)
		return new CVisitorList;
	if (_tcscmp(pstrClassName,_T("ListPlusContainerElement"))==0)
	{
		return new CListContainerElementUI;
	}
	return NULL;
}
