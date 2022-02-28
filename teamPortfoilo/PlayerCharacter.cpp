#include "Stdafx.h"
#include "PlayerCharacter.h"
#include "Animation.h"

PlayerCharacter::UnitState PlayerCharacter::getState()
{
	return _state;
}

PlayerCharacter::PlayerCharacter()
{
	ObjectInit = bind(&PlayerCharacter::init, this, std::placeholders::_1, std::placeholders::_2);
	ObjectrRelease = bind(&PlayerCharacter::release, this);
	ObjectUpdate = bind(&PlayerCharacter::update, this);
	ObjectRender = bind(&PlayerCharacter::render, this);

	_hp[BaseEnum::STATE] = 1;
	_hp[BaseEnum::MAX] = 136;
	_mp[BaseEnum::STATE] = 96;
	_mp[BaseEnum::MAX] = 96;
}

PlayerCharacter::~PlayerCharacter() { } // ! DO NOTING

HRESULT PlayerCharacter::init(POINT point, vector<RECT*>floor)
{
	this->floor = floor;
	point.x = 400;
	point.y = CENTER_Y;

	_Collider[BaseEnum::UNIT] = RectMakeCenter(point.x, point.y, 50, 60);
	_Collider[BaseEnum::UNIT].top--;
	_Collider[BaseEnum::UNIT].bottom--;
	_oldState = UnitState::UNITNULL;
	_state = UnitState::JUMP;
	_isMove = 0;
	_isLeft = 1;
	_imageAni.second = new Animation;
	_imageAni.first = false;
	_effect = nullptr;



	return S_OK;
}

void PlayerCharacter::release(void)
{

}

void PlayerCharacter::update(void)
{
	GameNode::update();
	_updateFloor();

	if (_updateHit())
	{
		_updateSide();  _inputUpdate(); return;
	}

	_updateMove();
	_state = _inputKey(_updateSide());
	_inputUpdate();
	_inputAnimation();
	//_smashRender();
}

void PlayerCharacter::render(void)
{
	HPEN hpen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
	HPEN hpenOld = (HPEN)::SelectObject(getMemDC(), (HGDIOBJ)hpen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);

	float left = _Collider[BaseEnum::UNIT].left - _cameraRect.left;
	float top = _Collider[BaseEnum::UNIT].top - _cameraRect.top;
	float right = _Collider[BaseEnum::UNIT].right - _cameraRect.left;
	float bottom = _Collider[BaseEnum::UNIT].bottom - _cameraRect.top;

	Rectangle(getMemDC(), left, top, right, bottom);

	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
	hpen = (HPEN)::SelectObject(getMemDC(), hpenOld);

	for (int i = 0; i < smash.size(); i++)
	{
		Rectangle(getMemDC(), smash[i].first.left, smash[i].first.top, smash[i].first.right, smash[i].first.bottom);
	}

	if (_image != nullptr)
	{
		float imageX = _image->getX() - _cameraRect.left;
		float imageY = _image->getY() - _cameraRect.top;
		_image->frameRender(getMemDC(), imageX, imageY, _image->getFrameX(), _image->getFrameY());
	}
	if (_effect != nullptr)
	{
		float effectX = _effect->getX() - _cameraRect.left;
		float effectY = _effect->getY() - _cameraRect.top;
		_effect->frameRender(getMemDC(), effectX, effectY, _effect->getFrameX(), _effect->getFrameY());
	}
}

