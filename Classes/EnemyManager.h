/*
************************************************************************
*
*	EnemyManager.h
*	���Ƿ� 2015��8��13��
*   ����: ����л��Ĳ��������ٵ�
*
************************************************************************
*/
#ifndef __EnemyManager_H__
#define __EnemyManager_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "Controller.h"
#include "BackgroundMove.h"

USING_NS_CC;

class EnemyManager : public Layer
{
public:
	EnemyManager();
	~EnemyManager();
	virtual bool init();
	CREATE_FUNC(EnemyManager);

public:
	//�󶨿�����(���·���/����)
	void bindController(Controller* controller,BackgroundMove* background);

	//���ݷ���������ӵл��ٶ�
	void addBackground(float dt);

	//���ݷ���������ӵл��ٶ�
	void addSpeed(float dt);

	// ��ӵл�1
	void addEnemy1(float dt); 

	// ��ӵл�2
	void addEnemy2(float dt); 

	// ��ӵл�3
	void addEnemy3(float dt); 

	// ��ӵл�4
	void addEnemy4(float dt);

	// ��ӵл�5
	void addEnemy5(float dt);

	// �л���ը
	void blowupEnemy(Enemy* pEnemySprite);	

	// �Ƴ��л�pNode
	void removeEnemy(Node *pNode);	

	//��ȡ�л����Ƿ��˶�
	bool isRun()
	{
		return m_bRun;
	}

	//�жϵл����Ƿ��˶�
	void setRun(bool bRun);

public:
	Vector<Enemy*> vecEnemy;// �л����������ڱ�����ײ����
	Controller* m_controlLayer;	//������
	BackgroundMove* m_background;	//���Ʊ����ƶ�
	float m_fSpeed;	//��ӵл��ٶ�
	float m_fEnemy1;
	float m_fEnemy2;
	float m_fEnemy3;
	float m_fEnemy4;
	float m_fEnemy5;

	bool m_bRun;
};

#endif