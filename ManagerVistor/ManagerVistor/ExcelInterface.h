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

class  OperateExcel
{
public:
	OperateExcel();
	~OperateExcel();
private:
	// ʵ����excel�������Զ�������
	HRESULT AutoWrap(const int autoType, VARIANT *pvResult, IDispatch *pDisp, LPOLESTR ptName,const int cArgs ...);
	// ����������󲢻�ýӿ�ָ��
	IDispatch* CreateInstance();
	// ��ȡ������
	IDispatch* GetWorkbook(IDispatch* const pApp);
	// ��õ�ǰ������
	IDispatch* GetActiveSheet(IDispatch* const pApp);
	// ��ȡ��Ԫ��
	IDispatch* GetRange(IDispatch* const pSheet,const int row,const int col,const int startrow,const int startcol);
	// ����˽�г�Աm_VArray���������excel
	void FillArray(const int row,const int col,ExcelData* data);
	// �������
	IDispatch* GetFont(IDispatch* const pRange);
	// ���excel
	void FillExcel(IDispatch* const pRange);
	// �����ļ�
	void SaveFile(IDispatch* const pSheet,const WCHAR* FileName);
	// �˳�
	void Quit(IDispatch* const pApp);
	// ����ʱ����Ӧ��xls�ļ�
	IDispatch* OpenXlsFile(IDispatch* const pApp,const WCHAR* FilePath);
	// ����xls�ļ���ʹ�õ�range������һ�����飬�����
	ExcelData* ArrayForXls(IDispatch* const pApp,ExcelData* data);
public:
	// ����������ɫ
	void SetFontcolr(IDispatch* const pFont,const LONG colr);
	// ����������ʽ
	void SetFontStyle(IDispatch* const pFont,const WCHAR* pName);
	// ���������С
	void SetFontSize(IDispatch* const pFont,const short size);
	// ���õ�Ԫ��Ŀ�͸�
	void SetRange(IDispatch* const pRange,const short Width,const short Height);
	// Excel�ĵ���
	void ExportExcel(const WCHAR* FileName,const int row,const int col,ExcelData* data);
	// Excel�ĵ���
	ExcelData* ImportExcel(const WCHAR* FilePath,ExcelData* data);
private:
	VARIANT m_VArray;
};