// ! Å°º¸µå ÀÔ·Â
PlayerCharacter::UnitState PlayerCharacter::_inputKey(int updateSide)
{
	if (_state == UnitState::PARING)
	{
		_isMove = 0;
		return _state;
	}

	if (_state < UnitState::ATTACK)
	{
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_isLook = 1;
		}
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_isLook = -1;
		}
		else
		{
			_isLook = 0;
		}
	}

	if (UnitState::SLIDE != _state && _state < UnitState::ATTACK && _state != UnitState::DOWNATTACK && _isLook != -1)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_state < UnitState::ATTACK)
			{
				_isLeft = -1;
			}

			if (updateSide != -1)
			{
				_isMove = -1;
			}
			else
			{
				_isMove = 0;
			}

			if (_state != UnitState::JUMP && _state != UnitState::JUMPATTACK && _state != UnitState::JUMPATTACK_DOUBLE)
			{
				_oldState = _state;
				_state = UnitState::RUN;
			}
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			if (_state < UnitState::ATTACK)
			{
				_isLeft = 1;
			}
			if (updateSide != 1)
			{
				_isMove = 1;
			}
			else
			{
				_isMove = 0;
			}

			if (_state != UnitState::JUMP && _state != UnitState::JUMPATTACK && _state != UnitState::JUMPATTACK_DOUBLE)
			{
				_oldState = _state;
				_state = UnitState::RUN;
			}
		}
		else
		{
			_isMove = 0;
		}
	}
	else
	{
		_isMove = 0;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _state != UnitState::JUMP && _state < UnitState::JUMPATTACK && _isLook != -1)
	{
		_oldState = _state;
		_jump["Weight"] = 4.0f;
		return UnitState::JUMP;
	}
	else if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_state == UnitState::ATTACK)// && smash.size() == 0)
		{
			_isAttack = false;
			if (_isLeft != -1)
			{
				IMAGEMANAGER->findImage("²¿±ò¾îÅÃ1")->setFrameX(0);
			}
			else
			{
				IMAGEMANAGER->findImage("²¿±ò¾îÅÃ1")->setFrameX(IMAGEMANAGER->findImage("²¿±ò¾îÅÃ1")->getMaxFrameX());
			}
			return UnitState::ATTACK_DOUBLE;
		}
		else if (_state == UnitState::ATTACK_DOUBLE)
		{
			_isAttack = false;
			if (_isLeft != -1)
			{
				IMAGEMANAGER->findImage("²¿±ò¾îÅÃ2")->setFrameX(0);
			}
			else
			{
				IMAGEMANAGER->findImage("²¿±ò¾îÅÃ2")->setFrameX(IMAGEMANAGER->findImage("²¿±ò¾îÅÃ2")->getMaxFrameX());
			}
			return UnitState::ATTACK_TRIPLE;
		}
		else if (_state == UnitState::JUMPATTACK)
		{
			_isAttack = false;
			IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ¾îÅÃÀÌÆåÆ®")->setFrameX(2);
			IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ¾îÅÃ")->setFrameX(4);
			return UnitState::JUMPATTACK_DOUBLE;
		}

		if (_state < UnitState::SLIDE)
		{
			_oldState = _state;
			_isAttack = false;
			if (_state == UnitState::JUMP)
			{
				IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ¾îÅÃÀÌÆåÆ®")->setFrameX(0);
				if (_isLeft != -1)
				{
					IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ¾îÅÃ")->setFrameX(0);
				}
				else
				{
					IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ¾îÅÃ")->setFrameX(IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ¾îÅÃ")->getMaxFrameX());
				}
				return UnitState::JUMPATTACK;
			}
			else if (_isLook == 1)
			{
				if (_isLeft != -1)
				{
					IMAGEMANAGER->findImage("²¿±ò»ó´Ü¾îÅÃ")->setFrameX(0);
				}
				else
				{
					IMAGEMANAGER->findImage("²¿±ò»ó´Ü¾îÅÃ")->setFrameX(IMAGEMANAGER->findImage("²¿±ò»ó´Ü¾îÅÃ")->getMaxFrameX());
				}
				return UnitState::UPATTACK;
			}
			else if (_isLook == -1)
			{
				return UnitState::DOWNATTACK;
			}
			else
			{
				_isAttack = false;
				if (_isLeft != -1)
				{
					IMAGEMANAGER->findImage("²¿±ò¾îÅÃ0")->setFrameX(0);
				}
				else
				{
					IMAGEMANAGER->findImage("²¿±ò¾îÅÃ0")->setFrameX(IMAGEMANAGER->findImage("²¿±ò¾îÅÃ0")->getMaxFrameX());
				}
				return UnitState::ATTACK;
			}
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('S') && _state == UnitState::IDLE_0 && _state == UnitState::IDLE_1 && _isLook != -1)
	{
		_oldState = _state;
		return UnitState::PARING;
	}
	else if (KEYMANAGER->isOnceKeyDown('D') && _state != UnitState::JUMPATTACK && _state != UnitState::PARING && _state != UnitState::JUMP && _state != UnitState::SLIDE)
	{
		_oldState = _state;
		smash.clear();
		_slide["Max"] = 0.5f + TIMEMANAGER->getWorldTime();
		IMAGEMANAGER->findImage("²¿±ò½½¶óÀÌµå")->setFrameX(0);
		return UnitState::SLIDE;
	}

	if (_state == UnitState::RUN && _isMove == 0 && updateSide != 0)
	{
		return UnitState::RUN;
	}
	else if (_state < UnitState::JUMP && _isMove == 0)
	{
		_oldState = _state;
		smash.clear();
		return UnitState::IDLE_0;
	}
	else return _state;
}

