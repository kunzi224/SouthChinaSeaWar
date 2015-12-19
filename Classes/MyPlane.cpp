/*
************************************************************************
*
*	MyPlane.cpp
*	杜星飞 2015年8月13日
*   描述: 包含飞机的属性、功能等
*
************************************************************************
*/

#include "MyPlane.h"
#include "SimpleAudioEngine.h"

MyPlane::MyPlane() :m_alive(5), m_fire(1), m_bHide(false)
{

}
MyPlane::~MyPlane()
{

}

MyPlane* MyPlane::instancePlane = NULL;

MyPlane* MyPlane::create()
{
	MyPlane* m_plane = NULL;
	do 
	{
		m_plane = new MyPlane();
		CC_BREAK_IF(!m_plane);

		if (m_plane && m_plane->init())
		{
			m_plane->autorelease();
			instancePlane = m_plane;
		}
		else
			CC_SAFE_DELETE(m_plane);
	} while (0);

	return m_plane;
}


//飞机动画
Animate* MyPlane::planeFly()
{
	Vector<SpriteFrame *> vector;
	for (int i = 0; i < 4; i++)
	{
		auto frameName = __String::createWithFormat("t_chinaFly%d.png", i + 1);
		auto temSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		vector.pushBack(temSpriteFrame);
	}
	//设置不断播放飞机的动画
	auto animation = Animation::createWithSpriteFrames(vector, 0.2f, -1);
	auto animate = Animate::create(animation);

	return animate;
}

bool MyPlane::init()
{
	if(!Layer::init())
		return false;

	Size winSize = Director::getInstance()->getWinSize();

	//添加飞机
	auto m_planeSprite = Sprite::createWithSpriteFrameName("t_chinaFly1.png");
	m_planeSprite->setPosition(Point(winSize.width / 2, m_planeSprite->getContentSize().height / 2));
	m_planeSprite->setTag(AIRPLANE);
	this->addChild(m_planeSprite);
	m_planeSprite->runAction(this->planeFly());

	// 飞机触摸
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);	//吞噬触摸事件

	//对触摸事件的监听过程直接写在这里
	listener->onTouchBegan = [](Touch* touch, Event *event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());

		Point locationInNode = target->convertToNodeSpace(touch->getLocation());
		Size s = target->getContentSize();
		Rect rect = Rect(0, 0, s.width, s.height);

		if (rect.containsPoint(locationInNode))
			return true;
		else
			return false;
	};

	listener->onTouchMoved = [](Touch* touch, Event *event)
	{
		auto target = static_cast<Sprite*>(event->getCurrentTarget());
		target->setPosition(target->getPosition() + touch->getDelta());
	};

	listener->onTouchEnded = [](Touch* touch, Event* event)
	{
	};

	//将触摸监听添加到eventDispacher中去  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, m_planeSprite);

	// 开启边界检测
	this->schedule(schedule_selector(MyPlane::borderCheck));

	return true;
}


//边界检测
void MyPlane::borderCheck(float dt)
{
	//进行边界判断,不可超出屏幕  
	Point location = this->getChildByTag(AIRPLANE)->getPosition();
	Size winSize = Director::getInstance()->getWinSize();  

	// 返回的就是这个矩形的大小
	Size planeSize = this->getChildByTag(AIRPLANE)->getContentSize();  
	
	if (location.x<-planeSize.width / 64)
		location.x = -planeSize.width / 64;

	if (location.x>winSize.width + planeSize.width / 64)
		location.x = winSize.width + planeSize.width / 64;

	if (location.y<planeSize.height / 2)
		location.y = planeSize.height / 2;

	if (location.y>winSize.height - planeSize.height / 2)
		location.y = winSize.height - planeSize.height / 2;

	this->getChildByTag(AIRPLANE)->setPosition(location);
}

//飞机爆炸
void MyPlane::blowUp()
{
	this->unscheduleAllSelectors(); // 停止飞机的所有行动

	//加载飞机爆炸动画 音效
	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/chinaDown.mp3");
	}
	
	Vector<SpriteFrame*> planeBlowUp;
	for (int i = 0; i < 4; i++)
	{
		auto planeName = __String::createWithFormat("t_china1_down%d.png", i + 1);
		auto tempBlowUp = SpriteFrameCache::getInstance()->getSpriteFrameByName(
			planeName->getCString());
		planeBlowUp.pushBack(tempBlowUp);
	}

	Animation* animation = Animation::createWithSpriteFrames(planeBlowUp, 0.1f);
	Animate* animate = Animate::create(animation);
	CallFunc* m_removePlane = CallFunc::create(this, callfunc_selector(MyPlane::removePlane));
	Sequence* sequence = Sequence::create(animate, m_removePlane, NULL); 

	// 停止一切的飞机动作
	this->getChildByTag(AIRPLANE)->stopAllActions(); 

	this->getChildByTag(AIRPLANE)->runAction(sequence);
}

//移除飞机
void MyPlane::removePlane()
{
	// 移除飞机精灵 true子节点上的所有运行行为和回调将清理
	this->removeChildByTag(AIRPLANE, true); 
}

//获取生命值
int MyPlane::getAlive()
{
	return m_alive;
}

//设定生命值
void MyPlane::loseAlive()
{
	--m_alive;
	m_fire = 1;
}

//增加生命值
void MyPlane::addAlive()
{
	++m_alive;
}

//获取火力值
int MyPlane::getFire()
{
	return m_fire;
}

//增加火力值
void MyPlane::addFire()
{
	++m_fire;
}

//设定是否隐身
void MyPlane::isHide(bool hide)
{
	m_bHide = hide;
}

//获取是否隐身
bool MyPlane::getHide()
{
	return m_bHide;
}