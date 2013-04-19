#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    virtual bool init();  

    static cocos2d::CCScene* scene();
    
    void menuCloseCallback(CCObject* pSender);

    CREATE_FUNC(HelloWorld);

//    virtual void visit();

private:
    CCLayer* m_pBackground;
};

#endif // __HELLOWORLD_SCENE_H__
