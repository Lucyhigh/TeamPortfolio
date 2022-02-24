#include "Stdafx.h"
#include "PlayerCharacter.h"

PlayerCharacter::PlayerCharacter() 
{ 
	ObjectUpdate = bind(&PlayerCharacter::update, this);
	ObjectRender = bind(&PlayerCharacter::render, this);
} 

PlayerCharacter::~PlayerCharacter() { } // ! DO NOTING

HRESULT PlayerCharacter::init(POINT point,vector<RECT*>floor)
{
	this->floor = floor;
	_Collider[BaseEnum::UNIT] = RectMakeCenter(400, 400, 100, 100); 
	_Collider[BaseEnum::UNIT].top--;
	_Collider[BaseEnum::UNIT].bottom--;
	_oldState = UnitState::UNITNULL;
	_state = UnitState::JUMP;
	_isMove = 0;
	_isLeft = 1;
	return S_OK;
}

void PlayerCharacter::release(void)
{
	// 애니메이션 굴리기 
}

void PlayerCharacter::update(void)
{
	GameNode::update();
	_updateFloor();

	// 슬라이드 -> if(슬라이드 != ) { 명령어 } else { 다른명령어 }
	// 슬라이드 펑션 <= 
	
	if (_updateHit())
	{ _updateSide(); _inputUpdate(); return; }

	_updateMove();
	_state = _inputKey(_updateSide());
	_inputUpdate();
	_inputAnimation();
}

void PlayerCharacter::render(void)
{
	Rectangle(getMemDC(), _Collider[BaseEnum::UNIT].left, _Collider[BaseEnum::UNIT].top, _Collider[BaseEnum::UNIT].right, _Collider[BaseEnum::UNIT].bottom);

	for (int i = 0; i < smash.size(); i++)
	{ Rectangle(getMemDC(), smash[i].first.left, smash[i].first.top, smash[i].first.right, smash[i].first.bottom); }
}
// ! 키보드 입력
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
		}
		else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{ 
			if (_state < UnitState::ATTACK)
			{ _isLeft = 1; }

			if (updateSide != 1)
			{ _isMove = 1; }
			else
			{ _isMove = 0; }
		}
		else
		{ _isMove = 0; }
	}
	else
	{ _isMove = 0; }

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _state != UnitState::JUMP&& _state < UnitState::ATTACK && _isLook != -1)
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
	else if (KEYMANAGER->isOnceKeyDown('D') && _state != UnitState::JUMPATTACK && _state != UnitState::PARING && _state != UnitState::JUMP)
	{
		_oldState = _state;
		smash.clear();
		_slide["Max"] = 200 + GetTickCount();
		return UnitState::SLIDE;
	}

	if (_state < UnitState::JUMP && _isMove == false)
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

void PlayerCharacter::_inputAnimation()
{
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
	_Collider[BaseEnum::UNIT].left += _isLeft * (GAMESPEED*3);
	_Collider[BaseEnum::UNIT].right += _isLeft *( GAMESPEED*3);

	_slide["State"] = GetTickCount();
	if (_slide["State"] >= _slide["Max"])
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
			for (auto iter = _jump.begin(); iter != _jump.end(); ++iter)
			{ iter->second = 0; }
		}
	}
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
		smash.push_back // 좌  
		(pair<RECT, Image*>{ RectMakeCenter(mid.x - 40, mid.y - 50, 10, 10), new Image });
		smash.push_back // 중앙 
		(pair<RECT, Image*>{ RectMakeCenter(mid.x, mid.y -75, 10, 10), new Image });
		smash.push_back // 우
		(pair<RECT, Image*>{ RectMakeCenter(mid.x +40, mid.y -50, 10, 10), new Image });
	}
}

bool PlayerCharacter::_updateHit()
{
	static int a = 0;
	// 안맞앗다!
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




