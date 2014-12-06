#pragma once

#include "SLZEvaData.h"
#include "afxmt.h"
#include "HardWareDef.h"
//#include "SLZWindowQueryView.h"


// SLZCEvaluator ����Ŀ��

class SLZCEvaluator
{
	friend class CDoComInOut;
	friend class SLZCCaller;
private:
	SLZCEvaluator();
public:
	//////////////�ӿ�
	BOOL HasData();
	SLZEvaData GetData();
	~SLZCEvaluator();
	///////////////////////�õ�Ψһʵ��
	static SLZCEvaluator* GetInstance();//��������(�������ʵ��) 
	//////////////////////////
	BOOL ReFlushWindowTable();//ˢ�´�����
private:
	CList<SLZEvaData,SLZEvaData&> m_pEvaDataList; 
	CMutex m_evaLock;
private:
	static void CALLBACK MyDoOutTimerMsg(
		HWND hwnd, // handle of window for timer messages
		UINT uMsg, // WM_TIMER message
		UINT idEvent, // timer identifier
		DWORD dwTime // current system time	
		);///�ص���������ʱ��
	CList<EvaltOutTime,EvaltOutTime&> m_listEvaltOutTime;
	BOOL Start();
	//////////////�������
	void AddEvaData(SLZEvaData data);
private:
	void SystemSendToEva(char* evabuf,const char* buf);
	//������������
	void DoEvaltorMsg(char* buf);
	//�ж����۳�ʱ����ֵ
	void IsOutTimeAndReser(char* buf);
	void StartEvaltor(char* buf);//�������۳�ʱ
private:
//	SLZWindowQueryView m_windowTable;//���ļ������Ĵ�����Ϣ��
};


