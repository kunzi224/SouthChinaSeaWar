/*
************************************************************************
*
*	AboutGame.h
*	杜星飞 2015年8月13日
*   描述: 游戏玩法、剧情介绍、建议意见
*
************************************************************************
*/
#ifndef __AboutGame_H__
#define __AboutGame_H__

#include "cocos2d.h"

USING_NS_CC;

class AboutGame : public Layer
{
public:
	AboutGame();
	~AboutGame();

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AboutGame);

public:
	//返回按钮
	void back(EventKeyboard::KeyCode keyCode, Event* pEvent);
};

#endif