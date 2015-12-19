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
	//预加载声音和图片
	void preLoadPicture();

	//开始游戏
	void startGame(Ref* pSender);

	//高分记录
	void highScore(Ref* pSender);

	//游戏说明
	void aboutGame(Ref* pSender);

	//退出游戏
	void menuCloseCallback(cocos2d::Ref* pSender);

	//启动界面动画
	Animate* startMainAnimate();

	//卸载不必要的资源
	virtual void onExit();

	//响应键盘(主要针对Android)
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void onSpriteLoading(float dt);

private:
	EventListenerKeyboard* m_listener;
	int m_spriteNum;
};

#endif // __HELLOWORLD_SCENE_H__