/*
 * TouchEventTest.h
 *
 *  Created on: May 24, 2013
 *      Author: leafsoar
 */

#ifndef TOUCHEVENTTEST_H_
#define TOUCHEVENTTEST_H_

#include "testBasic.h"
#include "cocos2d.h"
#include "LsTouch.h"

class TouchEventTestScene: public TestScene {
public:
	virtual void runThisTest();
};

class TouchEventTest: public CCLayer , public LsTouchEvent{
public:
	CREATE_FUNC(TouchEventTest)
	;
	virtual bool init();

	virtual void ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent);

	virtual void touchEventAction(LsTouch* touch);
};


#endif /* TOUCHEVENTTEST_H_ */
