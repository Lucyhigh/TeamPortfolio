#include "Stdafx.h"
#include "PixelCollision.h"

HRESULT PixelCollision::init(float x, float y, char* image)
{
	_playerIdleImage = IMAGEMANAGER->findImage("������");
	_playerMoveImage = IMAGEMANAGER->findImage("�����̵�");
	_playerWakeUpImage = IMAGEMANAGER->findImage("������");
	_bgImage = IMAGEMANAGER->findImage(image);

	_ani = new Animation;
	_ani2 = new Animation;
	_ani3 = new Animation;

	_ani->init(_playerIdleImage->getWidth(), _playerIdleImage->getHeight(), 128,73);
	_ani2->init(_playerMoveImage->getWidth(), _playerMoveImage->getHeight(), 79,70);
	_ani3->init(_playerWakeUpImage->getWidth(), _playerWakeUpImage->getHeight(), 128,128);
	_ani->setFPS(7);
	_ani->setPlayFrame(0, 12, false, true);

	_ani2->setFPS(7);
	_ani2->setPlayFrame(0, 13, false, true);

	_ani3->setFPS(7);
	_ani3->setDefPlayFrame(false, false);

	_isWalk = false;
	_isLeft = false;
	_isWakeUp = false;
	_speed = 3.0f;

	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, _playerIdleImage->getWidth(), _playerIdleImage->getHeight());
	return S_OK;
}
void PixelCollision::release(void)
{
	_ani->release();
	SAFE_DELETE(_ani);
	_ani2->release();
	SAFE_DELETE(_ani2);
	_ani3->release();
	SAFE_DELETE(_ani3);
}

void PixelCollision::update(char* image)
{
	if (KEYMANAGER->isOnceKeyDown('K'))
	{
		_ani3->AniStart();
		_count = 1;
	}
	_ani3->frameUpdate(TIMEMANAGER->getElapsedTime() * 0.4);

	if (_count >= 1 && _isWakeUp == false)
	{
		_count++;
		if (_count > 1000)
		{
			_ani->AniStart();
			_ani2->AniStart();
			_isWakeUp = true;
		}
	}

	if (_isWakeUp)
	{
		_ani->frameUpdate(TIMEMANAGER->getElapsedTime() * 0.4);
		_ani2->frameUpdate(TIMEMANAGER->getElapsedTime() * 0.4);
		if (KEYMANAGER->isStayKeyDown('D'))
		{
			_isLeft = false;
			_isWalk = true;
			_x += _speed;
		}
		else if (KEYMANAGER->isStayKeyDown('A'))
		{
			_isLeft = true;
			_isWalk = true;
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
		else if (!_isLeft)
		{
			_ani->setPlayFrame(0, 12, false, true);
			_ani2->setPlayFrame(0, 13, false, true);
		}

		int bgHeight = _bgImage->getHeight() / 2 + _y;
		_probeY = _y + _playerIdleImage->getFrameHeight() / 2;

		for (int i = _probeY - 30; i < _probeY + 30; i++)
		{
			COLORREF color = GetPixel(IMAGEMANAGER->findImage(image)->getMemDC(), _x, i);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			if (!(r == 255 && g == 0 && b == 255))
			{
				_y = i - _playerIdleImage->getFrameHeight() / 2;
				break;
			}
		}
		if (_isWalk)
			_rc = RectMakeCenter(_x, _y, _playerMoveImage->getFrameWidth(), _playerMoveImage->getFrameHeight());
		else
			_rc = RectMakeCenter(_x, _y, _playerIdleImage->getFrameWidth(), _playerIdleImage->getFrameHeight());
	}
	else
	{
		_rc = RectMakeCenter(_x, _y, _playerWakeUpImage->getFrameWidth(), _playerWakeUpImage->getFrameHeight());
	}

	//cout << _isWakeUp << endl;
}

void PixelCollision::render(void)
{
	float cameraX = _rc.left - _cameraRect.left;
	float cameraY = _rc.top + -_cameraRect.top;

	if (_isWakeUp)
	{
		if (_isWalk)
		{
			_playerMoveImage->aniRender(getMemDC(), cameraX, cameraY, _ani2);
		}
		else if (!_isWalk)
		{
			_playerIdleImage->aniRender(getMemDC(), cameraX, cameraY, _ani);
			cout << _ani->getFrame() << endl;
		}
	}
	else
	{
		_playerWakeUpImage->aniRender(getMemDC(), cameraX, cameraY-14, _ani3);
	}

	//cout << rcCenterX << endl;
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

bool PixelCollision::getWakeUp()
{
	return _isWakeUp;
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
