#pragma once
#include "GameNode.h"
#include "Camera.h"

class PixelCollision : public GameNode
{
private:
    Camera* _camera;
    Image* _bgImage;
    Image* _image;
    vector<RECT*> _floor;
    RECT* floor0;
    RECT _rc;
    //픽셀 충돌 탐지할 Y값 센서
    int _probeY;
    int _x, _y;
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
public:
    PixelCollision() {}
    ~PixelCollision() {}
};

