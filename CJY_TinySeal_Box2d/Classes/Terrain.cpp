//
//  Terrain.cpp
//  CJY_TinySeal
//
//  Created by CC on 14-1-24.
//
//

#include "Terrain.h"
#include "HelloWorldScene.h"
using namespace cocos2d;

Terrain::Terrain(void)
{
    _stripes = NULL;
    _fromKeyPointI = 0;
    _toKeyPointI = 0;
    _offsetX = 0;
    
    _world = NULL;
    _body = NULL;
    _debugDraw = NULL;
}
Terrain::~Terrain(void)
{
    CC_SAFE_RELEASE_NULL(_stripes);
}

bool Terrain::init()
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!CCNode::init());
        this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture));
        this->generateHills();
        this->resetHillVertices();
        bRet = true;
    }while(0);
    return bRet;
}

void Terrain::draw()
{
    CC_NODE_DRAW_SETUP();
    
    ccGLBindTexture2D(_stripes->getTexture()->getName());
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords);
    
    ccDrawColor4F(1.0f, 1.0f, 1.0f, 1.0f);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, _hillVertices);
    glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, _hillTexCoords);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)_nHillVertices);
    
    CCNode::draw();
    
//    _world->DrawDebugData();
    
//    for (int i = MAX(_fromKeyPointI, 1); i <= _toKeyPointI; ++i)
//    {
//        ccDrawColor4F(1.0, 0, 0, 1.0);
//        ccDrawLine(_hillKeyPoints[i - 1], _hillKeyPoints[i]);
//        
//        /*cos*/
//        ccDrawColor4F(1.0, 1.0, 1.0, 1.0);
//        CCPoint p0 = _hillKeyPoints[i - 1];
//        CCPoint p1 = _hillKeyPoints[i];
//        int hSegments = floorf((p1.x - p0.x) / kHillSegmentWidth);
//        float dx = (p1.x - p0.x) / hSegments;
//        float da = M_PI / hSegments;
//        float ymid = (p0.y + p1.y) / 2;
//        float ampl = (p0.y - p1.y) / 2;
//        
//        CCPoint pt0,pt1;
//        pt0 = p0;
//        for (int j = 0; j < hSegments + 1; ++j) {
//            pt1.x = p0.x + j * dx;
//            pt1.y = ymid + ampl * cosf(da * j);
//            
//            ccDrawLine(pt0, pt1);
//            
//            pt0 = pt1;
//        }
//    }
}
void Terrain::setOffsetX(float newOffsetX)
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _offsetX = newOffsetX;
    this->setPosition(ccp(winSize.width / 8 - _offsetX * this->getScale(), 0));
    this->resetHillVertices();
}
void Terrain::resetHillVertices()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    static int prevFromKeyPointI = -1;
    static int prevToKeyPointI = -1;
    
    // key points interval for drawing
    while (_hillKeyPoints[_fromKeyPointI + 1].x < _offsetX - winSize.width / 8 / this->getScale())
    {
        _fromKeyPointI++;
    }
    while (_hillKeyPoints[_toKeyPointI].x < _offsetX + winSize.width * 9 / 8 / this->getScale())
    {
        _toKeyPointI++;
    }
    
    if (prevFromKeyPointI != _fromKeyPointI || prevToKeyPointI != _toKeyPointI)
    {
        // vertices for visible area
        _nHillVertices = 0;
        _nBorderVertices = 0;
        CCPoint p0, p1, pt0, pt1;
        p0 = _hillKeyPoints[_fromKeyPointI];
        for (int i = _fromKeyPointI + 1; i < _toKeyPointI + 1; ++i)
        {
            p1 = _hillKeyPoints[i];
            
            // triangle strip between p0 and p1
            int hSegments = floorf((p1.x - p0.x) / kHillSegmentWidth);
            float dx = (p1.x - p0.x) / hSegments;
            float da = M_PI / hSegments;
            float ymid = (p0.y + p1.y) / 2;
            float ampl = (p0.y - p1.y) / 2;
            pt0 = p0;
            _borderVertices[_nBorderVertices++] = pt0;
            for (int j = 1; j < hSegments + 1; ++j)
            {
                pt1.x = p0.x + j * dx;
                pt1.y = ymid + ampl * cosf(da * j);
                _borderVertices[_nBorderVertices++] = pt1;
                
                _hillVertices[_nHillVertices] = ccp(pt0.x, 0);
                _hillTexCoords[_nHillVertices++] = ccp(pt0.x / 512, 1.0f);
                
                _hillVertices[_nHillVertices] = ccp(pt1.x, 0);
                _hillTexCoords[_nHillVertices++] = ccp(pt1.x / 512, 1.0f);
                
                _hillVertices[_nHillVertices] = ccp(pt0.x, pt0.y);
                _hillTexCoords[_nHillVertices++] = ccp(pt0.x / 512, 0);
                
                _hillVertices[_nHillVertices] = ccp(pt1.x, pt1.y);
                _hillTexCoords[_nHillVertices++] = ccp(pt1.x / 512, 0);
                pt0 = pt1;
            }
            
            p0 = p1;
        }
        
        prevFromKeyPointI = _fromKeyPointI;
        prevToKeyPointI = _toKeyPointI;
        
        this->resetBox2DBody();
    }
}

