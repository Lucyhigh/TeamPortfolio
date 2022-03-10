#pragma once
#include "GameNode.h"

class Camera : public GameNode
{
private:
    POINT _trace;
    RECT _screen;
    int _count;
    float _leftLimit;
    float _rightLimit;
    float _topLimit;
    float _bottomLimit;

public:
    Camera();
    ~Camera() {}
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);

    POINT getCameraPos();
    void setCameraPos(POINT cameraPos);

    RECT getScreenRect();
    void setScreenRect(RECT screenRect);

    void setLimitsX(float leftLimit, float rightLimit);
    void setLimitsY(float topLimit, float bottomLimit);
};