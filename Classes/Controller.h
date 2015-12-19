/*
************************************************************************
*
*	Controller.h
*	���Ƿ� 2015��8��13��
*   ����: ���� ������������Ϸ״̬
*
************************************************************************
*/
#ifndef __Controller_H__
#define __Controller_H__

#include "cocos2d.h"
#include "SaveData.h"

USING_NS_CC;

class Controller : public Layer
{
public:
	Controller();
	~Controller();
	virtual bool init();
	CREATE_FUNC(Controller);

	//����ҷ����Ĳ���
	CC_SYNTHESIZE_READONLY(SaveData *, m_saveData, SaveData);
	void updateScore();

public:
	Label * m_score;
	Label * score_label;
};

#endif