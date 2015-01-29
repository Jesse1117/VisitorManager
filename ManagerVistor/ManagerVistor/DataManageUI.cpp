#include "StdAfx.h"
#include "DataManageUI.h"

CDataManageUI::CDataManageUI(CPaintManagerUI* pManager)
{
	CDialogBuilder builder;
	CContainerUI* pDataManageUI = static_cast<CContainerUI*>(builder.Create(_T("xmls\\DataManage.xml"),NULL,NULL,pManager,NULL));
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
}

CDataManageUI::~CDataManageUI(void)
{
}
