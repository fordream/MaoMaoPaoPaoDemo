//
//  Hills.h
//  MaoMaoPaoPaoDemo
//
//  Created by Timothy DenOuden on 9/24/15.
//
//

#ifndef Hills_h
#define Hills_h

#include "cocos2d.h"

USING_NS_CC;

#define NumPoints 16
#define NumVerticies 32

class Hills : public Node {
private:
    int numHillVertices = 0;
    
    Point* points = new Point[NumPoints]{
        Point(3.991683991683992f,137.14285714285714f),
        Point(94.8024948024948f,97.3913043478261f),
        Point(220.54054054054055f,90.43478260869566f),
        Point(300.3742203742204f,119.25465838509317f),
        Point(345.2806652806653f,131.1801242236025f),
        Point(402.1621621621622f,129.19254658385094f),
        Point(486.985446985447f,113.29192546583852f),
        Point(535.8835758835759f,83.47826086956522f),
        Point(601.7463617463618f,68.57142857142858f),
        Point(643.6590436590437f,84.47204968944101f),
        Point(738.4615384615385f,130.1863354037267f),
        Point(793.3471933471934f,198.75776397515529f),
        Point(807.3180873180874f,257.39130434782606f),
        Point(858.2120582120583f,290.18633540372673f),
        Point(900.1247401247401f,252.4223602484472f),
        Point(951.0187110187111f,205.71428571428572f),
    };
    
    Point groundVertices[NumVerticies];
    Point groundTexCoords[NumVerticies];
    Point grassVertices[NumVerticies];
    Point grassTexCoords[NumVerticies];
    
    Texture2D* grassTexture;
    Texture2D* groundTexture;
    
    CustomCommand rendererCommands[1];
public:
    Hills();
    ~Hills();
    
    void destroy();
    void generateXYPoints();
    void generateMeshes();
    Point* getPoints();
    
    void onDraw(const Mat4 &transform);
    virtual void draw(Renderer *renderer, const Mat4& transform, uint32_t flags);
    virtual void update(float dt);
    
    virtual bool init();
    CREATE_FUNC(Hills);
};
#endif /* Hills_h */
