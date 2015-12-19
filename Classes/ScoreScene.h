/*
************************************************************************
*
*	ScoreScene.h
*	杜星飞 2015年8月13日
*   描述: 显示游戏玩家高分列表
*
************************************************************************
*/
#ifndef __ScoreScene_H__
#define __ScoreScene_H__

#include "cocos2d.h"

#include "cocos-ext.h" 

USING_NS_CC;
USING_NS_CC_EXT;

class ScoreScene : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
	ScoreScene();
	~ScoreScene();
public:
	static Scene * createScene();
	bool init();
	CREATE_FUNC(ScoreScene);
public:
	void tableCellTouched(TableView *table, TableViewCell * cell){}; 
	TableViewCell * tableCellAtIndex(TableView * table, ssize_t index);
	Size tableCellSizeForIndex(TableView * table, ssize_t index);
	
	ssize_t numberOfCellsInTableView(TableView * table);
	
	void scrollViewDidScroll(ScrollView *){};
	void scrollViewDidZoom(ScrollView *){};

	//对返回键的响应
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);
private:
	Size size;
};

#endif