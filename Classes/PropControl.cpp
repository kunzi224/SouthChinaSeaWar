/*
************************************************************************
*
*	PropControl.cpp
*	杜星飞 2015年8月13日
*   描述: 
*
************************************************************************
*/

#include "PropControl.h"
#include "SimpleAudioEngine.h"

PropControl::PropControl() : pPauseItem(NULL), pMusicItem(NULL), aliveItem1(nullptr), aliveItem2(nullptr), fireItem1(nullptr), fireItem2(nullptr), m_bBackground(false)
{

}

PropControl::~PropControl()
{
	
}

bool PropControl::init()
{
	if (!Layer::init())
	{
		return false;
	}

	bool bRect = false;

	do
	{
		Size winSize = Director::getInstance()->getWinSize();

		//从xml文件中读取中文显示出来
		auto dictionary = Dictionary::createWithContentsOfFile("fonts/AboutMe.xml");

		//游戏声音控制按钮
		Sprite *normalMusic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_musicPause.png"));
		Sprite *pressedMusic = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_musicPause.png"));
		pMusicItem = MenuItemSprite::create(
			normalMusic,
			normalMusic,
			NULL,
			CC_CALLBACK_1(PropControl::menuMusicCallback, this));


		//游戏暂停按钮
		Sprite *normalPause = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_nor.png"));
		Sprite *pressedPause = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_pressed.png"));
		pPauseItem = MenuItemSprite::create(
			normalPause,
			pressedPause,
			NULL,
			CC_CALLBACK_1(PropControl::menuPauseCallback, this));

		Menu *menuPause = Menu::create(pMusicItem, pPauseItem, NULL);
		menuPause->alignItemsHorizontallyWithPadding(pPauseItem->getContentSize().width / 2);
		menuPause->setPosition(
			Point(winSize.width - pPauseItem->getContentSize().width * 2, winSize.height - normalPause->getContentSize().height));
		this->addChild(menuPause);


		
		aliveItem1 = Label::createWithTTF(
			(((__String*)(dictionary->objectForKey("alive"))))->getCString(),
			"fonts/DFPShaoNvW5-GB.ttf",
			25);
		aliveItem1->setPosition(Point(winSize.width / 8, winSize.height - aliveItem1->getContentSize().height));
		aliveItem1->setColor(Color3B(255, 0, 0));
		aliveItem1->enableShadow();
		this->addChild(aliveItem1);

		aliveItem2 = Label::createWithTTF(
			"5",
			"fonts/DFPShaoNvW5-GB.ttf",
			25);
		aliveItem2->setPosition(Point(aliveItem1->getPositionX() * 2, winSize.height - aliveItem1->getContentSize().height));
		aliveItem2->setColor(Color3B::YELLOW);
		aliveItem2->enableShadow();
		this->addChild(aliveItem2);

		fireItem1 = Label::createWithTTF(
			(((__String*)(dictionary->objectForKey("fire"))))->getCString(),
			"fonts/DFPShaoNvW5-GB.ttf",
			25);
		fireItem1->setPosition(Point(winSize.width / 8, winSize.height - aliveItem1->getContentSize().height - fireItem1->getContentSize().height));
		fireItem1->setColor(Color3B::GREEN);
		fireItem1->enableShadow();
		this->addChild(fireItem1);

		fireItem2 = Label::createWithTTF(
			"1",
			"fonts/DFPShaoNvW5-GB.ttf",
			25);
		fireItem2->setPosition(Point(aliveItem1->getPositionX() * 2, winSize.height - aliveItem1->getContentSize().height-fireItem2->getContentSize().height));
		fireItem2->enableShadow();
		this->addChild(fireItem2);

	} while (0);

	return true;
}

//游戏暂停
void PropControl::menuPauseCallback(cocos2d::Ref* pSender)
{
	if (!Director::getInstance()->isPaused())
	{
		// 图标状态设置
		pPauseItem->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_nor.png")));
		pPauseItem->setSelectedImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_pause_press.png")));
		
		if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			m_bBackground = true;
			CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); // 停止背景音乐
			CocosDenshion::SimpleAudioEngine::getInstance()->stopAllEffects(); // 停止所有的特效
		}

		Director::getInstance()->pause(); // 停止所有的动作，敌机飞行，子弹前进等
	}
	else
	{
		pPauseItem->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_nor.png")));
		pPauseItem->setSelectedImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_resume_pressed.png")));
		if (m_bBackground)
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();// 恢复
			m_bBackground = false;
		}
		Director::getInstance()->resume(); // 恢复
	}
}

void PropControl::menuMusicCallback(cocos2d::Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/button.mp3");
	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		// 图标状态设置
		pMusicItem->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_music.png")));
		pMusicItem->setSelectedImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_music.png")));
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(); // 停止背景音乐
	}
	else
	{
		pMusicItem->setNormalImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_musicPause.png")));
		pMusicItem->setSelectedImage(Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_musicPause.png")));
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BackgroundMusic.mp3", true);// 恢复
	}
}


// 更新生命值
void PropControl::updateAlive(int alive)
{
	// 更新分数
	if (alive >= 0)
	{
		auto strAlive = String::createWithFormat("%d", alive);
		aliveItem2->setString(strAlive->getCString());
	}
}

// 更新火力值
void PropControl::updateFire(int fire)
{
	// 更新分数
	if (fire >= 0)
	{
		auto strFire = String::createWithFormat("%d", fire);
		fireItem2->setString(strFire->getCString());
	}
}