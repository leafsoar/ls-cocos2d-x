#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* HelloWorld::scene() {
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::create();

	CCLayer* b = CCLayer::create();
	scene->addChild(b);

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint center = ccp(size.width/2, size.height/2);
	CCSprite* pb = CCSprite::create("Back.jpg");
	pb->setPosition(center);
	b->addChild(pb, 0);

	HelloWorld *lsLayer = HelloWorld::create();

	scene->addChild(lsLayer);

	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init() {
	if (!CCLayer::init()) {
		return false;
	}

	CCMenuItemImage *pCloseItem = CCMenuItemImage::create("CloseNormal.png",
			"CloseSelected.png", this,
			menu_selector(HelloWorld::menuCloseCallback));
	pCloseItem->setPosition(
			ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

	// create menu, it's an autorelease object
	CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
	pMenu->setPosition(CCPointZero);
	this->addChild(pMenu, 1);

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCPoint center = ccp(size.width/2, size.height/2);

	// 大小 600x500
//	CCSprite* pb = CCSprite::create("Back.jpg");
//	pb->setPosition(center);
//	this->addChild(pb, 0);

	// 480x320
	CCSprite* pSprite = CCSprite::create("HelloWorld.png");
	pSprite->setPosition(center);
	this->addChild(pSprite, 0);

	// 37x37
	CCSprite* p1 = CCSprite::create("Peas.png");
	p1->setPosition(ccpAdd(center, ccp(-240, -160)));
	this->addChild(p1);

	CCSprite* p2 = CCSprite::create("Peas.png");
	p2->setPosition(ccpAdd(center, ccp(240, 160)));
	this->addChild(p2);

	CCSprite* p3 = CCSprite::create("Peas.png");
	p3->setPosition(ccpAdd(center, ccp(-240, 160)));
	this->addChild(p3);

	CCSprite* p4 = CCSprite::create("Peas.png");
	p4->setPosition(ccpAdd(center, ccp(240, -160)));
	this->addChild(p4);

//	CCSprite* p5 = CCSprite::create("Peas.png");
//	p5->setPosition(ccp(0, 40));
//	this->addChild(p5);

	return true;
}

//void HelloWorld::visit() {
//	glEnable(GL_SCISSOR_TEST);              // 开启显示指定区域
//	glScissor(40, 0, 960, 640);     // 只显示当前窗口的区域
//	glScissor(10, 0, 240, 160);     // 只显示当前窗口的区域
//	CCLayer::visit();                       // 调用下面的方法
//	glDisable(GL_SCISSOR_TEST);             // 禁用
//}

void HelloWorld::menuCloseCallback(CCObject* pSender) {
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
