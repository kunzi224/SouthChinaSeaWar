/*
************************************************************************
*
*	BenefitControl.cpp
*	杜星飞 2015年8月13日
*   描述: 道具控制
*
************************************************************************
*/

#include "BenefitControl.h"
#include "SimpleAudioEngine.h"

BenefitControl::BenefitControl() : vecBenefit(NULL)
{

}

BenefitControl::~BenefitControl()
{

}

bool BenefitControl::init()
{
	if (!Layer::init())
	{
		return false;
	}

	//根据当前分数来设定添加各种道具
	this->schedule(schedule_selector(BenefitControl::addBenefit), 10);

	return true;
}

void BenefitControl::addBenefit(float dt)
{
	Size size = Director::getInstance()->getVisibleSize();

	Benefit *pBenefitSprite = Benefit::create();

	struct timeval tv;

	gettimeofday(&tv, nullptr);

	log("-------------------- %d  ----------------------", (int)tv.tv_usec );

	srand((unsigned int)(tv.tv_usec/100));

	int m_type = cocos2d::random(1, 12);

	log("rand %d", m_type);

	switch (m_type)
	{
	case 1:
		pBenefitSprite->setBenefitType(Benefit1);
		pBenefitSprite->setTag(Benefit1);
		break;

	case 2:
		pBenefitSprite->setBenefitType(Benefit2);
		pBenefitSprite->setTag(Benefit2);
		break;

	case 3:
		pBenefitSprite->setBenefitType(Benefit3);
		pBenefitSprite->setTag(Benefit3);
		break;

	case 4:
		pBenefitSprite->setBenefitType(Benefit4);
		pBenefitSprite->setTag(Benefit4);
		break;

	case 5:
		pBenefitSprite->setBenefitType(Benefit5);
		pBenefitSprite->setTag(Benefit5);
		break;

	case 6:
		pBenefitSprite->setBenefitType(Benefit6);
		pBenefitSprite->setTag(Benefit6);
		break;

	case 7:
		pBenefitSprite->setBenefitType(Benefit7);
		pBenefitSprite->setTag(Benefit7);
		break;

	case 8:
		pBenefitSprite->setBenefitType(Benefit8);
		pBenefitSprite->setTag(Benefit8);
		break;

	case 9:
		pBenefitSprite->setBenefitType(Benefit9);
		pBenefitSprite->setTag(Benefit9);
		break;

	case 10:
		pBenefitSprite->setBenefitType(Benefit10);
		pBenefitSprite->setTag(Benefit10);
		break;

	case 11:
		pBenefitSprite->setBenefitType(Benefit11);
		pBenefitSprite->setTag(Benefit11);
		break;

	case 12:
		pBenefitSprite->setBenefitType(Benefit12);
		pBenefitSprite->setTag(Benefit12);
		break;

	default:
		break;
	}

	this->addChild(pBenefitSprite);
	vecBenefit.pushBack(pBenefitSprite);

	// 设置运动轨迹 以及到终点时调用的函数

	auto actionMove = MoveTo::create(6.0f, Vec2(cocos2d::random(size.width / 4, size.width * 3 / 4), 0));

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(BenefitControl::removeBenefit, this));
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	pBenefitSprite->runAction(sequence);

}

void BenefitControl::removeBenefit(Node *pNode)
{

	Benefit* benefit = (Benefit*)pNode;
	if (benefit != NULL)
	{
		this->removeChild(benefit, true);
		vecBenefit.eraseObject(benefit);
	}
	
}