#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    //scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
    auto backgroundLayer = Layer::create();
    auto backgroundImage = Sprite::create("DemoAssets/SkyBackground_Demo.png");
    backgroundImage->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 2);
    backgroundLayer->addChild(backgroundImage);
    scene->addChild(backgroundLayer);
    
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
    
    hills = Hills::create();
    addChild(hills);
    hills->generateXYPoints();
    hills->generateMeshes();
    
    auto playerBody = PhysicsBody::createCircle(16.0f, PhysicsMaterial(0.1f, 0.0f, 1.0f));
    player = Sprite::create("DemoAssets/King_Demo.png");
    player->setPosition(20, visibleSize.height);
    player->setPhysicsBody(playerBody);
    player->getPhysicsBody()->setVelocity(Vec2(100, 0));
    player->getPhysicsBody()->setAngularVelocity(-30.0f);
    addChild(player);
    
    cameraTarget = Sprite::create();
    cameraTarget->setPositionX(player->getPosition().x);
    cameraTarget->setPositionY(visibleSize.height / 2);
    cameraTarget->retain();
    schedule(schedule_selector(HelloWorld::updateScene));
    addChild(cameraTarget);
    
    camera = Follow::create(cameraTarget, Rect::ZERO);
    camera->retain();
    
    runAction(camera);
    
    auto groundBody = PhysicsBody::createEdgeChain(hills->getPoints(), NumPoints, PhysicsMaterial(0.1f, 0.0f, 1.0f));
    auto groundNode = Node::create();
    addChild(groundNode);
    groundNode->setPhysicsBody(groundBody);
    
    return true;
}

void HelloWorld::updateScene(float delta) {
    cameraTarget->setPositionX(player->getPosition().x);
}
