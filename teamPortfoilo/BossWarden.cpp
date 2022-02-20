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
	_Collider[BaseEnum::UNIT] = RectMakeCenter(600, 450, 100, 100);
	function<void()> _update;
	_update = std::bind(&BossWarden::_updateIdle,this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateJump, this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateAttack, this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateJump, this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateStart, this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateDie, this);
	_pattenFunc.push_back(_update);

	return S_OK;
}

void BossWarden::release(void)
{ }

void BossWarden::update(void)
{	
	_updateFloor();
	_updateSide();
	if (_state == UnitState::END) { _inputPatten(); }
	_pattenFunc[(int)_state]();
}

void BossWarden::render(void)
{
	Rectangle(getMemDC(), _Collider[BaseEnum::UNIT].left, _Collider[BaseEnum::UNIT].top, _Collider[BaseEnum::UNIT].right, _Collider[BaseEnum::UNIT].bottom);

	for (int i = 0; i < smash.size(); i++)
	{ Rectangle(getMemDC(), smash[i].first.left, smash[i].first.top, smash[i].first.right, smash[i].first.bottom); }
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


	tamp[1].bottom += GAMESPEED;
	if (!(IntersectRect(&tamp[0], &tamp[1], &stateFloor)))
	{
		if (_state != UnitState::JUMPATTACK) 
		{ _state = UnitState::JUMP; }
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
	_state = (UnitState)RND->getInt(2);
	if (_state == UnitState::IDLE) { _pattenDely = TIMEMANAGER->getWorldTime() + 2; }
	else if (_state == UnitState::JUMPATTACK)  { _jump["Weight"] = 16.0f; }
}

void BossWarden::_inputAnimation()
{

}


void BossWarden::_updateIdle()
{
	if (_pattenDely <= TIMEMANAGER->getWorldTime())
	{ _state = UnitState::END; }
}

void BossWarden::_updateJump()
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
			if (_state != UnitState::JUMPATTACK) 
			{ _state = UnitState::END; }
			else
			{
				_state = UnitState::END;
				stateFloor = *floor[i];
				smash.push_back({ { stateFloor.left, stateFloor.top - 10, stateFloor.right, stateFloor.bottom}, new Image });
			}
			
			for (auto iter = _jump.begin(); iter != _jump.end(); ++iter)
			{
				iter->second = 0;
			}
		}
	}
}

void BossWarden::_updateAttack()
{
	// 순차적으로 렉트그려주기 

	int a = 0;

	smash.clear();
	// tmxoxlr? 





	
}
