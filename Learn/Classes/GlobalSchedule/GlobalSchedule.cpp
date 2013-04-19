/*
 * GlobalSchedule.cpp
 *
 *  Created on: May 9, 2013
 *      Author: leafsoar
 */

#include "GlobalSchedule.h"

#define SCHEDULE CCDirector::sharedDirector()->getScheduler()

GlobalSchedule* GlobalSchedule::m_pSchedule = NULL;

GlobalSchedule::GlobalSchedule(float fInterval, float fDelay) {
	CCLog("GlobalSchedule()");

	CCAssert(!m_pSchedule, "已定义，不能重复定义");

	SCHEDULE->scheduleSelector(
			schedule_selector(GlobalSchedule::globalUpdate), this, fInterval,
			false,
			kCCRepeatForever, fDelay);

	m_pSchedule = this;
}

GlobalSchedule::~GlobalSchedule() {
	CCLog("GlobalSchedule().~()");

	SCHEDULE->unscheduleSelector(
			schedule_selector(GlobalSchedule::globalUpdate), this);
}

void GlobalSchedule::globalUpdate() {
	// 这里写全局定时器的逻辑处理代码
	CCLog("global update");
}

void GlobalSchedule::start(float fInterval, float fDelay) {
	CCLog("GlobalSchedule().start()");
	new GlobalSchedule(fInterval, fDelay);
}

void GlobalSchedule::stop() {
	CCLog("GlobalSchedule().stop()");

	CCAssert(m_pSchedule, "未定义");
	CC_SAFE_DELETE(m_pSchedule);
}

void GlobalSchedule::pause() {
	CCLog("GlobalSchedule().pause()");

	CCAssert(m_pSchedule, "未定义");
	SCHEDULE->pauseTarget(m_pSchedule);
}

void GlobalSchedule::resume() {
	CCLog("GlobalSchedule().resume()");

	CCAssert(m_pSchedule, " 未定义");
	SCHEDULE->resumeTarget(m_pSchedule);
}
