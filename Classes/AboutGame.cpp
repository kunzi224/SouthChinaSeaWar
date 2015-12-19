/*
************************************************************************
*
*	AboutGame.cpp
*	杜星飞 2015年8月13日
*   描述: 游戏玩法、剧情介绍、建议意见
*
************************************************************************
*/

#include "AboutGame.h"
#include "SimpleAudioEngine.h"

AboutGame::AboutGame()
{

}
AboutGame::~AboutGame()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}

Scene* AboutGame::createScene()
{
	do 
	{
		auto scene = Scene::create();
		CC_BREAK_IF(!scene);

		auto layer = AboutGame::create();
		CC_BREAK_IF(!layer);

		scene->addChild(layer);

		return scene;
	} while (0);
	return NULL;
}
bool AboutGame::init()
{
	if (!Layer::init())
		return false;

	//背景音乐
	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	}

	
//	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BackgroundMusic1.mp3", true);
	
	bool bRect = false;

	do 
	{
		auto size = Director::getInstance()->getWinSize();

		//设置背景图片
		auto m_background = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("backgroundStartGame.jpg"));//SpriteFrameName("backgroundTollgateOne.jpg");
		m_background->setPosition(Vec2(size.width/2,size.height/2));
		m_background->setAnchorPoint(Vec2(0.5, 0.5));
		this->addChild(m_background);

		//设置监听器
		auto m_listener = EventListenerKeyboard::create();
		m_listener->onKeyReleased = CC_CALLBACK_2(AboutGame::back, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(m_listener, this);

		//设置标签 并 获取中文文本
		auto dictionary = Dictionary::createWithContentsOfFile("fonts/AboutMe.xml");

		auto m_label3 = Label::createWithTTF(
			((__String*)(dictionary->objectForKey("Others")))->getCString(),
			"fonts/DFPShaoNvW5-GB.ttf",
			35
			);
		m_label3->setDimensions(size.width / 3 * 2, size.height/3);
		m_label3->setColor(Color3B(255, 255, 255));
		m_label3->enableShadow();
		m_label3->setPosition(Point(size.width / 2, size.height*3/4));

		this->addChild(m_label3);

		auto m_label1 = Label::createWithTTF(
			((__String*)(dictionary->objectForKey("AboutMe1")))->getCString(),
			"fonts/DFPShaoNvW5-GB.ttf",
			35
			);
		m_label1->setColor(Color3B(255, 0, 0));
		m_label1->enableShadow();
		m_label1->setPosition(
			Point(size.width/2, size.height-m_label3->getContentSize().height-m_label1->getContentSize().height*3)
			);
		
		this->addChild(m_label1);

		auto m_label4 = Label::createWithTTF(
			((__String*)(dictionary->objectForKey("AboutMe2")))->getCString(),
			"fonts/DFPShaoNvW5-GB.ttf",
			35
			);
		m_label4->setColor(Color3B(255, 0, 0));
		m_label4->enableShadow();
		m_label4->setPosition(
			Point(size.width / 2, size.height - m_label3->getContentSize().height - m_label1->getContentSize().height*4)
			);

		this->addChild(m_label4);

		auto m_label5 = Label::createWithTTF(
			((__String*)(dictionary->objectForKey("AboutMe3")))->getCString(),
			"fonts/DFPShaoNvW5-GB.ttf",
			35
			);
		m_label5->setColor(Color3B(255, 0, 0));
		m_label5->enableShadow();
		m_label5->setPosition(
			Point(size.width / 2, size.height - m_label3->getContentSize().height - m_label1->getContentSize().height*5)
			);

		this->addChild(m_label5);

		auto m_label2 = Label::createWithTTF(
			((__String*)(dictionary->objectForKey("QQ")))->getCString(),
			"fonts/DFPShaoNvW5-GB.ttf",
			35
			);
		m_label2->setDimensions(size.width / 3 * 2, size.height / 6);
		m_label2->setColor(Color3B(0, 255, 0));
		m_label2->enableShadow();
		m_label2->setPosition(Point(size.width / 2, m_label5->getPositionY() - m_label2->getContentSize().height));

		this->addChild(m_label2);

		bRect = true;
	} while (0);

	return bRect;
}

//返回按钮
void AboutGame::back(EventKeyboard::KeyCode keyCode, Event* pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		//背景音乐
//		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
//		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_start.mp3", true);
		Director::getInstance()->popScene();
	}
		
}