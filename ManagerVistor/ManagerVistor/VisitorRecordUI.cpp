#include "StdAfx.h"
#include "VisitorRecordUI.h"

CVisitorRecordUI::CVisitorRecordUI(CPaintManagerUI* pManager)
{
	CDialogBuilder builder;
	CContainerUI* pVistorRecordUI = static_cast<CContainerUI*>(builder.Create(_T("xmls\\VistorRecord.xml"),NULL,NULL,pManager,NULL));
	if( pVistorRecordUI ) 
	{
		m_pManager = pManager;
		this->Add(pVistorRecordUI);
	}
	else
	{
		this->RemoveAll();
		return;
	}
}

CVisitorRecordUI::~CVisitorRecordUI(void)
{
}

void CVisitorRecordUI::DoEvent(TEventUI& event)
{
	switch(event.Type)
	{
	case UIEVENT_RBUTTONDOWN:
		break;
	case UIEVENT_KEYDOWN:
		break;
	}
	CContainerUI::DoEvent(event);
}