void PlayerCharacter::_inputUpdate()
{
	if (_state == UnitState::JUMP || _state == UnitState::JUMPATTACK || _state == UnitState::JUMPATTACK_DOUBLE)
	{
		_updataJump();
	}
	if (_state >= UnitState::JUMPATTACK)
	{
		_updateAttack();
	}
	else
	{
		switch (_state)
		{
		case UnitState::IDLE_0:
			break;
		case UnitState::SLIDE:
			_updateSlide(); break;
		}
	}
}

void PlayerCharacter::_updateFloor()
{
	RECT tamp[2] = { 0,0,0,0 };
	tamp[1] = { _Collider[BaseEnum::UNIT].left + 10, _Collider[BaseEnum::UNIT].bottom - 10,
			 _Collider[BaseEnum::UNIT].right - 10, _Collider[BaseEnum::UNIT].bottom };

	for (int i = 0; i < floor.size(); i++)
	{
		if (IntersectRect(&tamp[0], &tamp[1], floor[i]))
		{
			smash.clear();
			_Collider[BaseEnum::UNIT].top -= _Collider[BaseEnum::UNIT].bottom - tamp[0].top;
			_Collider[BaseEnum::UNIT].bottom -= _Collider[BaseEnum::UNIT].bottom - tamp[0].top;
			IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ")->setFrameX(0);
			stateFloor = *floor[i];
			break;
		}
	}

	tamp[1].bottom += GAMESPEED;
	if (!(IntersectRect(&tamp[0], &tamp[1], &stateFloor)))
	{
		if (_state < UnitState::JUMPATTACK)
		{
			_state = UnitState::JUMP;
		}
	}
}

int PlayerCharacter::_updateSide()
{
	RECT tamp[2];
	for (int i = 0; i < floor.size(); i++)
	{
		if (IntersectRect(&tamp[0], &_Collider[BaseEnum::UNIT], floor[i]))
		{
			tamp[1] = { _Collider[BaseEnum::UNIT].left - GAMESPEED, _Collider[BaseEnum::UNIT].top - GAMESPEED,
						_Collider[BaseEnum::UNIT].left, _Collider[BaseEnum::UNIT].bottom - GAMESPEED };

			if (IntersectRect(&tamp[0], &tamp[1], floor[i]))
			{
				_Collider[BaseEnum::UNIT].right += floor[i]->right - _Collider[BaseEnum::UNIT].left;
				_Collider[BaseEnum::UNIT].left += floor[i]->right - _Collider[BaseEnum::UNIT].left;
				return -1;
			}

			tamp[1] = { _Collider[BaseEnum::UNIT].right, _Collider[BaseEnum::UNIT].top - GAMESPEED,
						_Collider[BaseEnum::UNIT].right + GAMESPEED, _Collider[BaseEnum::UNIT].bottom - GAMESPEED };
			if (IntersectRect(&tamp[0], &tamp[1], floor[i]))
			{
				_Collider[BaseEnum::UNIT].left -= _Collider[BaseEnum::UNIT].right - floor[i]->left;
				_Collider[BaseEnum::UNIT].right -= _Collider[BaseEnum::UNIT].right - floor[i]->left;
				return 1;
			}
		}
	}
	return 0;
}

void PlayerCharacter::_updateSlide()
{
	_Collider[BaseEnum::UNIT].left += _isLeft * (GAMESPEED * 1.4f);
	_Collider[BaseEnum::UNIT].right += _isLeft * (GAMESPEED * 1.4f);

	_slide["State"] = TIMEMANAGER->getWorldTime();
	if (_slide["State"] >= _slide["Max"] || _updateSide() != 0)
	{
		_oldState = _state;
		_state = UnitState::UNITNULL;
	}
}

void PlayerCharacter::_updateMove()
{
	_Collider[BaseEnum::UNIT].left += (_isMove * GAMESPEED);
	_Collider[BaseEnum::UNIT].right += (_isMove * GAMESPEED);
}

