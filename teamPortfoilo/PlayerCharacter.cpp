#include "Stdafx.h"
#include "Animation.h"

PlayerCharacter::PlayerCharacter() 
{ 
	ObjectInit = bind(&PlayerCharacter::init, this, std::placeholders::_1, std::placeholders::_2);
	ObjectrRelease = bind(&PlayerCharacter::release, this);
	ObjectUpdate = bind(&PlayerCharacter::update, this);
	ObjectRender = bind(&PlayerCharacter::render, this);
} 

PlayerCharacter::~PlayerCharacter() { } // ! DO NOTING

HRESULT PlayerCharacter::init(POINT point,vector<RECT*>floor)
{
    
	this->floor = floor;
    point.x = 400;
    point.y = CENTER_Y;
	_Collider[BaseEnum::UNIT] = RectMakeCenter(point.x, point.y,50,60);
	_Collider[BaseEnum::UNIT].top--;
	_Collider[BaseEnum::UNIT].bottom--;
	_oldState = UnitState::UNITNULL;
	_state = UnitState::JUMP;
	_isMove = 0;
	_isLeft = 1;
	_imageAni.second = new Animation;
	_imageAni.first = false;

	return S_OK;
}

void PlayerCharacter::release(void)
{
	// ¾Ö´Ï¸ÞÀÌ¼Ç ±¼¸®±â 
}

void PlayerCharacter::update(void)
{
	GameNode::update();
	_updateFloor();

	if (_updateHit())
	{ _updateSide();  _inputUpdate(); return; }

	_updateMove();
	_state = _inputKey(_updateSide());
	_inputUpdate();
	_inputAnimation();
}

void PlayerCharacter::render(void)
{
	HPEN hpen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	HPEN hpenOld = (HPEN)::SelectObject(getMemDC(), (HGDIOBJ)hpen);
	HBRUSH myBrush = (HBRUSH)GetStockObject(NULL_BRUSH);
	HBRUSH oldBrush = (HBRUSH)SelectObject(getMemDC(), myBrush);
	Rectangle(getMemDC(), _Collider[BaseEnum::UNIT].left, _Collider[BaseEnum::UNIT].top, _Collider[BaseEnum::UNIT].right, _Collider[BaseEnum::UNIT].bottom);
	SelectObject(getMemDC(), oldBrush);
	DeleteObject(myBrush);
	hpen = (HPEN)::SelectObject(getMemDC(), hpenOld);

	//if (_imageAni.first) { _image->aniRender(getMemDC(), _image->getX(), _image->getY(), _imageAni.second); }
	
	for (int i = 0; i < smash.size(); i++)
	{ Rectangle(getMemDC(), smash[i].first.left, smash[i].first.top, smash[i].first.right, smash[i].first.bottom); }

	if (_image != nullptr)
	{ _image->frameRender(getMemDC(),_image->getX(),_image->getY(), _image->getFrameX(), _image->getFrameY()); }


}
// ! Å°º¸µå ÀÔ·Â
PlayerCharacter::UnitState PlayerCharacter::_inputKey(int updateSide)
{
	if (_state == UnitState::PARING)
	{
		_isMove = 0;
		return _state;
	}

	if(_state < UnitState::ATTACK )
	{ 
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{ _isLook = 1; }
		else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{ _isLook = -1; }
		else
		{ _isLook = 0; }
	}

	if (UnitState::SLIDE != _state && _state < UnitState::ATTACK && _state != UnitState::DOWNATTACK && _isLook != -1)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			if (_state < UnitState::ATTACK)
			{ _isLeft = -1; }

			if (updateSide != -1 )
			{ _isMove = -1; }
			else
			{ _isMove = 0; }

			if(_state != UnitState::JUMP && _state != UnitState::JUMPATTACK && _state != UnitState::JUMPATTACK_DOUBLE)
			{ 
				_oldState = _state;
				_state = UnitState::RUN; 
			}
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{ 
			if (_state < UnitState::ATTACK)
			{ _isLeft = 1; }

			if (updateSide != 1)
			{ _isMove = 1; }
			else
			{ _isMove = 0; }

			if(_state != UnitState::JUMP && _state != UnitState::JUMPATTACK && _state != UnitState::JUMPATTACK_DOUBLE)
			{ 
				_oldState = _state;
				_state = UnitState::RUN; 
			}
		}
		else
		{ _isMove = 0; }
	}
	else
	{ _isMove = 0; }

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _state != UnitState::JUMP && _state < UnitState::ATTACK && _isLook != -1)
	{
		_oldState = _state;
		_jump["Weight"] =11.0f;
		return UnitState::JUMP;
	}
	else if (KEYMANAGER->isOnceKeyDown('A'))
	{
		if (_oldState == UnitState::ATTACK)
		{ return UnitState::ATTACK_DOUBLE; }
		else if (_oldState == UnitState::JUMPATTACK)
		{ return UnitState::JUMPATTACK_DOUBLE; }

		if (_state < UnitState::SLIDE)
		{
			_oldState = _state;
			if (_state == UnitState::JUMP)
			{ return UnitState::JUMPATTACK; }
			else if (_isLook == 1)
			{ return UnitState::UPATTACK; }
			else if (_isLook == -1)
			{ return UnitState::DOWNATTACK; }
			else
			{ return UnitState::ATTACK; }
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
		return UnitState::IDLE_0;
	}
	else return _state;
}

