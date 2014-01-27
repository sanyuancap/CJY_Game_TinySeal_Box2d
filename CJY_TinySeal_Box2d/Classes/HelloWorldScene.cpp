//
//  HelloWorldScene.cpp
//  CJY_TinySeal_Box2d
//
//  Created by CC on 14-1-26.
//  Copyright __MyCompanyName__ 2014年. All rights reserved.
//
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;


enum {
    kTagParentNode = 1,
};

PhysicsSprite::PhysicsSprite()
: m_pBody(NULL)
{

}

void PhysicsSprite::setPhysicsBody(b2Body * body)
{
    m_pBody = body;
}

// this method will only get called if the sprite is batched.
// return YES if the physics values (angles, position ) changed
// If you return NO, then nodeToParentTransform won't be called.
bool PhysicsSprite::isDirty(void)
{
    return true;
}

// returns the transform matrix according the Chipmunk Body values
CCAffineTransform PhysicsSprite::nodeToParentTransform(void)
{
    b2Vec2 pos  = m_pBody->GetPosition();

    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;

    if ( isIgnoreAnchorPointForPosition() ) {
        x += m_obAnchorPointInPoints.x;
        y += m_obAnchorPointInPoints.y;
    }

    // Make matrix
    float radians = m_pBody->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);

    if( ! m_obAnchorPointInPoints.equals(CCPointZero) ){
        x += c*-m_obAnchorPointInPoints.x + -s*-m_obAnchorPointInPoints.y;
        y += s*-m_obAnchorPointInPoints.x + c*-m_obAnchorPointInPoints.y;
    }

    // Rot, Translate Matrix
    m_sTransform = CCAffineTransformMake( c,  s,
        -s,    c,
        x,    y );

    return m_sTransform;
}


void HelloWorld::initPhysics()
{
    //
    //    CCSize s = CCDirector::sharedDirector()->getWinSize();
    //
    //    b2Vec2 gravity;
    //    gravity.Set(0.0f, -10.0f);
    //    world = new b2World(gravity);
    //
    //    // Do we want to let bodies sleep?
    //    world->SetAllowSleeping(true);
    //
    //    world->SetContinuousPhysics(true);
    //
    ////     m_debugDraw = new GLESDebugDraw( PTM_RATIO );
    ////     world->SetDebugDraw(m_debugDraw);
    //
    //    uint32 flags = 0;
    //    flags += b2Draw::e_shapeBit;
    //    //        flags += b2Draw::e_jointBit;
    //    //        flags += b2Draw::e_aabbBit;
    //    //        flags += b2Draw::e_pairBit;
    //    //        flags += b2Draw::e_centerOfMassBit;
    //    //m_debugDraw->SetFlags(flags);
    //
    //
    //    // Define the ground body.
    //    b2BodyDef groundBodyDef;
    //    groundBodyDef.position.Set(0, 0); // bottom-left corner
    //
    //    // Call the body factory which allocates memory for the ground body
    //    // from a pool and creates the ground box shape (also from a pool).
    //    // The body is also added to the world.
    //    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    //
    //    // Define the ground box shape.
    //    b2EdgeShape groundBox;
    //
    //    // bottom
    //
    //    groundBox.Set(b2Vec2(0,0), b2Vec2(s.width/PTM_RATIO,0));
    //    groundBody->CreateFixture(&groundBox,0);
    //
    //    // top
    //    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO));
    //    groundBody->CreateFixture(&groundBox,0);
    //
    //    // left
    //    groundBox.Set(b2Vec2(0,s.height/PTM_RATIO), b2Vec2(0,0));
    //    groundBody->CreateFixture(&groundBox,0);
    //
    //    // right
    //    groundBox.Set(b2Vec2(s.width/PTM_RATIO,s.height/PTM_RATIO), b2Vec2(s.width/PTM_RATIO,0));
    //    groundBody->CreateFixture(&groundBox,0);
}


