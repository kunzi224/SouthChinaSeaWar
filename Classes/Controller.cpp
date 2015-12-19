/*
************************************************************************
*
*	Controller.cpp
*	杜星飞 2015年8月13日
*   描述: 控制 背景更换、游戏状态
*
************************************************************************
*/

#include "Controller.h"

Controller::Controller() : m_score(NULL), score_label(NULL)
{

}

Controller::~Controller()
{
	m_saveData->release();
}

bool Controller::init()
{
	if (!Layer::init())
	{
		return false;
	}

	bool bRect = false;
	
	do 
	{
		Size winSize = Director::getInstance()->getWinSize();

		//从xml文件中读取中文显示出来
		auto dictionary = Dictionary::createWithContentsOfFile("fonts/AboutMe.xml");

		score_label = Label::createWithTTF(
			((__String *)(dictionary->objectForKey("score")))->getCString(),
			"fonts/DFPShaoNvW5-GB.ttf",
			25);
		score_label->setPosition(winSize.width-score_label->getContentSize().width * 2.5,
			winSize.height - score_label->getContentSize().height * 4);
		score_label->enableShadow();
		CC_BREAK_IF(!score_label);

		this->addChild(score_label);

		//添加显示分数的标签
		m_saveData = SaveData::create();
		//这里一定要retain一下saveData，在析构函数中release一下
		m_saveData->retain();
		auto str = __String::createWithFormat("%d", m_saveData->getScore());
		m_score = Label::createWithTTF(str->getCString(), "fonts/DFPShaoNvW5-GB.ttf", 25);
		m_score->setColor(Color3B(255, 0, 0));
		m_score->enableShadow();
		m_score->setPosition(Point(winSize.width- m_score->getContentSize().width *3,
			winSize.height - score_label->getContentSize().height * 4));
		CC_BREAK_IF(!m_score);

		this->addChild(m_score);

	} while (0);

	return true;
}

void Controller::updateScore()
{
	auto str = __String::createWithFormat("%d", m_saveData->getScore());
	//更新分数和坐标
	m_score->setString(str->getCString());
}