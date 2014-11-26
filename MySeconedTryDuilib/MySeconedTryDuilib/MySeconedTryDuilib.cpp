// MySeconedTryDuilib.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "MySeconedTryDuilib.h"
#include "MainFrame.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
//	CPaintManagerUI::SetResourceZip(_T("360SafeRes.zip"));

// 	HRESULT Hr = ::CoInitialize(NULL);
// 	if( FAILED(Hr) ) return 0;

	CMainFrame* pFrame = new CMainFrame();
	if( pFrame == NULL ) return 0;
	pFrame->Create(NULL, _T("360安全卫士"), UI_WNDSTYLE_FRAME,WS_EX_WINDOWEDGE);
	pFrame->CenterWindow();
	::ShowWindow(*pFrame, SW_SHOW);

	CPaintManagerUI::MessageLoop();//(处理消息循环)
//	::CoUninitialize();
	return 0;
}