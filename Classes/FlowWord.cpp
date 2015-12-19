/*
************************************************************************
*
*	FlowWord.cpp
*	杜星飞 2015年8月13日
*   描述: 游戏中的飘字效果
*
************************************************************************
*/

#include "FlowWord.h"

USING_NS_CC;

FlowWord* FlowWord::m_flowWord = nullptr;

FlowWord::~FlowWord()
{
	if (m_flowWord!=nullptr)
	{
		delete m_flowWord;
		m_flowWord = nullptr;
	}
}

//创建和初始化 飘字
FlowWord* FlowWord::getInstance()
{
	
	if (nullptr==m_flowWord)
	{
		m_flowWord = new FlowWord();
	}

	return m_flowWord;
}

void FlowWord::showFlowWordTollgate(const char* text, Point pos)
{
	log("showFlowWordTollgate");

	auto m_textLabel = Label::createWithTTF("", "fonts/DFPShaoNvW5-GB.ttf", 25);
	m_textLabel->setColor(ccc3(CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255));
//	m_textLabel->setAnchorPoint(ccp(1, 0));
	m_textLabel->setPosition(pos);
	m_textLabel->setString(text);
	m_textLabel->enableShadow();

	this->addChild(m_textLabel);


	//放大缩小
	ActionInterval* m_scaleLarge = ScaleTo::create(1.0f, 2.5, 2.5);
	ActionInterval* m_scaleSmall = ScaleTo::create(1.0f, 0.5, 0.5);

	//倾斜
	ActionInterval* m_skew = SkewTo::create(1.0f, 180, 0);
	ActionInterval* m_skewBack = SkewTo::create(1.0f, 0, 0);

	//组合动作
	ActionInterval* m_action = Spawn::create(m_scaleLarge, m_skew, NULL);
	ActionInterval* m_actionBack = Spawn::create(m_scaleSmall, m_skewBack, NULL);

	auto callFunc = CallFunc::create([m_textLabel]()
	{
		m_textLabel->removeFromParentAndCleanup(true);
	}
	);

	ActionInterval* flow = Sequence::create(m_action, m_actionBack, callFunc, NULL);

	m_textLabel->runAction(flow);
}

void FlowWord::showFlowWordProp(const char* text, Point pos)
{
	log("showFlowWordProp");

	auto m_textLabel = Label::createWithTTF("", "fonts/DFPShaoNvW5-GB.ttf", 25);
	m_textLabel->setColor(ccc3(CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255));
//	m_textLabel->setAnchorPoint(ccp(1, 0));
	m_textLabel->setPosition(pos);
	m_textLabel->setString(text);
	m_textLabel->enableShadow();

	this->addChild(m_textLabel);


	//放大缩小
	ActionInterval* m_scaleLarge = ScaleTo::create(1.0f, 2.5, 2.5);
	ActionInterval* m_scaleSmall = ScaleTo::create(1.0f, 0.5, 0.5);

	auto callFunc = CallFunc::create([m_textLabel]()
	{
		m_textLabel->removeFromParentAndCleanup(true);

	}
	);

	ActionInterval* flow = Sequence::create(m_scaleLarge, m_scaleSmall, callFunc, NULL);

	m_textLabel->runAction(flow);

}

