/*
************************************************************************
*
*	Loading.h
*	杜星飞 2015年8月13日
*   描述: 加载资源
*
************************************************************************
*/

#ifndef __Loading_H__
#define __Loading_H__

#include "cocos2d.h"

class Loading : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Loading);

private:
	void onSpriteLoading(float dt);

private:
	int m_spriteLoad;
};

#endif // __HELLOWORLD_SCENE_H__
