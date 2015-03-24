#pragma once	
#include "stdafx.h"
#include "ExcelInterface.h"

ExcelData::ExcelData()
{
	m_DataList.clear();
}

ExcelData::~ExcelData()
{
	m_DataList.clear();
}

void ExcelData::push_back(const wstring& wstr)
{
	m_DataList.push_back(wstr);
}

void ExcelData::insert_at(const wstring& wstr,int pos)
{
	if (m_DataList.empty() || m_DataList.begin() == m_DataList.end())
	{
		m_DataList.push_back(wstr);
	}
	list<wstring>::iterator it = m_DataList.begin();
	int mypos = 0;
	for (;it!=m_DataList.end();++it)
	{
		++mypos;
		if (pos == mypos)
		{
			m_DataList.insert(++it,wstr);
			break;
		}
	}
	if (pos!=mypos)
	{
		::MessageBox(NULL,_T("��������Χ��"),_T("��ʾ"),NULL);
	}

}

void ExcelData::delete_front()
{
	if (m_DataList.empty())
	{
		MessageBox(NULL,_T("�Ѿ�û��������"),_T("��ʾ"),NULL);
	}
	else
	{
		m_DataList.pop_front();
	}
}

void ExcelData::remove(const wstring& val)
{
	if (m_DataList.empty())
	{
		::MessageBox(NULL,_T("�յ�����"),_T("��ʾ"),NULL);
	}
	else
	{
		m_DataList.remove(val);
	}
}

wstring ExcelData::get_front()
{

	return m_DataList.front();
}

void ExcelData::clear()
{
	m_DataList.clear();
}

BOOL ExcelData::empty()
{
	return m_DataList.empty();
}

OperateExcel::OperateExcel(){ VariantInit(&m_VArray);}
OperateExcel::~OperateExcel(){ VariantClear(&m_VArray);}
HRESULT OperateExcel::AutoWrap(const int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName,const int cArgs ...)
{
	va_list marker;
	va_start(marker, cArgs);//��ͬ��(char*)(&cArgs)+4��������ָ��cArgs��ָ��ָ��������һ������
	if(!pDisp) {
		MessageBox(NULL,_T("�յĽӿ�"),_T("��ʾ"),NULL);
		_exit(0);
	}
	// Invoke�����Ĳ���
	DISPPARAMS dp = { NULL, NULL, 0, 0 };
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	DISPID dispID;
	HRESULT hr;
	hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
	if(FAILED(hr)) 
	{
		MessageBox(NULL,_T("�Ҳ����ú���������"),_T("��ʾ"),NULL);
		_exit(0);
		return hr;
	}
	VARIANT *pArgs = new VARIANT[cArgs+1]; 
	for(int i=0; i<cArgs; i++) {
		pArgs[i] = va_arg(marker, VARIANT);//�õ���һ��������ֵ������ָ��ָ��ڶ�������
	}
	dp.cArgs = cArgs;
	dp.rgvarg = pArgs;
	if(autoType & DISPATCH_PROPERTYPUT) {
		dp.cNamedArgs = 1;
		dp.rgdispidNamedArgs = &dispidNamed;
	}
	hr = pDisp->Invoke(dispID, IID_NULL, LOCALE_SYSTEM_DEFAULT, autoType, &dp, pvResult, NULL, NULL);
	va_end(marker);
	delete [] pArgs;
	return hr;
}

// ����������󲢻�ýӿ�ָ��
IDispatch* OperateExcel::CreateInstance()
{
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(L"Excel.Application",&clsid);
	if (FAILED(hr))
	{
		MessageBox(NULL,_T("��ȡIDʧ��"),_T("��ʾ"),NULL);
		exit(0);
	}
	IDispatch *pApp;
	hr = CoCreateInstance(clsid,NULL,CLSCTX_LOCAL_SERVER,IID_IDispatch,(void**)&pApp);
	if (FAILED(hr))
	{
		MessageBox(NULL,_T("�����Ƿ��Ѱ�װExcel"),_T("��ʾ"),NULL);
		exit(1);
	}
	// ����Application.visible���ԣ�1Ϊ�ɼ���0Ϊ���ɼ�
	VARIANT pro;
	pro.vt = VT_I4;
	pro.lVal = 0;
	AutoWrap(DISPATCH_PROPERTYPUT, NULL,pApp, L"Visible", 1, pro);
	return pApp;
}

