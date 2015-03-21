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

	// ������β����������
	void push_back(const wstring& wstr);

	// ��������pos�����������
	void insert_at(const wstring& wstr,int pos);

	// ɾ������ͷ�������
	void delete_front();

	// ���ɾ�������е�����
	void remove(const wstring& val);

	// �������ͷ��������
	wstring get_front();

	// �������
	void clear();

	// �ж϶����Ƿ�������
	BOOL empty();

};

class OperateExcel
{
public:
	OperateExcel();
	~OperateExcel();
public:
	ExcelData m_ExcelData;// ��������
	VARIANT m_Array; // ��ά����
private:
	// ʵ����excel�������Զ�������
	HRESULT AutoWrap(int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName, int cArgs ...);
	// ����������󲢻�ýӿ�ָ��
	IDispatch* CreateInstance();
	// ��ȡ������
	IDispatch* GetWorkbook(IDispatch* pApp);
	// ��õ�ǰ������
	IDispatch* GetActiveSheet(IDispatch* pApp);
	// ��ȡ��Ԫ��
	IDispatch* GetRange(IDispatch* pSheet,int row,int col,int startrow,int startcol);
	// ���һ����ά���飬�������excel
	void FillArray(int row,int col);
	// �������
	IDispatch* GetFont(IDispatch* pRange);
	// ���excel
	void FillExcel(IDispatch* pRange);
	// �����ļ�
	void SaveFile(IDispatch* pSheet,WCHAR* FileName);
	// �˳�
	void Quit(IDispatch* pApp);
	// ����ʱ����Ӧ��xls�ļ�
	IDispatch* OpenXlsFile(IDispatch* pApp,WCHAR* FilePath);
	// ����xls�ļ���ʹ�õ�range������һ�����飬�����
	void ArrayForXls(IDispatch* pApp);
	
public:
	// ����������ɫ
	void SetFontcolr(IDispatch* pFont,LONG colr);
	// ����������ʽ
	void SetFontStyle(IDispatch* pFont,WCHAR* pName);
	// ���������С
	void SetFontSize(IDispatch* pFont,short size);
	// ���õ�Ԫ��Ŀ�͸�
	void SetRange(IDispatch* pRange,short Width,short Height);
public:
	// Excel����
	void ImportExcel(WCHAR* FileName,int row,int col);
	// Excel����
	void ExportExcel(WCHAR* FilePath);
};