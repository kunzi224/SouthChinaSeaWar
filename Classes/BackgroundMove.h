/*
************************************************************************
*
*	BackgroundMove.h
*	杜星飞 2015年8月13日
*	描述： 在进入游戏场景之后，背景开始移动
*
************************************************************************
*/
#ifndef __BackgroundMove_H__
#define __BackgroundMove_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundMove : public Layer
{
public:
	BackgroundMove();
	~BackgroundMove();
	virtual bool init();
	virtual void onEnterTransitionDidFinish();	//等进入场景之后在进行背景的移动
	CREATE_FUNC(BackgroundMove);

public:
	void move(float dt);

	void updateBackground(int score);

private:
//	Sprite* m_background1;
//	Sprite* m_background2;
	Sprite* m_background3;
	Sprite* m_background4;

	enum 
	{
		OFFSET = 3
	};
};

#endif