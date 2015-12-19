/*
************************************************************************
*
*	MyPlane.cpp
*	���Ƿ� 2015��8��13��
*   ����: �����ɻ������ԡ����ܵ�
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


//�ɻ�����
Animate* MyPlane::planeFly()
{
	Vector<SpriteFrame *> vector;
	for (int i = 0; i < 4; i++)
	{
		auto frameName = __String::createWithFormat("t_chinaFly%d.png", i + 1);
		auto temSpriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		vector.pushBack(temSpriteFrame);
	}
	//���ò��ϲ��ŷɻ��Ķ���
	auto animation = Animation::createWithSpriteFrames(vector, 0.2f, -1);
	auto animate = Animate::create(animation);

	return animate;
}

bool MyPlane::init()
{
	if(!Layer::init())
		return false;

	Size winSize = Director::getInstance()->getWinSize();

	//��ӷɻ�
	auto m_planeSprite = Sprite::createWithSpriteFrameName("t_chinaFly1.png");
	m_planeSprite->setPosition(Point(winSize.width / 2, m_planeSprite->getContentSize().height / 2));
	m_planeSprite->setTag(AIRPLANE);
	this->addChild(m_planeSprite);
	m_planeSprite->runAction(this->planeFly());

	// �ɻ�����
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);	//���ɴ����¼�

	//�Դ����¼��ļ�������ֱ��д������
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

	//������������ӵ�eventDispacher��ȥ  
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, m_planeSprite);

	// �����߽���
	this->schedule(schedule_selector(MyPlane::borderCheck));

	return true;
}


//�߽���
void MyPlane::borderCheck(float dt)
{
	//���б߽��ж�,���ɳ�����Ļ  
	Point location = this->getChildByTag(AIRPLANE)->getPosition();
	Size winSize = Director::getInstance()->getWinSize();  

	// ���صľ���������εĴ�С
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

//�ɻ���ը
void MyPlane::blowUp()
{
	this->unscheduleAllSelectors(); // ֹͣ�ɻ��������ж�

	//���طɻ���ը���� ��Ч
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

	// ֹͣһ�еķɻ�����
	this->getChildByTag(AIRPLANE)->stopAllActions(); 

	this->getChildByTag(AIRPLANE)->runAction(sequence);
}

//�Ƴ��ɻ�
void MyPlane::removePlane()
{
	// �Ƴ��ɻ����� true�ӽڵ��ϵ�����������Ϊ�ͻص�������
	this->removeChildByTag(AIRPLANE, true); 
}

//��ȡ����ֵ
int MyPlane::getAlive()
{
	return m_alive;
}

//�趨����ֵ
void MyPlane::loseAlive()
{
	--m_alive;
	m_fire = 1;
}

//��������ֵ
void MyPlane::addAlive()
{
	++m_alive;
}

//��ȡ����ֵ
int MyPlane::getFire()
{
	return m_fire;
}

//���ӻ���ֵ
void MyPlane::addFire()
{
	++m_fire;
}

//�趨�Ƿ�����
void MyPlane::isHide(bool hide)
{
	m_bHide = hide;
}

//��ȡ�Ƿ�����
bool MyPlane::getHide()
{
	return m_bHide;
}