/*
************************************************************************
*
*	PropControl.h
*	���Ƿ� 2015��8��13��
*   ����: 
*
************************************************************************
*/
#ifndef __PropControl_H__
#define __PropControl_H__

#include "cocos2d.h"

USING_NS_CC;

class PropControl : public Layer
{
public:
	PropControl();
	~PropControl();
	virtual bool init();
	CREATE_FUNC(PropControl);


	// ��������ֵ
	void updateAlive(int alive);

	// ���»���ֵ
	void updateFire(int fire);


	//��Ϸ��ͣ��ָ�
	void menuPauseCallback(cocos2d::Ref* pSender);

	//��������
	void menuMusicCallback(cocos2d::Ref* pSender);
public:
	MenuItemSprite* pPauseItem;
	MenuItemSprite* pMusicItem;

	Label* aliveItem1;
	Label* aliveItem2;
	Label* fireItem1;
	Label* fireItem2;

	bool m_bBackground;
};

#endif