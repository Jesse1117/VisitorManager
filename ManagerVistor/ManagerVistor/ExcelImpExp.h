#pragma once
#include "stdafx.h"
#include <Ole2.h>
#include <list>
#include <string>
/*
#include <comutil.h>
#pragma comment(lib,"comsuppw.lib") */
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

class OperateExcel
{
public:
	OperateExcel();
	~OperateExcel();
public:
	ExcelData m_ExcelData;// 数据链表
	VARIANT m_Array; // 二维数组
private:
	// 实现与excel交互的自动化函数
	HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs ...);
	// 创建组件对象并获得接口指针
	IDispatch* CreateInstance();
	// 获取工作薄
	IDispatch* GetWorkbook(IDispatch* pApp);
	// 获得当前工作表
	IDispatch* GetActiveSheet(IDispatch* pApp);
	// 获取单元格
	IDispatch* GetRange(IDispatch* pSheet,int row,int col,int startrow,int startcol);
	// 获得一个二维数组，用来填充excel
	void FillArray(int row,int col);
	// 获得字体
	IDispatch* GetFont(IDispatch* pRange);
	// 填充excel
	void FillExcel(IDispatch* pRange);
	// 保存文件
	void SaveFile(IDispatch* pSheet,WCHAR* FileName);
	// 退出
	void Quit(IDispatch* pApp);
	// 导出时打开相应的xls文件
	IDispatch* OpenXlsFile(IDispatch* pApp,WCHAR* FilePath);
	// 根据xls文件中使用的range，创建一个数组，并填充
	void ArrayForXls(IDispatch* pApp);
	
public:
	// 设置字体颜色
	void SetFontcolr(IDispatch* pFont,LONG colr);
	// 设置字体样式
	void SetFontStyle(IDispatch* pFont,WCHAR* pName);
	// 设置字体大小
	void SetFontSize(IDispatch* pFont,short size);
	// 设置单元格的宽和高
	void SetRange(IDispatch* pRange,short Width,short Height);
public:
	// Excel导入
	void ImportExcel(WCHAR* FileName,int row,int col);
	// Excel导出
	void ExportExcel(WCHAR* FilePath);
};