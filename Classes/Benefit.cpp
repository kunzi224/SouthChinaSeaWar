/*
************************************************************************
*
*	Benefit.cpp
*	杜星飞 2015年8月13日
*   描述: 设定道具属性
*
************************************************************************
*/

#include "Benefit.h"

Benefit::Benefit() : pBenefitSprite(nullptr)
{

}

Benefit::~Benefit()
{

}

void Benefit::setBenefitType(BenefitType beType)
{
	switch (beType)
	{
	case Benefit1:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bullet3.png"));
		break;
	case Benefit2:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("tyre.png"));
		break;
	case Benefit3:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb.png"));
		break;
	case Benefit4:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("call.png"));
		break;
	case Benefit5:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("plane_hide.png"));
		pBenefitSprite->setScale(0.8);
		break;
	case Benefit6:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb_rect.png"));
		pBenefitSprite->setScale(0.8);
		break;
	case Benefit7:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb_direct.png"));
		pBenefitSprite->setScale(0.6);
		break;
	case Benefit8:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bomb_timed.png"));
		pBenefitSprite->setScaleY(0.8);
		break;
	case Benefit9:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy_timed.png"));
		break;
	case Benefit10:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("call.png"));
		break;
	case Benefit11:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("call.png"));
		break;
	case Benefit12:
		pBenefitSprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("call.png"));
		break;
	default:
		break;
	}

	this->addChild(pBenefitSprite);
	Size winSize = Director::getInstance()->getWinSize();
	Size benefitSize = pBenefitSprite->getContentSize();
	int minX = winSize.width / 4;
	int maxX = winSize.width *3/4;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;

	int minY = winSize.height-benefitSize.height;
	int maxY = winSize.height *3/4;
	int rangeY = maxY - minY;
	int actualY = (rand() % rangeY) + minY;

	// 设置道具出现位置
	this->setPosition(Point(actualX, actualY));
}

bool Benefit::init()
{
	bool pRet = true;
	if (!Node::init())
	{
		pRet = false;
	}

	return pRet;
}

Sprite* Benefit::getSprite()
{
	return pBenefitSprite;
}

Rect Benefit::getBoundingBox()
{
	if (nullptr == pBenefitSprite)
	{
		return Rect::ZERO;
	}

	Rect rect = pBenefitSprite->boundingBox();
	Point pos = this->convertToWorldSpace(rect.origin);
	Rect benefitRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return benefitRect;
}