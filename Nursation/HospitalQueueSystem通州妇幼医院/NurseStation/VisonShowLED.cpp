#include "StdAfx.h"
#include "VisonShowLED.h"
#include "CommonConvert.h"
#define DEFALT_LOCAL_PORT 9527


CVisonShowLED::CVisonShowLED() : m_hInstance(NULL)
{
	LED_Initialize();
	memset(&m_tLedParam,0,sizeof(m_tLedParam));
	m_tLedParam.devType = DEVICE_TYPE_UDP;
	m_tLedParam.locPort = DEFALT_LOCAL_PORT;
	m_tLedParam.rmtPort = 6666;
	m_tLedParam.pkpLength = DEFAULT_PKP_LENGTH;
	strcpy_s(m_tLedParam.rmtHost,16,"192.168.0.99");
	m_tLedParam.dstAddr = 0;
	memset(&m_tLedSendParam,0,sizeof(m_tLedSendParam));
	m_tLedSendParam.devParam = m_tLedParam;
	m_tLedSendParam.notifyMode = NOTIFY_EVENT;
	m_tLedSendParam.wmMessage = WM_LED_NOTIFY;
}

CVisonShowLED::CVisonShowLED(HWND hWnd) : 
m_hInstance(NULL)
{
	LED_Initialize();
	memset(&m_tLedParam,0,sizeof(m_tLedParam));
	m_tLedParam.devType = DEVICE_TYPE_UDP;
	m_tLedParam.locPort = DEFALT_LOCAL_PORT;
	m_tLedParam.rmtPort = 6666;
	m_tLedParam.pkpLength = DEFAULT_PKP_LENGTH;
	strcpy_s(m_tLedParam.rmtHost,16,"192.168.0.99");
	m_tLedParam.dstAddr = 0;
	memset(&m_tLedSendParam,0,sizeof(m_tLedSendParam));
	m_tLedSendParam.devParam = m_tLedParam;
	m_tLedSendParam.notifyMode = NOTIFY_EVENT;
	m_tLedSendParam.wmMessage = WM_LED_NOTIFY;
	m_tLedSendParam.wmHandle = (long)hWnd;
}

CVisonShowLED::~CVisonShowLED(void)
{
	Destory();
}

