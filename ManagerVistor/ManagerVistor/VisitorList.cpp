#include "StdAfx.h"
#include "VisitorList.h"
using namespace UiLib;
CVisitorList::CVisitorList()
{
}

CVisitorList::~CVisitorList(void)
{
}

void CVisitorList::Notify(TNotifyUI& msg)
{
	if (msg.sType==DUI_MSGTYPE_CLICK)
	{
		POINT pt = msg.ptMouse;
	}
}

BOOL CVisitorList::AddVisitorInfo(VisitorListInfo info,LPCTSTR StrXmlPath)
{
	CDialogBuilder dlgBuilder;
	CPaintManagerUI PaintManager;
	CListPlusContainerElement* pListItem = NULL;
	pListItem = static_cast<CListPlusContainerElement*>(dlgBuilder.Create(StrXmlPath,(UINT)0,NULL,&PaintManager));
	int nIndex = GetCount();
	InsertItem(nIndex,70,pListItem);
	//CButtonUI *pBtnPhoto = new CButtonUI;
	CButtonUI* pBtnPhoto = (CButtonUI*)PaintManager.FindSubControlByName(pListItem,_T("Photo"));
	pBtnPhoto->SetAttribute(_T("pos"),_T("20,5,0,0"));
	pBtnPhoto->SetFloat(true);
	pBtnPhoto->SetFixedWidth(60);
	pBtnPhoto->SetFixedHeight(60);
	pBtnPhoto->SetAttribute(_T("bkimage"),info.strPhotoPath);
	

	CLabelUI* pNameLabel = (CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("Visitorname"));
	pNameLabel->SetText(info.strName);
	pNameLabel=NULL;
	pNameLabel = (CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("Gender"));
	pNameLabel->SetText(info.strGender);
	pNameLabel=NULL;
	pNameLabel = (CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("VisitorNum"));
	pNameLabel->SetText(info.strVisitNum);
	pNameLabel=NULL;
	pNameLabel=(CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("IDCardNum"));
	pNameLabel->SetText(info.strCarNum);
	pNameLabel=NULL;
	pNameLabel=(CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("Address"));
	pNameLabel->SetText(info.strAddress);
	pNameLabel=NULL;
	pNameLabel=(CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("CarNum"));
	pNameLabel->SetText(info.strCarNum);
	pNameLabel=NULL;
	pNameLabel=(CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("PhoneNum"));
	pNameLabel->SetText(info.strPhoneNum);
	pNameLabel=NULL;
	pNameLabel=(CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("VisitReason"));
	pNameLabel->SetText(info.strVisitReason);
	pNameLabel=NULL;
	pNameLabel=(CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("VisitCount"));
	pNameLabel->SetText(info.strVisitCount);
	pNameLabel=NULL;
	pNameLabel=(CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("VisitTime"));
	pNameLabel->SetText(info.strVisitTime);
	pNameLabel=NULL;
	pNameLabel=(CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("LeaveTime"));
	pNameLabel->SetText(info.strLeaveTime);
	pNameLabel=NULL;
	pNameLabel=(CLabelUI*)PaintManager.FindSubControlByName(pListItem,_T("IsLeaved"));
	if (info.bLeaved)
	{
		pNameLabel->SetText(_T("ÊÇ"));
	}
	else
	{
		pNameLabel->SetText(_T("·ñ"));
	}
	return TRUE;
}