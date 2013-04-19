#ifndef _TESTS_H_
#define _TESTS_H_

//#include "ActionsTest/ActionsTest.h"
#include "TouchScaleTest/TouchScaleTest.h"
#include "TouchEventTest/TouchEventTest.h"
#include "Property/Property.h"

enum {
	TEST_TOUCH_SCALE = 0,
	TEST_TOUCH_EVENT,
	TEST_RETAIN_PROPERTY,
	TESTS_COUNT,
};

const std::string g_aTestNames[TESTS_COUNT] = {
		"Touch Scale",
		"Touch Event",
		"Retain Property"};

#endif