void HelloWorld::addNewSpriteAtPosition(CCPoint p)
{
    //    CCLOG("Add sprite %0.2f x %02.f",p.x,p.y);
    //    CCNode* parent = getChildByTag(kTagParentNode);
    //
    //    //We have a 64x64 sprite sheet with 4 different 32x32 images.  The following code is
    //    //just randomly picking one of the images
    //    int idx = (CCRANDOM_0_1() > .5 ? 0:1);
    //    int idy = (CCRANDOM_0_1() > .5 ? 0:1);
    //    PhysicsSprite *sprite = new PhysicsSprite();
    //    sprite->initWithTexture(m_pSpriteTexture, CCRectMake(32 * idx,32 * idy,32,32));
    //    sprite->autorelease();
    //
    //    parent->addChild(sprite);
    //
    //    sprite->setPosition( CCPointMake( p.x, p.y) );
    //
    //    // Define the dynamic body.
    //    //Set up a 1m squared box in the physics world
    //    b2BodyDef bodyDef;
    //    bodyDef.type = b2_dynamicBody;
    //    bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);
    //
    //    b2Body *body = world->CreateBody(&bodyDef);
    //
    //    // Define another box shape for our dynamic body.
    //    b2PolygonShape dynamicBox;
    //    dynamicBox.SetAsBox(.5f, .5f);//These are mid points for our 1m box
    //
    //    // Define the dynamic body fixture.
    //    b2FixtureDef fixtureDef;
    //    fixtureDef.shape = &dynamicBox;
    //    fixtureDef.density = 1.0f;
    //    fixtureDef.friction = 0.3f;
    //    body->CreateFixture(&fixtureDef);
    //    
    //    sprite->setPhysicsBody(body);
}


#pragma mark - begin
HelloWorld::HelloWorld()
{
//    setTouchEnabled( true );
//    setAccelerometerEnabled( true );
//
//    CCSize s = CCDirector::sharedDirector()->getWinSize();
//    // init physics
//    this->initPhysics();
//
//    CCSpriteBatchNode *parent = CCSpriteBatchNode::create("blocks.png", 100);
//    m_pSpriteTexture = parent->getTexture();
//
//    addChild(parent, 0, kTagParentNode);
//
//
//    addNewSpriteAtPosition(ccp(s.width/2, s.height/2));
//
//    CCLabelTTF *label = CCLabelTTF::create("Tap screen", "Marker Felt", 32);
//    addChild(label, 0);
//    label->setColor(ccc3(0,0,255));
//    label->setPosition(ccp( s.width/2, s.height-50));
//    
//    scheduleUpdate();
    
    _background = NULL;
    _tapDown = false;
    
}

HelloWorld::~HelloWorld()
{
//    delete world;
//    world = NULL;
    //delete m_debugDraw;
    
    
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do{
        CC_BREAK_IF(!CCLayer::init());
        bRet = true;
    }while(0);
    
    return bRet;
}


void HelloWorld::onEnter()
{
    CCLayer::onEnter();
    
    this->setupWorld();
    
    _terrain = Terrain::createWithWorld(_world);
    this->addChild(_terrain);
    
    this->genBackground();
    this->setTouchEnabled(true);
    
    this->setScale(1.0);
    
    this->scheduleUpdate();
    
    _hero = Hero::createWithWorld(_world);
    _terrain->getBatchNode()->addChild(_hero);
    
    CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("TinySeal.caf");
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("TinySeal.caf", true);
}


void HelloWorld::draw()
{
    //
    // IMPORTANT:
    // This is only for debug purposes
    // It is recommend to disable it
    //
//    CCLayer::draw();
//
//    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
//
//    kmGLPushMatrix();
//
//    world->DrawDebugData();
    
//
//    kmGLPopMatrix();
}


void HelloWorld::update(float dt)
{
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    
//    int velocityIterations = 8;
//    int positionIterations = 1;
    
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
//    world->Step(dt, velocityIterations, positionIterations);
    
    //Iterate over the bodies in the physics world
//    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
//    {
//        if (b->GetUserData() != NULL) {
//            //Synchronize the AtlasSprites position and rotation with the corresponding body
//            CCSprite* myActor = (CCSprite*)b->GetUserData();
//            myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
//            myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
//        }    
//    }
    if (_tapDown)
    {
        if (!_hero->getAwake())
        {
            _hero->wake();
            _tapDown = false;
        }
        else
        {
            _hero->dive();
        }
    }
    else
    {
        _hero->nodive();
    }
    _hero->limitVelocity();
    
    static double UPDATE_INTERVAL = 1.0f / 60.0f;
    static double MAX_CYCLES_PER_FRAME = 5;
    static double timeAccumulator = 0;
    
    timeAccumulator += dt;
    if (timeAccumulator > (MAX_CYCLES_PER_FRAME * UPDATE_INTERVAL)) {
        timeAccumulator = UPDATE_INTERVAL;
    }
    int32 velocityIterrations = 3;
    int32 positionIterations = 2;
    while (timeAccumulator >= UPDATE_INTERVAL) {
        timeAccumulator -= UPDATE_INTERVAL;
        _world->Step(UPDATE_INTERVAL, velocityIterrations, positionIterations);
        _world->ClearForces();
    }
    
    
//    float PIXELS_PER_SECOND = 100;
//    static float offset = 0;
//    offset += PIXELS_PER_SECOND * dt;
    
    _hero->update(dt);
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float scale = (winSize.height * 3 / 4) / _hero->getPosition().y;
    if (scale > 1)
    {
        scale = 1;
    }
    _terrain->setScale(scale);
    
    float offset = _hero->getPosition().x;
    
    CCSize textureSize = _background->getTextureRect().size;
    _background->setTextureRect(CCRectMake(offset, 0, textureSize.width, textureSize.height));
    
    _terrain->setOffsetX(offset);
    

}

