#pragma once
<<<<<<< HEAD
#include "SingletonBase.h"
class Camera : public SingletonBase<Camera>
{
private:
   // POINT 
=======
#include "GameNode.h"

class Camera : public GameNode
{
private:
    POINT _trace;
    RECT _screen;
    int _count;
    float _leftLimit;
    float _rightLimit;

>>>>>>> origin/SongYeeun-camera
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
<<<<<<< HEAD
public:
    Camera() {}
=======

    POINT getCameraPos();
    void setCameraPos(POINT cameraPos);

    RECT getScreenRect();
    void setScreenRect(RECT screenRect);

    void setLimits(float leftLimit, float rightLimit);

public:
    Camera();
>>>>>>> origin/SongYeeun-camera
    ~Camera() {}
};