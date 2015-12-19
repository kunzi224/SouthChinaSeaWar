/*
************************************************************************
*
*	Bullet.h
*	���Ƿ� 2015��8��13��
*   ����: ������ҷɻ��ӵ����л��ӵ�
*
************************************************************************
*/
#ifndef __Bullet_H__
#define __Bullet_H__

#include "cocos2d.h"

#include "MyPlane.h"
#include "EnemyManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC; // �����ռ�

class Bullet : public Layer
{
public:
	Bullet();
	~Bullet();
	virtual bool init();
	CREATE_FUNC(Bullet);

public:
	void bindEnemyManager(EnemyManager* enemyManager);
	void BeginBulletShoot(float dt = 0.0f);	// �����ӵ����
	void StopBulletShoot();					// ֹͣ�ӵ����
	void addBullet(float dt);				// ����ӵ�
	void removeBullet(Node* pNode);			// �Ƴ��ӵ�
	void addEnemyBullet(float dt);				// ��ӵл��ӵ�
	void removeEnemyBullet(Node* pNode);			// �Ƴ��л��ӵ�

	void addCall1();				// ����ӵ�
	void addCall2();				// ����ӵ�
	void addCall3();				// ����ӵ�
	void addCall4();				// ����ӵ�

private:
	void updateBullet1(Point bulletPos, float realFlyDuration);				// ����ӵ�1
	void updateBullet2(Point bulletPos, float realFlyDuration);				// ����ӵ�2
	void updateBullet3(Point bulletPos, float realFlyDuration);				// ����ӵ�3
	void updateBullet4(Point bulletPos, float realFlyDuration);				// ����ӵ�4

public:
	Vector<Sprite*> vecBullet; 
	Vector<Sprite*> vecEnemyBullet;
	EnemyManager* m_enemyManager;
};

#endif