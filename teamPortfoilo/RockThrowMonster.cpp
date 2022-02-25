#include "Stdafx.h"
#include "RockThrowMonster.h"


RockThrowMonster::RockThrowMonster()
{
	ObjectUpdate = bind(&RockThrowMonster::update, this);
	ObjectRender = bind(&RockThrowMonster::render, this);
}

RockThrowMonster::~RockThrowMonster() { }

HRESULT RockThrowMonster::init(POINT point, vector<RECT*> floor)
{
	speed = 2;
	angle = 0;
	_throw = false;
	this->floor = floor;
	_state = UnitState::END;
	_Collider[BaseEnum::UNIT] = RectMakeCenter(750, 550, 100, 100);
	_Collider[BaseEnum::UNIT].top--;
	_Collider[BaseEnum::UNIT].bottom--;
	function<void()> _update;
	_update = std::bind(&RockThrowMonster::_updateIdle, this);
	_pattenFunc.push_back(_update);

	return S_OK;
}

void RockThrowMonster::release(void)
{

}

void RockThrowMonster::update(void)
{
	_updateSide();
	_updateFloor();

	if (abs(MONSTER_CENTER - PLAYER_CENTER) < 200 && !_throw)
	{
		_state = UnitState::THROW;
		_rock();
		_throw = true;
	}
	else
	{
		_state = UnitState::IDLE;
	}


	_updateThrow();
	_delectRock();
}

void RockThrowMonster::render(void)
{
	Rectangle(getMemDC(), _Collider[BaseEnum::UNIT].left, _Collider[BaseEnum::UNIT].top, _Collider[BaseEnum::UNIT].right, _Collider[BaseEnum::UNIT].bottom);
	if (_throw)
	{
		Rectangle(getMemDC(), _rcRock.left, _rcRock.top, _rcRock.right, _rcRock.bottom);
	}
	cout << angle << endl;
}

void RockThrowMonster::_updateFloor()
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

void RockThrowMonster::_updateLook()
{
}

int RockThrowMonster::_updateSide()
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

void RockThrowMonster::_inputPatten()
{

}

void RockThrowMonster::_inputAnimation()
{
}


void RockThrowMonster::_updateIdle()
{
}

void RockThrowMonster::_updateThrow()
{
	_rcRock.left += cosl(angle) * speed;
	_rcRock.right += cosl(angle) * speed;
	_rcRock.top -= sinl(angle) * speed;
	_rcRock.bottom -= sinl(angle) * speed;
}

void RockThrowMonster::_rock()
{
	_rcRock = RectMakeCenter((_Collider[BaseEnum::UNIT].right + _Collider[BaseEnum::UNIT].left) / 2, _Collider[BaseEnum::UNIT].top, 20, 20);
	angle = getAngle((_Collider[BaseEnum::UNIT].right + _Collider[BaseEnum::UNIT].left) / 2, _Collider[BaseEnum::UNIT].top,
		(GAMEMANAGER->getPlayer()->getCollider().right + GAMEMANAGER->getPlayer()->getCollider().left) / 2, (GAMEMANAGER->getPlayer()->getCollider().top + GAMEMANAGER->getPlayer()->getCollider().bottom) / 2);
}

void RockThrowMonster::_delectRock()
{
	if (IntersectRect(&_rcTemp, &GAMEMANAGER->getPlayer()->getCollider(), &_rcRock))
	{
		_throw = false;
	}
}
