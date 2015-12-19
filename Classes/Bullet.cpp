/*
************************************************************************
*
*	Bullet.cpp
*	杜星飞 2015年8月13日
*   描述: 产生玩家飞机子弹、敌机子弹
*
************************************************************************
*/

#include "Bullet.h"


Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}

bool Bullet::init()
{
	if (!Layer::init())
	{
		return false;
	}
	BeginBulletShoot();
	return true;
}

void Bullet::bindEnemyManager(EnemyManager* enemyManager)
{
	this->m_enemyManager = enemyManager;
	m_enemyManager->retain();
}

void Bullet::BeginBulletShoot(float dt)
{
	this->schedule(schedule_selector(Bullet::addBullet), 0.2f, kRepeatForever, dt);
	this->schedule(schedule_selector(Bullet::addEnemyBullet), 2.0f, kRepeatForever, dt);
}

void Bullet::StopBulletShoot()
{
	this->unschedule(schedule_selector(Bullet::addBullet));
	this->unschedule(schedule_selector(Bullet::addEnemyBullet));
}

void Bullet::addBullet(float dt)
{
	// 获得飞机的位置
	Point planePos = MyPlane::instancePlane->getChildByTag(AIRPLANE)->getPosition();
	Point bulletPos = Point(planePos.x, planePos.y + MyPlane::instancePlane->getChildByTag(AIRPLANE)->getContentSize().height / 2);
	

	// 飞行长度 飞行就是超出窗体
	float flyLen = Director::getInstance()->getWinSize().height  - bulletPos.y;
	float flyVelocity = 320 / 1; //飞行速度
	float realFlyDuration = flyLen / flyVelocity; // 飞行时间
	

	int m_bulletFire = MyPlane::instancePlane->getFire();

	switch (m_bulletFire)
	{
	case 1:
		updateBullet1(bulletPos, realFlyDuration);
		break;

	case 2:
		updateBullet2(bulletPos, realFlyDuration);
		break;

	case 3:
		updateBullet3(bulletPos, realFlyDuration);
		break;

	case 4:
		updateBullet4(bulletPos, realFlyDuration);
		break;

	default:
		updateBullet4(bulletPos, realFlyDuration);
		break;
	}
	

	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/bullet.wav");
	}

	
}

void Bullet::updateBullet1(Point bulletPos, float realFlyDuration)			// 添加子弹1
{
	auto actionMove = MoveTo::create(realFlyDuration, Point(bulletPos.x, Director::getInstance()->getWinSize().height));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::removeBullet, this));

	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);

	// 子弹
	auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");

	if (NULL == bullet)
	{
		return;
	}

	this->addChild(bullet);		// 加到Layer中去
	vecBullet.pushBack(bullet); // 加到容器中去，用于以后的碰撞检测等

	bullet->setPosition(bulletPos);

	bullet->runAction(sequence);
}

void Bullet::updateBullet2(Point bulletPos,float realFlyDuration)			// 添加子弹2
{
	auto actionMove = MoveTo::create(realFlyDuration, Point(bulletPos.x, Director::getInstance()->getWinSize().height));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::removeBullet, this));

	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);

	// 子弹
	auto bullet = Sprite::createWithSpriteFrameName("bullet2.png");
//	bullet->setScale(0.6);

	if (NULL == bullet)
	{
		return;
	}

	this->addChild(bullet);		// 加到Layer中去
	vecBullet.pushBack(bullet); // 加到容器中去，用于以后的碰撞检测等

	bullet->setPosition(bulletPos);

	bullet->runAction(sequence);
}

void Bullet::updateBullet3(Point bulletPos, float realFlyDuration)			// 添加子弹3
{

	// 子弹
	auto bullet1 = Sprite::createWithSpriteFrameName("bullet3.png");
	auto bullet2 = Sprite::createWithSpriteFrameName("bullet3.png");
	
//	bullet1->setScale(0.8);
//	bullet2->setScale(0.8);


	if (NULL == bullet1 || nullptr==bullet2)
	{
		return;
	}

	this->addChild(bullet1);		// 加到Layer中去
	this->addChild(bullet2);		

	vecBullet.pushBack(bullet1); // 加到容器中去，用于以后的碰撞检测等
	vecBullet.pushBack(bullet2); 

	auto actionMove1 = MoveTo::create(realFlyDuration, Point(bulletPos.x + bullet1->getContentSize().width*2, Director::getInstance()->getWinSize().height));
	auto actionMove2 = MoveTo::create(realFlyDuration, Point(bulletPos.x - bullet1->getContentSize().width*2, Director::getInstance()->getWinSize().height));

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::removeBullet, this));

	Sequence* sequence1 = Sequence::create(actionMove1, actionDone, NULL);
	Sequence* sequence2 = Sequence::create(actionMove2, actionDone, NULL);

	bullet1->setPosition(Vec2(bulletPos.x+bullet1->getContentSize().width/2,bulletPos.y));
	bullet2->setPosition(Vec2(bulletPos.x - bullet1->getContentSize().width / 2, bulletPos.y));

	bullet1->runAction(sequence1);
	bullet2->runAction(sequence2);
}

