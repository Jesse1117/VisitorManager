#pragma once

class CPageTwo : public CNotifyPump
{
public:
	CPageTwo();
	~CPageTwo();
	void SetPaintMagager(CPaintManagerUI* pPaintMgr);
	virtual void OnClick( TNotifyUI& msg );
	virtual void OnSelectChanged( TNotifyUI &msg );
	virtual void OnItemClick( TNotifyUI &msg );
	virtual void Notify(TNotifyUI& msg);
private:
	CPaintManagerUI* m_pPaintManager;
};
