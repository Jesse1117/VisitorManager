#pragma once
#include "DataDef.h"
class CVisitorInfo
{
public:
	CVisitorInfo(void);
	~CVisitorInfo(void);
	
	CDuiString GetCardNum()const{ return m_strCardNum;}
	void SetCardNum(const CDuiString& strCardNum){m_strCardNum = strCardNum;}

	CDuiString GetIdNum() const	{ return m_strIdNum;}
	void SetIdNum(const CDuiString& strIdNum){m_strIdNum = strIdNum;}

	CDuiString GetName() const {return m_strName;}
	void SetName(const CDuiString& strName){m_strName = strName;}

	Gender GetGender() const{return m_gender;}
	void SetGender(const Gender& gender){m_gender = gender;}

	CDuiString GetAddress() const {return m_strAddress;}
	void SetAddress(const CDuiString& strAddress){m_strAddress = strAddress;}

	CDuiString GetCarNum() const {return m_strCarNum;}
	void SetCarNum(const CDuiString& strCarNum){m_strCarNum = strCarNum;}

	CDuiString GetPhoneNum() const {return m_strPhoneNum;}
	void SetPhoneNum(const CDuiString& strPhoneNum){m_strPhoneNum = strPhoneNum;}

	CDuiString GetVisitReason() const {return m_strVisitReason;}
	void SetVisitReason(const CDuiString& strVisitReason){m_strVisitReason = strVisitReason;}

	CDuiString GetVisitTime() const {return m_strVisitTime;}
	void SetVisitTime(const CDuiString& strVisitTime){m_strVisitTime = strVisitTime;}

	CDuiString GetLeaveTime()const {return m_strLeaveTime;}
	void SetLeaveTime(const CDuiString& strLeaveTime){m_strLeaveTime = strLeaveTime;}

	CDuiString GetVisitPersonNum() const {return m_strVisitPersonNum;}
	void SetVisitPersonNum(const CDuiString& strVisitPersonNum){m_strVisitPersonNum = strVisitPersonNum;}

	int GetCardType()const {return m_icardtype;}
	void SetCardType(const int cardtype){m_icardtype = cardtype;}

	bool GetIsLeave()const {return m_isLeave;}
	void SetIsLeave(const bool isLeave){m_isLeave = isLeave;}

	bool GetIsAppointment()const {return m_isAppointment;}
	void SetIsAppointment(const bool isAppointment){m_isAppointment = isAppointment;}

	CDuiString GetIdPath()const {return m_strIDPath;}
	void SetIdPath(const CDuiString strIdPath){m_strIDPath = strIdPath;}

	CDuiString GetPhotoPath()const {return m_strPhotoPath;}
	void SetPhotoPath(const CDuiString strPhotoPath){m_strPhotoPath = strPhotoPath;}

	CDuiString GetVideoPath()const {return m_strVideoPath;}
	void SetVideoPath(const CDuiString strVideoPath){m_strVideoPath = strVideoPath;}
private:
	CDuiString m_strCardNum;
	CDuiString m_strIdNum;
	CDuiString m_strName;
	Gender m_gender;
	CDuiString m_strAddress;
	CDuiString m_strCarNum;
	CDuiString m_strPhoneNum;
	CDuiString m_strVisitReason;
	CDuiString m_strVisitTime;
	CDuiString m_strLeaveTime;
	CDuiString m_strVisitPersonNum;
	int m_icardtype;
	bool m_isLeave;
	bool m_isAppointment;
	CDuiString m_strIDPath;
	CDuiString m_strPhotoPath;
	CDuiString m_strVideoPath;
};
