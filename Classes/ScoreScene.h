/*
************************************************************************
*
*	ScoreScene.h
*	���Ƿ� 2015��8��13��
*   ����: ��ʾ��Ϸ��Ҹ߷��б�
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

	//�Է��ؼ�����Ӧ
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent);
private:
	Size size;
};

#endif