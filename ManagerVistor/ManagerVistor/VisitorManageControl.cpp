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
					/*有预约发卡 保存数据库*/
				}
				else
				{
					CLANCommunicate Communicate;
					if (Communicate.DoVideoVerification(VisitorInfo.GetVisitPersonNum()))
					{
						/*允许进入 发卡 获取时间 写入数据库*/
					}
					else
					{
						/*离开 获取时间写入数据库*/
					}
				}
			}

		}
		else Sleep(20);
	}

	return 0;
}