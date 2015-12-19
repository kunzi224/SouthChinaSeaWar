/*
************************************************************************
*
*	AdHelp.cpp
*	Author: ���Ƿ�
*   describe: ����
*
************************************************************************
*/

#include "AdHelp.h"

AdHelp::AdHelp(){}
AdHelp::~AdHelp(){}

// -------------------------------------------------------------------------------------------------------------------------------------
// �޻��ֹ�����

/**
 * չʾ������棨C++ ͨ��JNI ����JAVA������
 */
void AdHelp::showSpotAd()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
    
    // ����JNI������Ϣ�ṹ��
    JniMethodInfo showSpotAd;
    
    /**
     * @param ��һ��������JNI������Ϣ�ṹ��
     * @param �ڶ�������������Android��Ŀ�е���Activity���ڵİ�����Ӧ��Demo��Ϊ��com.youmi.android.cocos2dx.demo.MainActivity����Ҫ��Ϊcom/youmi/android/cocos2dx/denmo/MainActivity
     * @param ������������Android��Ŀ�ж�Ӧ��Activity�����������JAVA��̬��������Demo��Ϊ��showSpotAd
     * @param ���ĸ���������JAVA��������Ҫ�����ֵ����ʽΪ"(JAVA��������Ҫ�����ֵ)c++�б���������ֵ"��Demo�У�showSpotAd��JAVA��������Ҫ����ֵ����YoumiAd::showSpotAd()����ֵΪvoid����������д "()V" 
     * @return ����boolֵ��ʾ�Ƿ��ҵ���̬����
     */
    bool isHave = JniHelper::getStaticMethodInfo(showSpotAd, "org/cocos2dx/cpp/AppActivity", "showSpotAd", "()V"); 
    if (!isHave) {
        CCLog("jni:showSpotAd�˺���������");
    }else{
        CCLog("jni:showSpotAd��������");
        showSpotAd.env->CallStaticVoidMethod(showSpotAd.classID, showSpotAd.methodID);
    }
	#endif
}

/**
 * �رղ�����棨C++ ͨ��JNI ����JAVA������
 */
bool AdHelp::closeSpotAd()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
    JniMethodInfo closeSpotAd;
    bool isHave = JniHelper::getStaticMethodInfo(closeSpotAd, "org/cocos2dx/cpp/AppActivity", "closeSpotAd", "()Z"); 
    if (!isHave) {
        CCLog("jni:closeSpotAd�˺���������");
        return false;
    }else{
        CCLog("jni:closeSpotAd��������");
        return closeSpotAd.env->CallStaticBooleanMethod(closeSpotAd.classID, closeSpotAd.methodID);
    }
	#endif

	return true;
}


/**
 * չʾ�������C++ ͨ��JNI ����JAVA������
 */
void AdHelp::showBanner()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨

    // ����JNI������Ϣ�ṹ��
    JniMethodInfo showBanner;
    
    /**
     * @param ��һ��������JNI������Ϣ�ṹ��
     * @param �ڶ�������������Android��Ŀ�е���Activity���ڵİ�����Ӧ��Demo��Ϊ��com.youmi.android.cocos2dx.demo.MainActivity����Ҫ��Ϊcom/youmi/android/cocos2dx/denmo/MainActivity
     * @param ������������Android��Ŀ�ж�Ӧ��Activity�����������JAVA��̬��������Demo��Ϊ��showBanner
     * @param ���ĸ���������JAVA��������Ҫ�����ֵ����ʽΪ"(JAVA��������Ҫ�����ֵ)c++�б���������ֵ"��Demo�У�showBanner��JAVA��������Ҫ����ֵ����YoumiAd::showBanner()����ֵΪvoid����������д "()V" 
     * @return ����boolֵ��ʾ�Ƿ��ҵ���̬����
     */
    bool isHave = JniHelper::getStaticMethodInfo(showBanner, "org/cocos2dx/cpp/AppActivity", "showBanner", "()V"); 
    if (!isHave) {
        CCLog("jni:showBanner�˺���������");
    }else{
        CCLog("jni:showBanner��������");
        showBanner.env->CallStaticVoidMethod(showBanner.classID, showBanner.methodID);
    }
	#endif
}
 
/**
 * ���ع������C++ ͨ��JNI ����JAVA������
 */
void AdHelp::hideBanner()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
    JniMethodInfo hideBanner;
    bool isHave = JniHelper::getStaticMethodInfo(hideBanner, "org/cocos2dx/cpp/AppActivity", "hideBanner", "()V"); 
    if (!isHave) {
        CCLog("jni:hideBanner�˺���������");
    }else{
        CCLog("jni:hideBanner��������");
        hideBanner.env->CallStaticVoidMethod(hideBanner.classID, hideBanner.methodID);
    }
	#endif
}

