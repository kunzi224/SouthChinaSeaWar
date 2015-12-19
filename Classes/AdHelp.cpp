/*
************************************************************************
*
*	AdHelp.cpp
*	Author: 杜星飞
*   describe: 插广告
*
************************************************************************
*/

#include "AdHelp.h"

AdHelp::AdHelp(){}
AdHelp::~AdHelp(){}

// -------------------------------------------------------------------------------------------------------------------------------------
// 无积分广告调用

/**
 * 展示插屏广告（C++ 通过JNI 调用JAVA方法）
 */
void AdHelp::showSpotAd()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    
    // 定义JNI函数信息结构体
    JniMethodInfo showSpotAd;
    
    /**
     * @param 第一个参数：JNI函数信息结构体
     * @param 第二个参数：与你Android项目中的主Activity所在的包名对应，Demo中为：com.youmi.android.cocos2dx.demo.MainActivity，需要改为com/youmi/android/cocos2dx/denmo/MainActivity
     * @param 第三个参数：Android项目中对应的Activity里面所定义的JAVA静态函数名，Demo中为：showSpotAd
     * @param 第四个参数：该JAVA方法所需要传入的值，格式为"(JAVA方法中需要传入的值)c++中本函数返回值"，Demo中，showSpotAd的JAVA方法不需要传入值，而YoumiAd::showSpotAd()返回值为void，所以这里写 "()V" 
     * @return 返回bool值表示是否找到静态函数
     */
    bool isHave = JniHelper::getStaticMethodInfo(showSpotAd, "org/cocos2dx/cpp/AppActivity", "showSpotAd", "()V"); 
    if (!isHave) {
        CCLog("jni:showSpotAd此函数不存在");
    }else{
        CCLog("jni:showSpotAd函数存在");
        showSpotAd.env->CallStaticVoidMethod(showSpotAd.classID, showSpotAd.methodID);
    }
	#endif
}

/**
 * 关闭插屏广告（C++ 通过JNI 调用JAVA方法）
 */
bool AdHelp::closeSpotAd()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo closeSpotAd;
    bool isHave = JniHelper::getStaticMethodInfo(closeSpotAd, "org/cocos2dx/cpp/AppActivity", "closeSpotAd", "()Z"); 
    if (!isHave) {
        CCLog("jni:closeSpotAd此函数不存在");
        return false;
    }else{
        CCLog("jni:closeSpotAd函数存在");
        return closeSpotAd.env->CallStaticBooleanMethod(closeSpotAd.classID, closeSpotAd.methodID);
    }
	#endif

	return true;
}


/**
 * 展示广告条（C++ 通过JNI 调用JAVA方法）
 */
void AdHelp::showBanner()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台

    // 定义JNI函数信息结构体
    JniMethodInfo showBanner;
    
    /**
     * @param 第一个参数：JNI函数信息结构体
     * @param 第二个参数：与你Android项目中的主Activity所在的包名对应，Demo中为：com.youmi.android.cocos2dx.demo.MainActivity，需要改为com/youmi/android/cocos2dx/denmo/MainActivity
     * @param 第三个参数：Android项目中对应的Activity里面所定义的JAVA静态函数名，Demo中为：showBanner
     * @param 第四个参数：该JAVA方法所需要传入的值，格式为"(JAVA方法中需要传入的值)c++中本函数返回值"，Demo中，showBanner的JAVA方法不需要传入值，而YoumiAd::showBanner()返回值为void，所以这里写 "()V" 
     * @return 返回bool值表示是否找到静态函数
     */
    bool isHave = JniHelper::getStaticMethodInfo(showBanner, "org/cocos2dx/cpp/AppActivity", "showBanner", "()V"); 
    if (!isHave) {
        CCLog("jni:showBanner此函数不存在");
    }else{
        CCLog("jni:showBanner函数存在");
        showBanner.env->CallStaticVoidMethod(showBanner.classID, showBanner.methodID);
    }
	#endif
}
 
/**
 * 隐藏广告条（C++ 通过JNI 调用JAVA方法）
 */
