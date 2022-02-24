#pragma once
#include "SingletonBase.h"
class Camera : publuc SingletonBase<Camera>
{
private:
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
public:
    Camera() {}
    ~Camera() {}
};