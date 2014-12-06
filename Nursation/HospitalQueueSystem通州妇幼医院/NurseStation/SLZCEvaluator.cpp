// SLZCEvaluator.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SLZCEvaluator.h"


//SLZCEvaluator* SLZCEvaluator::m_pInstance=NULL;//new SLZCEvaluator;
// SLZCEvaluator
extern  void MyWriteConsole(CString str); 

SLZCEvaluator::SLZCEvaluator()
{
	Start();
//	m_windowTable.LoadWindows();
}

SLZCEvaluator::~SLZCEvaluator()
{
}

SLZCEvaluator* SLZCEvaluator::GetInstance()
{
	static SLZCEvaluator instance;
	return &instance;
}

void SLZCEvaluator::AddEvaData(SLZEvaData data)
{
	m_evaLock.Lock();
	m_pEvaDataList.AddTail(data);
	m_evaLock.Unlock();
}

BOOL SLZCEvaluator::HasData()
{
	return !m_pEvaDataList.IsEmpty();
}

SLZEvaData SLZCEvaluator::GetData()
{
	m_evaLock.Lock();
	SLZEvaData data = m_pEvaDataList.GetHead();
	m_pEvaDataList.RemoveHead();
	m_evaLock.Unlock();
	return data;
}

void SLZCEvaluator::SystemSendToEva(char* evabuf,const char* buf)
{
	//	evabuf[0]=HARDWARE_EVALTOR_HEAD;
	evabuf[0]=HARDWARE_EVALTOR_CONST;//0x68
	evabuf[1]=0x02;//��С
	evabuf[2]=0x02;
	evabuf[3]=HARDWARE_EVALTOR_CONST;
	evabuf[4]=buf[5];//��ַ
	evabuf[5]=HARDWARE_EVALTOR_TOEVA;//
	evabuf[6]=evabuf[4]+evabuf[5];//У��
	evabuf[7]=HARDWARE_EVALTOR_TAIL;//β
}

void CALLBACK SLZCEvaluator::MyDoOutTimerMsg(HWND hwnd, 
												UINT uMsg, UINT idEvent, DWORD dwTime)
{
/*	SLZCEvaluator* pEval = SLZCEvaluator::GetInstance();
	POSITION pos;
	int count=SLZCEvaluator::GetInstance()->m_listEvaltOutTime.GetCount();
	for(int i=0;i<count;i++)
	{
		EvaltOutTime Eval;
		pos=pEval->m_listEvaltOutTime.FindIndex(i);
		if(!pos)break;
		Eval=pEval->m_listEvaltOutTime.GetAt(pos);
		if(Eval.IsEvalt)//δ����
		{
			Eval.time++;
			pEval->m_listEvaltOutTime.SetAt(pos,Eval);
#ifdef _DEBUG
			CString evaid;
			evaid.Format(_T("%d"),Eval.address);
			MyWriteConsole(evaid);
#endif
			SLZWindow* pWindow = pEval->m_windowTable.QueryWindowByEvaId(Eval.address+128);
			if(!pWindow)//û���ҵ���Ӧ�Ĵ���
			{
				pEval->m_listEvaltOutTime.RemoveAt(pos);//ɾ��
				break;
			}
			if(Eval.time>pWindow->GetEvaTimeOut())
			{
				EvaltOutTime evalouttime=pEval->m_listEvaltOutTime.GetAt(pos);
				CString c_address;
				pEval->m_listEvaltOutTime.RemoveAt(pos);
				SLZEvaData evaData;
				evaData.SetEvaluatorId(evalouttime.address+128);
				evaData.SetEvaLevel(evaNone);
				pEval->AddEvaData(evaData);
			}
		}
	}
	*/
}

void SLZCEvaluator::DoEvaltorMsg(char* buf)
{
	SLZEvaData evaData;
	int address=buf[5]+128;
	evaData.SetEvaluatorId(address);
	switch(buf[7])
	{
	case HARDWARE_EVALTOR_GRADEZERO://��
		evaData.SetEvaLevel(evaBad);
		break;
	case HARDWARE_EVALTOR_GRADEONE://һ��
		evaData.SetEvaLevel(evaNormal);
		break;
	case HARDWARE_EVALTOR_GRADETWO://��
		evaData.SetEvaLevel(evaGood);
		break;
	case HARDWARE_EVALTOR_GRADETHREE://�ܺ�
		evaData.SetEvaLevel(evaPefect);
		break;
	}
	AddEvaData(evaData);
}


void SLZCEvaluator::IsOutTimeAndReser(char* buf)
{
	EvaltOutTime Eval;
	POSITION pos;
	int count=m_listEvaltOutTime.GetCount();
	for(int i=0;i<count;i++)
	{
		pos=m_listEvaltOutTime.FindIndex(i);
		if(!pos)break;
		Eval=m_listEvaltOutTime.GetAt(pos);
		if(Eval.address==buf[5])
		{
			Eval.IsEvalt=FALSE;
			Eval.time=0;
			m_listEvaltOutTime.SetAt(pos,Eval);
			break;
		}
	}
}

void SLZCEvaluator::StartEvaltor(char* buf)
{
	EvaltOutTime Eval;
	POSITION pos;
	BOOL isAt=FALSE;
	int count=m_listEvaltOutTime.GetCount();
	for(int i=0;i<count;i++)
	{
		pos=m_listEvaltOutTime.FindIndex(i);
		if(!pos)break;
		Eval=m_listEvaltOutTime.GetAt(pos);
		if(Eval.address==buf[5]+0xffffff80)
		{
			Eval.IsEvalt=TRUE;
			Eval.time=0;
			m_listEvaltOutTime.SetAt(pos,Eval);
			isAt=TRUE;
			break;
		}
	}
	if(!isAt)
	{
		EvaltOutTime neweval;
		neweval.address=buf[5]+0xffffff80;
		neweval.IsEvalt=TRUE;
		neweval.time=0;
		m_listEvaltOutTime.AddTail(neweval);
	}
}

BOOL SLZCEvaluator::Start()
{
	SetTimer(NULL,0,1000,MyDoOutTimerMsg);
	return TRUE;
}

BOOL SLZCEvaluator::ReFlushWindowTable()
{
//	return m_windowTable.LoadWindows();
	return TRUE;
}