/*
************************************************************************
*
*	GameOver.h
*	杜星飞 2015年8月13日
*   描述: 游戏结束，显示玩家分数等信息
*
************************************************************************
*/
#ifndef __GameOver_H__
#define __GameOver_H__

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

class GameOver : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// 退出游戏
	void menuCloseCallback(cocos2d::Ref* pSender);

	// 返回主界面
	void menuMainCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);

public:
	EventListenerKeyboard* m_listener;
};

#endif