/*
************************************************************************
*
*	EnemyManager.cpp
*	杜星飞 2015年8月13日
*   描述: 管理敌机的产生、销毁等
*
************************************************************************
*/

#include "EnemyManager.h"
#include "SimpleAudioEngine.h"

EnemyManager::EnemyManager() : vecEnemy(NULL), m_controlLayer(NULL), m_background(nullptr), m_fSpeed(1), m_fEnemy1(3.0), m_fEnemy2(9.0), m_fEnemy3(15.0), m_fEnemy4(21.0), m_fEnemy5(60.0), m_bRun(true)
{

}

EnemyManager::~EnemyManager()
{
	m_controlLayer->release();
	m_background->release();
}

bool EnemyManager::init()
{
	if (!Layer::init())
	{
		return false;
	}
	cocos2d::Vector<SpriteFrame*> vecTemp;
	vecTemp.clear();

	// 敌机1爆炸
	for (int i = 0; i < 2; i++)
	{
		auto blowUpName = __String::createWithFormat("t_enemy1_down%d.png", i + 1);
		auto tempBlowUp = SpriteFrameCache::getInstance()->getSpriteFrameByName(
			blowUpName->getCString());
		vecTemp.pushBack(tempBlowUp);
	}

	Animation* pAnimation1 = Animation::createWithSpriteFrames(vecTemp, 0.1f);
	
	// 添加到AnimationCache，并且命名为Enemy1Blowup
	AnimationCache::getInstance()->addAnimation(pAnimation1, "Enemy1Blowup");

	// 敌机2爆炸
	vecTemp.clear();
	for (int i = 0; i < 3; i++)
	{
		auto blowUpName = __String::createWithFormat("t_enemy2_down%d.png", i + 1);
		auto tempBlowUp = SpriteFrameCache::getInstance()->getSpriteFrameByName(
			blowUpName->getCString());
		vecTemp.pushBack(tempBlowUp);
	}

	Animation *pAnimation2 = Animation::createWithSpriteFrames(vecTemp,0.2f);

	AnimationCache::getInstance()->addAnimation(pAnimation2, "Enemy2Blowup");

	// 敌机3爆炸
	vecTemp.clear();
	for (int i = 0; i < 3; i++)
	{
		auto blowUpName = __String::createWithFormat("t_enemy3_down%d.png", i + 1);
		auto tempBlowUp = SpriteFrameCache::getInstance()->getSpriteFrameByName(
			blowUpName->getCString());
		vecTemp.pushBack(tempBlowUp);
	}

	Animation *pAnimation3 = Animation::createWithSpriteFrames(vecTemp,0.2f);

	AnimationCache::getInstance()->addAnimation(pAnimation3, "Enemy3Blowup");

	// 敌机4爆炸
	vecTemp.clear();
	for (int i = 0; i < 3; i++)
	{
		auto blowUpName = __String::createWithFormat("t_enemy4_down%d.png", i + 1);
		auto tempBlowUp = SpriteFrameCache::getInstance()->getSpriteFrameByName(
			blowUpName->getCString());
		vecTemp.pushBack(tempBlowUp);
	}

	Animation *pAnimation4 = Animation::createWithSpriteFrames(vecTemp, 0.2f);

	AnimationCache::getInstance()->addAnimation(pAnimation4, "Enemy4Blowup");

	// 敌机5爆炸
	vecTemp.clear();
	for (int i = 0; i < 5; i++)
	{
		auto blowUpName = __String::createWithFormat("boss_down%d.png", i + 1);
		auto tempBlowUp = SpriteFrameCache::getInstance()->getSpriteFrameByName(
			blowUpName->getCString());
		vecTemp.pushBack(tempBlowUp);
	}

	Animation *pAnimation5 = Animation::createWithSpriteFrames(vecTemp, 0.4f);

	AnimationCache::getInstance()->addAnimation(pAnimation5, "Enemy5Blowup");

	//根据当前分数来设定添加各种敌机的速度
	this->schedule(schedule_selector(EnemyManager::addSpeed), 1);

	this->schedule(schedule_selector(EnemyManager::addBackground), 10);

	return true;
}

//绑定控制器(更新分数)
void EnemyManager::bindController(Controller* controller, BackgroundMove* background)
{
	this->m_controlLayer = controller;
	m_controlLayer->retain();

	this->m_background = background;
	m_background->retain();

}

