/*
 * LsTouch.cpp
 *
 *  Created on: May 24, 2013
 *      Author: leafsoar
 */

#include "LsTouch.h"

LsTouch::LsTouch() {
	CCLog("LsTouch()");
	m_iEventId = 0;
}

LsTouch::~LsTouch() {
	CCLog("LsTouch().~()");
}

bool LsTouch::init() {

	return true;
}

void LsTouch::setDisplay(CCSprite* dis) {
	// 设置之前先清除，没有也无所谓
	removeChildByTag(TAG_DISPLAY, true);
	addChild(dis, 0, TAG_DISPLAY);
}

void LsTouch::setEventId(int eventId) {
	m_iEventId = eventId;
}

int LsTouch::getEventId() {
	return m_iEventId;
}

bool LsTouch::selfCheck(CCTouch* ccTouch, LsTouchEvent* lsTe) {
	bool bRef = false;
	// 可点击项的检测，可扩展
	do {
		// 是否通过点击位置检测
		CC_BREAK_IF(!containsCCTouchPoint(ccTouch));
		// 是否正在运行，排除可能存在已经从界面移除，但是并没有释放的可能
		CC_BREAK_IF(!isRunning());

		// 判断是否隐藏
		CC_BREAK_IF(!isVisible());
		// 这里可能还需要判断内部显示项目是否隐藏
		///// 暂留
		// 不仅判断当前元素是否隐藏，还需要判断在它之上的元素直到事件处理层，是否存在隐藏
		CC_BREAK_IF(!isParentAllVisible(lsTe));

		bRef = true;
	} while (0);
	return bRef;
}

bool LsTouch::containsCCTouchPoint(CCTouch* ccTouch) {
	// 获得显示内容
	CCNode* dis = getChildByTag(TAG_DISPLAY);
	CCSprite* sprite = dynamic_cast<CCSprite*>(dis);
	CCPoint point = sprite->convertTouchToNodeSpaceAR(ccTouch);
	CCSize s = sprite->getTexture()->getContentSize();
	CCRect rect = CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);
	return rect.containsPoint(point);
}

bool LsTouch::isParentAllVisible(LsTouchEvent* lsTe) {
	bool bRef = true;
	// 向父类转型，以便获取地址比较对象，LsTouchEvent 的对象必须同时直接或者简介继承 CCNode
	CCNode* nLsTe = dynamic_cast<CCNode*>(lsTe);

	CCNode* parent = getParent();
	do {
		// 如果遍历完毕，说明 LsTouch 不再 LsTouchEvent 之内
		if (!parent) {
			bRef = false;
			break;
		}
		// 如果 LsTouch 在 LsTouchEvent 之内，返回 true
		// 注意：如果想让LsTouchEvent 处理 不在其 CCNode 结构之内的元素，则取消此处判断
		if (nLsTe == parent) {
			break;
		}
		if (!parent->isVisible()) {
			bRef = false;
			break;
		}
		parent = parent->getParent();
	} while (1);
	return bRef;
}

LsTouchEvent::LsTouchEvent() {
	CCLog("LsTouchEvent()");
	m_pLsTouches = CCArray::create();
	m_pLsTouches->retain();
}

LsTouchEvent::~LsTouchEvent() {
	CCLog("LsTouchEvent().~()");
	m_pLsTouches->release();
}

void LsTouchEvent::addLsTouch(LsTouch* touch, int eventId) {
	touch->setEventId(eventId);
	m_pLsTouches->addObject(touch);
}

void LsTouchEvent::removeLsTouch(LsTouch* touch) {
	m_pLsTouches->removeObject(touch, true);
}

bool LsTouchEvent::sendTouchMessage(CCTouch* ccTouch) {
	// 编写判断，集合中的哪个元素级别高，就触发哪一个
	LsTouch* lsTouch = NULL;

	// 获得点击的点
	CCObject* pObj = NULL;
	LsTouch* lt = NULL;
	CCARRAY_FOREACH(m_pLsTouches, pObj) {
		lt = dynamic_cast<LsTouch*>(pObj);
		if (lt) {
			if (lt->selfCheck(ccTouch, this)) {
				if (lsTouch == NULL)
					lsTouch = lt;
				else
					// 如果已存在符合条件元素，比较优先级
					lsTouch = getPriorityTouch(lsTouch, lt);
			}
		}
	}
// 比对最终只有一个元素触发
	if (lsTouch){
		touchEventAction(lsTouch);
		return true;
	}
	return false;
}

LsTouch* LsTouchEvent::getPriorityTouch(LsTouch* a, LsTouch* b) {
	// 触摸优先级通过 CCNode 树判断，也既是显示层次级别等因素
	// 以当前元素为“根”向父类转型，以便获取地址比较对象，LsTouchEvent 的对象必须同时直接或者简介继承 CCNode
	CCNode* nLsTe = dynamic_cast<CCNode*>(this);

	// 共同的分枝
	CCNode* allParent = NULL;
	// 寻找 a 与 b 共同的分枝
	CCNode* nAParent = a;
	CCNode* nBParent = b;
	CCNode* nAChild = NULL;
	CCNode* nBChild = NULL;
	do {
		nAChild = nAParent;
		nAParent = nAParent->getParent();
		if (!nAParent)
			break;

		nBParent = b;
		do {
			nBChild = nBParent;
			nBParent = nBParent->getParent();
			if (!nBParent)
				break;
			if (nAParent == nBParent) {
				allParent = nAParent;
				break;
			}
			if (nBParent == nLsTe) {
				break;
			}
		} while (1);
		if (allParent)
			break;
		if (nAParent == nLsTe) {
			break;
		}
	} while (1);

	// 此处只需要判断 nAChild 和 nBChild 的优先级即可，默认返回 a
	if (!nAChild || !nBChild)
		return a;
	// 根据 ZOrder 判断，如果 ZOrder一样，根据索引位置判断
	if (nAChild->getZOrder() == nBChild->getZOrder())
		return allParent->getChildren()->indexOfObject(nAChild) > allParent->getChildren()->indexOfObject(nBChild)? a: b;
	else
		return nAChild->getZOrder() > nBChild->getZOrder()? a: b;
}
