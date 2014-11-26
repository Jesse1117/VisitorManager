#pragma once

class ComputerExamineUI : public CContainerUI
{
public:
	ComputerExamineUI()
	{
		CDialogBuilder builder;
		CContainerUI* pComputerExamine = static_cast<CContainerUI*>(builder.Create(_T("ComputerExamine.xml"), (UINT)0));
		if( pComputerExamine ) {
			this->Add(pComputerExamine);
		}
		else {
			this->RemoveAll();
			return;
		}
	}

};

class CExamineBuliderCallbackEx : public IDialogBuilderCallback
{
public:
	CControlUI* CreateControl(LPCTSTR pstrClass)
	{
		if( _tcscmp(pstrClass, _T("ComputerExamine")) == 0 ) return new ComputerExamineUI;
		return NULL;
	}
};

class CFirst1XMLDialog : public CContainerUI,public INotifyUI
{
public:
	CFirst1XMLDialog()
	{
		CExamineBuliderCallbackEx examine;
		CDialogBuilder builder;
		CContainerUI* pFirst1XMLUI = static_cast<CContainerUI*>(builder.Create(_T("First1.xml"),NULL,&examine));
		if( pFirst1XMLUI ) {
			this->Add(pFirst1XMLUI);
		}
		else {
			this->RemoveAll();
			return;
		}
	}

	void Notify(TNotifyUI& msg)
	{
		if(msg.sType==_T("selectchanged"))
		{
			CDuiString name = msg.pSender->GetName();
			CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("switch")));
			if(name==_T("examine"))
				pControl->SelectItem(0);
			else if(name==_T("trojan"))
				pControl->SelectItem(1);
			else if(name==_T("plugins"))
				pControl->SelectItem(2);
			else if(name==_T("vulnerability"))
				pControl->SelectItem(3);
			else if(name==_T("rubbish"))
				pControl->SelectItem(4);
			else if(name==_T("cleanup"))
				pControl->SelectItem(5);
			else if(name==_T("fix"))
				pControl->SelectItem(6);
			else if(name==_T("tool"))
				pControl->SelectItem(7);
		}
	}
public:
	CPaintManagerUI m_pm;
};

class CDialogBuilderCallbackEx : public IDialogBuilderCallback
{
public:
	CControlUI* CreateControl(LPCTSTR pstrClass) 
	{
//		if( _tcscmp(pstrClass, _T("ComputerExamine")) == 0 ) return new ComputerExamineUI;
		if(_tcscmp(pstrClass,_T("First1")) == 0) return new CFirst1XMLDialog;
		return NULL;
	}
};

