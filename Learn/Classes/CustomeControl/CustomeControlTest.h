/*
 * CustomeControlTest.h
 *
 *  Created on: Jun 13, 2013
 *      Author: leafsoar
 */

#ifndef CUSTOMECONTROLTEST_H_
#define CUSTOMECONTROLTEST_H_

#include "cocos2d.h"
#include "testBasic.h"

USING_NS_CC;

class CustomeControlTestScene: public TestScene {
public:
	virtual void runThisTest();
};

class CustomeControlTest: public CCLayer {
	CREATE_FUNC(CustomeControlTest)
	;
	virtual bool init();
};

#endif /* CUSTOMECONTROLTEST_H_ */
