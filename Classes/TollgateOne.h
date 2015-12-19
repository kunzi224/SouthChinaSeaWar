/*
************************************************************************
*
*	TollgateOne.h
*	���Ƿ�
*   ����: �ؿ�1
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
	void gameUpdate(float dt);     // ��ײ���
	bool bulletCollisionEnemy(Sprite* pBullet);   // �ӵ��͵л���ײ
	void enemyCollisionPlane();    // �һ��͵л����л��ӵ���ײ
	
	void benefitCollisionPlane();	//�ɻ��������ײ

	void particleFire(Vec2 vec);	//���������Ч

	//��Ϸ�Ƿ����
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