void HelloWorld::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    this->genBackground();
    
    _tapDown = true;
    _hero->runForceAnimation();
    
}
void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    //Add a new body/atlas sprite at the touched location
//    CCSetIterator it;
//    CCTouch* touch;
//    
//    for( it = touches->begin(); it != touches->end(); it++) 
//    {
//        touch = (CCTouch*)(*it);
//        
//        if(!touch)
//            break;
//        
//        CCPoint location = touch->getLocationInView();
//        
//        location = CCDirector::sharedDirector()->convertToGL(location);
//        
//        addNewSpriteAtPosition( location );
//    }
    _tapDown = false;
    _hero->runNormalAnimation();
}

void HelloWorld::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
    _tapDown = false;
    _hero->runNormalAnimation();
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new HelloWorld();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}


CCSprite* HelloWorld::spriteWithColor1(cocos2d::ccColor4F c1, cocos2d::ccColor4F c2, float textureWidth, float textureHeight, int nStripes)
{
    /*render*/
    CCRenderTexture *rt = CCRenderTexture::create(textureWidth, textureHeight);
    rt->beginWithClear(c1.r, c1.g, c1.b, c1.a);
    this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    CC_NODE_DRAW_SETUP();
    /*stripes*/
    CCPoint *vertices = new CCPoint[nStripes * 6];
    ccColor4F *colors = new ccColor4F[nStripes * 6];
    int nVertices = 0;
    float x1 = -textureHeight;
    float x2;
    float y1 = textureHeight;
    float y2 = 0;
    float dx = textureWidth / nStripes * 2;
    float stripeWidth = dx / 2;
    for (int i = 0; i < nStripes; ++i)
    {
        x2  = x1 + textureHeight;
        
        vertices[nVertices] = ccp(x1, y1);//v0
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        
        vertices[nVertices] = ccp(x1 + stripeWidth, y1);//v1
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        
        vertices[nVertices] = ccp(x2, y2);//v2
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        
        vertices[nVertices] = vertices[nVertices - 2];//v1
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        
        vertices[nVertices] = vertices[nVertices - 2];//v2
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        
        vertices[nVertices] = ccp(x2 + stripeWidth, y2);//v3
        colors[nVertices++] = ccc4f(c2.r, c2.g, c2.b, c2.a);
        x1 += dx;
    }
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)nVertices);
    
    /*gradient and light*/
    float gradientAlpha = 0.7f;
    nVertices = 0;
    
    vertices[nVertices] = ccp(0, 0);
    colors[nVertices++] = ccc4f(0, 0, 0, 0);
    
    vertices[nVertices] = ccp(textureWidth, 0);
    colors[nVertices++] = ccc4f(0, 0, 0, 0);
    
    vertices[nVertices] = ccp(0, textureHeight);
    colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);
    
    vertices[nVertices] = ccp(textureWidth, textureHeight);
    colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);
    
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
    glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
    
    // Layer 3: top highlight
    float borderHeight = textureHeight / 16;
    float borderAlpha = 0.3f;
    nVertices = 0;
    
    vertices[nVertices] = ccp(0, 0);
    colors[nVertices++] = ccc4f(1, 1, 1, borderAlpha);
    
    vertices[nVertices] = ccp(textureWidth, 0);
    colors[nVertices++] = ccc4f(1, 1, 1, borderAlpha);
    
    vertices[nVertices] = ccp(0, borderHeight);
    colors[nVertices++] = ccc4f(0, 0, 0, 0);
    
    vertices[nVertices] = ccp(textureWidth, borderHeight);
    colors[nVertices++] = ccc4f(0, 0, 0, 0);
    
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_TRUE, 0, colors);
    glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
    
    CC_SAFE_DELETE_ARRAY(vertices);
    CC_SAFE_DELETE_ARRAY(colors);
    
    // Layer 4: Noise
	CCSprite *noise = CCSprite::create("Noise.png");
	ccBlendFunc blendFunc = {GL_DST_COLOR, CC_BLEND_DST};
    noise->setBlendFunc(blendFunc);
    noise->setPosition(ccp(textureWidth / 2, textureHeight / 2));
    noise->visit();
    
    // 4: Call CCRenderTexture:end
    rt->end();
    
    // 5: Create a new Sprite from the texture
    return CCSprite::createWithTexture(rt->getSprite()->getTexture());
    
}

