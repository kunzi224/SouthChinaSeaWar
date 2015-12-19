/*
 ************************************************************************
 *
 *	TollgateOne.cpp
 *	���Ƿ�
 *  ����: �ؿ�1
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

	// ������������
	this->setTouchEnabled(true);

//	this->addChild(FlowWord::getInstance());

	// �������޹���
	auto m_back = BackgroundMove::create();
	this->addChild(m_back,0);

	//��Ϸ��ʼ Ʈ��Ч��
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/AboutMe.xml");

	auto m_flow = FlowWord::getInstance();

	FlowWord::getInstance()->showFlowWordTollgate(
		((__String *)(dictionary->objectForKey("tollgate1")))->getCString(),
		Point(Director::getInstance()->getVisibleSize().width / 2 , Director::getInstance()->getVisibleSize().height / 2)
		);
	this->addChild(m_flow);


	// ����������Ʋ�
	controlLayer = Controller::create();
	this->addChild(controlLayer,2);

	// ������Ϸ���Ʋ�
	propControl = PropControl::create();
	this->addChild(propControl,2);

	//������߿���
	benefitControl = BenefitControl::create();
	this->addChild(benefitControl,1);

	// ����ɻ�
	planeLayer = MyPlane::create();
	this->addChild(planeLayer,1);

	// ����л��ͷ�����ʾ
	enemyLayer = EnemyManager::create();
	enemyLayer->bindController(controlLayer,m_back);
	this->addChild(enemyLayer,1);

	// �����ӵ�
	bulletLayer = Bullet::create();
	bulletLayer->bindEnemyManager(enemyLayer);
	this->addChild(bulletLayer,1);

	//�Է��ؼ�����Ӧ
	auto m_listener = EventListenerKeyboard::create();
	m_listener->onKeyReleased = CC_CALLBACK_2(TollgateOne::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

	//��Ϸ����
	this->schedule(schedule_selector(TollgateOne::gameUpdate));

	return true;
}

void TollgateOne::gameUpdate(float dt)
{
	bool bMoveButt = false;

	//�ӵ��͵л�����
	for (auto& eButtle : bulletLayer->vecBullet)
	{
		Sprite* pBullet = (Sprite*)eButtle; // ��ȡ�ӵ�����
		bMoveButt = bulletCollisionEnemy(pBullet);
		if (bMoveButt)
		{
			// �ӵ�ɾ���ˣ������ٱ���
			break;;
		}
	}

	// �л����л��ӵ����ҷ��ɻ���ײ
	enemyCollisionPlane();

	//�ɻ��������ײ
	benefitCollisionPlane();

	//��Ϸ�Ƿ����
	isGameOver();
}

bool TollgateOne::bulletCollisionEnemy(Sprite* pBullet)
{
	for (auto& eEnemy : enemyLayer->vecEnemy)
	{
		Enemy* pEnemySprite = (Enemy*)eEnemy;

		// �Ƿ�����ײ
		if (pBullet->boundingBox().intersectsRect(pEnemySprite->getBoundingBox()))
		{
			log("bulletCollisionEnemy");

			// �ɻ�ֻʣ��һ������ֵ
			if (1 == pEnemySprite->getLife())
			{
				pEnemySprite->loseLife(); // ֪��Ϊʲô����ҲҪloselife�����������ע�͵�����
				enemyLayer->blowupEnemy(pEnemySprite);
			}
			else
			{
				pEnemySprite->loseLife();
			}

			//ɾ���ӵ�
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

			// �Ƿ�����ײ
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
						TransitionMoveInT::create(4.0f, GameOver::createScene())); // �滻����
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
			Sprite* pEnemyBullet = (Sprite*)eEnemyBullet; // ��ȡ�ӵ�����

			// �Ƿ�����ײ
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
						TransitionMoveInT::create(1.0f, GameOver::createScene())); // �滻����
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

//�ɻ��������ײ
void TollgateOne::benefitCollisionPlane()
{
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/AboutMe.xml");
	Sprite* pPlane = (Sprite*)planeLayer->getChildByTag(AIRPLANE);

	for (auto& eBenefit : benefitControl->vecBenefit)
	{

		Benefit* pBenefitSprite = (Benefit*)eBenefit;

		// �Ƿ�����ײ
		if (pPlane->boundingBox().intersectsRect(pBenefitSprite->getBoundingBox()))
		{
			log("benefitCollisionPlane");
		
			if (Benefit1 == pBenefitSprite->getTag())
			{
				log("Fire Out");
				//������ǿ

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
				//��������ǿ
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
						//�л�ȫ����ը
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

						//�л�С��Χ��ը
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

						//�л�����ը
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
						//�л���ʱ��ը	
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
				//����������
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
				//������
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
				//�л���ʱ
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


//���������Ч
void TollgateOne::particleFire(Vec2 vec)
{

}

//��Ϸ�Ƿ����
void TollgateOne::isGameOver()
{
	if (controlLayer->getSaveData()->getScore()>6500)
	{
		controlLayer->getSaveData()->save();
		this->unscheduleAllSelectors();
		this->bulletLayer->StopBulletShoot();
		Director::getInstance()->replaceScene(
			TransitionMoveInT::create(1.0f, GameOver::createScene())); // �滻����
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