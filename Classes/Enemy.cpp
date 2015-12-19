/*
 ************************************************************************
 *
 *	Enemy.cpp
 *	���Ƿ� 2015��8��13��
 *  ����: �趨�з��ɻ������ԡ�������
 *
 ************************************************************************
 */

#include "Enemy.h"

Enemy::Enemy() : pEnemySprite(NULL)
{

}

Enemy::~Enemy()
{

}

void Enemy::setEnemyByType(EnemyType enType)
{
	switch (enType)
	{
	case Enemy1:
		pEnemySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("t_enemy1.png"));
		nLife = ENEMY1_MAXLIFE;
		break;
	case Enemy2:
		pEnemySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("t_enemy2.png"));
		nLife = ENEMY2_MAXLIFE;
		break;
	case Enemy3:
		pEnemySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("t_enemy3.png"));
		nLife = ENEMY3_MAXLIFE;
		break;
	case Enemy4:
		pEnemySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("t_enemy4.png"));
		nLife = ENEMY4_MAXLIFE;
		break;
	case Enemy5:
		pEnemySprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("boss.png"));
		nLife = ENEMY5_MAXLIFE;
		break;
	default:
		return;
		break;
	}

	this->addChild(pEnemySprite);
	Size winSize = Director::getInstance()->getWinSize();
	Size enemySize = pEnemySprite->getContentSize();
	int minX = enemySize.width/2;
	int maxX = winSize.width - enemySize.width / 2;
	int rangeX = maxX - minX;
	int actualX = (rand() % rangeX) + minX;

	// ���õл�Node��λ Node����Sprite
	this->setPosition(Point(actualX, winSize.height - enemySize.height/2));
}

bool Enemy::init()
{
	bool pRet = true;
	if (!Node::init())
	{
		pRet = false;
	}

	return pRet;
}

Sprite* Enemy::getSprite()
{
	return pEnemySprite;
}

int Enemy::getLife()
{
	return nLife;
}

void Enemy::loseLife()
{
	--nLife;
}

Rect Enemy::getBoundingBox()
{
	Rect rect = pEnemySprite->boundingBox();
	Point pos = this->convertToWorldSpace(rect.origin);
	Rect enemyRect(pos.x, pos.y, rect.size.width, rect.size.height);
	return enemyRect;
}