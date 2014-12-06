// RecordsetPatient.h : CRecordsetPatient ������

#pragma once

// ���������� 2014��7��18��, 8:26

class CRecordsetPatient : public CRecordset
{
public:
	CRecordsetPatient(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRecordsetPatient)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CStringA	m_SERIAL_ID;
	CStringA	m_ID_CARD;
	//CStringA	m_QUEUE_NUM;
	double		m_QUEUE_NUM;
	CStringA	m_PATIENT_NAME;
	double	m_PATIENT_GENDER;
	//CStringA	m_ID_DEPART;
	double		m_ID_DEPART;
	CTime	m_TIME;
	CStringA	m_ID_DOCTOR;
	double	m_PAY_FLAG;
	CStringA	m_PAY_DESC;
	//double	m_PAY_MONEY;
	CStringA	m_PAY_MONEY;

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


