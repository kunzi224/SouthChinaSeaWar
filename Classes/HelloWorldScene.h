#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
	HelloWorld();

	~HelloWorld();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

public:
	//Ԥ����������ͼƬ
	void preLoadPicture();

	//��ʼ��Ϸ
	void startGame(Ref* pSender);

	//�߷ּ�¼
	void highScore(Ref* pSender);

	//��Ϸ˵��
	void aboutGame(Ref* pSender);

	//�˳���Ϸ
	void menuCloseCallback(cocos2d::Ref* pSender);

	//�������涯��
	Animate* startMainAnimate();

	//ж�ز���Ҫ����Դ
	virtual void onExit();

	//��Ӧ����(��Ҫ���Android)
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void onSpriteLoading(float dt);

private:
	EventListenerKeyboard* m_listener;
	int m_spriteNum;
};

#endif // __HELLOWORLD_SCENE_H__