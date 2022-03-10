#include "Stdafx.h"
#include "Camera.h"

Camera::Camera()
{
    _trace.x = CENTER_X;
    _trace.y = CENTER_Y;
    _count = 0;

    _screen = RectMakeCenter(_trace.x, _trace.y, WINSIZE_X, WINSIZE_Y);
    _leftLimit = CENTER_X;
}

HRESULT Camera::init(void)
{
    return S_OK;
}

void Camera::release(void)
{

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

void Camera::setLimitsX(float leftLimit, float rightLimit)
{
    _leftLimit = leftLimit;
    _rightLimit = rightLimit - CENTER_X;
}

void Camera::setLimitsY(float topLimit, float bottomLimit)
{
    _topLimit = topLimit;
    _bottomLimit = bottomLimit - CENTER_Y;
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
    _trace.y = _trace.y < _topLimit ? _topLimit : _trace.y;
    _trace.y = _trace.y > _bottomLimit ? _bottomLimit : _trace.y;
}