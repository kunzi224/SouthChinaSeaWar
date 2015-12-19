/*
************************************************************************
*
*	EnemyManager.h
*	杜星飞 2015年8月13日
*   描述: 管理敌机的产生、销毁等
*
************************************************************************
*/
#ifndef __EnemyManager_H__
#define __EnemyManager_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "Controller.h"
#include "BackgroundMove.h"

USING_NS_CC;

class EnemyManager : public Layer
{
public:
	EnemyManager();
	~EnemyManager();
	virtual bool init();
	CREATE_FUNC(EnemyManager);

public:
	//绑定控制器(更新分数/背景)
	void bindController(Controller* controller,BackgroundMove* background);

	//根据分数决定添加敌机速度
	void addBackground(float dt);

	//根据分数决定添加敌机速度
	void addSpeed(float dt);

	// 添加敌机1
	void addEnemy1(float dt); 

	// 添加敌机2
	void addEnemy2(float dt); 

	// 添加敌机3
	void addEnemy3(float dt); 

	// 添加敌机4
	void addEnemy4(float dt);

	// 添加敌机5
	void addEnemy5(float dt);

	// 敌机爆炸
	void blowupEnemy(Enemy* pEnemySprite);	

	// 移除敌机pNode
	void removeEnemy(Node *pNode);	

	//获取敌机层是否运动
	bool isRun()
	{
		return m_bRun;
	}

	//判断敌机层是否运动
	void setRun(bool bRun);

public:
	Vector<Enemy*> vecEnemy;// 敌机容器，用于遍历碰撞问题
	Controller* m_controlLayer;	//控制器
	BackgroundMove* m_background;	//控制背景移动
	float m_fSpeed;	//添加敌机速度
	float m_fEnemy1;
	float m_fEnemy2;
	float m_fEnemy3;
	float m_fEnemy4;
	float m_fEnemy5;

	bool m_bRun;
};

#endif