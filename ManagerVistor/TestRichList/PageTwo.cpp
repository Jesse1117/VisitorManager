#include "StdAfx.h"
#include "PageTwo.h"

/*
DUI_BEGIN_MESSAGE_MAP(CPageTwo, CNotifyPump)
DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK,OnClick)
DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED,OnSelectChanged)
DUI_ON_MSGTYPE(DUI_MSGTYPE_ITEMCLICK,OnItemClick)
DUI_END_MESSAGE_MAP()
*/
CPageTwo::CPageTwo(void) : m_pPaintManager(NULL)
{
}

CPageTwo::~CPageTwo(void)
{
}

void CPageTwo::SetPaintMagager(CPaintManagerUI* pPaintMgr)
{
	ASSERT(pPaintMgr);
	m_pPaintManager = pPaintMgr;
}

void CPageTwo::OnClick( TNotifyUI& msg )
{

}

void CPageTwo::OnItemClick( TNotifyUI &msg )
{

}

void CPageTwo::OnSelectChanged( TNotifyUI &msg )
{

}

void CPageTwo::Notify(TNotifyUI& msg)
{
	if(msg.sType == DUI_MSGTYPE_CLICK){
		OnClick(msg);
	}
	else if(msg.sType == DUI_MSGTYPE_SELECTCHANGED){
		OnSelectChanged(msg);
	}
	else if(msg.sType == DUI_MSGTYPE_ITEMCLICK){
		OnItemClick(msg);
	}
}