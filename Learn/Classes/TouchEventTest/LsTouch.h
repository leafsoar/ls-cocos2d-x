/*
 * LsTouch.h
 *
 *  Created on: May 24, 2013
 *      Author: leafsoar
 */

#ifndef LSTOUCH_H_
#define LSTOUCH_H_

#include "cocos2d.h"

USING_NS_CC;

class LsTouchEvent;

/**
 * 定义可触摸元素，用于统一管理
 */
class LsTouch: public CCNode {
public:
	LsTouch();
	~LsTouch();
	CREATE_FUNC(LsTouch);
	virtual bool init()	;

	// 设置显示项
	void setDisplay(CCSprite* dis);

	void setEventId(int eventId);
	int getEventId();

	/// 常规判断
	bool selfCheck(CCTouch* ccTouch, LsTouchEvent* lsTe);

private:
	// 判断当前的元素是否被点击
	bool containsCCTouchPoint(CCTouch* ccTouch);
	bool isParentAllVisible(LsTouchEvent* lsTe);

	// 用户保存显示精灵的 tag
	static const int TAG_DISPLAY = 100;
	int m_iEventId;

};

class LsTouchEvent {
public:
	LsTouchEvent();
	~LsTouchEvent();

	void addLsTouch(LsTouch* touch, int eventId);

	void removeLsTouch(LsTouch* touch);

	bool sendTouchMessage(CCTouch* ccTouch);

	// 返回优先级较高的可触摸对象
	LsTouch* getPriorityTouch(LsTouch* a, LsTouch* b);

	virtual void touchEventAction(LsTouch* touch) = 0;
private:
	CCArray* m_pLsTouches;
};

#endif /* LSTOUCH_H_ */
