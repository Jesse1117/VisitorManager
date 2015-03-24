#include "StdAfx.h"
#include "MainFrame.h"
#include <string.h>

#include "VisitorRecordUI.h"
#include "ConectToMySql.h"
#include "ConstDataDef.h"

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
	InitSearchCtrl();
	AddCertitypeMsg();
	
// 	CListUI* pList = static_cast<CListUI*>(m_PaintManager.FindControl(L"VisitorList"));
// 	CListContainerElementUI* pListItem = new CListContainerElementUI;
// 	if (!m_dlgBuilder.GetMarkup()->IsValid())
// 	{	
// 		/*pListItem = (CListContainerElementUI*)(m_dlgBuilder.Create(L"VisitorList_item.xml"),(UINT)0,NULL,&m_PaintManager);*/
// //		pList->Add(pListItem);
// //		pListItem->SetFixedHeight(30);
// 	}
// 	else {
// 		pListItem = static_cast<CListContainerElementUI*>(m_dlgBuilder.Create((UINT)0, &m_PaintManager));
// 	}
	//pListItem = (CListContainerElementUI*)(m_dlgBuilder.Create(L"VisitorList_item.xml"),(UINT)0,NULL,&m_PaintManager);
	//pList->Add(pListItem);
	//pListItem->SetFixedHeight(30);
	//CListContainerElementUI* pListItem =  NULL;

	//CListHeaderItemUI* pListHeaderItem = new CListHeaderItemUI;
	//pList->Add(pListHeaderItem);
	//pListHeaderItem->SetText(L"ÐÕÃû");
	//pListHeaderItem->SetFixedWidth(40);
	//pListHeaderItem->SetFixedHeight(30);
	//pListHeaderItem->SetSepWidth(1);
	//pListHeaderItem->SetHotImage(L"Image\list_header_hot.png");
	
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
	if(_tcscmp(pstrClassName,_T("DataManage"))==0)
		return new CDataManageUI(&m_PaintManager);
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
	if(msg.sType == DUI_MSGTYPE_SELECTCHANGED){
		CDuiString name = msg.pSender->GetName();
		CTabLayoutUI* pTabLayoutModule = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tabModule")));
		if(pTabLayoutModule){
			if(name==_T("record")){
				pTabLayoutModule->SelectItem(0);
			}
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
			if (name==_T("Visitor"))
			{
				pTabLayoutDataManage->SelectItem(0);
			}
			else if (name==_T("Stay"))
			{
				pTabLayoutDataManage->SelectItem(1);
			}
			else if (name==_T("Visited"))
			{
				pTabLayoutDataManage->SelectItem(2);
			}
			else if (name==_T("Blacklist"))
			{
				pTabLayoutDataManage->SelectItem(3);
			}
			else if (name==_T("Staffcard"))
			{
				pTabLayoutDataManage->SelectItem(4);
			}
			else if (name==_T("Usualcard"))
			{
				pTabLayoutDataManage->SelectItem(5);
			}
			else if (name==_T("Doorkeeper"))
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

void CMainFrame::InitSearchCtrl()
{
	m_pCertiTypeCombo = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("CertiTypeCombo")));
	m_pCertiNumEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("CertiNumEdit")));
	m_pVistorNameEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("VistorNameEdit")));
	m_pSexCombo = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("SexCombo")));
	m_pCardNumEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("CardNumEdit")));
	m_pAddressEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("AddressEdit")));
	m_pCarNumCombo = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("CarNumCombo")));
	m_pCarNumEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("CarNumEdit")));
	m_pCarTypeCombo = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("CarTypeCombo")));
	m_pAddCarTypeBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("AddCarTypeBtn")));
	m_pVistorUnitEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("VistorUnitEdit")));
	m_pVistorPhoneNumEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("VistorPhoneNumEdit")));
	m_pVistorNumCombo = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("VistorNumCombo")));
	m_pAddVistorBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("AddVistorBtn")));
	m_pLeaveDate = static_cast<CDateTimeUI*>(m_PaintManager.FindControl(_T("LeaveDate")));
	m_pLeaveTime = static_cast<CDateTimeUI*>(m_PaintManager.FindControl(_T("LeaveTime")));
	m_pBatchCombo = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("BatchCombo")));
	m_pAddBatchBtn = static_cast<CButtonUI*>(m_PaintManager.FindControl(_T("AddBatchBtn")));
}

void CMainFrame::AddCertitypeMsg()
{
// 	CListLabelElementUI* pListItem1 = new CListLabelElementUI;
// 	pListItem1->SetOwner(m_pCertiTypeCombo);
// 	pListItem1->SetText(CERTITYPE_SECOND_GENIDCARD);
// 	m_pCertiTypeCombo->Add(pListItem1);
// 
// 	CListLabelElementUI* pListItem2 = new CListLabelElementUI;
// 	pListItem2->SetText(CERTITYPE_FIRST_GENIDCARD);
// 	pListItem2->SetOwner(m_pCertiTypeCombo);
// 	m_pCertiTypeCombo->Add(pListItem2);
// 
// 	CListLabelElementUI* pListItem3 = new CListLabelElementUI;
// 	pListItem3->SetText(CERTITYPE_HONGKANG_PERMIT);
// 	pListItem3->SetOwner(m_pCertiTypeCombo);
// 	m_pCertiTypeCombo->Add(pListItem3);
// 	
// 	CListLabelElementUI* pListItem4 = new CListLabelElementUI;
// 	pListItem4->SetText(CERTITYPE_INTERNA_PASSPORT);
// 	pListItem4->SetOwner(m_pCertiTypeCombo);
// 	m_pCertiTypeCombo->Add(pListItem4);
// 
// 	CListLabelElementUI* pListItem5 = new CListLabelElementUI;
// 	pListItem5->SetText(CERTITYPE_HVPS);
// 	pListItem5->SetOwner(m_pCertiTypeCombo);
// 	m_pCertiTypeCombo->Add(pListItem5);
// 
// 	CListLabelElementUI* pListItem6 = new CListLabelElementUI;
// 	pListItem6->SetText(CERTITYPE_DRIVER_LICENSE);
// 	pListItem6->SetOwner(m_pCertiTypeCombo);
// 	m_pCertiTypeCombo->Add(pListItem6);
// 
// 	CListLabelElementUI* pListItem7 = new CListLabelElementUI;
// 	pListItem7->SetText(CERTITYPE_MILIT_OFFICER);
// 	pListItem7->SetOwner(m_pCertiTypeCombo);
// 	m_pCertiTypeCombo->Add(pListItem7);
// 
// 	CListLabelElementUI* pListItem8 = new CListLabelElementUI;
// 	pListItem8->SetText(CERTITYPE_SOLDIERS_CARD);
// 	pListItem8->SetOwner(m_pCertiTypeCombo);
// 	m_pCertiTypeCombo->Add(pListItem8);
	for(int i=0;i<31;i++)
	{
		CListLabelElementUI* pListItem = new CListLabelElementUI;
		pListItem->SetText(CarPrefix[i]);
//		pListItem->SetOwner(m_pCarNumCombo);
		m_pCarNumCombo->Add(pListItem);
	}
}