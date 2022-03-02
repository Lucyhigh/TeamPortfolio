#include "Stdafx.h"
#include "WheelMonster.h"

WheelMonster::WheelMonster()
{
	ObjectUpdate = bind(&WheelMonster::update, this);
	ObjectRender = bind(&WheelMonster::render, this);
}

WheelMonster::~WheelMonster() { }

HRESULT WheelMonster::init(POINT point, vector<RECT*> floor)
{
	this->floor = floor;
	_state = UnitState::END;
	_Collider[BaseEnum::UNIT] = RectMakeCenter(point.x, point.y, 100, 100);
	_Collider[BaseEnum::UNIT].top--;
	_Collider[BaseEnum::UNIT].bottom--;
	function<void()> _update;
	_update = std::bind(&WheelMonster::_updateIdle, this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&WheelMonster::_updateAttack, this);
	_pattenFunc.push_back(_update);

	return S_OK;
}

void WheelMonster::release(void)
{ }

void WheelMonster::update(void)
{
	_updateSide();
	_updateFloor();
	if (abs(MONSTER_CENTER - PLAYER_CENTER) < 150)
	{
		_state = UnitState::ATTACK;
		//오른쪽으로 공격
		if (MONSTER_CENTER - PLAYER_CENTER < 0)
		{
			_isLeft = 0;
		}
		//왼쪽으로 공격
		else if (MONSTER_CENTER - PLAYER_CENTER > 0)
		{
			_isLeft = 1;
		}
	}
	else if (abs(MONSTER_CENTER - PLAYER_CENTER) < 400)
	{
		_state = UnitState::MOVE;
		//오른쪽으로 이동 
		if (MONSTER_CENTER - PLAYER_CENTER < 0)
		{
			_isLeft = 0;
			_Collider[BaseEnum::UNIT].left += 10;
			_Collider[BaseEnum::UNIT].right += 10;
		}
		//왼쪽으로 이동
		else if (MONSTER_CENTER - PLAYER_CENTER > 0)
		{
			_isLeft = 1;
			_Collider[BaseEnum::UNIT].left -= 10;
			_Collider[BaseEnum::UNIT].right -= 10;
		}
	}
	else
	{
		_state = UnitState::IDLE;
	}
}

void WheelMonster::render(void)
{
	Rectangle(getMemDC(), _Collider[BaseEnum::UNIT].left, _Collider[BaseEnum::UNIT].top, _Collider[BaseEnum::UNIT].right, _Collider[BaseEnum::UNIT].bottom);
}

void WheelMonster::_updateFloor()
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
}

void WheelMonster::_updateLook()
{
}

int WheelMonster::_updateSide()
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

void WheelMonster::_inputPatten()
{

}

void WheelMonster::_inputAnimation()
{

}


void WheelMonster::_updateIdle()
{

}

void WheelMonster::_updateAttack()
{

}
