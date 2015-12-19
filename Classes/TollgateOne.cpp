/*
 ************************************************************************
 *
 *	TollgateOne.cpp
 *	杜星飞
 *  描述: 关卡1
 *
 ************************************************************************
 */

#include "TollgateOne.h"
#include "GameOver.h"

TollgateOne::TollgateOne() : planeLayer(NULL), bulletLayer(NULL), enemyLayer(NULL), benefitControl(nullptr), controlLayer(NULL), propControl(nullptr)
{

}
TollgateOne::~TollgateOne()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}

cocos2d::Scene* TollgateOne::createScene()
{
	auto scene = Scene::create();

	auto layer = TollgateOne::create();

	scene->addChild(layer);

	return scene;
}

bool TollgateOne::init()
{
	if (!Layer::init())
	{
		return false;
	}

//	log(UserDefault::getInstance()->getXMLFilePath().c_str());

	// 启动触摸机制
	this->setTouchEnabled(true);

//	this->addChild(FlowWord::getInstance());

	// 背景无限滚动
	auto m_back = BackgroundMove::create();
	this->addChild(m_back,0);

	//游戏开始 飘字效果
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/AboutMe.xml");

	auto m_flow = FlowWord::getInstance();

	FlowWord::getInstance()->showFlowWordTollgate(
		((__String *)(dictionary->objectForKey("tollgate1")))->getCString(),
		Point(Director::getInstance()->getVisibleSize().width / 2 , Director::getInstance()->getVisibleSize().height / 2)
		);
	this->addChild(m_flow);


	// 加入分数控制层
	controlLayer = Controller::create();
	this->addChild(controlLayer,2);

	// 加入游戏控制层
	propControl = PropControl::create();
	this->addChild(propControl,2);

	//加入道具控制
	benefitControl = BenefitControl::create();
	this->addChild(benefitControl,1);

	// 加入飞机
	planeLayer = MyPlane::create();
	this->addChild(planeLayer,1);

	// 加入敌机和分数显示
	enemyLayer = EnemyManager::create();
	enemyLayer->bindController(controlLayer,m_back);
	this->addChild(enemyLayer,1);

	// 开启子弹
	bulletLayer = Bullet::create();
	bulletLayer->bindEnemyManager(enemyLayer);
	this->addChild(bulletLayer,1);

	//对返回键的响应
	auto m_listener = EventListenerKeyboard::create();
	m_listener->onKeyReleased = CC_CALLBACK_2(TollgateOne::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

	//游戏更新
	this->schedule(schedule_selector(TollgateOne::gameUpdate));

	return true;
}

void TollgateOne::gameUpdate(float dt)
{
	bool bMoveButt = false;

	//子弹和敌机对碰
	for (auto& eButtle : bulletLayer->vecBullet)
	{
		Sprite* pBullet = (Sprite*)eButtle; // 获取子弹精灵
		bMoveButt = bulletCollisionEnemy(pBullet);
		if (bMoveButt)
		{
			// 子弹删除了，无需再遍历
			break;;
		}
	}

	// 敌机、敌机子弹与我方飞机碰撞
	enemyCollisionPlane();

	//飞机与道具碰撞
	benefitCollisionPlane();

	//游戏是否结束
	isGameOver();
}

bool TollgateOne::bulletCollisionEnemy(Sprite* pBullet)
{
	for (auto& eEnemy : enemyLayer->vecEnemy)
	{
		Enemy* pEnemySprite = (Enemy*)eEnemy;

		// 是否发生碰撞
		if (pBullet->boundingBox().intersectsRect(pEnemySprite->getBoundingBox()))
		{
			log("bulletCollisionEnemy");

			// 飞机只剩下一格生命值
			if (1 == pEnemySprite->getLife())
			{
				pEnemySprite->loseLife(); // 知道为什么这里也要loselife吗？你可以试着注释掉看看
				enemyLayer->blowupEnemy(pEnemySprite);
			}
			else
			{
				pEnemySprite->loseLife();
			}

			//删除子弹
			bulletLayer->removeBullet(pBullet);


			return true;
		}
	}

	return false;
}

void TollgateOne::enemyCollisionPlane()
{
	if (false==planeLayer->getHide())
	{
		Sprite* pPlane = (Sprite*)planeLayer->getChildByTag(AIRPLANE);
		for (auto& eEnemy : enemyLayer->vecEnemy)
		{
			Enemy* pEnemySprite = (Enemy*)eEnemy;

			// 是否发生碰撞
			if (pPlane->boundingBox().intersectsRect(pEnemySprite->getBoundingBox()) && pEnemySprite->getLife() > 0)
			{
				log("enemy and plane");

				enemyLayer->blowupEnemy(pEnemySprite);

				if (1 == planeLayer->getAlive())
				{
					planeLayer->loseAlive();
					propControl->updateAlive(planeLayer->getAlive());
					propControl->updateFire(planeLayer->getFire());
					controlLayer->getSaveData()->save();
					this->unscheduleAllSelectors();
					this->bulletLayer->StopBulletShoot();
					this->planeLayer->blowUp();
					Director::getInstance()->replaceScene(
						TransitionMoveInT::create(4.0f, GameOver::createScene())); // 替换场景
				}
				else
				{
					planeLayer->loseAlive();
					propControl->updateAlive(planeLayer->getAlive());
					propControl->updateFire(planeLayer->getFire());
				}

				return;
			}
		}

		for (auto& eEnemyBullet : bulletLayer->vecEnemyBullet)
		{
			Sprite* pEnemyBullet = (Sprite*)eEnemyBullet; // 获取子弹精灵

			// 是否发生碰撞
			if (pPlane->boundingBox().intersectsRect(pEnemyBullet->getBoundingBox()))
			{
				log("enemyCollisionPlane");

				if (1 == planeLayer->getAlive())
				{
					planeLayer->loseAlive();
					propControl->updateAlive(planeLayer->getAlive());
					propControl->updateFire(planeLayer->getFire());
					controlLayer->getSaveData()->save();
					this->unscheduleAllSelectors();
					this->bulletLayer->StopBulletShoot();
					this->planeLayer->blowUp();
					Director::getInstance()->replaceScene(
						TransitionMoveInT::create(1.0f, GameOver::createScene())); // 替换场景
				}
				else
				{
					planeLayer->loseAlive();
					propControl->updateAlive(planeLayer->getAlive());
					propControl->updateFire(planeLayer->getFire());
				}

				bulletLayer->removeEnemyBullet(pEnemyBullet);

				return;
			}
		}
	}
}

//飞机与道具碰撞
void TollgateOne::benefitCollisionPlane()
{
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/AboutMe.xml");
	Sprite* pPlane = (Sprite*)planeLayer->getChildByTag(AIRPLANE);

	for (auto& eBenefit : benefitControl->vecBenefit)
	{

		Benefit* pBenefitSprite = (Benefit*)eBenefit;

		// 是否发生碰撞
		if (pPlane->boundingBox().intersectsRect(pBenefitSprite->getBoundingBox()))
		{
			log("benefitCollisionPlane");
		
			if (Benefit1 == pBenefitSprite->getTag())
			{
				log("Fire Out");
				//火力增强

				if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/get_double_laser.mp3");
				}

				if (planeLayer->getFire()<4)
				{
					planeLayer->addFire();
					propControl->updateFire(planeLayer->getFire());

					FlowWord::getInstance()->showFlowWordProp(
						((__String *)(dictionary->objectForKey("addfire")))->getCString(),
						Point(pBenefitSprite->getPosition())
						);
				}
				else
				{
					controlLayer->getSaveData()->setScore(controlLayer->getSaveData()->getScore()+100);
				
					FlowWord::getInstance()->showFlowWordProp(
						((__String *)(dictionary->objectForKey("addfire1")))->getCString(),
						Point(pBenefitSprite->getPosition())
						);
				}
						

			}
			else if (Benefit2 == pBenefitSprite->getTag())
			{
				//生命力增强
				log("add alive");
				if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/achievement.mp3");
				}

				planeLayer->addAlive();
				propControl->updateAlive(planeLayer->getAlive());

				FlowWord::getInstance()->showFlowWordProp(
					((__String *)(dictionary->objectForKey("addalive")))->getCString(),
					Point(pBenefitSprite->getPosition())
					);

			}
			else if ((Benefit3 == pBenefitSprite->getTag()) || (Benefit6 == pBenefitSprite->getTag()) || (Benefit7 == pBenefitSprite->getTag()) || (Benefit8 == pBenefitSprite->getTag()))
			{

				if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() && (Benefit8 == pBenefitSprite->getTag()))
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/ThreeTwoOne.mp3");
				}
				else
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/get_bomb.mp3.");
				}

				switch (pBenefitSprite->getTag())
				{
					case Benefit3:
					{
						//敌机全部爆炸
						log("all bomb");
						for (auto& eEnemy : enemyLayer->vecEnemy)
						{
							Enemy* pEnemySprite = (Enemy*)eEnemy;

							enemyLayer->blowupEnemy(pEnemySprite);
						}


						FlowWord::getInstance()->showFlowWordProp(
							((__String *)(dictionary->objectForKey("addbomb")))->getCString(),
							Point(pBenefitSprite->getPosition())
							);

						break;

					}
					case Benefit6:
					{
						log("rect bomb");
						Vec2 pos = pPlane->getPosition();
						Size size = pPlane->getContentSize();
						Rect t_rect = Rect(pos.x - size.width * 3, pos.y - size.height * 3, size.width * 6, size.height * 6);

						//敌机小范围爆炸
						for (auto& eEnemy : enemyLayer->vecEnemy)
						{
							Enemy* pEnemySprite = (Enemy*)eEnemy;
							//intersectsRect
							if (t_rect.intersectsRect(pEnemySprite->getBoundingBox()))
							{
								enemyLayer->blowupEnemy(pEnemySprite);
							}
						}


						FlowWord::getInstance()->showFlowWordProp(
							((__String *)(dictionary->objectForKey("addbomb1")))->getCString(),
							Point(pBenefitSprite->getPosition())
							);

						break;
					}

					case Benefit7:
					{
						log("directon bomb");
						Vec2 pos = pPlane->getPosition();
						Size size = pPlane->getContentSize();
						Rect t_rect = Rect(pos.x - size.width * 1, 0, size.width * 2, Director::getInstance()->getVisibleSize().height);

						//敌机定向爆炸
						for (auto& eEnemy : enemyLayer->vecEnemy)
						{
							Enemy* pEnemySprite = (Enemy*)eEnemy;

							if (t_rect.intersectsRect(pEnemySprite->getBoundingBox()))
							{
								enemyLayer->blowupEnemy(pEnemySprite);
							}
						}

						FlowWord::getInstance()->showFlowWordProp(
							((__String *)(dictionary->objectForKey("addbomb2")))->getCString(),
							Point(pBenefitSprite->getPosition())
							);

						break;
					}

					case Benefit8:
					{
						//敌机定时爆炸	
						log("time bomb");
						auto m_call = CallFunc::create([this]()
						{
							for (auto& eEnemy : enemyLayer->vecEnemy)
							{
								Enemy* pEnemySprite = (Enemy*)eEnemy;

								enemyLayer->blowupEnemy(pEnemySprite);
							}
						}

						);
						enemyLayer->runAction(Sequence::create(DelayTime::create(3.0f), m_call, nullptr));

						FlowWord::getInstance()->showFlowWordProp(
							((__String *)(dictionary->objectForKey("addbomb3")))->getCString(),
							Point(pBenefitSprite->getPosition())
							);

						break;
					}

					default:
						break;
				}

			}
			else if ((Benefit4 == pBenefitSprite->getTag()) || (Benefit10 == pBenefitSprite->getTag()) || (Benefit11 == pBenefitSprite->getTag()) || (Benefit12 == pBenefitSprite->getTag()))
			{
				//呼叫辽宁号
				if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/out_porp.mp3");
				}

				switch (pBenefitSprite->getTag())
				{
				case Benefit4:
				{
					log("call 1");
					bulletLayer->addCall1();

					FlowWord::getInstance()->showFlowWordProp(
						((__String *)(dictionary->objectForKey("addcall")))->getCString(),
						Point(pBenefitSprite->getPosition())
						);

					break;
				}
				case Benefit10:
				{
					log("call 2");
					bulletLayer->addCall2();

					FlowWord::getInstance()->showFlowWordProp(
						((__String *)(dictionary->objectForKey("addcall1")))->getCString(),
						Point(pBenefitSprite->getPosition())
						);

					break;
				}
				case Benefit11:
				{
					log("call 3");
					bulletLayer->addCall3();

					FlowWord::getInstance()->showFlowWordProp(
						((__String *)(dictionary->objectForKey("addcall2")))->getCString(),
						Point(pBenefitSprite->getPosition())
						);

					break;
				}
				case Benefit12:
				{
					log("call 4");
					bulletLayer->addCall4();

					FlowWord::getInstance()->showFlowWordProp(
						((__String *)(dictionary->objectForKey("addcall3")))->getCString(),
						Point(pBenefitSprite->getPosition())
						);

					break;
				}
				default:
					break;
				}

			}
