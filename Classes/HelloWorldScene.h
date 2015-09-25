#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Hills.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    cocos2d::Sprite* player;
    cocos2d::Sprite* cameraTarget;
    cocos2d::Follow* camera;
    Hills* hills;

    virtual bool init();
    
    void updateScene(float delta);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
