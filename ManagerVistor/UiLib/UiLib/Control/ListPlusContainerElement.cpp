#include "StdAfx.h"
#include "ListPlusContainerElement.h"

namespace UiLib
{
	CListPlusContainerElement::CListPlusContainerElement()
	{
		m_BigCy=100;
	}

	CListPlusContainerElement::~CListPlusContainerElement()
	{
	}

	LPCTSTR CListPlusContainerElement::GetClass() const
	{
		return _T("ListContainerElementUI");
	}

	LPVOID CListPlusContainerElement::GetInterface(LPCTSTR pstrName)
	{
		if( _tcscmp(pstrName, DUI_CTR_LISTITEM) == 0 ) return static_cast<IListItemUI*>(this);
		if( _tcscmp(pstrName, _T("ListPlusContainerElement")) == 0 ) return static_cast<CListPlusContainerElement*>(this);
		return CContainerUI::GetInterface(pstrName);
	}

	void CListPlusContainerElement::DoEvent(TEventUI& event)
	{
		if (event.Type==UIEVENT_BUTTONDOWN)
		{
			if( IsEnabled() )
			{			
				//           m_pManager->SendNotify(this, DUI_MSGTYPE_ITEMCLICK);											
				
				Select();
				/*this->SetFixedHeight(m_BigCy);*/
				//Invalidate();				
			}
			
			return;
		}
		else if (event.Type==UIEVENT_RBUTTONDOWN)
		{
			if (IsEnabled())
			{
				Select();
			}
			return ;
		}
		CListContainerElementUI::DoEvent(event);
	}

	void CListPlusContainerElement::SetBigCy(int cy)
	{
		m_BigCy = cy;
	}
}

