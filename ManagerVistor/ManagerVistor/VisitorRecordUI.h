#pragma once

class CVisitorRecordUI : public CContainerUI 
{
public:
	CVisitorRecordUI(CPaintManagerUI* pManager);
	~CVisitorRecordUI(void);
protected:
	CPaintManagerUI* m_pManager;
};
