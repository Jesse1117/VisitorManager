#include "StdAfx.h"
#include "ListPlusUI.h"
#include "CDuiMenu.h"
using namespace UiLib;
	CListPlusUI::CListPlusUI()
	{
	}

	CListPlusUI::~CListPlusUI()
	{
	}

	//void CListPlusUI::DoEvent(TEventUI& event)
	//{
	//	//if (event.Type==UIEVENT_RBUTTONDOWN)
	//	//{
	//	//	if (_tcscmp(event.pSender->GetClass(),_T("ListHeaderUI"))!=0)
	//	//	{
	//	//		POINT pt = event.ptMouse;
	//	//		CDuiMenu* pMenu = new CDuiMenu(_T("xmls/ListMenu.xml"));
	//	//		pMenu->Init(HWND(this),pt);
	//	//		pMenu->ShowWindow(true);
	//	//	}
	//	//}

	//	if (event.Type==UIEVENT_SCROLLWHEEL)
	//	{
	//	}
	//	CListUI::DoEvent(event);
	//}
	

	void CListPlusUI::SetItemData(int nItem,int nColumn,LPCTSTR Text, LPCTSTR Name)
	{
		CLabelUI *pLabel = new CLabelUI;
		pLabel->SetText(Text);
		pLabel->SetFixedHeight(70);
		pLabel->SetFont(2);
		pLabel->SetAttribute(_T("align"),_T("center"));
		//pLabel->SetFloat(true);
		//pLabel->SetTextStyle(DT_CENTER);
		pLabel->SetAttribute(_T("endellipsis"), _T("true"));
		pLabel->SetName(Name);
		SetItemData(nItem, nColumn, pLabel);//添加到父控件
	}

	void CListPlusUI::SetItemData(int nItem, int nColumn,CControlUI* pControl)
	{
		CHorizontalLayoutUI *pSubHor = GetListSubItem(nItem, nColumn);
		if (pSubHor!=NULL)
		{
			//pSubHor->SetAttribute(_T("inset"), _T("3,0,3,1"));
			pSubHor->RemoveAll();
			pSubHor->Add(pControl);//添加到父控件
		}
	}

	BOOL CListPlusUI::InsertColumn(
		int nCol,
		CListHeaderItemUI *pHeaderItem
		)
	{
		CListHeaderUI *pHeader = CListUI::GetHeader();
		if (pHeader == NULL)
		{
			return FALSE;
		}

		if (pHeader->AddAt(pHeaderItem, nCol))
		{		
			return TRUE;
		}

		delete pHeaderItem;
		pHeaderItem = NULL;
		return FALSE;
	}

	int CListPlusUI::InsertItem(int nItem, int nHeight)
	{
		CListContainerElementUI *pListItem = new CListContainerElementUI;
		pListItem->SetFixedHeight(nHeight);/*固定一个行高*/

		pListItem->m_pHeader = CListUI::GetHeader();
		if (NULL != pListItem->m_pHeader)
		{
			int nHeaderCount = pListItem->m_pHeader->GetCount();
			for (int i = 0; i < nHeaderCount; i++)
			{
				pListItem->Add(new CHorizontalLayoutUI);
			}
		}
		if ( !CListUI::AddAt(pListItem, nItem) )
		{
			delete pListItem;
			pListItem = NULL;
			return -1;
		}
		return nItem;
	}

	int CListPlusUI::InsertItem(int nItem, int nHeight, CListContainerElementUI *pListItem)
	{
		pListItem->SetFixedHeight(nHeight);	
		pListItem->m_pHeader =  CListUI::GetHeader();
		if ( !CListUI::AddAt(pListItem, nItem) )
		{
			delete pListItem;
			pListItem = NULL;
			return -1;
		}

		return nItem;
	}

	BOOL CListPlusUI::SetHeaderItemData(int nColumn, CControlUI* pControl)
	{
		CListHeaderUI *pHeader = CListUI::GetHeader();
		if (pHeader == NULL)
		{
			return FALSE;
		}
		CListHeaderItemUI *pHeaderItem = (CListHeaderItemUI *)pHeader->GetItemAt(nColumn);
		pHeaderItem->RemoveAll();
		pHeaderItem->Add(pControl);
		return TRUE;
	}



	CHorizontalLayoutUI* CListPlusUI::GetListSubItem(int iIndex, int iSubIndex)
	{
		//获取具体行控件
		CListContainerElementUI *pListItem = static_cast<CListContainerElementUI*>(CListUI::GetItemAt(iIndex));
		if (pListItem == NULL)
			return NULL;
		return static_cast<CHorizontalLayoutUI*>(pListItem->GetItemAt(iSubIndex));
	}

	CListContainerElementUI* CListPlusUI::GetListItem(int iIndex)
	{
		return static_cast<CListContainerElementUI*>(CListUI::GetItemAt(iIndex));
	}



