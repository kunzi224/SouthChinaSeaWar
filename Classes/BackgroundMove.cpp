/*
************************************************************************
*
*	BackgroundMove.cpp
*	杜星飞 2015年8月13日
*	描述： 在进入游戏场景之后，背景开始移动
*
************************************************************************
*/

#include "BackgroundMove.h"
#include "SimpleAudioEngine.h"
#include "FlowWord.h"

BackgroundMove::BackgroundMove() : m_background3(NULL), m_background4(NULL)//m_background1(NULL), m_background2(NULL), m_background3(NULL), m_background4(NULL)
{

}
BackgroundMove::~BackgroundMove()
{
//	CC_SAFE_DELETE(m_background1);
//	CC_SAFE_DELETE(m_background2);
//	CC_SAFE_DELETE(m_background3);
//	CC_SAFE_DELETE(m_background4);
}
bool BackgroundMove::init()
{
	bool bRect = false;

	do 
	{
		if (!Layer::init())
			return false;
#if 0

		//加载背景图片
		m_background1 = Sprite::createWithSpriteFrameName("backgroundTollgate2.png");
		m_background1->setPosition(Point(0,0));
		m_background1->setAnchorPoint(Vec2(0, 0));

		this->addChild(m_background1,1);

		m_background2 = Sprite::createWithSpriteFrameName("backgroundTollgate2.png");
		m_background2->setPosition(Point(0, 0));
		m_background2->setAnchorPoint(Vec2(0, 0));
		m_background2->setFlipY(true);

		this->addChild(m_background2,1);

#endif

		//加载背景图片
		m_background3 = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("backgroundTollgateThree.jpg"));//WithSpriteFrameName("backgroundTollgateThree.jpg");
//		m_background3 = Sprite::createWithSpriteFrameName("12.png");
//		m_background3 = Sprite::create("ui/12.png");
		m_background3->setPosition(Point(0, 0));
		m_background3->setAnchorPoint(Vec2(0, 0));

		this->addChild(m_background3, 0);

		m_background4 = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("backgroundTollgateThree.jpg")); //("backgroundTollgateThree.jpg");
//		m_background4 = Sprite::createWithSpriteFrameName("12.png");
//		m_background4 = Sprite::create("ui/12.png");
		m_background4->setPosition(Point(0, 0));
		m_background4->setAnchorPoint(Vec2(0, 0));
		m_background4->setFlipY(true);

		this->addChild(m_background4, 0);

		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BackgroundMusic.mp3", true);
//		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BackgroundMusic2.mp3", true);		
		bRect = true;
	} while (0);

	return bRect;
}
void BackgroundMove::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	this->schedule(SEL_SCHEDULE(&BackgroundMove::move));
}

void BackgroundMove::move(float dt)
{
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
#if 0

	m_background1->setPositionY(m_background1->getPositionY() - OFFSET);
	m_background2->setPositionY(m_background1->getPositionY() + m_background1->getContentSize().height);
	if (m_background2->getPositionY() <= origin.y)
		m_background1->setPositionY(0);

#endif

	if (nullptr==m_background3)
	{
		return;
	}

	m_background3->setPositionY(m_background3->getPositionY() + OFFSET);
	m_background4->setPositionY(m_background3->getPositionY() - m_background3->getContentSize().height);
	if (m_background4->getPositionY() >= origin.y)
		m_background3->setPositionY(0);

}

