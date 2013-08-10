//
//  PopupScene.cpp
//  TestCpp
//
//  Created by leafsoar on 7/29/13.
//
//

#include "PopupScene.h"
#include "PopupLayer.h"

CCScene* Popup::scene(){
    CCScene* scene = CCScene::create();
    CCLayer* layer = Popup::create();
    scene->addChild(layer);
    return scene;
}

bool Popup::init(){
    bool bRef = false;
    
    do {
        CC_BREAK_IF(!CCLayer::init());
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        CCPoint pointCenter = ccp(winSize.width / 2, winSize.height / 2);

        // 添加背景图片
        CCSprite* background = CCSprite::create("HelloWorld.png");
        background->setPosition(pointCenter);
        background->setScale(1.5f);
        this->addChild(background);    
        
//        popupLayer();
        
        
        // 添加菜单
        CCMenu* menu = CCMenu::create();
        
        CCMenuItemFont* menuItem = CCMenuItemFont::create("popup", this, menu_selector(Popup::menuCallback));
        menuItem->setPosition(ccp(200, 50));
        menuItem->setColor(ccc3(0, 0, 0));
        menu->addChild(menuItem);
        

        menu->setPosition(CCPointZero);
        this->addChild(menu);
        

        CCLog("klt");
        bRef = true;
    } while (0);
    
    return bRef;
}

void Popup::popupLayer(){
    // 定义一个弹出层，传入一张背景图
    PopupLayer* pl = PopupLayer::create("popuplayer/BackGround.png");
    // ContentSize 是可选的设置，可以不设置，如果设置把它当作 9 图缩放
    pl->setContentSize(CCSizeMake(400, 350));
    pl->setTitle("吾名一叶");
    pl->setContentText("娇兰傲梅世人赏，却少幽芬暗里藏。不看百花共争艳，独爱疏樱一枝香。", 20, 60, 250);
    // 设置回调函数，回调传回一个 CCNode 以获取 tag 判断点击的按钮
    // 这只是作为一种封装实现，如果使用 delegate 那就能够更灵活的控制参数了
    pl->setCallbackFunc(this, callfuncN_selector(Popup::buttonCallback));
    // 添加按钮，设置图片，文字，tag 信息
    pl->addButton("popuplayer/pop_button.png", "popuplayer/pop_button.png", "确定", 0);
    pl->addButton("popuplayer/pop_button.png", "popuplayer/pop_button.png", "取消", 1);
    // 添加到当前层
    this->addChild(pl);
}

void Popup::menuCallback(cocos2d::CCObject *pSender){
    popupLayer();
}

void Popup::buttonCallback(cocos2d::CCNode *pNode){
    CCLog("button call back. tag: %d", pNode->getTag());
}