#pragma once
#include "ListPlusUI.h"
#include "DataDef.h"
using namespace UiLib;
class CVisitorList :
	public CListPlusUI
{
public:
	CVisitorList();
	~CVisitorList(void);

	//void Notify(TNotifyUI& msg);
	//���һ����Ϣ
	BOOL AddVisitorInfo(VisitorListInfo info,LPCTSTR StrXmlPath);
private:
	/*CPaintManagerUI& paint_manager_;*/
};
