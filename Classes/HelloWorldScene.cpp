#include "HelloWorldScene.h"
#include "TollgateOne.h"
#include "ScoreScene.h"
#include "AboutGame.h"

USING_NS_CC;

HelloWorld::HelloWorld()
{

}

HelloWorld::~HelloWorld()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
}

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//开始游戏 按钮
	auto tempStart1 = Sprite::createWithSpriteFrameName("StartGame_nor.png");
	auto tempStart2 = Sprite::createWithSpriteFrameName("StartGame_touched.png");

	auto startItem = MenuItemSprite::create(
		tempStart1, tempStart2, CC_CALLBACK_1(HelloWorld::startGame, this)
		);

	//高分记录 按钮
	auto tempScore1 = Sprite::createWithSpriteFrameName("GameScore_nor.png");
	auto tempScore2 = Sprite::createWithSpriteFrameName("GameScore_touched.png");

	auto highScoreItem = MenuItemSprite::create(
		tempScore1, tempScore2, CC_CALLBACK_1(HelloWorld::highScore, this)
		);

	//游戏说明 按钮
	auto tempHelp1 = Sprite::createWithSpriteFrameName("GameHelp_nor.png");
	auto tempHelp2 = Sprite::createWithSpriteFrameName("GameHelp_touched.png");

	auto aboutGameItem = MenuItemSprite::create(
		tempHelp1, tempHelp2, CC_CALLBACK_1(HelloWorld::aboutGame, this)
		);

	//退出游戏 按钮
	auto tempOver1 = Sprite::createWithSpriteFrameName("GameOver_nor.png");
	auto tempOver2 = Sprite::createWithSpriteFrameName("GameOver_touched.png");

	auto closeItem = MenuItemSprite::create(
		tempOver1, tempOver2, CC_CALLBACK_1(HelloWorld::menuCloseCallback, this)
		);

	// create menu, it's an autorelease object
	auto menu = Menu::create(startItem, highScoreItem, aboutGameItem, closeItem, NULL);
	menu->alignItemsVerticallyWithPadding(closeItem->getContentSize().height / 2);
	menu->setPosition(Vec2(origin.x + closeItem->getContentSize().width, closeItem->getContentSize().height * 3));
	menu->setAnchorPoint(Vec2(0, 0));
	this->addChild(menu, 1);

	//加载背景
	auto m_background = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("backgroundStartGame.jpg"));
	m_background->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2));
	m_background->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(m_background);

	//加载启动界面动画
	auto startSprite = Sprite::createWithSpriteFrameName("backgroundAnimate1.png");
	startSprite->setPosition(Vec2(origin.x + visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(startSprite, 1);

	startSprite->runAction(this->startMainAnimate());


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

	//监听手机键盘
	m_listener = EventListenerKeyboard::create();
	m_listener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		m_listener, this);

	//预加载图片
	preLoadPicture();

	this->schedule(schedule_selector(HelloWorld::onSpriteLoading));

    return true;
}

//预加载声音 图片
void HelloWorld::preLoadPicture()
{
	//加载声音
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/game_over.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/BackgroundMusic.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/BackgroundMusic1.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/BackgroundMusic2.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/bullet.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemyBullet.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/chinaDown.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy1_down.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy2_down.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy3_down.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy4_down.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/enemy5_down.wav");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/achievement.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/get_bomb.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/get_double_laser.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/out_porp.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/benefit_hide.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/benefit_time.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/ThreeTwoOne.mp3.mp3");
	//异步加载图片
	m_spriteNum = 0;
	int* m_pNum = &m_spriteNum;

	auto m_call = [m_pNum](Texture2D*)
	{
		(*m_pNum)++;
		log("m_pNum %d",*m_pNum);
	};

	TextureCache::getInstance()->addImageAsync("2.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("3.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("4.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("5.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("6.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("7.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("8.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("9.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("10.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("11.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("12.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("backgroundGameOver.jpg", m_call);
	TextureCache::getInstance()->addImageAsync("backgroundTollgateThree.jpg", m_call);
}


void HelloWorld::onSpriteLoading(float dt)
{

	if (m_spriteNum == 14)
	{
		this->unschedule(schedule_selector(HelloWorld::onSpriteLoading));
	}
}


//开始游戏
void HelloWorld::startGame(Ref* pSender)
{
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	log("banner hide");

	Director::getInstance()->replaceScene(TransitionFade::create(0.5f, TollgateOne::createScene()));
}
//高分记录
void HelloWorld::highScore(Ref* pSender)
{
	Director::getInstance()->pushScene(
		TransitionProgressRadialCCW::create(1.0f, ScoreScene::createScene()));
}
//游戏说明
void HelloWorld::aboutGame(Ref* pSender)
{
	Director::getInstance()->pushScene(
		TransitionJumpZoom::create(1.0f, AboutGame::createScene()));
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

//启动界面动画
Animate* HelloWorld::startMainAnimate()
{
	Vector<SpriteFrame*> vecStartAnimate;
	for (int i = 0; i < 4; i++)
	{
		auto tempString = __String::createWithFormat("backgroundAnimate%d.png", i + 1);
		auto tempAnimate = SpriteFrameCache::getInstance()->getSpriteFrameByName(tempString->getCString());

		vecStartAnimate.pushBack(tempAnimate);
	}

	auto animate = Animate::create(Animation::createWithSpriteFrames(
		vecStartAnimate, 0.5f, -1));

	return animate;
}

//卸载不必要的资源
void HelloWorld::onExit()
{
	Layer::onExit();
//	Director::getInstance()->getTextureCache()->removeUnusedTextures();
}


//响应键盘(主要针对Android)
void HelloWorld::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		Director::getInstance()->end();
}