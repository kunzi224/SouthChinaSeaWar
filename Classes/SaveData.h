/*
************************************************************************
*
*	SaveData.h
*	杜星飞 2015年8月13日
*   描述: 保存玩家信息
*
************************************************************************
*/
#ifndef __SaveData_H__
#define __SaveData_H__

#include "cocos2d.h"

USING_NS_CC;

class SaveData : public Ref
{
public:
	SaveData();
	~SaveData();
public:
	bool init();
	CREATE_FUNC(SaveData);
private:
	//用户数据操作的成员变量
	UserDefault * m_userDefault;
	
	//要用到这种特殊的容器了。。
	ValueVector m_vector;
	//记录玩家的当前分数
	CC_SYNTHESIZE(int, m_score, Score);
public:
	void save();
};

#endif