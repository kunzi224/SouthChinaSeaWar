/*
************************************************************************
*
*	BenefitControl.h
*	���Ƿ� 2015��8��13��
*   ����: ���߿���
*
************************************************************************
*/
#ifndef __BenefitControl_H__
#define __BenefitControl_H__

#include "cocos2d.h"
#include "Benefit.h"

USING_NS_CC;

class BenefitControl : public Layer
{
public:
	BenefitControl();
	~BenefitControl();
	virtual bool init();
	CREATE_FUNC(BenefitControl);

public:

	// ��ӵ���
	void addBenefit(float dt);

	// �Ƴ�����
	void removeBenefit(Node *pNode);

public:
	Vector<Benefit*> vecBenefit;// ��������

};

#endif