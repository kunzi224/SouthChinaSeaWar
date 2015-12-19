/*
************************************************************************
*
*	Bullet.h
*	杜星飞 2015年8月13日
*   描述: 产生玩家飞机子弹、敌机子弹
*
************************************************************************
*/
#ifndef __Bullet_H__
#define __Bullet_H__

#include "cocos2d.h"

#include "MyPlane.h"
#include "EnemyManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC; // 命名空间

class Bullet : public Layer
{
public:
	Bullet();
	~Bullet();
	virtual bool init();
	CREATE_FUNC(Bullet);

public:
	void bindEnemyManager(EnemyManager* enemyManager);
	void BeginBulletShoot(float dt = 0.0f);	// 开启子弹射击
	void StopBulletShoot();					// 停止子弹射击
	void addBullet(float dt);				// 添加子弹
	void removeBullet(Node* pNode);			// 移除子弹
	void addEnemyBullet(float dt);				// 添加敌机子弹
	void removeEnemyBullet(Node* pNode);			// 移除敌机子弹

	void addCall1();				// 添加子弹
	void addCall2();				// 添加子弹
	void addCall3();				// 添加子弹
	void addCall4();				// 添加子弹

private:
	void updateBullet1(Point bulletPos, float realFlyDuration);				// 添加子弹1
	void updateBullet2(Point bulletPos, float realFlyDuration);				// 添加子弹2
	void updateBullet3(Point bulletPos, float realFlyDuration);				// 添加子弹3
	void updateBullet4(Point bulletPos, float realFlyDuration);				// 添加子弹4

public:
	Vector<Sprite*> vecBullet; 
	Vector<Sprite*> vecEnemyBullet;
	EnemyManager* m_enemyManager;
};

#endif