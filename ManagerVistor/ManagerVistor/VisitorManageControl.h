#pragma once


/*ҵ���߼�������*/

class CVisitorManageControl
{
public:
	CVisitorManageControl(void);
	~CVisitorManageControl(void);

	BOOL Start();
	BOOL End();
private:
	static DWORD WINAPI TakingVisitorInfoProc(LPVOID pParam);
	HANDLE m_pTakingInfoThread;

};
