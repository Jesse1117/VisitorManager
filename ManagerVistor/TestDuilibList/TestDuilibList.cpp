// TestDuilibList.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TestDuilibList.h"
#include "MainFrame.h"

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	//	CPaintManagerUI::SetResourcePath(_T("xmls"));
	CMainFrame *pFrame = new CMainFrame(_T("List.xml"));
	pFrame->Create(NULL, _T("MainFrameWnd"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pFrame->ShowModal();
	delete pFrame;
	return 0;
}