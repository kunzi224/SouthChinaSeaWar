/*
************************************************************************
*
*	TollgateOne.h
*	杜星飞
*   描述: 关卡1
*
************************************************************************
*/
#ifndef __TollgateOne_H__
#define __TollgateOne_H__

#include "cocos2d.h"
#include "MyPlane.h"
#include "Bullet.h"
#include "EnemyManager.h"
#include "BenefitControl.h"
#include "Controller.h"
#include "PropControl.h"
#include "BackgroundMove.h"
#include "FlowWord.h"

USING_NS_CC;

class TollgateOne : public Layer
{
public:
	TollgateOne();
	~TollgateOne();

	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(TollgateOne);

public:
	void gameUpdate(float dt);     // 碰撞检测
	bool bulletCollisionEnemy(Sprite* pBullet);   // 子弹和敌机碰撞
	void enemyCollisionPlane();    // 我机和敌机、敌机子弹碰撞
	
	void benefitCollisionPlane();	//飞机与道具碰撞

	void particleFire(Vec2 vec);	//喷火粒子特效

	//游戏是否结束
	void isGameOver();

	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);
	virtual void onExit();

public:
	MyPlane *planeLayer;
	Bullet *bulletLayer;
	EnemyManager *enemyLayer;
	BenefitControl* benefitControl;
	Controller *controlLayer;
	PropControl* propControl;
//	FlowWord* m_flow;
};

#endif