/*
 This code is written by Hafiz K.Irshaid
 Date 12/3/2013
 Computer engineering department at Najah National University
 Artificial Intelligence
 Frog Jumping Game
 Description :
 
 TODO:
 
 */

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "FrogSprite.h"
#include "gameModel.h"

class HelloWorld : public cocos2d::CCLayer
{
public:
    
    //this list contains all frog items pointers
    CCMenuItemSprite *RF1MenuItem;
    CCMenuItemSprite *RF2MenuItem;
    CCMenuItemSprite *RF3MenuItem;
    CCMenuItemSprite *GF3MenuItem;
    CCMenuItemSprite *GF2MenuItem;
    CCMenuItemSprite *GF1MenuItem;
    
    //this function is going to simulate the solution of the puzzle
    void simulate__(CCObject * sender);
    
    //group of points reperesents the center of all frogs
    CCPoint Locations[7];
    
    //game model pointer
    frog_jumping_game_model *game_model;
    
    //click on a frog action listener
    void move_frog_click(CCObject * Sender);
    
    CCMenuItemSprite * get_frog_by_tag(int tag);
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
    //restart game button action listener
    void restartGameCallback(CCObject * sender);
    
    //solve game action listener
    void solveGameCallback(CCObject * Sender);
    
    //this function si going to move the given frog pntr to the given address
    void move_frog_to_address(CCObject * frog, int index);
    
    // implement the "static node()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