//根据分数决定添加敌机速度
void EnemyManager::addSpeed(float dt)
{
	m_fSpeed = m_controlLayer->getSaveData()->getScore() / 500*0.3 + 1;
//	m_fSpeed = m_controlLayer->getSaveData()->getScore() / 20 * 0.4 + 1;

	this->schedule(schedule_selector(EnemyManager::addEnemy1), m_fEnemy1 / m_fSpeed); // 每1秒出现一架敌机1
	this->schedule(schedule_selector(EnemyManager::addEnemy2), m_fEnemy2 / m_fSpeed);
	this->schedule(schedule_selector(EnemyManager::addEnemy3), m_fEnemy3 / m_fSpeed);
	this->schedule(schedule_selector(EnemyManager::addEnemy4), m_fEnemy4 / m_fSpeed);
	this->schedule(schedule_selector(EnemyManager::addEnemy5), m_fEnemy5 / m_fSpeed);
}

//根据分数决定添加敌机速度
void EnemyManager::addBackground(float dt)
{
	m_background->updateBackground(m_controlLayer->getSaveData()->getScore());
}

void EnemyManager::addEnemy1(float dt)
{
	Size size = Director::getInstance()->getVisibleSize();

	Enemy *pEnemySprite = Enemy::create();
	pEnemySprite->setEnemyByType(Enemy1);
	pEnemySprite->setTag(Enemy1);
	this->addChild(pEnemySprite);
	vecEnemy.pushBack(pEnemySprite);

	// 设置运动轨迹 以及到终点时调用的函数
	ccBezierConfig m_bezier;
	m_bezier.controlPoint_1 = ccp(size.width/20, size.height*0.7);
	m_bezier.controlPoint_2 = ccp(size.width/2, size.height/2);
	m_bezier.endPosition = ccp(size.width*0.9, size.height*0.9);
	auto actionMove = BezierTo::create(7.0f, m_bezier);

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyManager::removeEnemy, this));
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	pEnemySprite->runAction(sequence);

	//根据分数改变敌机数量
	
}

void EnemyManager::addEnemy2(float dt)
{
	Size size = Director::getInstance()->getVisibleSize();

	Enemy *pEnemySprite = Enemy::create();
	pEnemySprite->setEnemyByType(Enemy2);
	pEnemySprite->setTag(Enemy2);
	this->addChild(pEnemySprite);
	vecEnemy.pushBack(pEnemySprite);

	// 设置运动轨迹 以及到终点时调用的函数
	ccBezierConfig m_bezier;
	m_bezier.controlPoint_1 = ccp(size.width/11, size.height*0.6);
	m_bezier.controlPoint_2 = ccp(size.width/1.8, size.height/1.9);
	m_bezier.endPosition = ccp(size.width*0.9, size.height / 1.1);
	auto actionMove = BezierTo::create(9.0f, m_bezier);

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyManager::removeEnemy, this));
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL); 
	pEnemySprite->runAction(sequence);
}

void EnemyManager::addEnemy3(float dt)
{
	Size size = Director::getInstance()->getVisibleSize();

	Enemy *pEnemySprite = Enemy::create();
	pEnemySprite->setEnemyByType(Enemy3);
	pEnemySprite->setTag(Enemy3);
	this->addChild(pEnemySprite);
	vecEnemy.pushBack(pEnemySprite);

	// 设置运动轨迹 以及到终点时调用的函数
	ccBezierConfig m_bezier;
	m_bezier.controlPoint_1 = ccp(size.width/7.5, size.height/1.4);
	m_bezier.controlPoint_2 = ccp(size.width/4.5, size.height/1.9);
	m_bezier.endPosition = ccp(size.width*0.9, size.height / 1.1);
	auto actionMove = BezierTo::create(12.0f, m_bezier);

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyManager::removeEnemy, this));
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL); 
	pEnemySprite->runAction(sequence);
}

// 添加敌机4
void EnemyManager::addEnemy4(float dt)
{
	Size size = Director::getInstance()->getVisibleSize();

	Enemy *pEnemySprite = Enemy::create();
	pEnemySprite->setEnemyByType(Enemy4);
	pEnemySprite->setTag(Enemy4);
	this->addChild(pEnemySprite);
	vecEnemy.pushBack(pEnemySprite);

	// 设置运动轨迹 以及到终点时调用的函数
	ccBezierConfig m_bezier;
	m_bezier.controlPoint_1 = ccp(size.width/5.6, size.height/1.2);
	m_bezier.controlPoint_2 = ccp(size.width/1.3, size.height/1.7);
	m_bezier.endPosition = ccp(size.width * 0.9, size.height / 1.1);
	auto actionMove = BezierTo::create(20.0f, m_bezier);

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyManager::removeEnemy, this));
	
	// 按顺序执行 敌机飞到边缘，敌机移动结束
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	pEnemySprite->runAction(sequence);
}

