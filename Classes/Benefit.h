/*
************************************************************************
*
*	Benefit.h
*	杜星飞 2015年8月13日
*   描述: 设定道具属性
*
************************************************************************
*/

#ifndef __Benefit_H__
#define __Benefit_H__

#include "cocos2d.h"

USING_NS_CC;

// 敌机类型
enum BenefitType
{
	Benefit1=5,
	Benefit2,
	Benefit3,
	Benefit4,
	Benefit5,
	Benefit6,
	Benefit7,
	Benefit8,
	Benefit9,
	Benefit10,
	Benefit11,
	Benefit12
};

class Benefit : public Node
{
public:
	Benefit();
	~Benefit();
	virtual bool init();
	CREATE_FUNC(Benefit);

public:
	void setBenefitType(BenefitType beType);
	Sprite* getSprite();

	Rect getBoundingBox();

private:
	Sprite *pBenefitSprite;
};


#endif