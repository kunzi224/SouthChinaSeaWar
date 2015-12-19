/*
************************************************************************
*
*	BackgroundMove.h
*	���Ƿ� 2015��8��13��
*	������ �ڽ�����Ϸ����֮�󣬱�����ʼ�ƶ�
*
************************************************************************
*/
#ifndef __BackgroundMove_H__
#define __BackgroundMove_H__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundMove : public Layer
{
public:
	BackgroundMove();
	~BackgroundMove();
	virtual bool init();
	virtual void onEnterTransitionDidFinish();	//�Ƚ��볡��֮���ڽ��б������ƶ�
	CREATE_FUNC(BackgroundMove);

public:
	void move(float dt);

	void updateBackground(int score);

private:
//	Sprite* m_background1;
//	Sprite* m_background2;
	Sprite* m_background3;
	Sprite* m_background4;

	enum 
	{
		OFFSET = 3
	};
};

#endif