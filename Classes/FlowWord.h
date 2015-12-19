/*
************************************************************************
*
*	FlowWord.h
*	���Ƿ� 2015��8��13��
*   ����: ��Ϸ�е�Ʈ��Ч��
*
************************************************************************
*/
#ifndef __FlowWord_H__
#define __FlowWord_H__

#include "cocos2d.h"

USING_NS_CC;

class FlowWord :public Node
{
public:
	~FlowWord();

	//�����ͳ�ʼ�� Ʈ��
	static FlowWord* getInstance();

	//��ʾƮ��

	void showFlowWordTollgate(const char* text, Point pos);
	void showFlowWordProp(const char* text, Point pos);
	void showFlowWordTalk(const char* text, Point pos);

protected:
private:
	static FlowWord* m_flowWord;
};

#endif