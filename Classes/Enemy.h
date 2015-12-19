/*
************************************************************************
*
*	Enemy.h
*	杜星飞 2015年8月13日
*   描述: 设定敌方飞机的属性、动作等
*
************************************************************************
*/

#ifndef __Enemy_H__
#define __Enemy_H__

#include "cocos2d.h"

USING_NS_CC;

// 敌机生命值
const int ENEMY1_MAXLIFE = 2;
const int ENEMY2_MAXLIFE = 5;
const int ENEMY3_MAXLIFE = 10;
const int ENEMY4_MAXLIFE = 20;
const int ENEMY5_MAXLIFE = 80;

// 敌机分数
const int ENEMY1_SCORE = 3;
const int ENEMY2_SCORE = 9;
const int ENEMY3_SCORE = 15;
const int ENEMY4_SCORE = 25;
const int ENEMY5_SCORE = 40;

// 敌机类型
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