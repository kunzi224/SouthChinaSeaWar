/*
************************************************************************
*
*	Benefit.h
*	���Ƿ� 2015��8��13��
*   ����: �趨��������
*
************************************************************************
*/

#ifndef __Benefit_H__
#define __Benefit_H__

#include "cocos2d.h"

USING_NS_CC;

// �л�����
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