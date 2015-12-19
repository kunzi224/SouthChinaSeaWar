/*
************************************************************************
*
*	FlowWord.h
*	杜星飞 2015年8月13日
*   描述: 游戏中的飘字效果
*
************************************************************************
*/
#ifndef __FlowWord_H__
#define __FlowWord_H__

#include "cocos2d.h"

USING_NS_CC;

class FlowWord :public Node
{
public:
	~FlowWord();

	//创建和初始化 飘字
	static FlowWord* getInstance();

	//显示飘字

	void showFlowWordTollgate(const char* text, Point pos);
	void showFlowWordProp(const char* text, Point pos);
	void showFlowWordTalk(const char* text, Point pos);

protected:
private:
	static FlowWord* m_flowWord;
};

#endif