void Bullet::updateBullet4(Point bulletPos, float realFlyDuration)			// 添加子弹4
{
	// 子弹
	auto bullet1 = Sprite::createWithSpriteFrameName("bullet4.png");
	auto bullet2 = Sprite::createWithSpriteFrameName("bullet4.png");
	auto bullet3 = Sprite::createWithSpriteFrameName("bullet4.png");

//	bullet1->setScale(0.5);
//	bullet2->setScale(0.5);
//	bullet3->setScale(0.5);

	if (NULL == bullet1 || nullptr==bullet2 || nullptr==bullet3)
	{
		return;
	}

	this->addChild(bullet1);		// 加到Layer中去
	this->addChild(bullet2);
	this->addChild(bullet3);

	vecBullet.pushBack(bullet1); // 加到容器中去，用于以后的碰撞检测等
	vecBullet.pushBack(bullet2);
	vecBullet.pushBack(bullet3);

	auto actionMove1 = MoveTo::create(realFlyDuration, Point(bulletPos.x+bullet1->getContentSize().width*2, Director::getInstance()->getWinSize().height));
	auto actionMove2 = MoveTo::create(realFlyDuration, Point(bulletPos.x, Director::getInstance()->getWinSize().height));
	auto actionMove3 = MoveTo::create(realFlyDuration, Point(bulletPos.x - bullet1->getContentSize().width*2, Director::getInstance()->getWinSize().height));

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::removeBullet, this));

	Sequence* sequence1 = Sequence::create(DelayTime::create(0.1f), actionMove1, actionDone, NULL);
	Sequence* sequence2 = Sequence::create(actionMove2, actionDone, NULL);
	Sequence* sequence3 = Sequence::create(DelayTime::create(0.1f), actionMove3, actionDone, NULL);
	
	bullet1->setPosition(Vec2(bulletPos.x + bullet1->getContentSize().width, bulletPos.y));
	bullet2->setPosition(bulletPos);
	bullet3->setPosition(Vec2(bulletPos.x - bullet1->getContentSize().width, bulletPos.y));

	bullet1->runAction(sequence1);
	bullet2->runAction(sequence2);
	bullet3->runAction(sequence3);
}

void Bullet::removeBullet(Node* pNode)
{
	if (NULL == pNode)
	{
		return;
	}

	Sprite* bullet = (Sprite*)pNode;
	this->removeChild(bullet, true);
	vecBullet.eraseObject(bullet);
}

// 添加敌机子弹
void Bullet::addEnemyBullet(float dt)
{

	for (auto& eEnemy : m_enemyManager->vecEnemy)
	{
		Enemy* pEnemySprite = (Enemy*)eEnemy;

		// 子弹
		auto bullet = Sprite::createWithSpriteFrameName("enemyBullet.png");
		if (NULL == bullet)
		{
			return;
		}

		this->addChild(bullet);		// 加到Layer中去
		vecEnemyBullet.pushBack(bullet); // 加到容器中去，用于以后的碰撞检测等

		// 获得敌方飞机的位置
		Point enemyPos = pEnemySprite->getPosition();

		Point bulletPos = Point(enemyPos.x, enemyPos.y - pEnemySprite->getContentSize().height / 2);
		bullet->setPosition(bulletPos);

		// 飞行长度 飞行就是超出窗体
		float flyLen = bulletPos.y - bullet->getContentSize().height / 2;
		float flyVelocity = 320 / 1; //飞行速度
		float realFlyDuration = flyLen / flyVelocity; // 飞行时间
		auto actionMove = MoveTo::create(realFlyDuration, Point(bulletPos.x, Director::getInstance()->getVisibleOrigin().y - bullet->getContentSize().height / 2));
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::removeEnemyBullet, this));

		Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
		bullet->runAction(sequence);

		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemyBullet.mp3");
		}

	}
}