// ��ȡ������
IDispatch* OperateExcel::GetWorkbook(IDispatch* const pApp)
{
	VARIANT result;
	VariantInit(&result);
	AutoWrap(DISPATCH_PROPERTYGET, &result,pApp, L"Workbooks", 0);
	IDispatch* pBooks = result.pdispVal;
	VARIANT result2;
	VariantInit(&result2);
	AutoWrap(DISPATCH_PROPERTYGET,&result2,pBooks,L"Add",0);
	IDispatch* pBook = result2.pdispVal;
	return pBook;
}

// ��õ�ǰ������
IDispatch* OperateExcel::GetActiveSheet(IDispatch* const pApp)
{
	VARIANT result;
	VariantInit(&result);
	AutoWrap(DISPATCH_PROPERTYGET,&result,pApp,L"ActiveSheet",0);
	IDispatch* pSheet = result.pdispVal;
	return pSheet;
}

// ��ȡ��Ԫ��
IDispatch* OperateExcel::GetRange(IDispatch* const pSheet,const int row,const int col,const int startrow,const int startcol)
{
	int ms = startcol/26;
	int ns = startcol%26;
	int me = (startcol+col-1)/26;
	int ne = (startcol+col-1)%26;
	WCHAR sbcol,dbcol1,dbcol2,encol,endcol1,endcol2;
	WCHAR Rangearr[24];
	if (!ms)
	{
		sbcol = 'A'+startcol-1;
		if (!me)

		{
			encol = 'A'+ne-1;
			wsprintf(Rangearr,L"%c%d:%c%d",sbcol,startrow,encol,startrow+row-1);
		}
		else
		{
			endcol1 = 'A'+me-1;
			endcol2 = 'A'+ne-1;
			wsprintf(Rangearr,L"%c%d:%c%c%d",sbcol,startrow,endcol1,endcol2,startrow+row-1);
		}

	}
	else
	{
		dbcol1 = 'A'+ms-1;
		dbcol2 = 'A'+ns-1;
		endcol1 = 'A'+me-1;		
		endcol2 = 'A'+ne-1;
		wsprintf(Rangearr,L"%c%c%d:%c%c%d",dbcol1,dbcol2,startrow,endcol1,endcol2,startrow+row-1);
	}
	// ���ϲ�����Ϊ�˰�����ת��Ϊexcel��ʾ��Χ�ķ�ʽ
	VARIANT zone;
	zone.vt = VT_BSTR;
	zone.bstrVal = SysAllocString(Rangearr);
	VARIANT result;
	VariantInit(&result);
	AutoWrap(DISPATCH_PROPERTYGET,&result,pSheet,L"Range",1,zone);
	IDispatch* pRange = result.pdispVal;
	VariantClear(&zone);
	return pRange;
}

// ����˽�г�Աm_VArray���������excel
void OperateExcel::FillArray(const int row,const int col,ExcelData* data)
{
	if (!data)
	{
		MessageBox(NULL,_T("�յ�����"),_T("��ʾ"),NULL);
	}
	VariantInit(&m_VArray);
	m_VArray.vt = VT_ARRAY|VT_VARIANT;
	SAFEARRAYBOUND sab[2];
	sab[0].lLbound = 1; sab[0].cElements = row;
	sab[1].lLbound = 1; sab[1].cElements = col;
	m_VArray.parray = SafeArrayCreate(VT_VARIANT, 2, sab);
	for (int i=1;i<=row;++i)
	{
		for (int j=1;j<=col;++j)
		{
			VARIANT tmp;
			tmp.vt = VT_BSTR;
			if (data->empty())
			{
			}
			else
			{
				wstring wstr = data->get_front();
				data->delete_front();
				tmp.bstrVal = SysAllocString(wstr.c_str());
				// ������ݵ�������
				long indices[] = {i,j};
				SafeArrayPutElement(m_VArray.parray, indices, (void *)&tmp);	
			}
		}
	}
}

