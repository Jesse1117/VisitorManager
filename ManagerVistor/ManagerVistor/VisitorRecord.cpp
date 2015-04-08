#include "StdAfx.h"
#include "VisitorRecord.h"
#include "VisitorInfo.h"

CVisitorRecord::CVisitorRecord(void)
{
}

CVisitorRecord::~CVisitorRecord(void)
{
}

BOOL CVisitorRecord::Run()
{
	return TRUE;
}

BOOL CVisitorRecord::GetFirstData(CVisitorInfo& VisitorInfo)
{
	return TRUE;
}

BOOL CVisitorRecord::HasData()
{
	return TRUE;
}