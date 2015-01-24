#pragma once

class CPageOne : public CNotifyPump
{
public:
	CPageOne();
	~CPageOne();
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);
//	DUI_DECLARE_MESSAGE_MAP()
	virtual void OnClick(TNotifyUI& msg);
	virtual void OnSelectChanged( TNotifyUI &msg );
	virtual void OnItemClick( TNotifyUI &msg );
	virtual void Notify(TNotifyUI& msg);
private:
	CPaintManagerUI* m_pPaintManager;
};
