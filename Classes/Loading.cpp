/*
************************************************************************
*
*	Loading.cpp
*	杜星飞 2015年8月13日
*   描述: 加载资源
*
************************************************************************
*/

#include "HelloWorldScene.h"
#include "Loading.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* Loading::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = Loading::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Loading::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 3. add your codes below...

	auto dictionary = Dictionary::createWithContentsOfFile("fonts/AboutMe.xml");

	// 初始化提示标签
	auto m_label = Label::createWithTTF(
		((__String *)(dictionary->objectForKey("loading")))->getCString(),
		"fonts/DFPShaoNvW5-GB.ttf",
		35);
	m_label->setTextColor(Color4B::RED);
	m_label->enableShadow();
	m_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *3/4));
	this->addChild(m_label);

	/************************************************************************/
	/* 加载资源                                                             */
	/************************************************************************/

	//播放背景音乐
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_start.mp3");

	//加载图片
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/add.plist");


	//异步加载图片
	m_spriteLoad = 0;
	int* m_pNum = &m_spriteLoad;

	auto m_call = [m_pNum](Texture2D*)
	{
		(*m_pNum)++;
		log("m_pNum first %d", *m_pNum);
	};
	TextureCache::getInstance()->addImageAsync("backgroundStartGame.jpg", m_call);

	this->schedule(schedule_selector(Loading::onSpriteLoading));

	return true;
}

void Loading::onSpriteLoading(float dt)
{

	if (m_spriteLoad==1)
	{
		this->unschedule(schedule_selector(Loading::onSpriteLoading));

		auto m_callFunc = CallFunc::create([]()
		{
			auto m_scene = HelloWorld::createScene();
			Director::getInstance()->replaceScene(TransitionFadeTR::create(1.0f, m_scene));
		}
		);

		this->runAction(m_callFunc);
	}
}