void PlayerCharacter::_updataJump()
{
	_jump["Weight"] += -1 * 0.05f;
	_Collider[BaseEnum::UNIT].top += -1 * _jump["Weight"];
	_Collider[BaseEnum::UNIT].bottom += -1 * _jump["Weight"];
	_jump["Unit"] += -1 * _jump["Weight"];

	RECT tamp;
	for (int i = 0; i < floor.size(); i++)
	{
		if (IntersectRect(&tamp, &_Collider[BaseEnum::UNIT], floor[i]))
		{
			if (_state == UnitState::JUMPATTACK || _state == UnitState::JUMPATTACK_DOUBLE)
			{
				_effect = nullptr;
			}

			_oldState = _state;
			_state = UnitState::UNITNULL;
			IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ")->setFrameX(0);

			for (auto iter = _jump.begin(); iter != _jump.end(); ++iter)
			{
				iter->second = 0;
			}
		}
	}
}

void PlayerCharacter::setCameraRect(RECT rect)
{
	_cameraRect = rect;
}

void PlayerCharacter::_updateAttack()
{
	POINT mid;

	if (_isAttack == true)
	{
		return;
	}

	long left = _Collider[BaseEnum::UNIT].left - _cameraRect.left;
	long top = _Collider[BaseEnum::UNIT].top - _cameraRect.top;
	long right = _Collider[BaseEnum::UNIT].right - _cameraRect.left;
	long bottom = _Collider[BaseEnum::UNIT].bottom - _cameraRect.top;

	if (_isLook != 1)
	{
		smash.clear();
		mid = { 0, top + ((bottom - top) / 2) };
		if (_isLeft != 1)
		{
			mid.x = left;
		}
		else
		{
			mid.x = right;
		}

		if (_isLook != -1)
		{
			smash.push_back
			(pair<RECT, Image>{ RectMakeCenter(mid.x, top - 20, 10, 10), Image() });
			smash.push_back
			(pair<RECT, Image>{  RectMakeCenter(mid.x + (_isLeft * 50), top, 10, 10), Image() });
		}
		smash.push_back
		(pair<RECT, Image>{ RectMakeCenter(mid.x + (_isLeft * 75), mid.y, 10, 10), Image() });
		smash.push_back
		(pair<RECT, Image>{ RectMakeCenter(mid.x + (_isLeft * 50), bottom, 10, 10), Image() });
	}
	else
	{
		mid = { left + ((right - left) / 2) , top };
		smash.push_back // ÁÂ  
		(pair<RECT, Image>{ RectMakeCenter(mid.x - 40, mid.y - 50, 10, 10), Image() });
		smash.push_back // Áß¾Ó 
		(pair<RECT, Image>{ RectMakeCenter(mid.x, mid.y - 75, 10, 10), Image() });
		smash.push_back // ¿ì
		(pair<RECT, Image>{ RectMakeCenter(mid.x + 40, mid.y - 50, 10, 10), Image() });
	}
}

bool PlayerCharacter::_updateHit()
{
	static int a = 0;
	// ¾È¸Â¾Ñ´Ù!
	if (_isHit == 0 || _state == UnitState::SLIDE) { return false; }

	if (a == 0)
	{
		_jump["Weight"] = 2;
		_state = UnitState::JUMP;
	}

	_Collider[BaseEnum::UNIT].left -= _isLeft * GAMESPEED / 2;
	_Collider[BaseEnum::UNIT].right -= _isLeft * GAMESPEED / 2;

	if (a >= 30)
	{
		_hp[BaseEnum::STATE] -= _isHit;
		_isHit = 0;
		a = 0;
		return true;
	}
	a++;
}