bool CVisonShowLED::LED_Initialize()
{
	if ((m_hInstance=LoadLibrary(_T("LEDSender2010.dll")))!=NULL)
	{
		LED_Startup=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Startup");
		LED_Cleanup=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cleanup");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//���߿��ƿ��б���ؽӿں���
		LED_Report_CreateServer=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_Report_CreateServer");
		LED_Report_RemoveServer=(void (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Report_RemoveServer");
		LED_Report_RemoveAllServer=(void (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Report_RemoveAllServer");
		LED_Report_GetOnlineList=(long (_stdcall *)(long, void*, long))GetProcAddress(m_hInstance,"LED_Report_GetOnlineList");
		LED_Report_GetOnlineItemName=(char* (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_Report_GetOnlineItemName");
		LED_Report_GetOnlineItemHost=(char* (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_Report_GetOnlineItemHost");
		LED_Report_GetOnlineItemPort=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_Report_GetOnlineItemPort");
		LED_Report_GetOnlineItemAddr=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_Report_GetOnlineItemAddr");
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		LED_ResetDisplay=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_ResetDisplay");
		LED_AdjustTime=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_AdjustTime");
		LED_AdjustTimeEx=(long (_stdcall *)(PSenderParam, LPSYSTEMTIME))GetProcAddress(m_hInstance,"LED_AdjustTimeEx");
		LED_SetCurChapter=(long (_stdcall *)(PSenderParam, long))GetProcAddress(m_hInstance,"LED_SetCurChapter");
		LED_SetPower=(long (_stdcall *)(PSenderParam, long))GetProcAddress(m_hInstance,"LED_SetPower");
		LED_GetPower=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_GetPower");
		LED_SetBright=(long (_stdcall *)(PSenderParam, long))GetProcAddress(m_hInstance,"LED_SetBright");
		LED_GetBright=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_GetBright");
		LED_SetPowerSchedule=(long (_stdcall *)(PSenderParam, PPowerSchedule))GetProcAddress(m_hInstance,"LED_SetPowerSchedule");
		LED_GetPowerSchedule=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_GetPowerSchedule");
		LED_SetBrightSchedule=(long (_stdcall *)(PSenderParam, PBrightSchedule))GetProcAddress(m_hInstance,"LED_SetBrightSchedule");
		LED_GetBrightSchedule=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_GetBrightSchedule");
		LED_SendToScreen=(long (_stdcall *)(PSenderParam, long))GetProcAddress(m_hInstance,"LED_SendToScreen");
		LED_ComTransfer=(long (_stdcall *)(PSenderParam, BYTE*, DWORD))GetProcAddress(m_hInstance,"LED_ComTransfer");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//�˴���֮ǰͬ������������ͬ��ֻ�ǽ��ṹ��ָ�������ֳɶ����������������PB��java�ȿ������Ե���
		LED_UDP_SenderParam=(long (_stdcall *)(long, long, char*, long, long, long, long, long))GetProcAddress(m_hInstance,"LED_UDP_SenderParam");
		LED_COM_SenderParam=(long (_stdcall *)(long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"LED_COM_SenderParam");
		LED_UDP_SenderParam_ByReportName=(long (_stdcall *)(long, long, long, char*, long, long, long))GetProcAddress(m_hInstance,"LED_UDP_SenderParam_ByReportName");
		LED_ResetDisplay2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_ResetDisplay2");
		LED_AdjustTime2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_AdjustTime2");
		LED_AdjustTimeEx2=(long (_stdcall *)(long, LPSYSTEMTIME))GetProcAddress(m_hInstance,"LED_AdjustTimeEx2");
		
		LED_SetCurChapter2=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_SetCurChapter2");
		LED_SetPower2=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_SetPower2");
		LED_GetPower2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_GetPower2");
		LED_SetBright2=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_SetBright2");
		LED_GetBright2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_GetBright2");
		LED_SetPowerSchedule2=(long (_stdcall *)(long, PPowerSchedule))GetProcAddress(m_hInstance,"LED_SetPowerSchedule2");
		LED_GetPowerSchedule2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_GetPowerSchedule2");
		LED_SetBrightSchedule2=(long (_stdcall *)(long, PBrightSchedule))GetProcAddress(m_hInstance,"LED_SetBrightSchedule2");
		LED_GetBrightSchedule2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_GetBrightSchedule2");
		LED_SendToScreen2=(long (_stdcall *)(long, long))GetProcAddress(m_hInstance,"LED_SendToScreen2");
		LED_ComTransfer2=(long (_stdcall *)(long, BYTE*, DWORD))GetProcAddress(m_hInstance,"LED_ComTransfer2");

			///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//��ȡ���ƿ�����
		LED_Cache_GetBoardParam=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam");
		LED_Cache_GetBoardParam2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam2");
		//��ȡ��������
		LED_Cache_GetBoardParam_SaveToFile=(long (_stdcall *)(char*))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_SaveToFile");
		LED_Cache_GetBoardParam_IP=(char* (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_IP");
		LED_Cache_GetBoardParam_Mac=(char* (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_Mac");
		LED_Cache_GetBoardParam_Addr=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_Addr");
		LED_Cache_GetBoardParam_Width=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_Width");
		LED_Cache_GetBoardParam_Height=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_Height");
		LED_Cache_GetBoardParam_Brightness=(long (_stdcall *)(void))GetProcAddress(m_hInstance,"LED_Cache_GetBoardParam_Brightness");
		//�޸ĸ�������
		LED_Cache_SetBoardParam_LoadFromFile=(long (_stdcall *)(char*))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_LoadFromFile");
		LED_Cache_SetBoardParam_IP=(void (_stdcall *)(char*))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_IP");
		LED_Cache_SetBoardParam_Mac=(void (_stdcall *)(char*))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_Mac");
		LED_Cache_SetBoardParam_Addr=(void (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_Addr");
		LED_Cache_SetBoardParam_Width=(void (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_Width");
		LED_Cache_SetBoardParam_Height=(void (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_Height");
		LED_Cache_SetBoardParam_Brightness=(void (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam_Brightness");
		//���޸ĺ�Ĳ���������ƿ�
		LED_Cache_SetBoardParam=(long (_stdcall *)(PSenderParam))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam");
		LED_Cache_SetBoardParam2=(long (_stdcall *)(long))GetProcAddress(m_hInstance,"LED_Cache_SetBoardParam2");

		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		LED_GetNotifyParam=(long (_stdcall *)(PNotifyParam, long))GetProcAddress(m_hInstance,"LED_GetNotifyParam");

		MakeFromVsqFile=(long (_stdcall *)(char*, long, long, long))GetProcAddress(m_hInstance,"MakeFromVsqFile");
		MakeRoot=(long (_stdcall *)(long, long, long))GetProcAddress(m_hInstance,"MakeRoot");
		MakeChapter=(long (_stdcall *)(long, long, long, long, DWORD, WORD))GetProcAddress(m_hInstance,"MakeChapter");
		MakeRegion=(long (_stdcall *)(long, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"MakeRegion");
		MakeLeaf=(long (_stdcall *)(long, long, long, long, long, long, DWORD, WORD))GetProcAddress(m_hInstance,"MakeLeaf");
		MakeObject=(long (_stdcall *)(long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"MakeObject");

		AddChapter=(long (_stdcall *)(WORD, DWORD, WORD))GetProcAddress(m_hInstance,"AddChapter");
		AddRegion=(long (_stdcall *)(WORD, long, long, long, long, long))GetProcAddress(m_hInstance,"AddRegion");
		AddLeaf=(long (_stdcall *)(WORD, DWORD, WORD))GetProcAddress(m_hInstance,"AddLeaf");

		AddDateTime=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, long, long, long, long, long, long, long, char*))GetProcAddress(m_hInstance,"AddDateTime");
		AddCampaignEx=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, long, long, long, char*, PTimeStamp, PTimeStamp, PTimeStamp, long))GetProcAddress(m_hInstance,"AddCampaignEx");
		AddClock=(long (_stdcall *)(WORD, long, long, long, long, long, long, long, DWORD, DWORD, DWORD, long, long, long, DWORD, long, DWORD, long, DWORD, long, DWORD, long, DWORD))GetProcAddress(m_hInstance,"AddClock");
		AddMovie=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, long))GetProcAddress(m_hInstance,"AddMovie");

		AddWindows=(long (_stdcall *)(WORD, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddWindows");
		AddChildWindow=(long (_stdcall *)(WORD, HDC, long, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddChildWindow");
		AddChildPicture=(long (_stdcall *)(WORD, char*, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddChildPicture");
		AddChildText=(long (_stdcall *)(WORD, char*, char*, long, long, long, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddChildWindow");
		AddStrings=(long (_stdcall *)(WORD, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddStrings");
		AddChildString=(long (_stdcall *)(WORD, char*, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddChildString");

		AddWindow=(long (_stdcall *)(WORD, long, long, long, long, long, long, HDC, long, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddWindow");
		AddPicture=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddPicture");
		AddText=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, char*, long, long, long, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddText");
		AddString=(long (_stdcall *)(WORD, long, long, long, long, long, long, char*, long, long, long, long, long, long, long, long, long))GetProcAddress(m_hInstance,"AddString");

		if (LED_Startup) 
			LED_Startup();
		return true;
	}
	else
	{
		return false;
	}
	
}

void CVisonShowLED::Destory()
{
	if(LED_Cleanup) 
		LED_Cleanup();
 	if(m_hInstance)
 		FreeLibrary(m_hInstance);
}

void CVisonShowLED::SendDataToScreen(const CString& msg,const CString& wStrIP,const CRect& rect, DWORD lShowTime)
{
 	long index = CreateData(msg,rect,lShowTime);//���ɷ�������
	int len = CCommonConvert::CStringToChar(wStrIP,NULL);
	char* pStrIP = new char[len+1];
	memset(pStrIP,0,len+1);
	CCommonConvert::CStringToChar(wStrIP,pStrIP);
	strcpy_s(m_tLedParam.rmtHost,16,pStrIP);//IP��ַ
	delete [] pStrIP;
	m_tLedSendParam.devParam = m_tLedParam;
	if(m_hInstance)
 		LED_SendToScreen(&m_tLedSendParam,index);//����
}

void CVisonShowLED::SetHWnd(HWND hWnd)
{
	m_tLedSendParam.wmHandle = (long)hWnd;
}

long CVisonShowLED::CreateData(const CString& msg,const CRect& rect, DWORD lShowTime)
{
	DWORD left,rigth,top,bottom;
	left = rect.left;rigth = rect.right;
	top = rect.top; bottom = rect.bottom;
	long index = -1;
	if(m_hInstance)
	{
		index = MakeRoot(ROOT_PLAY,COLOR_MODE_DOUBLE,ROOT_SURVIVE_ALWAYS);
		index = MakeChapter(ROOT_PLAY_CHAPTER,ACTMODE_REPLACE,0,COLOR_MODE_DOUBLE,lShowTime,LED_WAIT_CHILD);
		index = MakeRegion(ROOT_PLAY_REGION,ACTMODE_REPLACE,0,0,COLOR_MODE_DOUBLE,left,top,rigth/2,bottom,0);
		AddRegion(index,left,top,rigth/2,bottom,0);
		AddLeaf(index,lShowTime,LED_WAIT_CHILD);
		int len = CCommonConvert::CStringToChar(msg,NULL);
		char* pStrMsg = new char[len+1];
		memset(pStrMsg,0,len+1);
		CCommonConvert::CStringToChar(msg,pStrMsg);
		AddText(index,left,top,rigth/2,bottom,0,0,pStrMsg,
			"����",12,RGB(255,0,0),WFS_NONE,1/*�Զ�����*/,0/*�����*/,
			1/*������ʾ*/,5/*�����ٶ�*/,2/*��������*/,2/*�����ٶ�*/,
			0/*������̬��ʾ*/,3/*�����ٶ�*/,lShowTime/*����ʱ��*/);
	
		delete [] pStrMsg;
	}
// 	AddLeaf(index,10*1000,LED_WAIT_CHILD);
// 	AddText(index,0,0,128,48,0,0,"song is a bitch",
// 		"����",12,RGB(255,255,0),WFS_BOLD, 1, 0, 20, 2, 1, 2, 0, 1, 10000);
// 	
// 	AddLeaf(index,10*1000,LED_WAIT_CHILD);
// 	AddText(index,0,0,128,48,0,0,"���� is a bitch",
// 		"����",12,RGB(255,255,0),WFS_BOLD, 1, 0, 20, 2, 1, 2, 0, 1, 10000);
//  	AddChapter(index, 3000000, LED_WAIT_CHILD);
//  	AddRegion(index, 0, 0, 64, 16, 0);
//  	AddLeaf(index, 10000, LED_WAIT_CHILD);
//  	AddText(index, 0, 0, 32, 16, V_TRUE, 0, 
// 		"ͬһ������ͬһ������ͬһ������ͬһ������", "����", 12, RGB(255,255,0), WFS_NONE, V_TRUE, 0, 7, 5, 1, 5, 0, 1, 3000);

	return index;
}
