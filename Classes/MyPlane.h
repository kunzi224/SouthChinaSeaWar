/*
************************************************************************
*
*	MyPlane.h
*	���Ƿ� 2015��8��13��
*   ����: �����ɻ������ԡ����ܵ�
*
************************************************************************
*/
#ifndef __MyPlane_H__
#define __MyPlane_H__

#include "cocos2d.h"

USING_NS_CC;

enum 
{
	AIRPLANE = 1,
};

class MyPlane : public Layer
{
public:
	MyPlane();
	~MyPlane();
	
	static MyPlane* create();

	virtual bool init();

public:
	//�ɻ�����
	Animate* planeFly();

	//�߽���
	void borderCheck(float dt);

	//�ɻ���ը
	void blowUp();

	//�Ƴ��ɻ�
	void removePlane();

	//��ȡ����ֵ
	int getAlive();

	//�趨����ֵ
	void loseAlive();

	//��������ֵ
	void addAlive();

	//��ȡ����ֵ
	int getFire();

	//���ӻ���ֵ
	void addFire();

	//�趨�Ƿ�����
	void isHide(bool hide);

	//��ȡ�Ƿ�����
	bool getHide();

public:
	static MyPlane* instancePlane;	//�ɻ�ʵ��

private:
	int m_alive;
	int m_fire;
	bool m_bHide;
};

#endif