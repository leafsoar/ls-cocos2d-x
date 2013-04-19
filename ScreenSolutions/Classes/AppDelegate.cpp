#include "AppDelegate.h"

#include "cocos2d.h"
#include "HelloWorldScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() {
}

bool AppDelegate::applicationDidFinishLaunching() {
	CCDirector *pDirector = CCDirector::sharedDirector();
	pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

	pDirector->setDisplayStats(true);

	pDirector->setAnimationInterval(1.0 / 60);

//	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480, 320,
//			kResolutionNoBorder);
//	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480, 320,
//				kResolutionNoBorder);

	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	CCSize lsSize = CCSizeMake(480, 320);

	float scaleX = (float) frameSize.width / lsSize.width;
	float scaleY = (float) frameSize.height / lsSize.height;

	float scale = MAX(scaleX, scaleY);

//	if (scaleX > scaleY) {
//		scale = scaleX / (frameSize.height / (float) lsSize.height);
//	} else {
//		scale = scaleY / (frameSize.width / (float) lsSize.width);
//	}

// 固定高度
//	if (scaleX > scaleY)
//		scale = scaleX / (frameSize.height / (float) lsSize.height);
//	else
//		scale = scaleX / (frameSize.width / (float) lsSize.width);

// 固定宽度
	if (scaleX > scaleY)
		scale = scaleY / (frameSize.height / (float) lsSize.height);
	else
		scale = scaleY / (frameSize.width / (float) lsSize.width);

	CCLog("x: %f; y: %f; scale: %f", scaleX, scaleY, scale);

	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(lsSize.width * scale,
			lsSize.height * scale, kResolutionNoBorder);

//	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480, 320,
//			kResolutionNoBorder);

//	CCEGLView::sharedOpenGLView()->setDesignResolutionSize(480 * 1.083,
//			320 * 1.083, kResolutionNoBorder);

//	pDirector->setContentScaleFactor(
//			CCEGLView::sharedOpenGLView()->getScaleY() );

	CCScene *pScene = HelloWorld::scene();

	pDirector->runWithScene(pScene);

//	CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint visibleOrigin = CCDirector::sharedDirector()->getVisibleOrigin();

	CCLog("FrameSize: width[%f], height[%f]", frameSize.width,
			frameSize.height);
	CCLog("WinSize: width[%f], height[%f]", winSize.width, winSize.height);
	CCLog("VisibleSize: width[%f], height[%f]", visibleSize.width,
			visibleSize.height);
	CCLog("VisibleOrigin: x[%f], y[%f]", visibleOrigin.x, visibleOrigin.y);

	CCLog("XScale: %f, YScale: %f", CCEGLView::sharedOpenGLView()->getScaleX(),
			CCEGLView::sharedOpenGLView()->getScaleY());

	return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	CCDirector::sharedDirector()->pause();

	// if you use SimpleAudioEngine, it must be pause
	// SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
	CCDirector::sharedDirector()->resume();

	// if you use SimpleAudioEngine, it must resume here
	// SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
