//
//  FrogSprite.h
//  FrogJumppingGame
//
//  Created by Hafiz on 3/29/14.
//
//

#ifndef __FrogJumppingGame__FrogSprite__
#define __FrogJumppingGame__FrogSprite__

#include <iostream>

#include "cocos2d.h"
using namespace cocos2d;


class FrogSprite : public cocos2d::CCSprite, public CCTargetedTouchDelegate
{
public:
    CC_SYNTHESIZE(CCPoint, _nextPosition, NextPosition);
    CC_SYNTHESIZE(CCPoint, _vector, Vector);
    CC_SYNTHESIZE(CCTouch *, _touch, Touch);
   
    FrogSprite();
    ~FrogSprite();
   
   // static FrogSprite* gameSpriteWithFile(const char *
      //                                    pszFileName);
    //virtual void setPosition(const CCPoint& pos);
    //float radius();
    virtual void onEnter();
    virtual void onExit();
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    
};


#endif /* defined(__FrogJumppingGame__FrogSprite__) */
