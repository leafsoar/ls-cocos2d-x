/*
 * CustomeControlTest.cpp
 *
 *  Created on: Jun 13, 2013
 *      Author: leafsoar
 */

#include "CustomeControlTest.h"

void TouchScaleTestScene::runThisTest() {
	CCLayer* pLayer = TouchScaleTest::create();
	addChild(pLayer);

	CCDirector::sharedDirector()->replaceScene(this);
}
