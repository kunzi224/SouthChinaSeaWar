/*
************************************************************************
*
*	MyPlane.h
*	杜星飞 2015年8月13日
*   描述: 包含飞机的属性、功能等
*
************************************************************************
*/
#ifndef __MyPlane_H__
#define __MyPlane_H__

#include "cocos2d.h"

USING_NS_CC;

enum 
{
	AIRPLANE = 1,
};

class MyPlane : public Layer
{
public:
	MyPlane();
	~MyPlane();
	
	static MyPlane* create();

	virtual bool init();

public:
	//飞机动画
	Animate* planeFly();

	//边界检测
	void borderCheck(float dt);

	//飞机爆炸
	void blowUp();

	//移除飞机
	void removePlane();

	//获取生命值
	int getAlive();

	//设定生命值
	void loseAlive();

	//增加生命值
	void addAlive();

	//获取火力值
	int getFire();

	//增加火力值
	void addFire();

	//设定是否隐身
	void isHide(bool hide);

	//获取是否隐身
	bool getHide();

public:
	static MyPlane* instancePlane;	//飞机实例

private:
	int m_alive;
	int m_fire;
	bool m_bHide;
};

#endif