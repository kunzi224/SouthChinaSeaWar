/*
************************************************************************
*
*	AboutGame.h
*	���Ƿ� 2015��8��13��
*   ����: ��Ϸ�淨��������ܡ��������
*
************************************************************************
*/
#ifndef __AboutGame_H__
#define __AboutGame_H__

#include "cocos2d.h"

USING_NS_CC;

class AboutGame : public Layer
{
public:
	AboutGame();
	~AboutGame();

	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(AboutGame);

public:
	//���ذ�ť
	void back(EventKeyboard::KeyCode keyCode, Event* pEvent);
};

#endif