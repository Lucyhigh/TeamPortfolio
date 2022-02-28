#pragma once
#include "GameNode.h"
#include "PixelCollision.h"
class PixelScene : public GameNode
{
private:
    Image* _image;
    PixelCollision* _pixel;
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
public:
    PixelScene() {}
    ~PixelScene() {}

};

