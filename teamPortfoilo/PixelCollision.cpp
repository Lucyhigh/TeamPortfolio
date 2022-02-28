#include "Stdafx.h"
#include "PixelCollision.h"

HRESULT PixelCollision::init(void)
{
	_playerIdleImage = IMAGEMANAGER->findImage("꼬깔대기");// 1664, 146, 13, 2
	_playerMoveImage = IMAGEMANAGER->findImage("꼬깔이동");// 1106, 140, 14, 2
	_bgImage = IMAGEMANAGER->findImage("오프닝씬 픽셀");

	_ani = new Animation;
	_ani2 = new Animation;

	_ani->init(_playerIdleImage->getWidth(), _playerIdleImage->getHeight(), 128, 73);//대기
	_ani2->init(_playerMoveImage->getWidth(), _playerMoveImage->getHeight(), 79, 70);//이동

	//확장성을 위해 상수보다 변수를 쓰라햇지만 리소스엔 예외임 특히 나누기 개안조음
	_ani->setDefPlayFrame(false,true);
	_ani->setFPS(6);

	//_ani2->setPlayFrame(0,13,false, true);
	_ani2->setDefPlayFrame(false,true);
	_ani2->setFPS(6);
	_ani->AniStart();
	_ani2->AniStart();
	_isWalk = false;
	_isLeft = false;
	_speed = 3.0f;
    _x = 1680;//좌표이상
    _y = 944;
	_rc = RectMakeCenter(_x, _y, _playerIdleImage->getWidth(), _playerIdleImage->getHeight());

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
	//cout << TIMEMANAGER->getElapsedTime() * 1 << endl;
	_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_isLeft = false;
		_isWalk = true;
		_ani->setPlayFrame(0, 12, false, true);
		_ani2->setPlayFrame(0, 13, false, true);
		_x += _speed;
	}
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_isLeft = true;
		_isWalk = true;
		_ani->setPlayFrame(13, 25, false, true);
		_ani2->setPlayFrame(14, 25, false, true);
		_x -= _speed;
	}
	else
	{
		_isWalk = false;
	}

	if (_isLeft)
	{
		_ani->setPlayFrame(13, 25, false, true);
		_ani2->setPlayFrame(14, 25, false, true);
	}
	else if(!_isLeft)
	{
		_ani->setPlayFrame(0, 12, false, true);
		_ani2->setPlayFrame(0, 13, false, true);
	}

	int bgHeight = _bgImage->getHeight() / 2 + _y;
	_probeY = _y + _playerIdleImage->getFrameHeight() / 2;

	for (int i = _probeY - 30; i < _probeY + 30; i++)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("오프닝씬 픽셀")->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - _playerIdleImage->getFrameHeight() / 2;
			break;
		}
	}
	if(_isWalk)
		_rc = RectMakeCenter(_x, _y, _playerMoveImage->getFrameWidth(), _playerMoveImage->getFrameHeight());
	else
		_rc = RectMakeCenter(_x, _y, _playerIdleImage->getFrameWidth(), _playerIdleImage->getFrameHeight());
}

void PixelCollision::render(void)
{
	float cameraX = _rc.left - _cameraRect.left;
	float cameraY = _rc.top+ - _cameraRect.top;
	//cout << _x << ", " << _y << endl;
	
	if (_isWalk)
	{
		_playerMoveImage->aniRender(getMemDC(), cameraX, cameraY, _ani2);
	}
	else
	{
		_playerIdleImage->aniRender(getMemDC(), cameraX, cameraY, _ani);
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
