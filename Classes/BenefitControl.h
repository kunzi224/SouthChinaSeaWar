/*
************************************************************************
*
*	BenefitControl.h
*	杜星飞 2015年8月13日
*   描述: 道具控制
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

	// 添加道具
	void addBenefit(float dt);

	// 移除道具
	void removeBenefit(Node *pNode);

public:
	Vector<Benefit*> vecBenefit;// 道具容器

};

#endif