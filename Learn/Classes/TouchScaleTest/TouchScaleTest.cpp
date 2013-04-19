/*
 * TouchScaleTest.cpp
 *
 *  Created on: Apr 27, 2013
 *      Author: leafsoar
 */

#include "TouchScaleTest.h"
#include "cocos2d.h"

USING_NS_CC;

void TouchScaleTestScene::runThisTest() {
	CCLayer* pLayer = TouchScaleTest::create();
	addChild(pLayer);

	CCDirector::sharedDirector()->replaceScene(this);
}

bool TouchScaleTest::init() {
	bool bRef = false;
	do {
		CC_BREAK_IF(!CCLayer::init());
		mSize = CCDirector::sharedDirector()->getWinSize();

		this->m_pBackGround = CCSprite::create("move.jpg");
//		 使用 anchor 为 PointZero 能更好判断其位置
		CCSize bgSize = m_pBackGround->getContentSize();
//		m_pBackGround->setPosition(
//				ccp(mSize.width / 2- bgSize.width / 2,mSize.height / 2 -bgSize.height / 2));
		m_pBackGround->setPosition(CCPointZero);
		m_pBackGround->setAnchorPoint(CCPointZero);
		addChild(m_pBackGround);
//		m_pBackGround->setScale(0.5);

		setTouchEnabled(true);

		bRef = true;
	} while (0);
	return bRef;
}

void TouchScaleTest::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent) {
//	CCSetIterator it = pTouches->begin();
//	CCTouch* touch = (CCTouch*) (*it);

//	m_tBeginPos = touch->getLocation();

	CCLog("touch began ...");

}

void TouchScaleTest::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent) {

	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*) (*it);

	// 获取地图区域大小
	CCPoint diff = touch->getDelta();
	CCPoint currentPos = m_pBackGround->getPosition();
	CCPoint newPos = ccpAdd(currentPos, diff);

	CCRect bound = m_pBackGround->boundingBox();
	// 边界检查
	if (newPos.x > 0)
		newPos.x = 0;
	if (newPos.y > 0)
		newPos.y = 0;
	if (newPos.x < mSize.width - bound.size.width)
		newPos.x = mSize.width - bound.size.width;
	if (newPos.y < mSize.height - bound.size.height)
		newPos.y = mSize.height - bound.size.height;

	m_pBackGround->setPosition(newPos);

	CCLog("touch move ...");

}
