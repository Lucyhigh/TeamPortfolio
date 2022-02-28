#include "Stdafx.h"
#include "PixelCollision.h"

HRESULT PixelCollision::init(void)
{
	_playerIdleImage = IMAGEMANAGER->findImage("²¿±ò´ë±â");// 1664, 146, 13, 2
	_playerMoveImage = IMAGEMANAGER->findImage("²¿±òÀÌµ¿");// 1106, 140, 14, 2

	_ani = new Animation;
	_ani2 = new Animation;

	_ani->init(_playerIdleImage->getWidth(), _playerIdleImage->getHeight(), 128, 73);//´ë±â
	_ani2->init(_playerMoveImage->getWidth(), _playerMoveImage->getHeight(), 79, 70);//ÀÌµ¿

	//È®Àå¼ºÀ» À§ÇØ »ó¼öº¸´Ù º¯¼ö¸¦ ¾²¶óÇÞÁö¸¸ ¸®¼Ò½º¿£ ¿¹¿ÜÀÓ Æ¯È÷ ³ª´©±â °³¾ÈÁ¶À½
	_ani->setPlayFrame(0,12,false, true);
	_ani->setFPS(12);

	_ani2->setPlayFrame(0,13,false, true);
	_ani2->setFPS(12);

	_isWalk = false;
	_isLeft = false;
	_speed = 3.0f;
    _x = 300;//ÁÂÇ¥ÀÌ»ó
    _y = CENTER_Y;
	_rc = RectMakeCenter(_x, _y, _playerIdleImage->getWidth(), _playerIdleImage->getHeight());

    _probeY = _y + _playerIdleImage->getHeight()/ 2;
    return S_OK;
}

void PixelCollision::release(void)
{
	_ani->release();
	SAFE_DELETE(_ani);
	_ani2->release();
	SAFE_DELETE(_ani2);
}

void PixelCollision::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		_ani->AniStart();
		_ani2->AniStart();
	}
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isWalk = true;
		_isLeft = false;
		_x += _speed;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		_isWalk = true;
		_x -= _speed;
	}
	else
	{
		_isWalk = false;
	}
	/*if (_isLeft)
	{
		_ani->setPlayFrame(13, 25, false, true);
		_ani2->setPlayFrame(13, 25, false, true);
	}
	else
	{
		_ani->setPlayFrame(0, 12, false, true);
		_ani2->setPlayFrame(0, 13, false, true);
	}*/

    //YÃà Å½Áö
    _probeY = _y + _playerIdleImage->getHeight() / 2;
	Image* bgImage = IMAGEMANAGER->findImage("¿ÀÇÁ´×¾À ÇÈ¼¿");
	float bgHeight = bgImage->getHeight();
    for (int i = 0; i < bgHeight; i++)
    {
        COLORREF color = GetPixel(bgImage->getMemDC(), _x, i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255)
			|| i >= bgHeight - 1)
        {
			_y = _probeY = i;// -_playerIdleImage->getHeight() / 2;
            break;
        }
    }
   // GAMEMANAGER->getPlayer()->setCameraRect(_camera->getScreenRect());
	if(_isWalk)
		_rc = RectMakeCenter(_x, _y, _playerMoveImage->getFrameWidth(), _playerMoveImage->getFrameHeight());
	else
		_rc = RectMakeCenter(_x, _y, _playerIdleImage->getFrameWidth(), _playerIdleImage->getFrameHeight());
}

void PixelCollision::render(void)
{
	float cameraX = _rc.left - _cameraRect.left;
	float cameraY = _rc.top - _cameraRect.top;
	cout << _x << ", " << _y << endl;
	if (_isWalk)
	{
		_playerMoveImage->aniRender(getMemDC(), cameraX, cameraY, _ani);
		//IMAGEMANAGER->frameRender("²¿±òÀÌµ¿", getMemDC(), _rc.left, _rc.top);
	}
	else
	{
		_playerIdleImage->aniRender(getMemDC(), cameraX, cameraY, _ani2);
		//IMAGEMANAGER->frameRender("²¿±ò´ë±â", getMemDC(), _rc.left, _rc.top);
	}

    if (KEYMANAGER->isToggleKey(VK_F1))
    {
        Rectangle(getMemDC(), _x, _probeY, _x + 10, _probeY + 10);
    }
}

int PixelCollision::getX()
{
	return _x;
}

int PixelCollision::getY()
{
	return _y;
}

void PixelCollision::setX(int x)
{
	_x = x;
}

float PixelCollision::getPlayerPosX()
{
	return _x;
}

void PixelCollision::setPlayerPosX(float x)
{
	_x = x;
}

void PixelCollision::setPlayerPosY(float y)
{
	_y = y;
}

RECT PixelCollision::getPlayerRect()
{
	return _rc;
}

void PixelCollision::setCameraRect(RECT rect)
{
	_cameraRect = rect;
}
