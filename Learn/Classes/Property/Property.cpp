/*
 * Property.cpp
 *
 *  Created on: May 29, 2013
 *      Author: leafsoar
 */

#include "Property.h"

void PropertyTestScene::runThisTest() {
	CCLayer* layer = PropertyTest::create();
	addChild(layer);
	CCDirector::sharedDirector()->replaceScene(this);
}

