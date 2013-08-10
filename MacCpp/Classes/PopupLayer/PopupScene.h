//
//  PopupScene.h
//  TestCpp
//
//  Created by leafsoar on 7/29/13.
//
//

#ifndef TestCpp_PopupScene_h
#define TestCpp_PopupScene_h

#include "cocos2d.h"

USING_NS_CC;

class Popup: public CCLayer{
public:
    static CCScene* scene();
    virtual bool init();
    CREATE_FUNC(Popup);

    void popupLayer();
    
    void menuCallback(CCObject* pSender);
    void buttonCallback(CCNode* pSender);
};

#endif