void PlayerCharacter::_inputUpdate()
{
	if (_state == UnitState::JUMP || _state == UnitState::JUMPATTACK || _state == UnitState::JUMPATTACK_DOUBLE)
	{ _updataJump(); }
	if ( _state >= UnitState::JUMPATTACK)
	{ _updateAttack(); }
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
		{ _state = UnitState::JUMP; }
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
							_Collider[BaseEnum::UNIT].right+GAMESPEED, _Collider[BaseEnum::UNIT].bottom - GAMESPEED };
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
	_Collider[BaseEnum::UNIT].left += _isMove * GAMESPEED;
	_Collider[BaseEnum::UNIT].right += _isMove * GAMESPEED;
}

void PlayerCharacter::_updataJump()
{ 
	_jump["Weight"] += -1 * 0.3f;
	_Collider[BaseEnum::UNIT].top += -1 * _jump["Weight"];
	_Collider[BaseEnum::UNIT].bottom += -1 * _jump["Weight"];
	_jump["Unit"] += -1 * _jump["Weight"];

	RECT tamp;
	for (int i = 0; i < floor.size(); i++)
	{
		if (IntersectRect(&tamp, &_Collider[BaseEnum::UNIT], floor[i]))
		{			
			_oldState = _state;
 	 		_state = UnitState::UNITNULL;
			IMAGEMANAGER->findImage("²¿±òÁ¡ÇÁ")->setFrameX(0);
			for (auto iter = _jump.begin(); iter != _jump.end(); ++iter)
			{ iter->second = 0; }
		}
	}
}

void PlayerCharacter::setPlayerPosX(float x)
{
   // point.x = x;
}
void PlayerCharacter::setPlayerPosY(float y)
{
   // point.y = y;
}

RECT PlayerCharacter::getPlayerRect()
{
    return _rcPlayer;
}

void PlayerCharacter::setCameraRect(RECT rect)
{
    _cameraRect = rect;
}

void PlayerCharacter::_updateAttack()
{
	POINT mid;
	if(_isLook != 1)
	{ 
		smash.clear();
		mid = {0, _Collider[BaseEnum::UNIT].top + ((_Collider[BaseEnum::UNIT].bottom - _Collider[BaseEnum::UNIT].top) / 2) };
		if (_isLeft != 1)
		{ mid.x = _Collider[BaseEnum::UNIT].left; }
		else
		{ mid.x = _Collider[BaseEnum::UNIT].right; }

		if (_isLook != -1)
		{
			smash.push_back
			(pair<RECT, Image*>{ RectMakeCenter(mid.x, _Collider[BaseEnum::UNIT].top - 20, 10, 10) , new Image });
			smash.push_back
			(pair<RECT, Image*>{  RectMakeCenter(mid.x + (_isLeft * 50), _Collider[BaseEnum::UNIT].top, 10, 10), new Image });
		}
		smash.push_back
		(pair<RECT, Image*>{ RectMakeCenter(mid.x + (_isLeft * 75), mid.y, 10, 10), new Image });
		smash.push_back
		(pair<RECT, Image*>{ RectMakeCenter(mid.x + (_isLeft * 50), _Collider[BaseEnum::UNIT].bottom, 10, 10), new Image });
	}
	else
	{
		mid = { _Collider[BaseEnum::UNIT].left+ ((_Collider[BaseEnum::UNIT].right - _Collider[BaseEnum::UNIT].left) / 2)  , _Collider[BaseEnum::UNIT].top  };
		smash.push_back // ÁÂ  
		(pair<RECT, Image*>{ RectMakeCenter(mid.x - 40, mid.y - 50, 10, 10), new Image });
		smash.push_back // Áß¾Ó 
		(pair<RECT, Image*>{ RectMakeCenter(mid.x, mid.y -75, 10, 10), new Image });
		smash.push_back // ¿ì
		(pair<RECT, Image*>{ RectMakeCenter(mid.x +40, mid.y -50, 10, 10), new Image });
	}
}

bool PlayerCharacter::_updateHit()
{
	static int a = 0;
	// ¾È¸Â¾Ñ´Ù!
	if (_isHit == 0 || _state == UnitState::SLIDE ) { return false; }

	if (a == 0)
	{
		smash.clear();
		_jump["Weight"] = 2;
		_state = UnitState::JUMP;
	}
	
	_Collider[BaseEnum::UNIT].left -= _isLeft * GAMESPEED/2;
	_Collider[BaseEnum::UNIT].right -= _isLeft * GAMESPEED/2;

	if (a >= 30)
	{
		_hp[BaseEnum::STATE] -= _isHit;
		_isHit = 0;
		a = 0;
		return true;
	}
	a ++;
}


void PlayerCharacter::_inputAnimation()
{
    float cameraLeft = _Collider[BaseEnum::UNIT].left - _cameraRect.left;
    float cameraTop =  _Collider[BaseEnum::UNIT].top - _cameraRect.top;


	if (_state == UnitState::SLIDE)
	{
		_image = IMAGEMANAGER->findImage("²¿±ò½½¶óÀÌµå");
		
		_image->setY(_Collider[BaseEnum::UNIT].top-9);
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
	if (_state == UnitState::JUMP)
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
		{ _image->setFrameX(_image->getFrameX() + 1); }

		return;
	}
	else if (_state == UnitState::RUN)
	{ 
		_image = IMAGEMANAGER->findImage("²¿±òÀÌµ¿");
		if (_isLeft != -1)
		{ _image->setX(cameraLeft - 10); }
		else
		{ _image->setX(cameraLeft +5); }
		_image->setY(cameraTop - 14);

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
		{ _image->setFrameX(0); }
		else
		{ _image->setFrameX(_image->getFrameX() + 1); }

		if (_isLeft != -1)
		{ _image->setFrameY(0); }
		else
		{ _image->setFrameY(1); }
	}
}



