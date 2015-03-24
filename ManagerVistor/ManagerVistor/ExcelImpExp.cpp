#pragma once
#include "stdafx.h"
#include "ExcelImpExp.h"

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
		::MessageBox(NULL,_T("超出链表范围！"),_T("提示"),NULL);
	}

}

void ExcelData::delete_front()
{
	if (m_DataList.empty())
	{
		MessageBox(NULL,_T("已经没有数据了"),_T("提示"),NULL);
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
		::MessageBox(NULL,_T("空的链表！"),_T("提示"),NULL);
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

OperateExcel::OperateExcel()
{
	m_ExcelData.clear();
	VariantInit(&m_Array);
}

OperateExcel::~OperateExcel()
{
	m_ExcelData.clear();
	VariantInit(&m_Array);
}

HRESULT OperateExcel::AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs ...)
{
	va_list marker;
	va_start(marker, cArgs);//等同于(char*)(&cArgs)+4，就是让指向cArgs的指针指向它后面一个参数
	if(!pDisp) {
		MessageBox(NULL,_T("空的接口"),_T("提示"),NULL);
		_exit(0);
	}
	// Invoke函数的参数
	DISPPARAMS dp = { NULL, NULL, 0, 0 };
	DISPID dispidNamed = DISPID_PROPERTYPUT;
	DISPID dispID;
	HRESULT hr;
	hr = pDisp->GetIDsOfNames(IID_NULL, &ptName, 1, LOCALE_USER_DEFAULT, &dispID);
	if(FAILED(hr)) 
	{
		MessageBox(NULL,_T("找不到该函数或属性"),_T("提示"),NULL);
		_exit(0);
		return hr;
	}
	VARIANT *pArgs = new VARIANT[cArgs+1]; 
	for(int i=0; i<cArgs; i++) {
		pArgs[i] = va_arg(marker, VARIANT);//得到第一个参数的值，并让指针指向第二个参数
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


// 创建组件对象并获得接口指针
IDispatch* OperateExcel::CreateInstance()
{
	CLSID clsid;
	HRESULT hr = CLSIDFromProgID(L"Excel.Application",&clsid);
	if (FAILED(hr))
	{
		MessageBox(NULL,_T("获取ID失败"),_T("提示"),NULL);
		exit(0);
	}
	IDispatch *pApp;
	hr = CoCreateInstance(clsid,NULL,CLSCTX_LOCAL_SERVER,IID_IDispatch,(void**)&pApp);
	if (FAILED(hr))
	{
		MessageBox(NULL,_T("请检查是否已安装Excel"),_T("提示"),NULL);
		exit(1);
	}
	// 设置Application.visible属性，1为可见，0为不可见
	VARIANT pro;
	pro.vt = VT_I4;
	pro.lVal = 0;
	AutoWrap(DISPATCH_PROPERTYPUT, NULL,pApp, L"Visible", 1, pro);
	return pApp;
}
// 获取工作薄
IDispatch* OperateExcel::GetWorkbook(IDispatch* pApp)
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
// 获得当前工作表
IDispatch* OperateExcel::GetActiveSheet(IDispatch* pApp)
{
	VARIANT result;
	VariantInit(&result);
	AutoWrap(DISPATCH_PROPERTYGET,&result,pApp,L"ActiveSheet",0);
	IDispatch* pSheet = result.pdispVal;
	return pSheet;
}
// 获取单元格
IDispatch* OperateExcel::GetRange(IDispatch* pSheet,int row,int col,int startrow,int startcol)
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
	// 以上操作是为了把整数转换为excel表示范围的方式
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
// 设置单元格的宽和高
void OperateExcel::SetRange(IDispatch* pRange,short Width,short Height)
{
	VARIANT width,heigth;
	width.vt = VT_I2;
	heigth.vt = VT_I2;
	width.iVal = Width;
	heigth.iVal = Height;
	AutoWrap(DISPATCH_PROPERTYPUT, NULL,pRange, L"ColumnWidth", 1,width);
	AutoWrap(DISPATCH_PROPERTYPUT, NULL,pRange, L"RowHeight", 1,heigth);
}
// 获得一个二维数组，用来填充excel
void OperateExcel::FillArray(int row,int col)
{
	VariantInit(&m_Array);
	m_Array.vt = VT_ARRAY|VT_VARIANT;
	SAFEARRAYBOUND sab[2];
	sab[0].lLbound = 1; sab[0].cElements = row;
	sab[1].lLbound = 1; sab[1].cElements = col;
	m_Array.parray = SafeArrayCreate(VT_VARIANT, 2, sab);
	for (int i=1;i<=row;++i)
	{
		for (int j=1;j<=col;++j)
		{
			VARIANT tmp;
			tmp.vt = VT_BSTR;
			if (m_ExcelData.empty())
			{
			}
			else
			{
				wstring wstr = m_ExcelData.get_front();
				m_ExcelData.delete_front();
				tmp.bstrVal = SysAllocString(wstr.c_str());
				// 添加数据到数组中
				long indices[] = {i,j};
				SafeArrayPutElement(m_Array.parray, indices, (void *)&tmp);	
			}
		}
	}
}
// 获得字体
IDispatch* OperateExcel::GetFont(IDispatch* pRange)
{
	VARIANT result;
	VariantInit(&result);
	AutoWrap(DISPATCH_PROPERTYGET, &result,pRange, L"Font", 0);
	IDispatch *pFont = result.pdispVal;	
	return pFont;
}
// 设置字体颜色
void OperateExcel::SetFontcolr(IDispatch* pFont,LONG colr)
{
	VARIANT clr;
	clr.vt = VT_I4;
	clr.lVal =colr;
	AutoWrap(DISPATCH_PROPERTYPUT,NULL,pFont,L"Color",1,clr);
}
// 设置字体样式
void OperateExcel::SetFontStyle(IDispatch* pFont,WCHAR* pName)
{
	VARIANT fname;
	fname.vt = VT_BSTR;
	LPOLESTR str = pName;
	fname.bstrVal = ::SysAllocString(str);
	AutoWrap(DISPATCH_PROPERTYPUT,NULL,pFont,L"Name",1,fname); 
	::SysFreeString(str);
}
//设置字体大小
void OperateExcel::SetFontSize(IDispatch* pFont,short size)
{
	VARIANT fsize;
	fsize.vt = VT_I2;
	fsize.iVal = size;
	AutoWrap(DISPATCH_PROPERTYPUT,NULL,pFont,L"Size",1,fsize);
}
// 填充excel
void OperateExcel::FillExcel(IDispatch* pRange)
{
	AutoWrap(DISPATCH_PROPERTYPUT, NULL,pRange, L"Value", 1,m_Array);
}
// 保存文件
void OperateExcel::SaveFile(IDispatch* pSheet,WCHAR* FileName)
{
	VARIANT name;
	name.vt = VT_BSTR;
	name.bstrVal = SysAllocString(FileName);
	AutoWrap(DISPATCH_METHOD, NULL,pSheet, L"SaveAs", 1, name);
}
// 退出
void OperateExcel::Quit(IDispatch* pApp)
{
	AutoWrap(DISPATCH_METHOD, NULL,pApp, L"Quit",0);
}
// 导出时打开相应的xls文件
IDispatch* OperateExcel::OpenXlsFile(IDispatch* pApp,WCHAR* FilePath)
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
// 根据xls文件中使用的range，创建一个数组,并填充数组
void OperateExcel::ArrayForXls(IDispatch* pApp)
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
	VariantInit(&m_Array);
	m_Array.vt = VT_ARRAY|VT_VARIANT;
	SAFEARRAYBOUND rb[2];
	rb[0].lLbound = 1; rb[0].cElements =rownumber;
	rb[1].lLbound = 1; rb[1].cElements =colnumber;
	m_Array.parray = SafeArrayCreate(VT_VARIANT,2,rb);
	AutoWrap(DISPATCH_PROPERTYGET,&m_Array,pRange,L"Value",0);
	wstring wstr;
	char srctmp[200];
	WCHAR dsctmp[200];
	m_ExcelData.clear();
	for (int i=1;i<=rownumber;++i)
	{
		for (int j=1;j<=colnumber;++j)
		{
			wstr = _T("");
			long index[] = {i,j};
			VARIANT temp;
			SafeArrayGetElement(m_Array.parray,index,(void*)&temp);
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
			m_ExcelData.push_back(wstr);
		}
	}
}
// Excel导出
void OperateExcel::ExportExcel(WCHAR* FilePath)
{
	IDispatch* pApp = CreateInstance();
	OpenXlsFile(pApp,FilePath);
	ArrayForXls(pApp);
	Quit(pApp);
}
// Excel导入
void OperateExcel::ImportExcel(WCHAR* FileName,int row,int col)
{
	IDispatch* pApp = CreateInstance();
	IDispatch* pBook = GetWorkbook(pApp);
	IDispatch* pSheet = GetActiveSheet(pApp);
	IDispatch* pRange = GetRange(pSheet,row,col,1,1);
	FillArray(row,col);
	IDispatch* pFont = GetFont(pRange);
	//SetRange(pRange,16,32);
	//SetFontcolr(pFont,0xFFAA00EE);
	//SetFontSize(pFont,32);
	//SetFontStyle(pFont,L"黑体");
	FillExcel(pRange);
	SaveFile(pSheet,FileName);
	Quit(pApp);
	pFont->Release();
	pRange->Release();
	pSheet->Release();
	pBook->Release();
	pApp->Release();
}