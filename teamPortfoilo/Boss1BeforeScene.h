#pragma once
#include "GameNode.h"
#include "Camera.h"

class Boss1BeforeScene : public GameNode
{
private:
    vector<RECT*> _floor;
    Camera* _camera;
    Image* _mapImage;
    Image* _objectImage;
    RECT* floor0;
    RECT* floor1;
    RECT* floor2;
    RECT _ObjectRc;

    float _x, _y;
    int _count;
    int _indexA;

public:
    Boss1BeforeScene() {}
    ~Boss1BeforeScene() {}

public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
};