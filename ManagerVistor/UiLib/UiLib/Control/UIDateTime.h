#ifndef __UIDATETIME_H__
#define __UIDATETIME_H__

#pragma once

namespace UiLib
{
	class CDateTimeWnd;

	/// 时间选择控件
	class UILIB_API CDateTimeUI : public CLabelUI
	{
		friend class CDateTimeWnd;
	public:
		CDateTimeUI();
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		SYSTEMTIME& GetTime();
		void SetTime(SYSTEMTIME* pst);
		void SetReadOnly(bool bReadOnly);
		bool IsReadOnly() const;
		void UpdateText();
		void DoEvent(TEventUI& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	protected:
		SYSTEMTIME m_sysTime;
		int        m_nDTUpdateFlag;
		bool       m_bReadOnly;
		CDateTimeWnd* m_pWindow;
	private:
		void SetWindowShowNone();
		void SetWindowUpDown();
		void SetWindowShowExpanded();
		void SetWindowTimeFormat();
		BOOL GetWindowTimeFormat();
	};
}
#endif // __UIDATETIME_H__