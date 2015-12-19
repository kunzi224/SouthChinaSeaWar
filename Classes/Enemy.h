/*
************************************************************************
*
*	Enemy.h
*	���Ƿ� 2015��8��13��
*   ����: �趨�з��ɻ������ԡ�������
*
************************************************************************
*/

#ifndef __Enemy_H__
#define __Enemy_H__

#include "cocos2d.h"

USING_NS_CC;

// �л�����ֵ
const int ENEMY1_MAXLIFE = 2;
const int ENEMY2_MAXLIFE = 5;
const int ENEMY3_MAXLIFE = 10;
const int ENEMY4_MAXLIFE = 20;
const int ENEMY5_MAXLIFE = 80;

// �л�����
const int ENEMY1_SCORE = 3;
const int ENEMY2_SCORE = 9;
const int ENEMY3_SCORE = 15;
const int ENEMY4_SCORE = 25;
const int ENEMY5_SCORE = 40;

// �л�����
enum EnemyType
{
	Enemy1 = 1,
	Enemy2,
	Enemy3,
	Enemy4,
	Enemy5,
};

class Enemy : public Node
{
public:
	Enemy();
	~Enemy();
	virtual bool init();
	CREATE_FUNC(Enemy);

public:
	void setEnemyByType(EnemyType enType);
	Sprite* getSprite();

	int getLife();
	void loseLife();
	Rect getBoundingBox();

private:
	Sprite *pEnemySprite;
	int nLife;
};


#endif