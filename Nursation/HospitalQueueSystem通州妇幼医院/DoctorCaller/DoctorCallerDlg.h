// DoctorCallerDlg.h : ͷ�ļ�
//

#pragma once
#include "Resource.h"
#include "afxcmn.h"
#include "afxwin.h"
#include <afxmt.h>
//#define WM_MY_TRAYICON (WM_USER+1)
//#define WM_MY_CLOSEWINDOW (WM_USER+2)
//#include "..\NurseStation\SocketServer.h"
//#include "..\NurseStation\SocketClient.h"
//#include "..\NurseStation\MySocketUDP.h"
//#include "..\NurseStation\NurseDef.h"
#include "DoctorController.h"
#include "../NurseStation/ListCtrlCl.h"
#include "../NurseStation/ado2.h"
#include "DownDiscardListDlg.h"


// CDoctorCallerDlg �Ի���
class CDoctorCallerDlg : public CDialog
{
// ����
public:
	CDoctorCallerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_DOCTORCALLER_DIALOG };
	//enum { IDD = IDD_DOCTORCALLER_DIALOG1 };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	CDoctorController* GetController()
	{
		return m_pDoctorController;
	}


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:

	LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);

	afx_msg void OnBnClickedButtonCall();
	afx_msg void OnBnClickedButtonRecall();
	afx_msg void OnBnClickedButtonDiscard();
	afx_msg void OnBnClickedButtonWait();
	afx_msg void OnBnClickedButtonWelcome();
	afx_msg void OnBnClickedButtonEvaluate();
	afx_msg void OnBnClickedButtonThanks();
	afx_msg void OnBnClickedButtonPause();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	BOOL TaskBarAddIcon(HWND hwnd, UINT uID, HICON hicon, LPCWSTR lpszTip);
	void AddTrayIcon();
	BOOL TaskBarDeleteIcon(HWND hwnd, UINT uID);
	void RemoveTrayIcon();
	afx_msg LRESULT OnTrayIcon(WPARAM wParam, LPARAM lParam);
	afx_msg void OnSubmenuDisplay();
	afx_msg void OnSubmenuQuit();
	afx_msg void OnClose();
	afx_msg void OnDestroy();
	afx_msg void OnMenuitemDoccall();
	afx_msg void OnMenuitemDocwait();
	afx_msg void OnNMRClickListPatient(NMHDR *pNMHDR, LRESULT *pResult);
	//����ҽ��ָ��
	BOOL SendCmd(DoctorCmdEnum eDoctorCmdEnum, CString strQueSerialId = _T(""));
	//void OnShowPatients(LPCMDRESULT pPatients);
	//void OnShowPatients(DbParam& dbParam);
	void OnShowPatients(CADORecordset& rset);

	//void InitCtrls();
	static UINT SoundThread(LPVOID pParam);
	void StopSoundThread();
	void SoundAdd(CString str);
	int GetCurSel();

public:
	CDoctorController* m_pDoctorController;

	//CListCtrl m_lstPatientList;
	CListCtrlCl m_lstPatientList;
	CButton m_btnCall;
	CButton m_btnRecall;
	CButton m_btnDiscard;
	CButton m_btnWait;
	//CButton m_btnWelcome;
	//CButton m_btnEvaluate;
	//CButton m_btnThanks;
	CButton m_btnPause;
	CButton m_btnChat;
	//CStatic m_stDocName;
	//CStatic m_stCurPatient;
	//CStatic m_stCurPatientName;

	int m_nEveryoneItem;
	//CString m_strUserID;
	//CString m_strUserName;
	//BOOL m_bCallSpecial;

	BOOL m_bHaveCall, m_bHaveWait;
	CWinThread* m_pSoundThread;
	BOOL m_bSoundThread;
	CMutex m_Mutex;
	CList<CString> m_lstStr;
	CString m_strWavLibPath;
	//CStatic m_staNum;

	typedef struct {
		CString strQueSerialId;
		QueueStatusEnum eStatus;

	} PATIENTINFO, *LPPATIENTINFO;

	CMap<int, int, PATIENTINFO, PATIENTINFO&> m_mapPatientList;

public:
	afx_msg void OnBnClickedButtonChat();

	BOOL BeforeUserQuit();

private:
	CString GetStatus(QueueStatusEnum qs);
private:
	//DbParam m_DbParam;
	//CString m_strConn;
	//CString m_strSelect;
	//BOOL m_bExpertFlag;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	void OnUpdatePatient();
	BOOL m_bCanRefrush;
	CStatic m_stOptStatus;
	afx_msg void OnBnClickedButtonReflush();
	void SetOptStatus(DoctorCmdEnum eDocCmd, BOOL bSuccess);
	BOOL m_bOptStatusSuccess;
	afx_msg void OnBnClickedButtonDoneAndDiscard();

	CDownDiscardListDlg* m_pDownDiscardListDlg;
	BOOL m_bReInlineDlg;
};

