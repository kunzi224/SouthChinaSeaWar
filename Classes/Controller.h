/*
************************************************************************
*
*	Controller.h
*	杜星飞 2015年8月13日
*   描述: 控制 背景更换、游戏状态
*
************************************************************************
*/
#ifndef __Controller_H__
#define __Controller_H__

#include "cocos2d.h"
#include "SaveData.h"

USING_NS_CC;

class Controller : public Layer
{
public:
	Controller();
	~Controller();
	virtual bool init();
	CREATE_FUNC(Controller);

	//对玩家分数的操作
	CC_SYNTHESIZE_READONLY(SaveData *, m_saveData, SaveData);
	void updateScore();

public:
	Label * m_score;
	Label * score_label;
};

#endif