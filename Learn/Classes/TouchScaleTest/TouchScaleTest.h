/*
 * TouchScaleTest.h
 *
 *  Created on: Apr 27, 2013
 *      Author: leafsoar
 */

#ifndef TOUCHSCALETEST_H_
#define TOUCHSCALETEST_H_

#include "testBasic.h"
#include "cocos2d.h"

class TouchScaleTestScene: public TestScene {
public:
	virtual void runThisTest();
};

/**
 * 实现屏幕背景的拖动与缩放
 */
class TouchScaleTest: public CCLayer {
public:
	CREATE_FUNC(TouchScaleTest)
	;
	virtual bool init();

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);
	virtual void ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent);
//	virtual void ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent);

private:
	cocos2d::CCSize mSize;						// 屏幕大小
	cocos2d::CCNode* m_pBackGround;		// 屏幕背景

	int distance;
	int flag;
	int scale;
};

#endif /* TOUCHSCALETEST_H_ */
