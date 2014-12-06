#pragma once
#include "DataDef.h"
class SLZEvaData
{
public:
	SLZEvaData(void) : m_iEvaluatorId(0){}
	~SLZEvaData(void){}

	//��ȡ��������ַ
	int GetEvaluatorId() const
	{
		return m_iEvaluatorId;
	}
	//������������ַ
	void SetEvaluatorId(int iEvaluatorId)
	{
		m_iEvaluatorId = iEvaluatorId;
	}
	//��ȡ���۵ȼ�
	EvaLevel GetEvaLevel() const
	{
		return m_evaLevel;
	}
	//�������۵ȼ�
	void SetEvaLevel(EvaLevel evaLevel)
	{
		m_evaLevel = evaLevel;
	}

private:
	int m_iEvaluatorId;		//��������ַ
	EvaLevel m_evaLevel;	//���۵ȼ�
};
