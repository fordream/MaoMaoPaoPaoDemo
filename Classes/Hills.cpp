//
//  Hills.cpp
//  MaoMaoPaoPaoDemo
//
//  Created by Timothy DenOuden on 9/24/15.
//
//
#include <iostream>
#include "Hills.h"

USING_NS_CC;

Hills::Hills() {
    Sprite* groundSprite = Sprite::create("DemoAssets/Ground_Demo.png");
    groundSprite->retain();
    groundTexture = groundSprite->getTexture();
    groundTexture->setTexParameters( {GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT} );
    
    Sprite* grassSprite = Sprite::create("DemoAssets/grass_Demo.png");
    grassSprite->retain();
    grassTexture = grassSprite->getTexture();
    grassTexture->setTexParameters( {GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT} );
    
    GLProgram *shaderProgram = ShaderCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE);
    setGLProgram(shaderProgram);
    scheduleUpdate();
}

Hills::~Hills() {
    
}

bool Hills::init() {
    if(!Node::init()) {
        return false;
    }
    return true;
}

void Hills::update(float dt) {
    
}

void Hills::generateXYPoints() {
    
}

void Hills::generateMeshes() {
    numHillVertices = 0;
    Point p;
    for(int i = 0; i < NumPoints; i++) {
        p = points[i];
        grassVertices[numHillVertices] = Point(p.x, p.y - 12.0f);
        grassTexCoords[numHillVertices++] = Point(p.x / grassTexture->getPixelsWide(), 1.0f);
        grassVertices[numHillVertices] = Point(p.x, p.y);
        grassTexCoords[numHillVertices++] = Point(p.x / grassTexture->getPixelsWide(), 0);
        
    }
    
    numHillVertices = 0;
    for(int i = 0; i < NumPoints; i++) {
        p = points[i];
        groundVertices[numHillVertices] = Point(p.x, 0);
        groundTexCoords[numHillVertices++] = Point(p.x / groundTexture->getPixelsWide(), 0);
        groundVertices[numHillVertices] = Point(p.x, p.y - 5.0f);
        groundTexCoords[numHillVertices++] = Point(p.x / groundTexture->getPixelsWide(), (p.y / groundTexture->getPixelsHigh()));
    }
}

void Hills::draw(Renderer* renderer, const Mat4 &transform, uint32_t flags) {
    Node::draw(renderer, transform, flags);
    rendererCommands[0].init(0.0f);
    rendererCommands[0].func = CC_CALLBACK_0(Hills::onDraw, this, transform);
    renderer->addCommand(&rendererCommands[0]);
}

void Hills::onDraw(const Mat4 &transform) {
    auto glProgram = getGLProgram();
    glProgram->use();
    glProgram->setUniformsForBuiltins(transform);
    
    GL::bindTexture2D(groundTexture->getName());
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, groundVertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, groundTexCoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)NumVerticies);
    
    GL::bindTexture2D(grassTexture->getName());
    GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, grassVertices);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_TEX_COORD, 2, GL_FLOAT, GL_FALSE, 0, grassTexCoords);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)NumVerticies);
}

Point* Hills::getPoints() {
    return points;
}