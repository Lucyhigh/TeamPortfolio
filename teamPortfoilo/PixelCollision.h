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
    //�ȼ� �浹 Ž���� Y�� ����
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

