#include "StdAfx.h"
#include "RichListWnd.h"

CRichListWnd::CRichListWnd(void) : m_pCloseBtn(NULL)
 , m_pRestoreBtn(NULL)
 , m_pMaxBtn(NULL)
 , m_pMinBtn(NULL)
{
}

CRichListWnd::~CRichListWnd(void)
{
}

void CRichListWnd::OnFinalMessage( HWND hWnd )
{
	__super::OnFinalMessage(hWnd);
	delete this;
}

CDuiString CRichListWnd::GetSkinFile()
{
#ifdef _DEBUG
	return _T("skin\\RichListRes\\");
#else
	return _T("skin\\");
#endif
}

CDuiString CRichListWnd::GetSkinFolder()
{
	return _T("duilib.xml");
}

UILIB_RESOURCETYPE CRichListWnd::GetResourceType() const
{
#ifdef _DEBUG
	return UILIB_FILE;
#else
	return UILIB_ZIP;
#endif
}

CDuiString CRichListWnd::GetZIPFileName() const
{
	return _T("RichListRes.zip");
}


LPCTSTR CRichListWnd::GetWindowClassName() const
{
	return _T("RichListWnd");
}

