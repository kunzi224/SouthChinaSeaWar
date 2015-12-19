/*
************************************************************************
*
*	AdHelp.h
*	Author: 杜星飞
*   describe: 插广告
*
************************************************************************
*/

#ifndef __AdHelp__H__
#define __AdHelp__H__

#include <cocos2d.h>
using namespace cocos2d;

#if(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include <jni.h>

#endif

class AdHelp
{
public:

	AdHelp();
	virtual ~AdHelp();

	// -------------------------------------------------------------
	// 无积分广告使用
	static void showSpotAd();           //通过JNI调用JAVA静态函数，实现展示插屏广告
	static bool closeSpotAd();          //通过JNI调用JAVA静态函数，实现关闭插屏广告
	static void showBanner();           //通过JNI调用JAVA静态函数，实现展示广告条
	static void hideBanner();           //通过JNI调用JAVA静态函数，实现隐藏广告条

	// -------------------------------------------------------------
	// 积分广告使用
	static void showOfferWall();        //通过JNI调用JAVA静态函数，实现展示积分墙（全屏）
	static void showOfferWallDialog();  //通过JNI调用JAVA静态函数，实现展示积分墙（对话框）
	static int queryPoints();           //通过JNI调用JAVA静态函数，实现查询当前积分
	static bool awardPoints(int points);//通过JNI调用JAVA静态函数，实现增加积分
	static bool spendPoints(int points);//通过JNI调用JAVA静态函数，实现消耗积分
};

#endif