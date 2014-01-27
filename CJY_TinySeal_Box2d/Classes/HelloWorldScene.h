//
//  HelloWorldScene.h
//  CJY_TinySeal_Box2d
//
//  Created by CC on 14-1-26.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "Terrain.h"
#include "Hero.h"

#define PTM_RATIO 32

class PhysicsSprite : public cocos2d::CCSprite
{
public:
    PhysicsSprite();
    void setPhysicsBody(b2Body * body);
    virtual bool isDirty(void);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
private:
    b2Body* m_pBody;    // strong ref
};

#pragma mark - begin
class HelloWorld : public cocos2d::CCLayer {
public:
    
    void initPhysics();
// adds a new sprite at a given coordinate
    void addNewSpriteAtPosition(cocos2d::CCPoint p);
    
    
    ~HelloWorld();
    HelloWorld();
    bool virtual init();
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    virtual void draw();
    void virtual ccTouchesBegan(cocos2d::CCSet *pTouches,cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesCancelled(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void update(float dt);
    void onEnter();
    void genBackground();
    cocos2d::CCSprite* spriteWithColor(cocos2d::ccColor4F bgColor,float textureWidth,float textureHeight);
    cocos2d::CCSprite* spriteWithColor1(cocos2d::ccColor4F c1,cocos2d::ccColor4F c2,float textureWidth,float textureHeight,int nStripes);
    cocos2d::ccColor4F randomBrightColor();
    
    void setupWorld();
    void createTestBodyAtPosition(cocos2d::CCPoint position);
    
private:
//    cocos2d::CCTexture2D* m_pSpriteTexture; // weak ref
    
    b2World * _world;    
    Terrain *_terrain;
    cocos2d::CCSprite *_background;
    Hero *_hero;
    bool _tapDown;
};

#endif // __HELLO_WORLD_H__

























