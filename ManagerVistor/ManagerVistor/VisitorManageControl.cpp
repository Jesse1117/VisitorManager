#include "StdAfx.h"
#include "VisitorManageControl.h"
#include "VisitorRecord.h"
#include "DataManage.h"
#include "VisitorInfo.h"
#include "VisitorRecordUI.h"
#include "LANCommunicate.h"
CVisitorManageControl::CVisitorManageControl(void)
{
	
}

CVisitorManageControl::~CVisitorManageControl(void)
{
}

BOOL CVisitorManageControl::Start()
{
		m_pTakingInfoThread = CreateThread(NULL,0,TakingVisitorInfoProc,this,0,0);
		if (m_pTakingInfoThread==0)
		{
			return FALSE;
		}
		return TRUE;
}

DWORD WINAPI CVisitorManageControl::TakingVisitorInfoProc(LPVOID pParam)
{
	CVisitorManageControl* pthis = (CVisitorManageControl*) pParam;
	while (1)
	{
		if (CVisitorRecord::GetInstance()->HasData())
		{
			CVisitorInfo VisitorInfo;
			if (CVisitorRecord::GetInstance()->GetFirstData(VisitorInfo))
			{
				CDataManage Dodata;
				if (Dodata.IsAppointment(VisitorInfo))
				{
					/*��ԤԼ���� �������ݿ�*/
				}
				else
				{
					CLANCommunicate Communicate;
					if (Communicate.DoVideoVerification(VisitorInfo.GetVisitPersonNum()))
					{
						/*������� ���� ��ȡʱ�� д�����ݿ�*/
					}
					else
					{
						/*�뿪 ��ȡʱ��д�����ݿ�*/
					}
				}
			}

		}
		else Sleep(20);
	}

	return 0;
}