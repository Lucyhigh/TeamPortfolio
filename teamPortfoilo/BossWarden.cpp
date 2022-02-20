#include "Stdafx.h"
#include "BossWarden.h"

BossWarden::BossWarden() 
{ 
	ObjectUpdate = bind(&BossWarden::update, this);
	ObjectRender = bind(&BossWarden::render, this);
}
BossWarden::~BossWarden() { }

HRESULT BossWarden::init(POINT point, vector<RECT*> floor)
{
	this->floor = floor;
	_state = UnitState::END;
	_Collider[BaseEnum::UNIT] = RectMakeCenter(600, 400, 100, 100);
	_Collider[BaseEnum::UNIT].top--;
	_Collider[BaseEnum::UNIT].bottom--;
	function<void()> _update;
	_update = std::bind(&BossWarden::_updateIdle,this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateJump, this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateDownAttack, this);
	_pattenFunc.push_back(_update);

	return S_OK;
}

void BossWarden::release(void)
{ }

void BossWarden::update(void)
{
	GameNode::update();
	
	_updateSide();
	_updateFloor();
	if (_state == UnitState::END) { _inputPatten(); }
	_pattenFunc[(int)_state]();
}

void BossWarden::render(void)
{
	Rectangle(getMemDC(), _Collider[BaseEnum::UNIT].left, _Collider[BaseEnum::UNIT].top, _Collider[BaseEnum::UNIT].right, _Collider[BaseEnum::UNIT].bottom);
}

void BossWarden::_updateFloor()
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

void BossWarden::_updateLook()
{
}

int BossWarden::_updateSide()
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

void BossWarden::_inputPatten()
{
	_state = (UnitState)RND->getInt(3);
	if (_state == UnitState::IDLE) { _pattenDely = RND->getFromInTo(1000, 3000); }
}

void BossWarden::_inputAnimation()
{
}


void BossWarden::_updateIdle()
{
	_isHit = 100;
	int a = 0;
}

void BossWarden::_updateJump()
{

}

void BossWarden::_updateDownAttack()
{

}
