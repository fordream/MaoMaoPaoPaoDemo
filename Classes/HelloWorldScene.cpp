#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    //-------------------------------------------------------------------------------------------
    //This is Tim's code
    auto playerBody = PhysicsBody::createCircle(10.0f, PhysicsMaterial(0.1f, 0.0f, 0.0f));
    
    player = Sprite::create();
    player->setPosition(20, visibleSize.height * 3);
    addChild(player);
    player->setPhysicsBody(playerBody);
    
    cameraTarget = Sprite::create();
    cameraTarget->setPositionX(player->getPosition().x);
    cameraTarget->setPositionY(visibleSize.height / 2);
    cameraTarget->retain();
    schedule(schedule_selector(HelloWorld::updateScene));
    addChild(cameraTarget);
    
    camera = Follow::create(cameraTarget, Rect::ZERO);
    camera->retain();
    
    runAction(camera);
    
    //Vec2* points = new Vec2[10];
    
    //srand(time(NULL));
    //for(int i = 0; i < 10; i++) {
    //    float y = rand() % (200-10 + 1) + 10;
    //    points[i] = Vec2(i * 300.0, y);
    //}
    
    Vec2* points = new Vec2[23]{
        Vec2(1.995841995841996f,313.04347826086956f),
        Vec2(5.987525987525988f,205.71428571428572f),
        Vec2(11.975051975051976f,92.4223602484472f),
        Vec2(24.94802494802495f,44.72049689440996f),
        Vec2(40.91476091476092f,16.894409937888213f),
        Vec2(61.87110187110187f,2.9813664596273384f),
        Vec2(105.77962577962579f,1.9875776397515779f),
        Vec2(163.65904365904368f,1.9875776397515779f),
        Vec2(295.3846153846154f,1.9875776397515779f),
        Vec2(307.35966735966736f,4.968944099378859f),
        Vec2(315.34303534303535f,9.937888198757776f),
        Vec2(323.32640332640335f,17.888198757763973f),
        Vec2(322.3284823284823f,1.9875776397515779f),
        Vec2(574.8024948024948f,14.906832298136635f),
        Vec2(617.7130977130978f,5.962732919254677f),
        Vec2(683.5758835758836f,9.937888198757776f),
        Vec2(723.4927234927235f,21.863354037267072f),
        Vec2(742.4532224532225f,37.763975155279525f),
        Vec2(780.3742203742204f,89.44099378881987f),
        Vec2(806.3201663201663f,143.10559006211182f),
        Vec2(817.2972972972973f,193.7888198757764f),
        Vec2(820.2910602910604f,234.53416149068323f),
        Vec2(819.2931392931393f,303.1055900621118f),
    };
    
    auto groundBody = PhysicsBody::createEdgeChain(points, 23, PhysicsMaterial(0.1f, 0.0f, 0.0f));
    auto groundNode = Node::create();
    addChild(groundNode);
    groundNode->setPhysicsBody(groundBody);
    
    return true;
}

void HelloWorld::updateScene(float delta) {
    cameraTarget->setPositionX(player->getPosition().x);
}