// 移除敌机子弹
void Bullet::removeEnemyBullet(Node* pNode)
{
	if (NULL == pNode)
	{
		return;
	}

	Sprite* bullet = (Sprite*)pNode;
	this->removeChild(bullet, true);
	vecEnemyBullet.eraseObject(bullet);
}

void Bullet::addCall1()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (int i = 0; i < 15;i++)
	{
		// 子弹
		auto bullet = Sprite::createWithSpriteFrameName("bulletCarrier.png");

		if (NULL == bullet)
		{
			return;
		}

		this->addChild(bullet);		// 加到Layer中去
		vecBullet.pushBack(bullet); // 加到容器中去，用于以后的碰撞检测等

		bullet->setPosition(Vec2(visibleSize.width / 15 * i + bullet->getContentSize().width, bullet->getContentSize().height * 2));

		auto actionMove = MoveTo::create(2.0, Point(visibleSize.width / 15 * i, visibleSize.height));
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::removeBullet, this));

		Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);

		bullet->runAction(sequence);

	}
}

void Bullet::addCall2()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (int j = 0; j < 3;j++)
	{
		for (int i = 0; i < 15; i++)
		{
			// 子弹
			auto bullet = Sprite::createWithSpriteFrameName("rescue1.png");

			if (NULL == bullet)
			{
				return;
			}

			this->addChild(bullet);		// 加到Layer中去
			vecBullet.pushBack(bullet); // 加到容器中去，用于以后的碰撞检测等

			if (0==j)
			{
				bullet->setPosition(Vec2(visibleSize.width / 15 * i + bullet->getContentSize().width, bullet->getContentSize().height));
			}
			else if (1==j)
			{
				bullet->setPosition(Vec2(visibleSize.width / 15 * i + bullet->getContentSize().width, bullet->getContentSize().height * 2));
			}
			else
			{
				bullet->setPosition(Vec2(visibleSize.width / 15 * i + bullet->getContentSize().width, bullet->getContentSize().height * 3));
			}

			auto actionMove = MoveTo::create(2.0, Point(visibleSize.width / 15 * i, visibleSize.height));
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::removeBullet, this));

			Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);

			bullet->runAction(sequence);

		}
	}
}

void Bullet::addCall3()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	for (int j = 0; j < 1;j++)
	{
		for (int i = 0; i < 60; i++)
		{
			// 子弹
			auto bullet = Sprite::createWithSpriteFrameName("rescue2.png");
			bullet->setScaleY(0.8);

			if (NULL == bullet)
			{
				return;
			}

			this->addChild(bullet);		// 加到Layer中去
			vecBullet.pushBack(bullet); // 加到容器中去，用于以后的碰撞检测等

			if (0==j)
			{
				bullet->setPosition(Vec2(visibleSize.width / 60 * i + bullet->getContentSize().width / 2, bullet->getContentSize().height));
			}
			else
			{
				bullet->setPosition(Vec2(visibleSize.width / 60 * i + bullet->getContentSize().width / 2, bullet->getContentSize().height*2));
			}

			auto actionMove = MoveTo::create(2.0, Point(visibleSize.width / 60 * i, visibleSize.height));
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::removeBullet, this));

			Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);

			bullet->runAction(sequence);

		}
	}
}

void Bullet::addCall4()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 60; i++)
		{
			// 子弹
			auto bullet = Sprite::createWithSpriteFrameName("rescue2.png");

			if (NULL == bullet)
			{
				return;
			}

			this->addChild(bullet);		// 加到Layer中去
			vecBullet.pushBack(bullet); // 加到容器中去，用于以后的碰撞检测等

			if (0 == j)
			{
				bullet->setPosition(Vec2(visibleSize.width / 60 * i + bullet->getContentSize().width/2, bullet->getContentSize().height));
			}
			else if (1 == j)
			{
				bullet->setPosition(Vec2(visibleSize.width / 60 * i + bullet->getContentSize().width/2, bullet->getContentSize().height*3));
			}
			else if (2 == j)
			{
				bullet->setPosition(Vec2(visibleSize.width / 60 * i + bullet->getContentSize().width/2, bullet->getContentSize().height *5));
			}
			else
			{
				bullet->setPosition(Vec2(visibleSize.width / 60 * i + bullet->getContentSize().width / 2, bullet->getContentSize().height * 4));
			}

			auto actionMove = MoveTo::create(2.0, Point(visibleSize.width / 60 * i, visibleSize.height));
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::removeBullet, this));

			Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);

			bullet->runAction(sequence);

		}
	}
}