#pragma once

struct VisitorListItemInfo
{
	bool empty;
	CDuiString id;
	CDuiString logo;
	CDuiString nick_name;
	CDuiString description;
};
class CVisitorListUI :
	public CListUI
{
public:
	CVisitorListUI(CPaintManagerUI* paint_manager);
	~CVisitorListUI();
private:
	CPaintManagerUI* paint_manager_;

	CDialogBuilder m_dlgBuilder;
};
