#pragma once
class CVisitorInfo;
/*访客信息登记类*/
class CVisitorRecord
{
private:
	CVisitorRecord(void);
public:
	static CVisitorRecord* GetInstance()
	{
		static CVisitorRecord *m_pInstance;
		if(m_pInstance == NULL) //判断是否第一次调用
			m_pInstance = new CVisitorRecord();
		return m_pInstance;
	}
	~CVisitorRecord(void);

	BOOL Run();
	BOOL GetFirstData(CVisitorInfo& Visitorinfo);
	 BOOL HasData();
};