// �������
IDispatch* OperateExcel::GetFont(IDispatch* const pRange)
{
	VARIANT result;
	VariantInit(&result);
	AutoWrap(DISPATCH_PROPERTYGET, &result,pRange, L"Font", 0);
	IDispatch *pFont = result.pdispVal;	
	return pFont;
}

// ���excel
void OperateExcel::FillExcel(IDispatch* const pRange)
{
	AutoWrap(DISPATCH_PROPERTYPUT, NULL,pRange, L"Value", 1,m_VArray);
}

// �����ļ�
void OperateExcel::SaveFile(IDispatch* const pSheet,const WCHAR* FileName)
{
	VARIANT name;
	VariantInit(&name);
	name.vt = VT_BSTR;
	name.bstrVal = SysAllocString(FileName);
	AutoWrap(DISPATCH_METHOD, NULL,pSheet, L"SaveAs", 1, name);
}

// �˳�
void OperateExcel::Quit(IDispatch* const pApp)
{
	AutoWrap(DISPATCH_METHOD, NULL,pApp, L"Quit",0);
}

// ����ʱ����Ӧ��xls�ļ�
IDispatch* OperateExcel::OpenXlsFile(IDispatch* const pApp,const WCHAR* FilePath)
{
	IDispatch* pBooks;
	VARIANT result;
	AutoWrap(DISPATCH_PROPERTYGET,&result,pApp,L"Workbooks",0);
	pBooks = result.pdispVal;
	VARIANT File;
	File.vt = VT_BSTR;
	File.bstrVal = SysAllocString(FilePath);
	IDispatch* pBook;
	VARIANT result2;
	AutoWrap(DISPATCH_METHOD,&result2,pBooks,L"Open",1,File);
	pBook = result2.pdispVal;
	return pBook;
}

// ����xls�ļ���ʹ�õ�range������һ�����飬���������
ExcelData* OperateExcel::ArrayForXls(IDispatch* const pApp,ExcelData* data)
{
	IDispatch* pSheet = GetActiveSheet(pApp);
	IDispatch* pRange;
	VARIANT result;
	AutoWrap(DISPATCH_PROPERTYGET,&result,pSheet,L"UsedRange",0);
	pRange = result.pdispVal;
	VARIANT count;
	count.vt = VT_I4;
	AutoWrap(DISPATCH_PROPERTYGET,&count,pRange,L"Count",0);
	IDispatch* rowRange;
	VARIANT result2;
	AutoWrap(DISPATCH_PROPERTYGET,&result2,pRange,L"Rows",0);
	rowRange = result2.pdispVal;
	VARIANT row;
	row.vt = VT_I4;
	AutoWrap(DISPATCH_PROPERTYGET,&row,rowRange,L"Count",0);
	int rownumber = row.iVal;
	int colnumber = count.iVal/row.iVal;
	VariantClear(&m_VArray);
	m_VArray.vt = VT_ARRAY|VT_VARIANT;
	SAFEARRAYBOUND rb[2];
	rb[0].lLbound = 1; rb[0].cElements =rownumber;
	rb[1].lLbound = 1; rb[1].cElements =colnumber;
	m_VArray.parray = SafeArrayCreate(VT_VARIANT,2,rb);
	AutoWrap(DISPATCH_PROPERTYGET,&m_VArray,pRange,L"Value",0);
	wstring wstr;
	char srctmp[200];
	WCHAR dsctmp[200];
	data->clear();
	for (int i=1;i<=rownumber;++i)
	{
		for (int j=1;j<=colnumber;++j)
		{
			wstr = _T("");
			long index[] = {i,j};
			VARIANT temp;
			SafeArrayGetElement(m_VArray.parray,index,(void*)&temp);
			if (temp.vt == VT_BSTR)
			{
				wstr = temp.bstrVal;
			}
			else if(temp.vt == VT_R8)
			{
				sprintf_s(srctmp,sizeof(srctmp),"%g",temp.dblVal);
				MultiByteToWideChar(CP_ACP,0,srctmp,-1,dsctmp,200);
				wstr = dsctmp;
			}
			else if (temp.vt == VT_NULL)
			{
				wstr = L"";
			}
			data->push_back(wstr);
		}
	}
	return data;
}

