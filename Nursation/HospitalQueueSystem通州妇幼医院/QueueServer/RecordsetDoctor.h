// RecordsetDoctor.h : CRecordsetDoctor ������

#pragma once

// ���������� 2014��7��18��, 16:57

class CRecordsetDoctor : public CRecordset
{
public:
	CRecordsetDoctor(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecordsetDoctor)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CStringA	m_ID;
	CStringA	m_NAME;
	double	m_GENDER;
	CStringA	m_TITLE;
	double	m_EXPERT_FLAG;
	//CStringA	m_ID_DEPART;
	double		m_ID_DEPART;
	CStringA	m_ID_CLINIC;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


