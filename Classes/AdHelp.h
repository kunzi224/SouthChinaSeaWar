/*
************************************************************************
*
*	AdHelp.h
*	Author: ���Ƿ�
*   describe: ����
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
	// �޻��ֹ��ʹ��
	static void showSpotAd();           //ͨ��JNI����JAVA��̬������ʵ��չʾ�������
	static bool closeSpotAd();          //ͨ��JNI����JAVA��̬������ʵ�ֹرղ������
	static void showBanner();           //ͨ��JNI����JAVA��̬������ʵ��չʾ�����
	static void hideBanner();           //ͨ��JNI����JAVA��̬������ʵ�����ع����

	// -------------------------------------------------------------
	// ���ֹ��ʹ��
	static void showOfferWall();        //ͨ��JNI����JAVA��̬������ʵ��չʾ����ǽ��ȫ����
	static void showOfferWallDialog();  //ͨ��JNI����JAVA��̬������ʵ��չʾ����ǽ���Ի���
	static int queryPoints();           //ͨ��JNI����JAVA��̬������ʵ�ֲ�ѯ��ǰ����
	static bool awardPoints(int points);//ͨ��JNI����JAVA��̬������ʵ�����ӻ���
	static bool spendPoints(int points);//ͨ��JNI����JAVA��̬������ʵ�����Ļ���
};

#endif