// ����������ɫ
void OperateExcel::SetFontcolr(IDispatch* const pFont,const LONG colr)
{
	VARIANT clr;
	VariantInit(&clr);
	clr.vt = VT_I4;
	clr.lVal =colr;
	AutoWrap(DISPATCH_PROPERTYPUT,NULL,pFont,L"Color",1,clr);
}

// ����������ʽ
void OperateExcel::SetFontStyle(IDispatch* const pFont,const WCHAR* pName)
{
	VARIANT fname;
	VariantInit(&fname);
	fname.vt = VT_BSTR;
	LPOLESTR str = const_cast<LPOLESTR> (pName);
	fname.bstrVal = ::SysAllocString(str);
	AutoWrap(DISPATCH_PROPERTYPUT,NULL,pFont,L"Name",1,fname); 
	::SysFreeString(str);
}

// ���������С
void OperateExcel::SetFontSize(IDispatch* const pFont,const short size)
{
	VARIANT fsize;
	VariantInit(&fsize);
	fsize.vt = VT_I2;
	fsize.iVal = size;
	AutoWrap(DISPATCH_PROPERTYPUT,NULL,pFont,L"Size",1,fsize);
}

// ���õ�Ԫ��Ŀ�͸�
void OperateExcel::SetRange(IDispatch* const pRange,const short Width,const short Height)
{
	VARIANT width,heigth;
	VariantInit(&width);
	VariantInit(&heigth);
	width.vt = VT_I2;
	heigth.vt = VT_I2;
	width.iVal = Width;
	heigth.iVal = Height;
	AutoWrap(DISPATCH_PROPERTYPUT, NULL,pRange, L"ColumnWidth", 1,width);
	AutoWrap(DISPATCH_PROPERTYPUT, NULL,pRange, L"RowHeight", 1,heigth);
}

// Excel�ĵ���
void OperateExcel::ExportExcel(const WCHAR* FileName,const int row,const int col,ExcelData* data)
{
	IDispatch* pApp = CreateInstance();
	IDispatch* pBook = GetWorkbook(pApp);
	IDispatch* pSheet = GetActiveSheet(pApp);
	IDispatch* pRange = GetRange(pSheet,row,col,1,1);
	FillArray(row,col,data);
	IDispatch* pFont = GetFont(pRange);
	//SetRange(pRange,16,32);
	//SetFontcolr(pFont,0xFFAA00EE);
	//SetFontSize(pFont,32);
	//SetFontStyle(pFont,L"����");
	FillExcel(pRange);
	SaveFile(pSheet,FileName);
	Quit(pApp);
	pFont->Release();
	pRange->Release();
	pSheet->Release();
	pBook->Release();
	pApp->Release();
}

// Excel�ĵ���
ExcelData* OperateExcel::ImportExcel(const WCHAR* FilePath,ExcelData* data)
{
	IDispatch* pApp = CreateInstance();
	OpenXlsFile(pApp,FilePath);
	ArrayForXls(pApp,data);
	Quit(pApp);
	return data;
}