void PlayerCharacter::_inputAnimation()
{
	if (_state == UnitState::SLIDE)
	{
		_image = IMAGEMANAGER->findImage("²¿±ò½½¶óÀÌµå");
		_image->setY(_Collider[BaseEnum::UNIT].top - 9);

		if (_isLeft != -1)
		{
			_image->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left - 27);
		}
		else
		{
			_image->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left);
		}

		if (0.02f + _Fram >= TIMEMANAGER->getWorldTime()) { return; }
		_Fram = TIMEMANAGER->getWorldTime();

		if (_image->getFrameX() <= _image->getMaxFrameX())
		{
			_image->setFrameX(_image->getFrameX() + 1);
		}

		return;
	}
	else if (_state == UnitState::ATTACK)
	{
		_image = IMAGEMANAGER->findImage("²¿±ò¾îÅÃ0");

		_image->setY(_Collider[BaseEnum::UNIT].top - 10);

		if (_isLeft != -1)
		{
			_image->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left - 15);
		}
		else
		{
			_image->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left - 75);
		}

		if (0.02f + _Fram >= TIMEMANAGER->getWorldTime()) { return; }
		_Fram = TIMEMANAGER->getWorldTime();

		if (_isLeft != -1)
		{
			if (_image->getFrameX() < _image->getMaxFrameX())
			{
				_image->setFrameX(_image->getFrameX() + 1);
			}
			else
			{
				smash.clear();
				_state = UnitState::IDLE_0;
			}
		}
		else
		{
			if (_image->getFrameX() >= 0)
			{
				_image->setFrameX(_image->getFrameX() - 1);
			}
			else
			{
				smash.clear();
				_state = UnitState::IDLE_0;
			}
		}
		return;
	}
	else if (_state == UnitState::ATTACK_DOUBLE)
	{
		_image = IMAGEMANAGER->findImage("²¿±ò¾îÅÃ1");

		_image->setY(_Collider[BaseEnum::UNIT].top - 10);

		if (_isLeft != -1)
		{
			_image->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left - 15);
		}
		else
		{
			_image->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left - 75);
		}

		if (0.05f + _Fram >= TIMEMANAGER->getWorldTime()) { return; }
		_Fram = TIMEMANAGER->getWorldTime();

		if (_isLeft != -1)
		{
			if (_image->getFrameX() < _image->getMaxFrameX())
			{
				_image->setFrameX(_image->getFrameX() + 1);
			}
			else
			{
				smash.clear();
				_state = UnitState::IDLE_0;
			}
		}
		else
		{
			if (_image->getFrameX() >= 0)
			{
				_image->setFrameX(_image->getFrameX() - 1);
			}
			else
			{
				smash.clear();
				_state = UnitState::IDLE_0;
			}
		}
		return;
	}
	else if (_state == UnitState::ATTACK_TRIPLE)
	{
		_image = IMAGEMANAGER->findImage("²¿±ò¾îÅÃ2");

		_image->setY(_Collider[BaseEnum::UNIT].top - 24);

		if (_isLeft != -1)
		{
			_image->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left - 15);
		}
		else
		{
			_image->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left - 140);
		}

		if (0.02f + _Fram >= TIMEMANAGER->getWorldTime()) { return; }
		_Fram = TIMEMANAGER->getWorldTime();


		if (_isLeft != -1)
		{
			if (_image->getFrameX() < _image->getMaxFrameX())
			{
				_image->setFrameX(_image->getFrameX() + 1);
			}
			else
			{
				smash.clear();
				_state = UnitState::IDLE_0;
			}
		}
		else
		{
			if (_image->getFrameX() >= 0)
			{
				_image->setFrameX(_image->getFrameX() - 1);
			}
			else
			{
				smash.clear();
				_state = UnitState::IDLE_0;
			}
		}
		return;
	}
	else if (_state == UnitState::UPATTACK)
	{
		_image = IMAGEMANAGER->findImage("²¿±ò»ó´Ü¾îÅÃ");
		_image->setY(_Collider[BaseEnum::UNIT].top - 10);

		if (_isLeft != -1)
		{
			_image->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left - 15);
		}
		else
		{
			_image->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left - 15);
		}

		if (0.02f + _Fram >= TIMEMANAGER->getWorldTime()) { return; }
		_Fram = TIMEMANAGER->getWorldTime();

		if (_isLeft != -1)
		{
			if (_image->getFrameX() < _image->getMaxFrameX())
			{
				_image->setFrameX(_image->getFrameX() + 1);
			}
			else
			{
				smash.clear();
				_state = UnitState::IDLE_0;
			}
		}
		else
		{
			if (_image->getFrameX() >= 0)
			{
				_image->setFrameX(_image->getFrameX() - 1);
			}
			else
			{
				smash.clear();
				_state = UnitState::IDLE_0;
			}
		}
		return;
	}
	else if (_state == UnitState::JUMPATTACK)
	{
		_image = IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ¾îÅÃ");
		_effect = IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ¾îÅÃÀÌÆåÆ®");

		_image->setY(_Collider[BaseEnum::UNIT].top - 30);
		_effect->setY(_Collider[BaseEnum::UNIT].top - 30);

		if (_isLeft != -1)
		{
			_image->setFrameY(0);
			_effect->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left - 35);
			_effect->setX(_Collider[BaseEnum::UNIT].left - 35);
		}
		else
		{
			_image->setFrameY(1);
			_effect->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left - 55);
			_effect->setX(_Collider[BaseEnum::UNIT].left - 55);
		}

		if (0.1f + _Fram >= TIMEMANAGER->getWorldTime()) { return; }
		_Fram = TIMEMANAGER->getWorldTime();

		if (_isLeft != -1)
		{
			if (_image->getFrameX() < 4)
			{
				_image->setFrameX(_image->getFrameX() + 1);

				if (_image->getFrameX() == 0 || _image->getFrameX() == 2)
				{
					_effect->setFrameX(_effect->getFrameX() + 1);
				}
			}
			else
			{
				smash.clear();
				_effect = nullptr;
				_state = UnitState::IDLE_0;
			}
		}
		else
		{
			if (_image->getFrameX() > 4)
			{
				_image->setFrameX(_image->getFrameX() - 1);

				if (_image->getFrameX() == 8 || _image->getFrameX() == 6)
				{
					_effect->setFrameX(_effect->getFrameX() + 1);
				}
			}
			else
			{
				smash.clear();
				_effect = nullptr;
				_state = UnitState::IDLE_0;
			}
		}
		return;
	}
	else if (_state == UnitState::JUMPATTACK_DOUBLE)
	{
		_image = IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ¾îÅÃ");
		_effect = IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ¾îÅÃÀÌÆåÆ®");

		_image->setY(_Collider[BaseEnum::UNIT].top - 30);
		_effect->setY(_Collider[BaseEnum::UNIT].top - 30);

		if (_isLeft != -1)
		{
			_image->setFrameY(0);
			_effect->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left - 35);
			_effect->setX(_Collider[BaseEnum::UNIT].left - 35);
		}
		else
		{
			_image->setFrameY(1);
			_effect->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left - 55);
			_effect->setX(_Collider[BaseEnum::UNIT].left - 55);
		}

		if (0.07f + _Fram >= TIMEMANAGER->getWorldTime()) { return; }
		_Fram = TIMEMANAGER->getWorldTime();

		if (_isLeft != -1)
		{
			if (_image->getFrameX() < 7)
			{
				_image->setFrameX(_image->getFrameX() + 1);
				if (_image->getFrameX() == 5 || _image->getFrameX() == 7)
				{
					_effect->setFrameX(_effect->getFrameX() + 1);
				}
			}
			else
			{
				smash.clear();
				_effect = nullptr;
				_state = UnitState::IDLE_0;
			}
		}
		else
		{
			if (_image->getFrameX() > 1)
			{
				_image->setFrameX(_image->getFrameX() - 1);

				if (_image->getFrameX() == 3 || _image->getFrameX() == 1)
				{
					_effect->setFrameX(_effect->getFrameX() + 1);
				}
			}
			else
			{
				smash.clear();
				_effect = nullptr;
				_state = UnitState::IDLE_0;
			}
		}
		return;
	}
	else if (_state == UnitState::JUMP)
	{
		_image = IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ");

		if (_isLeft != -1)
		{
			_image->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left - 35);
		}
		else
		{
			_image->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left);
		}
		_image->setY(_Collider[BaseEnum::UNIT].top - 14);

		if (0.1f + _Fram >= TIMEMANAGER->getWorldTime()) { return; }
		_Fram = TIMEMANAGER->getWorldTime();

		if (_image->getFrameX() <= _image->getMaxFrameX())
		{
			_image->setFrameX(_image->getFrameX() + 1);
		}

		return;
	}
	else if (_state == UnitState::RUN)
	{
		_image = IMAGEMANAGER->findImage("²¿±òÀÌµ¿");
		if (_isLeft != -1)
		{
			_image->setX(_Collider[BaseEnum::UNIT].left - 10);
		}
		else
		{
			_image->setX(_Collider[BaseEnum::UNIT].left + 5);
		}
		_image->setY(_Collider[BaseEnum::UNIT].top - 14);

		if (0.09f + _Fram >= TIMEMANAGER->getWorldTime()) { return; }
		_Fram = TIMEMANAGER->getWorldTime();

	}
	else if (_state == UnitState::IDLE_0)
	{
		if (0.02f + _Fram >= TIMEMANAGER->getWorldTime()) { return; }
		_Fram = TIMEMANAGER->getWorldTime();

		_image = IMAGEMANAGER->findImage("²¿±ò´ë±â");

		_image->setX(_Collider[BaseEnum::UNIT].left - 35);
		_image->setY(_Collider[BaseEnum::UNIT].top - 14);
	}

	if (_image != nullptr)
	{
		if (_image->getFrameX() >= _image->getMaxFrameX())
		{
			_image->setFrameX(0);
		}
		else
		{
			_image->setFrameX(_image->getFrameX() + 1);
		}

		if (_isLeft != -1)
		{
			_image->setFrameY(0);
		}
		else
		{
			_image->setFrameY(1);
		}
	}
}