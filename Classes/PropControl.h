/*
************************************************************************
*
*	PropControl.h
*	杜星飞 2015年8月13日
*   描述: 
*
************************************************************************
*/
#ifndef __PropControl_H__
#define __PropControl_H__

#include "cocos2d.h"

USING_NS_CC;

class PropControl : public Layer
{
public:
	PropControl();
	~PropControl();
	virtual bool init();
	CREATE_FUNC(PropControl);


	// 更新生命值
	void updateAlive(int alive);

	// 更新火力值
	void updateFire(int fire);


	//游戏暂停与恢复
	void menuPauseCallback(cocos2d::Ref* pSender);

	//声音控制
	void menuMusicCallback(cocos2d::Ref* pSender);
public:
	MenuItemSprite* pPauseItem;
	MenuItemSprite* pMusicItem;

	Label* aliveItem1;
	Label* aliveItem2;
	Label* fireItem1;
	Label* fireItem2;

	bool m_bBackground;
};

#endif