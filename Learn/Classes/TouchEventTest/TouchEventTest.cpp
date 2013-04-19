/*
 * TouchEventTest.cpp
 *
 *  Created on: May 24, 2013
 *      Author: leafsoar
 */

#include "TouchEventTest.h"
#include "cocos2d.h"

USING_NS_CC;

void TouchEventTestScene::runThisTest() {
	CCLayer* layer = TouchEventTest::create();
	addChild(layer);

	CCDirector::sharedDirector()->replaceScene(this);
}

bool TouchEventTest::init() {
	bool bRef = false;
	do {
		CC_BREAK_IF(!CCLayer::init());

		// 启用触摸
		setTouchEnabled(true);

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		CCPoint center = ccp(winSize.width/ 2, winSize.height / 2);

		// 创建可触摸精灵
		LsTouch* lt = LsTouch::create();
		// 设置位置
		lt->setPosition(center);
		// 设置显示精灵
		lt->setDisplay(CCSprite::create("Peas.png"));
		// 添加到显示
		this->addChild(lt);
		// 添加到触摸管理，第二个参数，事件 Id
		this->addLsTouch(lt, 100);

		LsTouch* lt2 = LsTouch::create();
		lt2->setPosition(ccpAdd(center, ccp(20, 10)));
		lt2->setDisplay(CCSprite::create("Peas.png"));
		addChild(lt2);
		this->addLsTouch(lt2, 101);

		bRef = true;
	} while (0);

	return bRef;
}

void TouchEventTest::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*) (*it);
	// 发送触摸消息，并在 touchEventAction 自动回调相应的事件
	sendTouchMessage(touch);
}

void TouchEventTest::touchEventAction(LsTouch* touch) {
	CCLog("touch event action id: %d", touch->getEventId());
}

