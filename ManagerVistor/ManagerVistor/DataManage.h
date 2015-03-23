#pragma once
#include "VisitorInfo.h"
class CDataManage
{
public:
	CDataManage(void);
	~CDataManage(void);

	bool IsAppointment(const CVisitorInfo& info);
	bool SaveVisitorInfo(const CVisitorInfo& info);
		
};
