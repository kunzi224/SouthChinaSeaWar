/*
************************************************************************
*
*	Bullet.cpp
*	���Ƿ� 2015��8��13��
*   ����: ������ҷɻ��ӵ����л��ӵ�
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
	// ��÷ɻ���λ��
	Point planePos = MyPlane::instancePlane->getChildByTag(AIRPLANE)->getPosition();
	Point bulletPos = Point(planePos.x, planePos.y + MyPlane::instancePlane->getChildByTag(AIRPLANE)->getContentSize().height / 2);
	

	// ���г��� ���о��ǳ�������
	float flyLen = Director::getInstance()->getWinSize().height  - bulletPos.y;
	float flyVelocity = 320 / 1; //�����ٶ�
	float realFlyDuration = flyLen / flyVelocity; // ����ʱ��
	

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

void Bullet::updateBullet1(Point bulletPos, float realFlyDuration)			// ����ӵ�1
{
	auto actionMove = MoveTo::create(realFlyDuration, Point(bulletPos.x, Director::getInstance()->getWinSize().height));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::removeBullet, this));

	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);

	// �ӵ�
	auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");

	if (NULL == bullet)
	{
		return;
	}

	this->addChild(bullet);		// �ӵ�Layer��ȥ
	vecBullet.pushBack(bullet); // �ӵ�������ȥ�������Ժ����ײ����

	bullet->setPosition(bulletPos);

	bullet->runAction(sequence);
}

void Bullet::updateBullet2(Point bulletPos,float realFlyDuration)			// ����ӵ�2
{
	auto actionMove = MoveTo::create(realFlyDuration, Point(bulletPos.x, Director::getInstance()->getWinSize().height));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Bullet::removeBullet, this));

	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);

	// �ӵ�
	auto bullet = Sprite::createWithSpriteFrameName("bullet2.png");
//	bullet->setScale(0.6);

	if (NULL == bullet)
	{
		return;
	}

	this->addChild(bullet);		// �ӵ�Layer��ȥ
	vecBullet.pushBack(bullet); // �ӵ�������ȥ�������Ժ����ײ����

	bullet->setPosition(bulletPos);

	bullet->runAction(sequence);
}

void Bullet::updateBullet3(Point bulletPos, float realFlyDuration)			// ����ӵ�3
{

	// �ӵ�
	auto bullet1 = Sprite::createWithSpriteFrameName("bullet3.png");
	auto bullet2 = Sprite::createWithSpriteFrameName("bullet3.png");
	
//	bullet1->setScale(0.8);
//	bullet2->setScale(0.8);


	if (NULL == bullet1 || nullptr==bullet2)
	{
		return;
	}

	this->addChild(bullet1);		// �ӵ�Layer��ȥ
	this->addChild(bullet2);		

	vecBullet.pushBack(bullet1); // �ӵ�������ȥ�������Ժ����ײ����
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

void Bullet::updateBullet4(Point bulletPos, float realFlyDuration)			// ����ӵ�4
{
	// �ӵ�
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

	this->addChild(bullet1);		// �ӵ�Layer��ȥ
	this->addChild(bullet2);
	this->addChild(bullet3);

	vecBullet.pushBack(bullet1); // �ӵ�������ȥ�������Ժ����ײ����
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

// ��ӵл��ӵ�
void Bullet::addEnemyBullet(float dt)
{

	for (auto& eEnemy : m_enemyManager->vecEnemy)
	{
		Enemy* pEnemySprite = (Enemy*)eEnemy;

		// �ӵ�
		auto bullet = Sprite::createWithSpriteFrameName("enemyBullet.png");
		if (NULL == bullet)
		{
			return;
		}

		this->addChild(bullet);		// �ӵ�Layer��ȥ
		vecEnemyBullet.pushBack(bullet); // �ӵ�������ȥ�������Ժ����ײ����

		// ��õз��ɻ���λ��
		Point enemyPos = pEnemySprite->getPosition();

		Point bulletPos = Point(enemyPos.x, enemyPos.y - pEnemySprite->getContentSize().height / 2);
		bullet->setPosition(bulletPos);

		// ���г��� ���о��ǳ�������
		float flyLen = bulletPos.y - bullet->getContentSize().height / 2;
		float flyVelocity = 320 / 1; //�����ٶ�
		float realFlyDuration = flyLen / flyVelocity; // ����ʱ��
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

// �Ƴ��л��ӵ�
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
		// �ӵ�
		auto bullet = Sprite::createWithSpriteFrameName("bulletCarrier.png");

		if (NULL == bullet)
		{
			return;
		}

		this->addChild(bullet);		// �ӵ�Layer��ȥ
		vecBullet.pushBack(bullet); // �ӵ�������ȥ�������Ժ����ײ����

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
			// �ӵ�
			auto bullet = Sprite::createWithSpriteFrameName("rescue1.png");

			if (NULL == bullet)
			{
				return;
			}

			this->addChild(bullet);		// �ӵ�Layer��ȥ
			vecBullet.pushBack(bullet); // �ӵ�������ȥ�������Ժ����ײ����

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
			// �ӵ�
			auto bullet = Sprite::createWithSpriteFrameName("rescue2.png");
			bullet->setScaleY(0.8);

			if (NULL == bullet)
			{
				return;
			}

			this->addChild(bullet);		// �ӵ�Layer��ȥ
			vecBullet.pushBack(bullet); // �ӵ�������ȥ�������Ժ����ײ����

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
			// �ӵ�
			auto bullet = Sprite::createWithSpriteFrameName("rescue2.png");

			if (NULL == bullet)
			{
				return;
			}

			this->addChild(bullet);		// �ӵ�Layer��ȥ
			vecBullet.pushBack(bullet); // �ӵ�������ȥ�������Ժ����ײ����

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