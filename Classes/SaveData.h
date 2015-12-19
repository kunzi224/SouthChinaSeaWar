/*
************************************************************************
*
*	SaveData.h
*	���Ƿ� 2015��8��13��
*   ����: ���������Ϣ
*
************************************************************************
*/
#ifndef __SaveData_H__
#define __SaveData_H__

#include "cocos2d.h"

USING_NS_CC;

class SaveData : public Ref
{
public:
	SaveData();
	~SaveData();
public:
	bool init();
	CREATE_FUNC(SaveData);
private:
	//�û����ݲ����ĳ�Ա����
	UserDefault * m_userDefault;
	
	//Ҫ�õ���������������ˡ���
	ValueVector m_vector;
	//��¼��ҵĵ�ǰ����
	CC_SYNTHESIZE(int, m_score, Score);
public:
	void save();
};

#endif