void FlowWord::showFlowWordTalk(const char* text, Point pos)
{

	auto m_textLabel = Label::createWithTTF("", "fonts/DFPShaoNvW5-GB.ttf", 25);
	m_textLabel->setColor(ccc3(CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255, CCRANDOM_0_1() * 255));
	m_textLabel->setPosition(pos);
	m_textLabel->setString(text);
	m_textLabel->enableShadow();

	this->addChild(m_textLabel);

	//移位
	ActionInterval* m_move1 = MoveBy::create(0.5f, ccp(30, 30));
	ActionInterval* m_move2 = MoveBy::create(0.5f, ccp(-30, -30));
	ActionInterval* m_move3 = MoveBy::create(0.5f, ccp(30, -30));
	ActionInterval* m_move4 = MoveBy::create(0.5f, ccp(-30, 30));

	//放大缩小
	ActionInterval* m_scale1 = ScaleTo::create(0.5f, 4, 0.5);
	ActionInterval* m_scale2 = ScaleTo::create(0.5f, 3, 0.5);
	ActionInterval* m_scale3 = ScaleTo::create(0.5f, 2, 0.5);
	ActionInterval* m_scale4 = ScaleTo::create(0.5f, 1, 0.5);

	ActionInterval* m_action1 = Spawn::create(m_move1, m_scale1, NULL);
	ActionInterval* m_action2 = Spawn::create(m_move2, m_scale2, NULL);
	ActionInterval* m_action3 = Spawn::create(m_move3, m_scale3, NULL);
	ActionInterval* m_action4 = Spawn::create(m_move4, m_scale4, NULL);


	auto callFunc = CallFunc::create([m_textLabel]()
	{
		m_textLabel->removeFromParentAndCleanup(true);
	}
	);

	ActionInterval* flow = Sequence::create(m_action1, m_action2, m_action3, m_action4, callFunc, NULL);

	m_textLabel->runAction(flow);
}



#if 0
//游戏开始飘字
ActionInterval* FlowWord::beginFlowWord()
{
	//放大缩小
	ActionInterval* m_scaleLarge = ScaleTo::create(2.0f, 2.5, 2.5);
	ActionInterval* m_scaleSmall = ScaleTo::create(2.0f, 0.5, 0.5);

	//倾斜
	ActionInterval* m_skew = SkewTo::create(2.0f, 180, 0);
	ActionInterval* m_skewBack = SkewTo::create(2.0f, 0, 0);

	//组合动作
	ActionInterval* m_action = Spawn::create(m_scaleLarge, m_skew, NULL);
	ActionInterval* m_actionBack = Spawn::create(m_scaleSmall, m_skewBack, NULL);

	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(FlowWord::showEnd));

	ActionInterval* flow = Sequence::create(m_action, m_actionBack, callFunc, NULL);

	return flow;
}

//获得道具飘字
ActionInterval* FlowWord::propFlowWord()
{
	//放大缩小
	ActionInterval* m_scaleLarge = ScaleTo::create(2.0f, 2.5, 2.5);
	ActionInterval* m_scaleSmall = ScaleTo::create(2.0f, 0.5, 0.5);

	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(FlowWord::showEnd));

	ActionInterval* flow = Sequence::create(m_scaleLarge, m_scaleSmall, callFunc, NULL);

	return flow;
}



//其它飘字
ActionInterval* FlowWord::otherFlowWord()
{
	//移位
	ActionInterval* m_move1 = MoveBy::create(2.0f, ccp(30, 30));
	ActionInterval* m_move2 = MoveBy::create(2.0f, ccp(-30, -30));
	ActionInterval* m_move3 = MoveBy::create(2.0f, ccp(30, -30));
	ActionInterval* m_move4 = MoveBy::create(2.0f, ccp(-30, 30));

	//放大缩小
	ActionInterval* m_scale1 = ScaleTo::create(2.0f, CCRANDOM_0_1() * 4, CCRANDOM_0_1() * 4);
	ActionInterval* m_scale2 = ScaleTo::create(2.0f, CCRANDOM_0_1() * 4, CCRANDOM_0_1() * 4);
	ActionInterval* m_scale3 = ScaleTo::create(2.0f, CCRANDOM_0_1() * 4, CCRANDOM_0_1() * 4);
	ActionInterval* m_scale4 = ScaleTo::create(2.0f, CCRANDOM_0_1() * 4, CCRANDOM_0_1() * 4);

	ActionInterval* m_action1 = Spawn::create(m_move1, m_scale1, NULL);
	ActionInterval* m_action2 = Spawn::create(m_move2, m_scale2, NULL);
	ActionInterval* m_action3 = Spawn::create(m_move3, m_scale3, NULL);
	ActionInterval* m_action4 = Spawn::create(m_move4, m_scale4, NULL);


	CallFunc* callFunc = CallFunc::create(this, callfunc_selector(FlowWord::showEnd));

	ActionInterval* flow = Sequence::create(m_action1, m_action2, m_action3, m_action4, callFunc, NULL);

	return flow;
}
#endif