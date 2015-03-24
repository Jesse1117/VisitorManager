#pragma once

namespace UiLib
{
	class UILIB_API CListPlusContainerElement :
		public CListContainerElementUI
	{
	public:
		CListPlusContainerElement();
		~CListPlusContainerElement();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		void DoEvent(TEventUI& event);
		void SetBigCy(int cy);

		int m_BigCy;
	};

}
