#pragma once
#include "GameNode.h"
#include "PixelCollision.h"
#include "Camera.h"
class PixelScene : public GameNode
{
private:
	Camera* _camera;
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

