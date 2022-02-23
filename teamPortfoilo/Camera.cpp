#include "Stdafx.h"
<<<<<<< HEAD
#include "Camera.h"
=======
#include "Camera.h"

Camera::Camera()
{
    _trace.x = 100;
    _trace.y = 400;
    _count = 0;

    _screen = RectMake(_trace.x, _trace.y, WINSIZE_X, WINSIZE_Y);
    _leftLimit = CENTER_X;
}

HRESULT Camera::init(void)
{
    return S_OK;
}

void Camera::release(void) {
}

void Camera::update(void)
{
    _screen = RectMakeCenter(_trace.x, _trace.y, WINSIZE_X, WINSIZE_Y);
}

void Camera::render(void)
{
    //카메라 크기 및 이동 확인용 렉트
    //Rectangle(getMemDC(),_screen.left,_screen.top,_screen.right,_screen.bottom);
}

RECT Camera::getScreenRect()
{
    return _screen;
}

void Camera::setScreenRect(RECT screenRect)
{
    _screen = screenRect;
}

void Camera::setLimits(float leftLimit, float rightLimit)
{
    _leftLimit = leftLimit;
    _rightLimit = rightLimit - CENTER_X;
}

POINT Camera::getCameraPos()
{
    return _trace;
}

void Camera::setCameraPos(POINT cameraPos)
{
    _trace = cameraPos;
    _trace.x = _trace.x < _leftLimit ? _leftLimit : _trace.x;
    _trace.x = _trace.x > _rightLimit ? _rightLimit : _trace.x;
}
>>>>>>> origin/SongYeeun-camera
