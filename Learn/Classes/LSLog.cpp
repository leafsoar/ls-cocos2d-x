/*
 * LSLog.cpp
 *
 *  Created on: May 15, 2013
 *      Author: leafsoar
 */

#include "LSLog.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "platform/android/jni/JniHelper.h"
#include "platform/android/jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#include <jni.h>

#endif

USING_NS_CC;

#define kMaxStringLen (1024*100)
#define LOG_V 1
#define LOG_D 2
#define LOG_I 4
#define LOG_W 8
#define LOG_E 16

/// 需要打印的日志级别
//const int LSLog::LOG_VALUE = LOG_V | LOG_D | LOG_I | LOG_W | LOG_E;
//const int LSLog::LOG_VALUE = LOG_D | LOG_I | LOG_W | LOG_E;
const int LSLog::LOG_VALUE = LOG_I | LOG_W | LOG_E;
//const int LSLog::LOG_VALUE = LOG_W | LOG_E;
//const int LSLog::LOG_VALUE = LOG_E;
//const int LSLog::LOG_VALUE = 0;

//const int LSLog::LOG_VALUE = LOG_D;

void LSLog::verbose(const char * pszFormat, ...) {
	if (LOG_V & LOG_VALUE) {
		va_list ap;
		va_start(ap, pszFormat);
		LSLog::printLog(LSLOG_VERBOSE, pszFormat, ap);
		va_end(ap);
	}
}

void LSLog::debug(const char* pszFormat, ...) {
	if (LOG_D & LOG_VALUE) {
		va_list ap;
		va_start(ap, pszFormat);
		LSLog::printLog(LSLOG_DEBUG, pszFormat, ap);
		va_end(ap);
	}
}

void LSLog::info(const char* pszFormat, ...) {
	if (LOG_I & LOG_VALUE) {
		va_list ap;
		va_start(ap, pszFormat);
		LSLog::printLog(LSLOG_INFO, pszFormat, ap);
		va_end(ap);
	}
}

void LSLog::warn(const char* pszFormat, ...) {
	if (LOG_W & LOG_VALUE) {
		va_list ap;
		va_start(ap, pszFormat);
		LSLog::printLog(LSLOG_WARN, pszFormat, ap);
		va_end(ap);
	}
}

void LSLog::error(const char* pszFormat, ...) {
	if (LOG_E & LOG_VALUE) {
		va_list ap;
		va_start(ap, pszFormat);
		LSLog::printLog(LSLOG_ERROR, pszFormat, ap);
		va_end(ap);
	}
}

void LSLog::printLog(int type, const char* format, va_list ap) {
	char* pBuf = (char*) malloc(kMaxStringLen);
	std::string mstr;
	if (pBuf != NULL) {
		vsnprintf(pBuf, kMaxStringLen, format, ap);
		mstr = pBuf;
		free(pBuf);
	}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	printAndroidLog(lsLog_androidMethod[type].c_str(), mstr.c_str());
#else
	CCLog("%s :%s", lsLog_name[type].c_str(), mstr.c_str());
#endif
}

void LSLog::printAndroidLog(const char* methodName, const char* log) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo t;
	bool isHave = JniHelper::getStaticMethodInfo(t,
			"android/util/Log",
			methodName,
			"(Ljava/lang/String;Ljava/lang/String;)I");
	if (isHave)
	{
		jstring jTitle = t.env->NewStringUTF("cocos2d-x");
		jstring jMsg = t.env->NewStringUTF(
				log);
		t.env->CallStaticVoidMethod(t.classID, t.methodID, jTitle,
				jMsg);
		t.env->DeleteLocalRef(jTitle);
		t.env->DeleteLocalRef(jMsg);
	}
	else
	{
		CCLog("the jni method is not exits");
	}
#endif
}

