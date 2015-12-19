/*
************************************************************************
*
*	ScoreScene.cpp
*	���Ƿ� 2015��8��13��
*   ����: ��ʾ��Ϸ��Ҹ߷��б�
*
************************************************************************
*/

#include "ScoreScene.h"
#include "SimpleAudioEngine.h"

ScoreScene::ScoreScene()
{

}

ScoreScene::~ScoreScene()
{
	_eventDispatcher->removeEventListenersForTarget(this);
}

Scene * ScoreScene::createScene()
{
	auto scene = Scene::create();
	auto layer = ScoreScene::create();
	scene->addChild(layer);
	return scene;
}

bool ScoreScene::init()
{
	if (!Layer::init())
		return false;

	//��������
	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	}
//	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BackgroundMusic2.mp3", true);

	size = Director::getInstance()->getWinSize();

	//��ӱ���ͼƬ
	auto background = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("backgroundStartGame.jpg"));// 
	background->setPosition(Point(size.width / 2, size.height / 2));
	background->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(background);

	//����tableView������һЩ����
	auto tableView = TableView::create(this, Size(size.width, size.height*0.8));
	//���û�������
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	//����TableViewDelegate
	tableView->setDelegate(this);
	//index�Ĵ�С�Ǵ��ϵ�����������
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	//�õ�ǰ������ˢ��cell
	tableView->reloadData();
	this->addChild(tableView);

	//����
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/AboutMe.xml");

	auto rankNum = Label::createWithTTF(
		((__String*)(dictionary->objectForKey("rankNum")))->getCString(),
		"fonts/DFPShaoNvW5-GB.ttf",
		40);
	rankNum->setColor(Color3B(255, 0, 0));
	rankNum->enableShadow();
	rankNum->setPosition(Point(size.width*0.4, size.height*0.9));
	this->addChild(rankNum);

	//�÷�
	auto rankScore = Label::createWithTTF(
		((__String*)(dictionary->objectForKey("rankScore")))->getCString(),
		"fonts/DFPShaoNvW5-GB.ttf",
		40);
	rankScore->setPosition(Point(size.width*0.8, size.height*0.9));
	rankScore->enableShadow();
	rankScore->setColor(Color3B(255, 0, 0));
	this->addChild(rankScore);

	//�Է��ؼ�����Ӧ
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(ScoreScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

//�Է��ؼ�����Ӧ
void ScoreScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		//��������
//		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
//		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_start.mp3", true);

		//��������
		Director::getInstance()->popScene();
	}
		
}

//��������ÿ��cell�����ݵ�
TableViewCell * ScoreScene::tableCellAtIndex(TableView * table, ssize_t index)
{
	//����ÿ����¼ǰ�ߵ��ı�����
	auto index_text = __String::createWithFormat("%ld", index + 1);

	TableViewCell * cell = table->dequeueCell();
	if (cell == NULL)
	{
		//����һ��cell
		cell = new TableViewCell();
		cell->autorelease();

		//������ʾ�������ı���Ϣ
		auto text = Label::createWithTTF(index_text->getCString(), "fonts/DFPShaoNvW5-GB.ttf", 24);
		text->setTag(1024);
		text->setColor(Color3B(255, 0, 0));
		text->enableShadow();
		//�ı���Ϣ��cell���м�
		text->setPosition(Point(size.width*0.4, size.height*0.025));
		cell->addChild(text);

		//��ʾ�û��÷ֵ��ı���Ϣ
		auto index_score = __String::createWithFormat("%d", index);
		//����indexֵ��õ÷ֵ��ı�����Ϊ���ʱ���score��int�ͣ����Ի���Ҫת��һ������
		int i_score = UserDefault::getInstance()->getIntegerForKey(index_score->getCString());
		auto * str = __String::createWithFormat("%d", i_score);
		auto score = Label::createWithTTF(
			str->getCString(), "fonts/DFPShaoNvW5-GB.ttf", 24);
		score->setTag(2048);
		//��������
		score->setPosition(Point(size.width*0.8, size.height*0.025));
		score->setColor(Color3B(255, 0, 0));
		score->enableShadow();
		cell->addChild(score);

	}
	//�����õ�cell��ԭ����cell������ԭ��cell���ı���Ϣ�Ȼ���ԭ���ģ�����Ҫ��һЩ�ı�
	else
	{
		//ͨ��tagֵ����ı������Ҹı�
		auto text = (Label *)cell->getChildByTag(1024);
		text->setString(index_text->getCString());

		//�ı����
		auto * score = (Label *)cell->getChildByTag(2048);
		auto * index_score = __String::createWithFormat("%d", index);
		
		int i_score = UserDefault::getInstance()->getIntegerForKey(index_score->getCString());
		auto * str = __String::createWithFormat("%d", i_score);
		score->setString(str->getCString());

		if (cell->getChildByTag(100) != NULL)
		{
			Sprite * sprite = (Sprite *)cell->getChildByTag(100);
			sprite->removeFromParentAndCleanup(true);
		}
	}

	if (index == 0 || index == 1 || index == 2)
	{
		Sprite * sprite;
		switch (index)
		{
		case 0:
			sprite = Sprite::createWithSpriteFrameName("gold.png");
			break;
		case 1:
			sprite = Sprite::createWithSpriteFrameName("silvere.png");
			break;
		case 2:
			sprite = Sprite::createWithSpriteFrameName("copper.png");
			break;
		}
		sprite->setPosition(Point(size.width*0.15, size.height*0.025));
		sprite->setTag(100);
		cell->addChild(sprite);
	}

	return cell;
}

//�����������������ÿ��cell�Ĵ�С��
Size ScoreScene::tableCellSizeForIndex(TableView * table, ssize_t index)
{
	return Size(size.width, size.height*0.05);
}

//�����������������cell�ĸ�����
ssize_t ScoreScene::numberOfCellsInTableView(TableView * table)
{
	//�����Ǵ�XML�ļ��ж�ȡ���ģ��ж�������¼�������ö��ٸ�cell������տ�ʼû��count����ֶΣ��ͷ���0
	int count = UserDefault::getInstance()->getIntegerForKey("count", 0);

	return count;
}
