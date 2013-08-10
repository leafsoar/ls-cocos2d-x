//
//  PopupLayer.cpp
//  TestCpp
//
//  Created by leafsoar on 7/29/13.
//
//

#include "PopupLayer.h"

PopupLayer::PopupLayer():
m__pMenu(NULL)
, m_contentPadding(0)
, m_contentPaddingTop(0)
, m_callbackListener(NULL)
, m_callback(NULL)
, m__sfBackGround(NULL)
, m__s9BackGround(NULL)
, m__ltContentText(NULL)
, m__ltTitle(NULL)
{
    
}

PopupLayer::~PopupLayer(){
    CC_SAFE_RELEASE(m__pMenu);
    CC_SAFE_RELEASE(m__sfBackGround);
    CC_SAFE_RELEASE(m__ltContentText);
    CC_SAFE_RELEASE(m__ltTitle);
    CC_SAFE_RELEASE(m__s9BackGround);
}

bool PopupLayer::init(){
    bool bRef = false;
    do{
        CC_BREAK_IF(!CCLayer::init());
        this->setContentSize(CCSizeZero);
        
        // 初始化需要的 Menu
        CCMenu* menu = CCMenu::create();
        menu->setPosition(CCPointZero);
        setMenuButton(menu);
        
        setTouchEnabled(true);
        
        bRef = true;
    }while(0);
    return bRef;
}

void PopupLayer::registerWithTouchDispatcher(){
    // 这里的触摸优先级设置为 -128 这保证了，屏蔽下方的触摸
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -128, true);

}

bool PopupLayer::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent){
    //
    CCLog("PopupLayer touch");
    return true;
}

PopupLayer* PopupLayer::create(const char *backgroundImage){
    PopupLayer* ml = PopupLayer::create();
    ml->setSpriteBackGround(CCSprite::create(backgroundImage));
    ml->setSprite9BackGround(CCScale9Sprite::create(backgroundImage));
    return ml;
}

void PopupLayer::setTitle(const char *title, int fontsize){
    CCLabelTTF* ltfTitle = CCLabelTTF::create(title, "", fontsize);
    setLabelTitle(ltfTitle);
}

void PopupLayer::setContentText(const char *text, int fontsize, int padding, int paddingTop){
    CCLabelTTF* ltf = CCLabelTTF::create(text, "", fontsize);
    setLabelContentText(ltf);
    m_contentPadding = padding;
    m_contentPaddingTop = paddingTop;
}

void PopupLayer::setCallbackFunc(cocos2d::CCObject *target, SEL_CallFuncN callfun){
    m_callbackListener = target;
    m_callback = callfun;    
}


bool PopupLayer::addButton(const char *normalImage, const char *selectedImage, const char *title, int tag){
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pCenter = ccp(winSize.width / 2, winSize.height / 2);
    
    // 创建图片菜单按钮
    CCMenuItemImage* menuImage = CCMenuItemImage::create(normalImage, selectedImage, this, menu_selector(PopupLayer::buttonCallback));
    menuImage->setTag(tag);
    menuImage->setPosition(pCenter);
    
    // 添加文字说明并设置位置
    CCSize imenu = menuImage->getContentSize();
    CCLabelTTF* ttf = CCLabelTTF::create(title, "", 20);
    ttf->setColor(ccc3(0, 0, 0));
    ttf->setPosition(ccp(imenu.width / 2, imenu.height / 2));
    menuImage->addChild(ttf);
    
    getMenuButton()->addChild(menuImage);
    return true;
}

void PopupLayer::buttonCallback(cocos2d::CCObject *pSender){
    CCNode* node = dynamic_cast<CCNode*>(pSender);
    CCLog("touch tag: %d", node->getTag());
    if (m_callback && m_callbackListener){
        (m_callbackListener->*m_callback)(node);
    }
    this->removeFromParent();
}

void PopupLayer::onEnter(){
    CCLayer::onEnter();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCPoint pCenter = ccp(winSize.width / 2, winSize.height / 2);
    
    CCSize contentSize;
    // 设定好参数，在运行时加载
    if (getContentSize().equals(CCSizeZero)) {
        getSpriteBackGround()->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(getSpriteBackGround(), 0, 0);
        contentSize = getSpriteBackGround()->getTexture()->getContentSize();
    } else {
        CCScale9Sprite *background = getSprite9BackGround();
        background->setContentSize(getContentSize());
        background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        this->addChild(background, 0, 0);
        contentSize = getContentSize();
    }
    
    
    // 添加按钮，并设置其位置
    this->addChild(getMenuButton());
    float btnWidth = contentSize.width / (getMenuButton()->getChildrenCount() + 1);
    
    CCArray* array = getMenuButton()->getChildren();
    CCObject* pObj = NULL;
    int i = 0;
    CCARRAY_FOREACH(array, pObj){
        CCNode* node = dynamic_cast<CCNode*>(pObj);
        node->setPosition(ccp( winSize.width / 2 - contentSize.width / 2 + btnWidth * (i + 1), winSize.height / 2 - contentSize.height / 3));
        i++;
    }
    
    
    // 显示对话框标题
    if (getLabelTitle()){
        getLabelTitle()->setPosition(ccpAdd(pCenter, ccp(0, contentSize.height / 2 - 35.0f)));
        this->addChild(getLabelTitle());
    }
    
    // 显示文本内容
    if (getLabelContentText()){
        CCLabelTTF* ltf = getLabelContentText();
        ltf->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        ltf->setDimensions(CCSizeMake(contentSize.width - m_contentPadding * 2, contentSize.height - m_contentPaddingTop));
        ltf->setHorizontalAlignment(kCCTextAlignmentLeft);
        this->addChild(ltf);
    }

    // 弹出效果
    CCAction* popupLayer = CCSequence::create(CCScaleTo::create(0.0, 0.0),
                                              CCScaleTo::create(0.06, 1.05),
                                              CCScaleTo::create(0.08, 0.95),
                                              CCScaleTo::create(0.08, 1.0), NULL);
    this->runAction(popupLayer);

}

void PopupLayer::onExit(){
    
    CCLog("popup on exit.");
    CCLayer::onExit();
}