void BackgroundMove::updateBackground(int score)
{

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto dictionary = Dictionary::createWithContentsOfFile("fonts/AboutMe.xml");

//	auto m_flow = FlowWord::getInstance();
//	this->addChild(m_flow);

//	log("background score %d!", score);

	auto m_textureCache = TextureCache::getInstance();

	switch (score / 500)
//	switch (score / 100)
	{
	case 0:
		break;

	case 1:
		if (1==m_background3->getTag())
		{
			break;
		}
		else
		{
			m_background3->setTexture(m_textureCache->getTextureForKey("2.jpg"));
			m_background4->setTexture(m_textureCache->getTextureForKey("2.jpg"));
			FlowWord::getInstance()->showFlowWordTollgate(
				((__String *)(dictionary->objectForKey("tollgate2")))->getCString(),
				Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
				);

			m_background3->setTag(1);
		}
		break;

	case 2:
		if (2==m_background3->getTag())
		{
			break;
		}
		else
		{
			m_background3->setTexture(m_textureCache->getTextureForKey("3.jpg"));
			m_background4->setTexture(m_textureCache->getTextureForKey("3.jpg"));

			FlowWord::getInstance()->showFlowWordTollgate(
				((__String *)(dictionary->objectForKey("tollgate3")))->getCString(),
				Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
				);

			m_background3->setTag(2);
		}

		break;

	case 3:
		if (3==m_background3->getTag())
		{
			break;
		}
		else
		{
			m_background3->setTexture(m_textureCache->getTextureForKey("4.jpg"));
			m_background4->setTexture(m_textureCache->getTextureForKey("4.jpg"));

			FlowWord::getInstance()->showFlowWordTollgate(
				((__String *)(dictionary->objectForKey("tollgate4")))->getCString(),
				Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
				);

			m_background3->setTag(3);
		}

		break;

	case 4:
		if (4==m_background3->getTag())
		{
			break;
		}
		else
		{
			m_background3->setTexture(m_textureCache->getTextureForKey("5.jpg"));
			m_background4->setTexture(m_textureCache->getTextureForKey("5.jpg"));

			FlowWord::getInstance()->showFlowWordTollgate(
				((__String *)(dictionary->objectForKey("tollgate5")))->getCString(),
				Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
				);

			m_background3->setTag(4);
		}

		break;

	case 5:
		if (5==m_background3->getTag())
		{
			break;
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BackgroundMusic1.mp3", true);

			m_background3->setTexture(m_textureCache->getTextureForKey("6.jpg"));
			m_background4->setTexture(m_textureCache->getTextureForKey("6.jpg"));

			FlowWord::getInstance()->showFlowWordTollgate(
				((__String *)(dictionary->objectForKey("tollgate6")))->getCString(),
				Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
				);

			m_background3->setTag(5);
		}

		break;

	case 6:
		if (6==m_background3->getTag())
		{
			break;
		}
		else
		{
			m_background3->setTexture(m_textureCache->getTextureForKey("7.jpg"));
			m_background4->setTexture(m_textureCache->getTextureForKey("7.jpg"));

			FlowWord::getInstance()->showFlowWordTollgate(
				((__String *)(dictionary->objectForKey("tollgate7")))->getCString(),
				Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
				);

			m_background3->setTag(6);
		}

		break;

	case 7:
		if (7==m_background3->getTag())
		{
			break;
		}
		else
		{
			m_background3->setTexture(m_textureCache->getTextureForKey("8.jpg"));
			m_background4->setTexture(m_textureCache->getTextureForKey("8.jpg"));

			FlowWord::getInstance()->showFlowWordTollgate(
				((__String *)(dictionary->objectForKey("tollgate8")))->getCString(),
				Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
				);

			m_background3->setTag(7);
		}

		break;

	case 8:
		if (8==m_background3->getTag())
		{
			break;
		}
		else
		{
			m_background3->setTexture(m_textureCache->getTextureForKey("9.jpg"));
			m_background4->setTexture(m_textureCache->getTextureForKey("9.jpg"));
			FlowWord::getInstance()->showFlowWordTollgate(
				((__String *)(dictionary->objectForKey("tollgate9")))->getCString(),
				Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
				);

			m_background3->setTag(8);
		}
		break;

	case 9:
		if (9==m_background3->getTag())
		{
			break;
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BackgroundMusic2.mp3", true);

			m_background3->setTexture(m_textureCache->getTextureForKey("10.jpg"));
			m_background4->setTexture(m_textureCache->getTextureForKey("10.jpg"));
			FlowWord::getInstance()->showFlowWordTollgate(
				((__String *)(dictionary->objectForKey("tollgate10")))->getCString(),
				Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
				);

			m_background3->setTag(9);
		}
		break;

	case 10:
		if (10==m_background3->getTag())
		{
			break;
		}
		else
		{
			m_background3->setTexture(m_textureCache->getTextureForKey("11.jpg"));
			m_background4->setTexture(m_textureCache->getTextureForKey("11.jpg"));
			FlowWord::getInstance()->showFlowWordTollgate(
				((__String *)(dictionary->objectForKey("tollgate11")))->getCString(),
				Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
				);

			m_background3->setTag(10);
		}
		break;

	case 11:
		if (11==m_background3->getTag())
		{
			break;
		}
		else
		{
			m_background3->setTexture(m_textureCache->getTextureForKey("12.jpg"));
			m_background4->setTexture(m_textureCache->getTextureForKey("12.jpg"));
			FlowWord::getInstance()->showFlowWordTollgate(
				((__String *)(dictionary->objectForKey("tollgate12")))->getCString(),
				Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2)
				);

			m_background3->setTag(11);
		}
		break;

	default:
		break;
	}
}