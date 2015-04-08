#pragma once
class CVisitorInfo;
class CConectToMySql;
class CDataManage
{
public:
	CDataManage(void);
	~CDataManage(void);

	BOOL IsAppointment(const CVisitorInfo& info);
	BOOL UpdateVisitorInfo(const CVisitorInfo& info);
	
private:
	CConectToMySql* m_MySql;
};