CCSprite* HelloWorld::spriteWithColor(cocos2d::ccColor4F bgColor, float textureWidth, float textureHeight)
{
    /*render*/
    CCRenderTexture *rt = CCRenderTexture::create(textureWidth, textureHeight);
    rt->beginWithClear(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
    
    /*shader*/
    this->setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
    
    CC_NODE_DRAW_SETUP();
    
    // 3: Draw into the texture
    float gradientAlpha = 0.7f;
    CCPoint vertices[4];
    ccColor4F colors[4];
    int nVertices = 0;
    
    vertices[nVertices] = CCPointMake(0, 0);
    colors[nVertices++] = ccc4f(0, 0, 0, 0);
    vertices[nVertices] = CCPointMake(textureWidth, 0);
    colors[nVertices++] = ccc4f(0, 0, 0, 0);
    vertices[nVertices] = CCPointMake(0, textureHeight);
    colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);
    vertices[nVertices] = CCPointMake(textureWidth, textureHeight);
    colors[nVertices++] = ccc4f(0, 0, 0, gradientAlpha);
    
    ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
    
    glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_FLOAT, GL_FALSE, 0, colors);
    glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)nVertices);
    
    /*noise*/
    CCSprite *noise = CCSprite::create("Noise.png");
    ccBlendFunc blendFunc = {GL_DST_COLOR,GL_ZERO};
    noise->setBlendFunc(blendFunc);
    noise->setPosition(ccp(textureWidth / 2, textureHeight / 2));
    noise->visit();
    
    rt->end();
    
    return CCSprite::createWithTexture(rt->getSprite()->getTexture());
    
}

ccColor4F HelloWorld::randomBrightColor()
{
    while (true) {
        float requiredBrightness = 192;
        ccColor4B randomColor = ccc4(rand() % 255,
                                     rand() % 255,
                                     rand() % 255,
                                     rand() % 255);
        if (randomColor.r > requiredBrightness ||
            randomColor.g > requiredBrightness ||
            randomColor.b > requiredBrightness ) {
            return ccc4FFromccc4B(randomColor);
        }
    }
}

void HelloWorld::genBackground()
{
    if (_background)
    {
        _background->removeFromParentAndCleanup(true);
    }
    
    ccColor4F bgColor = this->randomBrightColor();
    _background = this->spriteWithColor(bgColor, 512, 512);
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _background->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    ccTexParams tp = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_REPEAT};
    _background->getTexture()->setTexParameters(&tp);
    _background->setScale(2.0);
    this->addChild(_background,-1);
    
    ccColor4F color3 = this->randomBrightColor();
    ccColor4F color4 = this->randomBrightColor();
    CCSprite *stripes = this->spriteWithColor1(color3, color4, 512, 512, 4);
    ccTexParams tp2 = {GL_LINEAR, GL_LINEAR, GL_REPEAT, GL_CLAMP_TO_EDGE};
    stripes->getTexture()->setTexParameters(&tp2);
    _terrain->setStripes(stripes);
    //    _terrain->setVisible(false);
    //    addChild(stripes);
    //    _background->setVisible(false);
}

void HelloWorld::setupWorld()
{
    bool doSleep = true;
    b2Vec2 gravity = b2Vec2(0.0f,-7.0f);
    
    _world = new b2World(gravity);
    _world->SetAllowSleeping(doSleep);
}

void HelloWorld::createTestBodyAtPosition(cocos2d::CCPoint position)
{
    b2BodyDef testBodyDef;
    testBodyDef.type = b2_dynamicBody;
    testBodyDef.position.Set(position.x / PTM_RATIO, position.y / PTM_RATIO);
    b2Body *testBody = _world->CreateBody(&testBodyDef);
    
    b2CircleShape testBodyShape;
    b2FixtureDef testFixtureDef;
    testBodyShape.m_radius = 25.0 / PTM_RATIO;
    testFixtureDef.shape = &testBodyShape;
    testFixtureDef.density = 1.0;
    testFixtureDef.friction = 2.0;
    testFixtureDef.restitution = 0.5;
    testBody->CreateFixture(&testFixtureDef);
    
}



































