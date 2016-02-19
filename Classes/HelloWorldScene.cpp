/*
 This code is written by Hafiz K.Irshaid
 Date 12/3/2013
 Computer engineering department at Najah National University
 Artificial Intelligence
 Frog Jumping Game
 Description :
 
 TODO:
 
 */

#include "HelloWorldScene.h"
#include <math.h>
USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

#define NEXT_FROG 60

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    //init the Locations array of all points that the frog will be there
    Locations[0] = ccp(35, 40);
    Locations[1] = ccp(103, 40);
    Locations[2] = ccp(174, 40);
    Locations[3] = ccp(242, 40);
    Locations[4] = ccp(310, 40);
    Locations[5] = ccp(377, 40);
    Locations[6] = ccp(446, 40);


    //init game model
    game_model = new frog_jumping_game_model;

    //set the background sprite
    CCSprite * background = CCSprite::create("background.png");
    background->cocos2d::CCNode::setPosition(240,160);
    this->addChild(background);
    
    //restart game button
    CCSprite * RestartGame = CCSprite::create("restart_btn.png");
    CCMenuItemSprite *RestartGameMenuItem  = CCMenuItemSprite::create(RestartGame, NULL, this, menu_selector(HelloWorld::restartGameCallback));
    CCMenu *RestartGameMenu = CCMenu::create(RestartGameMenuItem, NULL);
    RestartGameMenu->setPosition(135, 240);
    this->addChild(RestartGameMenu);
    
    //restart game button
    CCSprite * SolveGame = CCSprite::create("solve.png");
    CCMenuItemSprite *SolveGameMenuItem  = CCMenuItemSprite::create(SolveGame, NULL, this, menu_selector(HelloWorld::solveGameCallback));
    CCMenu *SolveGameMenu = CCMenu::create(SolveGameMenuItem, NULL);
    SolveGameMenu->setPosition(150, 300);
    this->addChild(SolveGameMenu);
    
    
    //third green  frog
    CCSprite * GF3 = CCSprite::create("GF.png");
    GF3MenuItem  = CCMenuItemSprite::create(GF3, NULL, this, menu_selector(HelloWorld::move_frog_click));
    GF3MenuItem->setTag(0);
    GF3MenuItem->setPosition(Locations[0]);
    
    //second green  frog
    CCSprite * GF2 = CCSprite::create("GF.png");
    GF2MenuItem  = CCMenuItemSprite::create(GF2, NULL, this, menu_selector(HelloWorld::move_frog_click));
    GF2MenuItem->setTag(1);
    GF2MenuItem->setPosition(Locations[1]);
    
    //first green  frog
    CCSprite * GF1 = CCSprite::create("GF.png");
    GF1MenuItem  = CCMenuItemSprite::create(GF1, NULL, this, menu_selector(HelloWorld::move_frog_click));
    GF1MenuItem->setTag(2);
    GF1MenuItem->setPosition(Locations[2]);
    
    //first red frog
    CCSprite * RF1 = CCSprite::create("RF.png");
    RF1MenuItem  = CCMenuItemSprite::create(RF1, NULL, this, menu_selector(HelloWorld::move_frog_click));
    RF1MenuItem->setTag(4);
    RF1MenuItem->setPosition(Locations[4]);
    
    //second red frog
    CCSprite * RF2 = CCSprite::create("RF.png");
    RF2MenuItem  = CCMenuItemSprite::create(RF2, NULL, this, menu_selector(HelloWorld::move_frog_click));
    RF2MenuItem->setTag(5);
    RF2MenuItem->setPosition(Locations[5]);
    
    //third red frog
    CCSprite * RF3 = CCSprite::create("RF.png");
    RF3MenuItem  = CCMenuItemSprite::create(RF3, NULL, this, menu_selector(HelloWorld::move_frog_click));
    RF3MenuItem->setTag(6);
    RF3MenuItem->setPosition(Locations[6]);
    
    //add all frogs to frogs menu
    CCMenu * frogs = CCMenu::create(RF1MenuItem,RF2MenuItem,RF3MenuItem,GF3MenuItem,GF2MenuItem,GF1MenuItem,NULL);
    
    //set its position on the begining
    frogs->setPosition(ccp(0,0));
    
    //add the frogs to the scene
    this->addChild(frogs);
    
    return true;
}

