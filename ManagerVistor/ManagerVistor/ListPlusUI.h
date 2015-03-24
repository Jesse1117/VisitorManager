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

	/* ��ȡĳһ�е�Elementָ��  iIndex���к�*/
	CListContainerElementUI* GetListItem(int iIndex);

	/*��ȡĳһ��ĳһ�еľ���ؼ�  iIndex���к�  iSubIndex���к�*/
	CHorizontalLayoutUI* GetListSubItem(int iIndex, int iSubIndex);
	
	/*���ñ�ͷ�ؼ�  nColumn���к� pControl���ؼ�*/
	BOOL SetHeaderItemData(int nColumn, CControlUI* pControl);

	/*����һ�� nCol���к�*/
	BOOL InsertColumn( int nCol, CListHeaderItemUI *pHeaderItem );

	/*����һ����*/
	int InsertItem(int nItem, int nHeight =70);

	/*����һ��*/
	int InsertItem(int nItem, int nHeight, CListContainerElementUI *pListItem);
	
	/*����ĳһ��һ�е�����*/
	void SetItemData(int nItem, int nColumn, LPCTSTR Text, LPCTSTR Name);
	
	/*����ĳһ��ĳһ�еĿؼ�*/
	void SetItemData(int nItem, int nColumn, CControlUI* pControl);

	//DUI_DECLARE_MESSAGE_MAP()
	//virtual void OnItemClick(TNotifyUI& msg);
private:
	//CPaintManagerUI& paint_manager_;

	//CDialogBuilder m_dlgBuilder;
};

#endif