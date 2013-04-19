#include "AppDelegate.h"

#include "cocos2d.h"
#include "controller.h"
#include "GlobalSchedule/GlobalSchedule.h"
#include "LSLog.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{

}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 ctive. Whenif you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
//    CCScene *pScene = HelloWorld::scene();

    // run
//    pDirector->runWithScene(pScene);

    CCScene * pScene = CCScene::create();
    CCLayer * pLayer = new TestController();
    pLayer->autorelease();

    pScene->addChild(pLayer);
    pDirector->runWithScene(pScene);

//    GlobalSchedule::start(0.2f);
//    GlobalSchedule::pause();
//    GlobalSchedule::resume();

//    LSLog::verbose("博客名称： %s","无间落叶");
//    LSLog::debug("博客地址： %s", "http://blog.leafsoar.com");
//    LSLog::info("基本信息： %s", "吾名 一叶");
//    LSLog::warn("多出警告： %s %s", "警告一", "警告二");
//    LSLog::error("坐标错误： (%f, %f)", 800.0f, 600.0f);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
