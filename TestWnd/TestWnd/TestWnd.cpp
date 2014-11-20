// TestWnd.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TestWnd.h"
#include "TestFrameWnd.h"
#define MAX_LOADSTRING 100

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath());
	CTestFrameWnd* pTestFrameWnd = new CTestFrameWnd;
	if(pTestFrameWnd==NULL)return 0;
	pTestFrameWnd->Create(NULL,_T("TestWnd"),UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pTestFrameWnd->CenterWindow();
	::ShowWindow(*pTestFrameWnd, SW_SHOW);

	CPaintManagerUI::MessageLoop();//(������Ϣѭ��)
	return 0;
}