//this function is going to handle the touch on the frog 
void HelloWorld::move_frog_click(CCObject * Sender)
{
    //get the object
    CCMenuItemSprite * frog = (CCMenuItemSprite *)Sender;
    
    printf("Frog Coordinateds is %f %f \n",frog->getPositionX(), frog->getPositionY());
    
    //get the frog tag
    int frog_tag = frog->getTag();
    
    //pass the frog number to the model
    int index = game_model->user_move_frog(frog_tag);
    printf("Model index is %d\n", index);
    
    //if illegal state do not meve the frog
    if(index == ILLEGAL_MOVE)
    {
        CCMessageBox("Illegal Move!", "Alert");
    }
    else
    {
        printf("i wanna go to index number %d\n", index);
        //move the frog to the index
        this->move_frog_to_address(frog,index);
    //    sleep(1);
        if(game_model->check_user_win() == SUCESS)
        {
            CCMessageBox("You win !", "Alert");
        }
    }
}

//this function is going to move the frog to given address
void HelloWorld::move_frog_to_address(CCObject * pzFrog, int index)
{
    CCMenuItemSprite * frog = (CCMenuItemSprite *) pzFrog;
    int frog_tag = frog->getTag();
    
    frog->setTag(index);
    
    float frog_x,frog_y;
    float frog_distination_x,frog_distination_y;
    frog_x = Locations[frog_tag].x;
    frog_y = Locations[frog_tag].y;
    frog_distination_x = Locations[index].x;
    frog_distination_y = Locations[index].y;
    
    //CCActionInterval *a = CCMoveBy::create(0, Locations[index]);
    
    CCPoint distination = ccp((frog_distination_x - frog_x), (frog_distination_y - frog_y));
    
    frog->runAction(CCMoveBy::create(1, distination));

    //frog->setPosition(ccp(Locations[index].x,Locations[index].y));
    //frog->updateTransform();
    
    printf("the given point is %f, %f\n",Locations[index].x, Locations[index].y);
    
}

//this function si going to restart the game
void HelloWorld::restartGameCallback(CCObject * sender)
{
    printf("restarting \n");
    //this->game_model = NULL;
    
    //move_frog_to_address(RF1MenuItem, 0);
    //move_frog_to_address(RF1MenuItem, 1);
    //move_frog_to_address(RF1MenuItem, 2);
    //move_frog_to_address(RF1MenuItem, 4);
    //move_frog_to_address(RF1MenuItem, 5);
    //move_frog_to_address(RF1MenuItem, 6);
    
    //this->game_model  = new frog_jumping_game_model;
    //this->restartGameCallback(this);
}


int ind = 0;
//this function is going to solve the puzzle
void HelloWorld::solveGameCallback(CCObject * Sender)
{
    printf("solving \n");
    
    game_model->solve_puzzle();
    
    this->schedule(schedule_selector(HelloWorld::simulate__), 1, game_model->solution_sequance.size() - 1, 1);
    
//    for(int i = 0 ; i < game_model->solution_sequance.size(); i++)
//    {
//        move_frog_to_address(get_frog_by_tag(game_model->solution_sequance[i]), game_model->solution_sequance[i]);
//        sleep(1);
//     
//    }
}

//this function is going to simulate the solution of the puzzle
void HelloWorld::simulate__(CCObject * sender)
{
    
    CCMenuItemSprite * frog_to_move = get_frog_by_tag(game_model->solution_sequance[ind++]);
    
    move_frog_click(frog_to_move);
    
}

//this function return a pointer to a frog by it's tag
CCMenuItemSprite * HelloWorld::get_frog_by_tag(int tag)
{
    if(GF1MenuItem->getTag() == tag)
    {
        return GF1MenuItem;
    }
    else if(GF2MenuItem->getTag() == tag)
    {
        return GF2MenuItem;
    }
    else if(GF3MenuItem->getTag() == tag)
    {
        return GF3MenuItem;
    }
    else if(RF1MenuItem->getTag() == tag)
    {
        return RF1MenuItem;
    }
    else if(RF2MenuItem->getTag() == tag)
    {
        return RF2MenuItem;
    }
    else if(RF3MenuItem->getTag() == tag)
    {
        return RF3MenuItem;
    }
    else
    {
        return NULL;
    }
}
