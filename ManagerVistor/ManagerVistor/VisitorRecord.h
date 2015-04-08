#pragma once
class CVisitorInfo;
/*�ÿ���Ϣ�Ǽ���*/
class CVisitorRecord
{
private:
	CVisitorRecord(void);
public:
	static CVisitorRecord* GetInstance()
	{
		static CVisitorRecord *m_pInstance;
		if(m_pInstance == NULL) //�ж��Ƿ��һ�ε���
			m_pInstance = new CVisitorRecord();
		return m_pInstance;
	}
	~CVisitorRecord(void);

	BOOL Run();
	BOOL GetFirstData(CVisitorInfo& Visitorinfo);
	 BOOL HasData();
};
