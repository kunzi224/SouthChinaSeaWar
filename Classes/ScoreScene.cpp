/*
************************************************************************
*
*	ScoreScene.cpp
*	杜星飞 2015年8月13日
*   描述: 显示游戏玩家高分列表
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

	//背景音乐
	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);

	}
//	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/BackgroundMusic2.mp3", true);

	size = Director::getInstance()->getWinSize();

	//添加背景图片
	auto background = Sprite::createWithTexture(TextureCache::getInstance()->getTextureForKey("backgroundStartGame.jpg"));// 
	background->setPosition(Point(size.width / 2, size.height / 2));
	background->setAnchorPoint(Vec2(0.5, 0.5));
	this->addChild(background);

	//创建tableView并设置一些参数
	auto tableView = TableView::create(this, Size(size.width, size.height*0.8));
	//设置滑动方向
	tableView->setDirection(ScrollView::Direction::VERTICAL);
	//设置TableViewDelegate
	tableView->setDelegate(this);
	//index的大小是从上到下依次增大
	tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	//用当前的配置刷新cell
	tableView->reloadData();
	this->addChild(tableView);

	//排名
	auto dictionary = Dictionary::createWithContentsOfFile("fonts/AboutMe.xml");

	auto rankNum = Label::createWithTTF(
		((__String*)(dictionary->objectForKey("rankNum")))->getCString(),
		"fonts/DFPShaoNvW5-GB.ttf",
		40);
	rankNum->setColor(Color3B(255, 0, 0));
	rankNum->enableShadow();
	rankNum->setPosition(Point(size.width*0.4, size.height*0.9));
	this->addChild(rankNum);

	//得分
	auto rankScore = Label::createWithTTF(
		((__String*)(dictionary->objectForKey("rankScore")))->getCString(),
		"fonts/DFPShaoNvW5-GB.ttf",
		40);
	rankScore->setPosition(Point(size.width*0.8, size.height*0.9));
	rankScore->enableShadow();
	rankScore->setColor(Color3B(255, 0, 0));
	this->addChild(rankScore);

	//对返回键的响应
	auto listener = EventListenerKeyboard::create();
	listener->onKeyReleased = CC_CALLBACK_2(ScoreScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

//对返回键的响应
void ScoreScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
	{
		//背景音乐
//		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
//		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/game_start.mp3", true);

		//场景弹出
		Director::getInstance()->popScene();
	}
		
}

//用来设置每个cell的内容的
TableViewCell * ScoreScene::tableCellAtIndex(TableView * table, ssize_t index)
{
	//设置每条记录前边的文本内容
	auto index_text = __String::createWithFormat("%ld", index + 1);

	TableViewCell * cell = table->dequeueCell();
	if (cell == NULL)
	{
		//创建一个cell
		cell = new TableViewCell();
		cell->autorelease();

		//创建显示排名的文本信息
		auto text = Label::createWithTTF(index_text->getCString(), "fonts/DFPShaoNvW5-GB.ttf", 24);
		text->setTag(1024);
		text->setColor(Color3B(255, 0, 0));
		text->enableShadow();
		//文本信息在cell的中间
		text->setPosition(Point(size.width*0.4, size.height*0.025));
		cell->addChild(text);

		//显示用户得分的文本信息
		auto index_score = __String::createWithFormat("%d", index);
		//根据index值获得得分的文本，因为这个时候的score是int型，所以还需要转化一下类型
		int i_score = UserDefault::getInstance()->getIntegerForKey(index_score->getCString());
		auto * str = __String::createWithFormat("%d", i_score);
		auto score = Label::createWithTTF(
			str->getCString(), "fonts/DFPShaoNvW5-GB.ttf", 24);
		score->setTag(2048);
		//设置坐标
		score->setPosition(Point(size.width*0.8, size.height*0.025));
		score->setColor(Color3B(255, 0, 0));
		score->enableShadow();
		cell->addChild(score);

	}
	//这里获得的cell是原来的cell，所以原来cell的文本信息等还是原来的，所以要做一些改变
	else
	{
		//通过tag值获得文本，并且改变
		auto text = (Label *)cell->getChildByTag(1024);
		text->setString(index_text->getCString());

		//改变分数
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

//这个函数是用来设置每个cell的大小的
Size ScoreScene::tableCellSizeForIndex(TableView * table, ssize_t index)
{
	return Size(size.width, size.height*0.05);
}

//这个函数是用来设置cell的个数的
ssize_t ScoreScene::numberOfCellsInTableView(TableView * table)
{
	//个数是从XML文件中读取到的，有多少条记录，就设置多少个cell，如果刚开始没有count这个字段，就返回0
	int count = UserDefault::getInstance()->getIntegerForKey("count", 0);

	return count;
}
