//
//  Hero.h
//  CJY_TinySeal_Box2d
//
//  Created by CC on 14-1-26.
//
//

#ifndef __CJY_TinySeal_Box2d__Hero__
#define __CJY_TinySeal_Box2d__Hero__

//#pragma once
#include <iostream>

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define NUM_PREV_VELS 5

class Hero : public cocos2d::CCSprite
{
public:
    Hero(void);
    ~Hero(void);
    
    static Hero *createWithWorld(b2World *world);
    bool initWithWorld(b2World *world);
    
    void update(float dt);
    void createBody();
    void limitVelocity();
    void dive();
    void wake();
    void nodive();
    void runForceAnimation();
    void runNormalAnimation();
    
    CC_SYNTHESIZE_READONLY(bool, _awake, Awake);
    
private:
    b2World *_world;
    b2Body *_body;
    b2Vec2 _prevVels[NUM_PREV_VELS];
    int _nextVel;
    cocos2d::CCAnimation *_normalAnim;
    cocos2d::CCAction *_normalAnimate;
};


#endif /* defined(__CJY_TinySeal_Box2d__Hero__) */


























