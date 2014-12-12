// ManagerVistor.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "ManagerVistor.h"
#include "MainFrame.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
					   HINSTANCE hPrevInstance,
					   LPTSTR    lpCmdLine,
					   int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	//	CPaintManagerUI::SetResourcePath(_T("xmls"));
	CMainFrame *pFrame = new CMainFrame(_T("xmls\\MainFrame.xml"));
	pFrame->Create(NULL, _T("MainFrameWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pFrame->ShowModal();
	delete pFrame;
	return 0;
}