//////////////////////////////////////////////////////////////////////////
			else if ((Benefit5 == pBenefitSprite->getTag()) && (false==planeLayer->getHide()))
			{
				//防护罩
				log("plane hide");
				if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/benefit_hide.mp3");
				}

				auto m_call1 = CallFunc::create([this]()
				{
					planeLayer->isHide(true);
				}
				);

				auto m_call2 = CallFunc::create([this]()
				{
					planeLayer->isHide(false);
				}
				);

				auto m_action = Spawn::createWithTwoActions(Blink::create(10.0f, 20), DelayTime::create(10.0f));

				planeLayer->runAction(Sequence::create(m_call1, m_action, m_call2, nullptr));


				FlowWord::getInstance()->showFlowWordProp(
					((__String *)(dictionary->objectForKey("hidePlane")))->getCString(),
					Point(pBenefitSprite->getPosition())
					);
			}

			else if (Benefit9 == pBenefitSprite->getTag() && (enemyLayer->isRun()))
			{
				//敌机定时
				log("enemy timed 1");

				if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
				{
					CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/benefit_time.wav");
				}

				auto m_call1 = CallFunc::create([this]()
				{
					enemyLayer->setRun(false);
				}
				);

				auto m_call2 = CallFunc::create([this]()
				{
					enemyLayer->setRun(true);

				}
				);

				enemyLayer->runAction(Sequence::create(m_call1, DelayTime::create(10.0f), m_call2, nullptr));

				FlowWord::getInstance()->showFlowWordProp(
					((__String *)(dictionary->objectForKey("inTime")))->getCString(),
					Point(pBenefitSprite->getPosition())
					);
			}

//////////////////////////////////////////////////////////////////////////

			//benefitControl->updateBenefit(pBenefitSprite);
			benefitControl->removeBenefit(pBenefitSprite);
			return;
		}
	}
}


//喷火粒子特效
void TollgateOne::particleFire(Vec2 vec)
{

}

//游戏是否结束
void TollgateOne::isGameOver()
{
	if (controlLayer->getSaveData()->getScore()>6500)
	{
		controlLayer->getSaveData()->save();
		this->unscheduleAllSelectors();
		this->bulletLayer->StopBulletShoot();
		Director::getInstance()->replaceScene(
			TransitionMoveInT::create(1.0f, GameOver::createScene())); // 替换场景
	}
}


void TollgateOne::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

		}

		this->stopAllActions();

		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelloWorld::createScene()));
	}
}

void TollgateOne::onExit()
{
	this->stopAllActions();
	this->removeAllChildrenWithCleanup(true);
	Layer::onExit();
}