void AdHelp::hideBanner()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo hideBanner;
    bool isHave = JniHelper::getStaticMethodInfo(hideBanner, "org/cocos2dx/cpp/AppActivity", "hideBanner", "()V"); 
    if (!isHave) {
        CCLog("jni:hideBanner此函数不存在");
    }else{
        CCLog("jni:hideBanner函数存在");
        hideBanner.env->CallStaticVoidMethod(hideBanner.classID, hideBanner.methodID);
    }
	#endif
}

// -------------------------------------------------------------------------------------------------------------------------------------
// 积分广告调用
/**
 * 展示积分墙（C++ 通过JNI 调用JAVA方法）
 */
void AdHelp::showOfferWall()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    
    // 定义JNI函数信息结构体
    JniMethodInfo showOfferWall;
    
    /**
     * @param 第一个参数：JNI函数信息结构体
     * @param 第二个参数：与你Android项目中的主Activity所在的包名对应，Demo中为：com.youmi.android.cocos2dx.demo.MainActivity，需要改为com/youmi/android/cocos2dx/denmo/MainActivity
     * @param 第三个参数：Android项目中对应的Activity里面所定义的JAVA静态函数名，Demo中为：showOfferWall
     * @param 第四个参数：该JAVA方法所需要传入的值，格式为"(JAVA方法中需要传入的值)c++中本函数返回值"，Demo中，showOfferWall的JAVA方法不需要传入值，而YoumiAd::showOfferWall()返回值为void，所以这里写 "()V" 
     * @return 返回bool值表示是否找到静态函数
     */
    bool isHave = JniHelper::getStaticMethodInfo(showOfferWall, "org/cocos2dx/cpp/AppActivity", "showOfferWall", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showOfferWall此函数不存在");
    }else{
        CCLog("jni:showOfferWall函数存在");
        showOfferWall.env->CallStaticVoidMethod(showOfferWall.classID, showOfferWall.methodID);
    }
	#endif
}

/**
 * 展示积分墙对话框（C++ 通过JNI 调用JAVA方法）
 */
void AdHelp::showOfferWallDialog()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo showOfferWallDialog;
    bool isHave = JniHelper::getStaticMethodInfo(showOfferWallDialog, "org/cocos2dx/cpp/AppActivity", "showOfferWallDialog", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showOfferWallDialog此函数不存在");
    }else{
        CCLog("jni:showOfferWalDialogl函数存在");
        showOfferWallDialog.env->CallStaticVoidMethod(showOfferWallDialog.classID, showOfferWallDialog.methodID);
    }
	#endif
}

/**
 * 查询当前积分（C++ 通过JNI 调用JAVA方法）
 */
int AdHelp::queryPoints()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo queryPoints;
    bool isHave = JniHelper::getStaticMethodInfo(queryPoints, "org/cocos2dx/cpp/AppActivity", "queryPoints", "()I"); 
    if (!isHave) {
        CCLog("jni:queryPoints此函数不存在");
        return -1;
    }else{
        CCLog("jni:queryPoints函数存在");
		return queryPoints.env->CallStaticIntMethod(queryPoints.classID, queryPoints.methodID);
    }
	#endif

	return true;
}

/**
 * 奖励积分 （C++ 通过JNI 调用JAVA方法）
 */
bool AdHelp::awardPoints(int points)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo awardPoints;
    bool isHave = JniHelper::getStaticMethodInfo(awardPoints, "org/cocos2dx/cpp/AppActivity", "awardPoints", "(I)Z"); 
 
    if (!isHave) {
        CCLog("jni:awardPoints此函数不存在");
        return false;
    }else{
        CCLog("jni:awardPoints此函数存在");
        return awardPoints.env->CallStaticBooleanMethod(awardPoints.classID, awardPoints.methodID, points);
    }
	#endif

	return true;
}

/**
 * 消耗积分 （C++ 通过JNI 调用JAVA方法）
 */
bool AdHelp::spendPoints(int points)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //判断当前是否为Android平台
    JniMethodInfo spendPoints;
    bool isHave = JniHelper::getStaticMethodInfo(spendPoints, "org/cocos2dx/cpp/AppActivity", "spendPoints", "(I)Z"); 
 
    if (!isHave) {
        CCLog("jni:spendPoints此函数不存在");
        return false;
    }else{
        CCLog("jni:spendPoints此函数存在");
        return spendPoints.env->CallStaticBooleanMethod(spendPoints.classID, spendPoints.methodID, points);
    }
	#endif

	return true;
}
