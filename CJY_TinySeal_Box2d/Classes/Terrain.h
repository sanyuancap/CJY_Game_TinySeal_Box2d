//
//  Terrain.h
//  CJY_TinySeal
//
//  Created by CC on 14-1-24.
//
//

#ifndef __CJY_TinySeal__Terrain__
#define __CJY_TinySeal__Terrain__

#include <iostream>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"

#define kMaxHillKeyPoints 1000
#define kHillSegmentWidth 5
#define kMaxHillVertices 4000
#define kMaxBorderVertices 800

class Terrain : public cocos2d::CCNode
{
public:
    Terrain(void);
    ~Terrain(void);
    static Terrain* createWithWorld(b2World *world);
    bool initWithWorld(b2World *world);
    void setupDebugDraw();
    void resetBox2DBody();
    
    CREATE_FUNC(Terrain);
    
    void generateHills();//初始化高低峰点数组 _hillKeyPoints[]
    bool init();
    void draw();
    void setOffsetX(float newOffsetX);
    void resetHillVertices();
    
    CC_SYNTHESIZE_RETAIN(cocos2d::CCSprite*, _stripes, Stripes);
    CC_SYNTHESIZE_RETAIN(cocos2d::CCSpriteBatchNode*, _batchNode, BatchNode);
    
private:
    int _offsetX;
    cocos2d::CCPoint _hillKeyPoints[kMaxHillKeyPoints];//高低峰点数组
    cocos2d::CCPoint _hillVertices[kMaxHillVertices];//绘制长度间隔点数组
    cocos2d::CCPoint _hillTexCoords[kMaxHillVertices];
    cocos2d::CCPoint _borderVertices[kMaxBorderVertices];//边缘坐标点数组
    int _fromKeyPointI;
    int _toKeyPointI;
    int _nHillVertices;
    int _nBorderVertices;
    
    b2World *_world;
    b2Body *_body;
    GLESDebugDraw *_debugDraw;
    
};

#endif /* defined(__CJY_TinySeal__Terrain__) */

























