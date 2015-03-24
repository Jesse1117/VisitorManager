#ifndef UIVISITORLIST_H
#define UIVISITORLIST_H

#include "DataDef.h"


using namespace UiLib;
class CListPlusUI :
	public CListUI
{
public:
	CListPlusUI();
	~CListPlusUI();

	void DoEvent(TEventUI& event);

	/* 获取某一行的Element指针  iIndex：行号*/
	CListContainerElementUI* GetListItem(int iIndex);

	/*获取某一行某一列的具体控件  iIndex：行号  iSubIndex：列号*/
	CHorizontalLayoutUI* GetListSubItem(int iIndex, int iSubIndex);
	
	/*设置表头控件  nColumn：列号 pControl：控件*/
	BOOL SetHeaderItemData(int nColumn, CControlUI* pControl);

	/*插入一列 nCol：列号*/
	BOOL InsertColumn( int nCol, CListHeaderItemUI *pHeaderItem );

	/*插入一空行*/
	int InsertItem(int nItem, int nHeight =70);

	/*插入一行*/
	int InsertItem(int nItem, int nHeight, CListContainerElementUI *pListItem);
	
	/*设置某一行一列的文字*/
	void SetItemData(int nItem, int nColumn, LPCTSTR Text, LPCTSTR Name);
	
	/*设置某一行某一列的控件*/
	void SetItemData(int nItem, int nColumn, CControlUI* pControl);

	//DUI_DECLARE_MESSAGE_MAP()
	//virtual void OnItemClick(TNotifyUI& msg);
private:
	//CPaintManagerUI& paint_manager_;

	//CDialogBuilder m_dlgBuilder;
};

#endif