// 添加敌机5
void EnemyManager::addEnemy5(float dt)
{
	Enemy *pEnemySprite = Enemy::create();
	pEnemySprite->setEnemyByType(Enemy5);
	pEnemySprite->setTag(Enemy5);
	this->addChild(pEnemySprite);
	vecEnemy.pushBack(pEnemySprite);

	// 设置运动轨迹 以及到终点时调用的函数
	auto actionMove = Repeat::create(Sequence::create(MoveTo::create(6.0f, Vec2(0, pEnemySprite->getPositionY())), MoveTo::create(6.0f, Vec2(Director::getInstance()->getVisibleSize().width*0.9, pEnemySprite->getPositionY())), nullptr), 3);

	auto actionDone = CallFuncN::create(CC_CALLBACK_1(EnemyManager::removeEnemy, this));

	// 按顺序执行 敌机飞到边缘，敌机移动结束
	Sequence* sequence = Sequence::create(actionMove, actionDone, NULL);
	pEnemySprite->runAction(sequence);
}

void EnemyManager::removeEnemy(Node *pNode)
{
	Enemy* enemy = (Enemy*)pNode;
	if (enemy != NULL)
	{
		this->removeChild(enemy, true);
		vecEnemy.eraseObject(enemy);
	}
}

void EnemyManager::blowupEnemy(Enemy* pEnemySprite)
{
	auto saveData = m_controlLayer->getSaveData();

	Animation *pAnimation = NULL;
	if (Enemy1 == pEnemySprite->getTag())
	{
		// 之前缓存的爆炸动作
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy1Blowup");
		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
		}
		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy1_down.wav");
		}
		saveData->setScore(saveData->getScore() + ENEMY1_SCORE);
	}
	else if (Enemy2 == pEnemySprite->getTag())
	{
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy2Blowup");
		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy2_down.wav");
		}
		saveData->setScore(saveData->getScore() + ENEMY2_SCORE);
	}
	else if (Enemy3 == pEnemySprite->getTag())
	{
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy3Blowup");
		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy3_down.wav");
		}
		saveData->setScore(saveData->getScore() + ENEMY3_SCORE);
	}
	else if (Enemy4 == pEnemySprite->getTag())
	{
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy4Blowup");
		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy4_down.mp3");
		}
		saveData->setScore(saveData->getScore() + ENEMY4_SCORE);
	}
	else if (Enemy5 == pEnemySprite->getTag())
	{
		pAnimation = AnimationCache::getInstance()->getAnimation("Enemy5Blowup");
		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/enemy5_down.wav");
		}
		saveData->setScore(saveData->getScore() + ENEMY5_SCORE);
	}
	else
	{
		return;
	}

	//更新分数
	m_controlLayer->updateScore();

	Animate *pAnimate = Animate::create(pAnimation);

	// 爆炸完，要移除敌机
	auto pActionDone = CallFuncN::create(CC_CALLBACK_0(EnemyManager::removeEnemy, this, pEnemySprite)); 
	Sequence* pSequence = Sequence::create(pAnimate, pActionDone, NULL);
	pEnemySprite->getSprite()->runAction(pSequence);
}

void EnemyManager::setRun(bool bRun)
{
	m_bRun = bRun;
	if (m_bRun)
	{

		this->schedule(schedule_selector(EnemyManager::addSpeed), 1);

		this->schedule(schedule_selector(EnemyManager::addEnemy1), m_fEnemy1 / m_fSpeed); // 每1秒出现一架敌机1
		this->schedule(schedule_selector(EnemyManager::addEnemy2), m_fEnemy2 / m_fSpeed);
		this->schedule(schedule_selector(EnemyManager::addEnemy3), m_fEnemy3 / m_fSpeed);
		this->schedule(schedule_selector(EnemyManager::addEnemy4), m_fEnemy4 / m_fSpeed);
		this->schedule(schedule_selector(EnemyManager::addEnemy5), m_fEnemy5 / m_fSpeed);

		log("this   unschedule");
	}
	else
	{
		this->unschedule(schedule_selector(EnemyManager::addSpeed));

		this->unschedule(schedule_selector(EnemyManager::addEnemy1)); // 每1秒出现一架敌机1
		this->unschedule(schedule_selector(EnemyManager::addEnemy2));
		this->unschedule(schedule_selector(EnemyManager::addEnemy3));
		this->unschedule(schedule_selector(EnemyManager::addEnemy4));
		this->unschedule(schedule_selector(EnemyManager::addEnemy5));
		
		log("this   schedule");
	}
}