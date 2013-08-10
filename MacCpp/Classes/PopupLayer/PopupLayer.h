//
//  PopupLayer.h
//  TestCpp
//
//  Created by leafsoar on 7/29/13.
//
//

#ifndef TestCpp_PopupLayer_h
#define TestCpp_PopupLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class PopupLayer: public CCLayer{
public:
    PopupLayer();
    ~PopupLayer();
    
    virtual bool init();
    CREATE_FUNC(PopupLayer);
    
    virtual void registerWithTouchDispatcher(void);
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    static PopupLayer* create(const char* backgroundImage);
    
    void setTitle(const char* title, int fontsize = 20);
    void setContentText(const char* text, int fontsize = 20, int padding = 50, int paddintTop = 100);

    void setCallbackFunc(CCObject* target, SEL_CallFuncN callfun);
    
    bool addButton(const char* normalImage, const char* selectedImage, const char* title, int tag = 0);    
    virtual void onEnter();
    virtual void onExit();
    
private:
    
    void buttonCallback(CCObject* pSender);

    // 文字内容两边的空白区
    int m_contentPadding;
    int m_contentPaddingTop;
    
    CCObject* m_callbackListener;
    SEL_CallFuncN m_callback;

    CC_SYNTHESIZE_RETAIN(CCMenu*, m__pMenu, MenuButton);
    CC_SYNTHESIZE_RETAIN(CCSprite*, m__sfBackGround, SpriteBackGround);
    CC_SYNTHESIZE_RETAIN(CCScale9Sprite*, m__s9BackGround, Sprite9BackGround);
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m__ltTitle, LabelTitle);
    CC_SYNTHESIZE_RETAIN(CCLabelTTF*, m__ltContentText, LabelContentText);
    
    
};

#endif
