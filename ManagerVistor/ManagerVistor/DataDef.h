#ifndef _VISITORMANAGER_DATADEF_H
#define _VISITORMANAGER_DATADEF_H

struct VisitorListInfo
{
	CDuiString strPhotoPath;
	CDuiString strName;
	CDuiString strGender;
	CDuiString strVisitNum;
	CDuiString strIDNum;
	CDuiString strAddress;
	CDuiString strCarNum;
	CDuiString strPhoneNum;
	CDuiString strVisitReason;
	CDuiString strVisitCount;
	CDuiString strVisitTime;
	CDuiString strLeaveTime;
	BOOL bLeaved;
};

typedef enum _tagGenderEnum
{
	gdNotDefined		= 0,	//δ����
	gdMale				= 1,	//��
	gdFemale			= 2		//Ů
} Gender;

#endif