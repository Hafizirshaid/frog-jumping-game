//
//  FrogSprite.cpp
//  FrogJumppingGame
//
//  Created by Hafiz on 3/29/14.
//
//

#include "FrogSprite.h"
void FrogSprite::onEnter(){
    // before 2.0:
    // CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
    printf("onEnter \n");
    // since 2.0:
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    CCSprite::onEnter();
}
void FrogSprite::onExit(){
    // before 2.0:
    // CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
    
    // since 2.0:
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCSprite::onExit();
}
bool FrogSprite::ccTouchBegan(CCTouch* touch, CCEvent* event){
    //do whatever you want here
    printf("Touch began \n");
    return true;
}
void FrogSprite::ccTouchMoved(CCTouch* touch, CCEvent* event){
    //do what you want
    printf("Tocuh move \n");
}
void FrogSprite::ccTouchEnded(CCTouch* touch, CCEvent* event){
    //do your job here
    printf("tocuh ended");
}