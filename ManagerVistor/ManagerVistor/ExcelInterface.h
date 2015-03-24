#pragma once
#include "stdafx.h"
#include <Ole2.h>
#include <list>
#include <string>


using namespace std;

class ExcelData
{
private:
	list<wstring> m_DataList;
public:
	ExcelData();
	~ExcelData();

	// 往链表尾部插入数据
	void push_back(const wstring& wstr);

	// 往链表中pos后面插入数据
	void insert_at(const wstring& wstr,int pos);

	// 删除链表头结点数据
	void delete_front();

	// 随机删除链表中的数据
	void remove(const wstring& val);

	// 获得链表头结点的数据
	wstring get_front();

	// 清空链表
	void clear();

	// 判断对象是否含有数据
	BOOL empty();
};

class  OperateExcel
{
public:
	OperateExcel();
	~OperateExcel();
private:
	// 实现与excel交互的自动化函数
	HRESULT AutoWrap(const int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName,const int cArgs ...);
	// 创建组件对象并获得接口指针
	IDispatch* CreateInstance();
	// 获取工作薄
	IDispatch* GetWorkbook(IDispatch* const pApp);
	// 获得当前工作表
	IDispatch* GetActiveSheet(IDispatch* const pApp);
	// 获取单元格
	IDispatch* GetRange(IDispatch* const pSheet,const int row,const int col,const int startrow,const int startcol);
	// 操作私有成员m_VArray，用来填充excel
	void FillArray(const int row,const int col,ExcelData* data);
	// 获得字体
	IDispatch* GetFont(IDispatch* const pRange);
	// 填充excel
	void FillExcel(IDispatch* const pRange);
	// 保存文件
	void SaveFile(IDispatch* const pSheet,const WCHAR* FileName);
	// 退出
	void Quit(IDispatch* const pApp);
	// 导入时打开相应的xls文件
	IDispatch* OpenXlsFile(IDispatch* const pApp,const WCHAR* FilePath);
	// 根据xls文件中使用的range，创建一个数组，并填充
	ExcelData* ArrayForXls(IDispatch* const pApp,ExcelData* data);
public:
	// 设置字体颜色
	void SetFontcolr(IDispatch* const pFont,const LONG colr);
	// 设置字体样式
	void SetFontStyle(IDispatch* const pFont,const WCHAR* pName);
	// 设置字体大小
	void SetFontSize(IDispatch* const pFont,const short size);
	// 设置单元格的宽和高
	void SetRange(IDispatch* const pRange,const short Width,const short Height);
	// Excel的导出
	void ExportExcel(const WCHAR* FileName,const int row,const int col,ExcelData* data);
	// Excel的导入
	ExcelData* ImportExcel(const WCHAR* FilePath,ExcelData* data);
private:
	VARIANT m_VArray;
};