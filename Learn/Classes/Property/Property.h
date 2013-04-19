/*
 * Property.h
 *
 *  Created on: May 29, 2013
 *      Author: leafsoar
 */

#ifndef PROPERTY_H_
#define PROPERTY_H_

#include "testBasic.h"
#include "cocos2d.h"

class PropertyTestScene: public TestScene {
public:
	virtual void runThisTest();
};

// 为了方便起见，自定义宏，并且为 varName 的实现加上了 __ls_ 的前缀，前缀可以修改，可以很长很长很长
// 加 __ls_ 前缀是为了，在使用的过程只通过 set 和 get 属性包装器调用，而不要直接使用此属性
#define LS_PRE(p) __ls_##p
//#define LS_PRE(p) __retain_##p			// 其它前缀都行，目的是为了不让在直接使用此类型对象

#define LS_PROPERTY_RETAIN(varType, varName, funName)\
private: varType LS_PRE(varName);\
public: void set##funName(varType value){\
	CC_SAFE_RELEASE_NULL(LS_PRE(varName));\
	LS_PRE(varName) = value;\
	CC_SAFE_RETAIN(LS_PRE(varName));\
}; \
public: varType get##funName(){return LS_PRE(varName);};

// 初始化和释放包装宏，主要为了封装前缀，始定义统一
#define LS_P_INIT(p) LS_PRE(p)(0)
#define LS_P_RELEASE(p) CC_SAFE_RELEASE_NULL(LS_PRE(p))

/**
 * 自定义类型数据：用户信息
 */
class LUser: public cocos2d::CCObject{
public:
	CREATE_FUNC(LUser);
	virtual bool init(){
		return true;
	};
	LUser():
		LS_P_INIT(m_pUser)
	{
		CCLog("LUser()");
	};
	~LUser(){
		CCLog("LUser().~():%s", m_sUserName.c_str());
		LS_P_RELEASE(m_pUser);
	};

	std::string m_sUserName;		// 用户名
	std::string m_sPassword;		// 用户密码

	// 其它数据
	LS_PROPERTY_RETAIN(LUser*, m_pUser, User);

};

class PropertyTest: public CCLayer{
public:
	CREATE_FUNC(PropertyTest);

	virtual bool init(){
		CCLog("PropertyTest().init()");
		LUser* lu = LUser::create();
		lu->m_sUserName = "leafsoar";
		lu->m_sPassword = "123456";
		setLUser(lu);

		// 为了方便在不同帧测试，启用定时器
		this->scheduleUpdate();

		return true;
	};

	virtual void update(float fDelta){
	        // 为了方便观察，不让 update 内部无止境的打印下去
	        if (updateCount < 5){
	            updateCount ++;
	            CCLog("update index: %d", updateCount);
	            // 在不同的帧做相关操作，以便观察
	            if (updateCount == 1){
	            	// 这里使用 getLUser 获取数据，而非 [__ls_]m_pLUser，所以我设置了前缀
	            	if (getLUser())
	            		CCLog("log lu: %s", getLUser()->m_sUserName.c_str());

	            } else if (updateCount == 2){
	            	// 重新赋值
	            	LUser* lu = LUser::create();
	            	lu->m_sUserName = "一叶";
	            	LUser* luc = LUser::create();
	            	luc->m_sUserName = "无间";
	            	lu->setUser(luc);
	            	setLUser(lu);
	            } else if (updateCount == 3){
	            	if (getLUser())
	            		CCLog("log lu: %s", getLUser()->m_sUserName.c_str());
	            } else if (updateCount == 4){
	            	// 这里调用 seLUser(0),直接取消引用持有对象，如果不调用也没有关系
	            	// 因为在当前类析构的时候会自动检测释放
//	            	setLUser(0);
	            }
	            CCLog("update index: %d end", updateCount);
	        }
	    };

	// 构造函数，初始化 LS_PROPERTY_RETAIN 属性为空
	PropertyTest():
		LS_P_INIT(m_pLUser),
		updateCount(0)
	{
	};

	// 析构函数释放
	~PropertyTest(){
		LS_P_RELEASE(m_pLUser);
	};

	// 使用 LS_PROPERTY_RETAIN 宏定义的属性，必须在构造和析构函数中初始化和释放
	// 初始化为 0 或者 NULL，是为了在进行赋值操作前判断时候以有引用
	// 析构函数释放是为了解除对持有对象的引用，如果有的话
	LS_PROPERTY_RETAIN(LUser*, m_pLUser, LUser);

private:
	int updateCount;
};


#endif /* PROPERTY_H_ */