void Terrain::generateHills()
{
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    float minDX = 160;
    float minDY = 60;
    int rangeDX = 80;
    int rangeDY = 40;
    float x = -minDX;
    float y = winSize.height / 2;
    
    float dy, ny;
    float sign = 1; // +1 - going up, -1 - going  down
    float paddingTop = 20;
    float paddingBottom = 20;
    
    for (int i = 0; i < kMaxHillKeyPoints; ++i)
    {
        _hillKeyPoints[i] = ccp(x, y);
        if (i == 0)
        {
            x = 0;
            y = winSize.height / 2;
        }
        else
        {
            x += rand() % rangeDX + minDX;
            while (true)
            {
                dy = rand() % rangeDY + minDY;
                ny = y + dy * sign;
                if (ny < (winSize.height - paddingTop) &&
                    ny > paddingBottom)
                {
                    break;
                }
            }
            y = ny;
        }
        sign *= -1;
    }
}

#pragma mark - box2d


void Terrain::resetBox2DBody()
{
    if (_body) {
        _world->DestroyBody(_body);
    }
    
    b2BodyDef bd;
    bd.position.Set(0, 0);
    _body = _world->CreateBody(&bd);
    
    b2EdgeShape shape;
    b2Vec2 p1,p2;
    for (int i = 0; i < _nBorderVertices - 1; ++i) {
        p1 = b2Vec2(_borderVertices[i].x / PTM_RATIO, _borderVertices[i + 1].y / PTM_RATIO);
        p2 = b2Vec2(_borderVertices[i + 1].x / PTM_RATIO, _borderVertices[i + 1].y / PTM_RATIO);
        shape.Set(p1, p2);
        _body->CreateFixture(&shape,0);
    }
}

Terrain* Terrain::createWithWorld(b2World *world)
{
    Terrain *pRet = new Terrain();
    if (pRet && pRet->initWithWorld(world)) {
        pRet->autorelease();
    }else{
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

bool Terrain::initWithWorld(b2World *world)
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!CCNode::init());
        _world = world;
        this->setupDebugDraw();
        this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture));
        this->generateHills();
        this->resetHillVertices();
        
        _batchNode = CCSpriteBatchNode::create("TinySeal.png");
        this->addChild(_batchNode);
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("TinySeal.plist");
        
        bRet = true;
    }while (0);
    return bRet;
}

void Terrain::setupDebugDraw()
{
    _debugDraw = new GLESDebugDraw(PTM_RATIO);
    _world->SetDebugDraw(_debugDraw);
    _debugDraw->SetFlags(GLESDebugDraw::e_shapeBit | GLESDebugDraw::e_jointBit);
}
    






































