#ifndef __MYDATETIMEUI_H__
#define __MYDATETIMEUI_H__

#pragma once



namespace UiLib
{
	class CMyDateTimeWnd;

	class CMyDateTimeUI : public CLabelUI
	{	
		friend class CMyDateTimeWnd;
	public:
		CMyDateTimeUI(void);
		~CMyDateTimeUI(void);
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		SYSTEMTIME& GetTime();
		void SetTime(SYSTEMTIME* pst);
		void SetReadOnly(bool bReadOnly);
		bool IsReadOnly() const;
		void UpdateText();
		void DoEvent(TEventUI& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void SetWindowShowNone();//ÓÐcheckbox
		void SetWindowUpDown();
		void SetWindowShowExpanded();
		void PaintBkColor(HDC hDC);
	protected:
		SYSTEMTIME m_sysTime;
		int m_nDTUpdateFlag;
		bool m_bReadOnly;
		CMyDateTimeWnd* m_pWindow;
	};
}

#endif