// -------------------------------------------------------------------------------------------------------------------------------------
// ���ֹ�����
/**
 * չʾ����ǽ��C++ ͨ��JNI ����JAVA������
 */
void AdHelp::showOfferWall()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
    
    // ����JNI������Ϣ�ṹ��
    JniMethodInfo showOfferWall;
    
    /**
     * @param ��һ��������JNI������Ϣ�ṹ��
     * @param �ڶ�������������Android��Ŀ�е���Activity���ڵİ�����Ӧ��Demo��Ϊ��com.youmi.android.cocos2dx.demo.MainActivity����Ҫ��Ϊcom/youmi/android/cocos2dx/denmo/MainActivity
     * @param ������������Android��Ŀ�ж�Ӧ��Activity�����������JAVA��̬��������Demo��Ϊ��showOfferWall
     * @param ���ĸ���������JAVA��������Ҫ�����ֵ����ʽΪ"(JAVA��������Ҫ�����ֵ)c++�б���������ֵ"��Demo�У�showOfferWall��JAVA��������Ҫ����ֵ����YoumiAd::showOfferWall()����ֵΪvoid����������д "()V" 
     * @return ����boolֵ��ʾ�Ƿ��ҵ���̬����
     */
    bool isHave = JniHelper::getStaticMethodInfo(showOfferWall, "org/cocos2dx/cpp/AppActivity", "showOfferWall", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showOfferWall�˺���������");
    }else{
        CCLog("jni:showOfferWall��������");
        showOfferWall.env->CallStaticVoidMethod(showOfferWall.classID, showOfferWall.methodID);
    }
	#endif
}

/**
 * չʾ����ǽ�Ի���C++ ͨ��JNI ����JAVA������
 */
void AdHelp::showOfferWallDialog()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
    JniMethodInfo showOfferWallDialog;
    bool isHave = JniHelper::getStaticMethodInfo(showOfferWallDialog, "org/cocos2dx/cpp/AppActivity", "showOfferWallDialog", "()V"); 
 
    if (!isHave) {
        CCLog("jni:showOfferWallDialog�˺���������");
    }else{
        CCLog("jni:showOfferWalDialogl��������");
        showOfferWallDialog.env->CallStaticVoidMethod(showOfferWallDialog.classID, showOfferWallDialog.methodID);
    }
	#endif
}

/**
 * ��ѯ��ǰ���֣�C++ ͨ��JNI ����JAVA������
 */
int AdHelp::queryPoints()
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
    JniMethodInfo queryPoints;
    bool isHave = JniHelper::getStaticMethodInfo(queryPoints, "org/cocos2dx/cpp/AppActivity", "queryPoints", "()I"); 
    if (!isHave) {
        CCLog("jni:queryPoints�˺���������");
        return -1;
    }else{
        CCLog("jni:queryPoints��������");
		return queryPoints.env->CallStaticIntMethod(queryPoints.classID, queryPoints.methodID);
    }
	#endif

	return true;
}

/**
 * �������� ��C++ ͨ��JNI ����JAVA������
 */
bool AdHelp::awardPoints(int points)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
    JniMethodInfo awardPoints;
    bool isHave = JniHelper::getStaticMethodInfo(awardPoints, "org/cocos2dx/cpp/AppActivity", "awardPoints", "(I)Z"); 
 
    if (!isHave) {
        CCLog("jni:awardPoints�˺���������");
        return false;
    }else{
        CCLog("jni:awardPoints�˺�������");
        return awardPoints.env->CallStaticBooleanMethod(awardPoints.classID, awardPoints.methodID, points);
    }
	#endif

	return true;
}

/**
 * ���Ļ��� ��C++ ͨ��JNI ����JAVA������
 */
bool AdHelp::spendPoints(int points)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) //�жϵ�ǰ�Ƿ�ΪAndroidƽ̨
    JniMethodInfo spendPoints;
    bool isHave = JniHelper::getStaticMethodInfo(spendPoints, "org/cocos2dx/cpp/AppActivity", "spendPoints", "(I)Z"); 
 
    if (!isHave) {
        CCLog("jni:spendPoints�˺���������");
        return false;
    }else{
        CCLog("jni:spendPoints�˺�������");
        return spendPoints.env->CallStaticBooleanMethod(spendPoints.classID, spendPoints.methodID, points);
    }
	#endif

	return true;
}
