#include "Stdafx.h"
#include "BossWarden.h"

void BossWarden::clearSmash(int num)
{
	if (_state != UnitState::ATTACK)
	{
		BaseData::clearSmash(num);
	}
	else
	{
		for (int i = 0; i < smash.size(); i++)
		{ smash[i].first.top = smash[i].first.bottom; }
	}
}

void BossWarden::setHit(int)
{
	_hp[BaseEnum::STATE] -=50;
}

BossWarden::BossWarden()
{ 
	ObjectInit = bind(&BossWarden::init, this, std::placeholders::_1, std::placeholders::_2);
	ObjectrRelease = bind(&BossWarden::release, this);
	ObjectUpdate = bind(&BossWarden::update, this);
	ObjectRender = bind(&BossWarden::render, this);
	_hp[BaseEnum::STATE] = 10 * 54;
}
BossWarden::~BossWarden(){}

HRESULT BossWarden::init(POINT point, vector<RECT*> floor)
{
	this->floor = floor;
	_state = UnitState::END;
	_Collider[BaseEnum::UNIT] = RectMakeCenter(point.x, point.y, 200, 225);

	function<void()> _update;
	_update = std::bind(&BossWarden::_updateIdle,this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateJump, this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateAttack, this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateJumpIdle, this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateJump, this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateStart, this);
	_pattenFunc.push_back(_update);
	_update = std::bind(&BossWarden::_updateJump, this);
	_pattenFunc.push_back(_update);

	if (GAMEMANAGER->getPlayer()->getCollider().left - _Collider[BaseEnum::UNIT].left <= 0)
	{
		_isLeft = -1;
	}
	else
	{
		_isLeft = 1;
	}

	return S_OK;
}

void BossWarden::release(void)
{ }

void BossWarden::update(void)
{	
	_updateLook();
	_updateFloor();
	_updateSide();

	if (_hp[BaseEnum::STATE] <= 0 && _state != UnitState::DIE) { _state = UnitState::END; }
	if (_state == UnitState::END) { _inputPatten(); }
	_inputAnimation();
	_pattenFunc[(int)_state]();
	_inputEffect();
}

void BossWarden::render(void)
{
	for (int i = 0; i < effect.size(); i++)
	{
		float effectX = effect[i].second->getX() - GAMEMANAGER->getPlayer()->getCamareRect().left;
		float effectY = effect[i].second->getY() - GAMEMANAGER->getPlayer()->getCamareRect().top;
		effect[i].second->frameRender(getMemDC(), effectX, effectY, effect[i].second->getFrameX(), effect[i].second->getFrameY());
	}

	if (_image != nullptr)
	{
		float imageX = _image->getX() - GAMEMANAGER->getPlayer()->getCamareRect().left;
		float imageY = _image->getY() - GAMEMANAGER->getPlayer()->getCamareRect().top;
		_image->frameRender(getMemDC(), imageX, imageY, _image->getFrameX(), _image->getFrameY());
	}
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
	if (_image != nullptr && _state != UnitState::ATTACK && _state != UnitState::JUMPATTACK &&_state != UnitState::DIE)
	{
		float currentY = GAMEMANAGER->getPlayer()->getCollider().left - _Collider[BaseEnum::UNIT].left;

		if (currentY <= 0)
		{
			_isLeft = -1;
		}
		else
		{
			_isLeft = 1;
		}
		
	}
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
	if (_hp[BaseEnum::STATE] <= 0)
	{ 
		if (_isLeft == 1)
		{
			IMAGEMANAGER->findImage("WardenDead")->setFrameY(0);
			IMAGEMANAGER->findImage("WardenDead")->setFrameX(IMAGEMANAGER->findImage("WardenDead")->getMaxFrameX());
		}
		else
		{
			IMAGEMANAGER->findImage("WardenDead")->setFrameY(1);
			IMAGEMANAGER->findImage("WardenDead")->setFrameX(0);
		}
		_state = UnitState::DIE; return; 
	}

	_state = (UnitState)RND->getInt(3);
	if (_state == UnitState::IDLE) 
	{ 
		_pattenDely = TIMEMANAGER->getWorldTime() + 2; 
	}
	else if (_state == UnitState::JUMPATTACK) 
	{ 
		IMAGEMANAGER->findImage("WardenJump")->setFrameX(0);
		_jump["Weight"] = 6.0f; 
	}
	else if (_state == UnitState::ATTACK)
	{
		if (_isLeft == 1)
		{
			IMAGEMANAGER->findImage("WardenAttack")->setFrameX(IMAGEMANAGER->findImage("WardenAttack")->getMaxFrameX());
		}
		else
		{
			IMAGEMANAGER->findImage("WardenAttack")->setFrameX(0);
		}
		_pattenDely = TIMEMANAGER->getWorldTime();
	}

	_fram = TIMEMANAGER->getWorldTime();
}

void BossWarden::_inputAnimation()
{
	if (_state == UnitState::IDLE)
	{
		_image = IMAGEMANAGER->findImage("WardenIdle");

		if (_isLeft == 1)
		{
			_image->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left - 30);
		}
		else
		{
			_image->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left - 100);
		}
		_image->setY(_Collider[BaseEnum::UNIT].top-100);

		if (0.1f + _fram >= TIMEMANAGER->getWorldTime())
		{
			return;
		}

		_fram = TIMEMANAGER->getWorldTime();
		if (_image->getFrameX() < _image->getMaxFrameX())
		{
			_image->setFrameX(_image->getFrameX() + 1);
		}
		else
		{
			_image->setFrameX(0);
		}

	}
	else if (_state == UnitState::JUMPATTACK)
	{
		_image = IMAGEMANAGER->findImage("WardenJump");

		_image->setY(_Collider[BaseEnum::UNIT].top - 175);

		if (_isLeft == 1)
		{
			_image->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left-85);
		}
		else
		{
			_image->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left-150);
		}

		if (0.1f + _fram >= TIMEMANAGER->getWorldTime())
		{
			return;
		}

		_fram = TIMEMANAGER->getWorldTime();
		if (_image->getFrameX() < _image->getMaxFrameX())
		{
			_image->setFrameX(_image->getFrameX() + 1);
		}
		else
		{
			_image->setFrameX(0);
		}
	}
	else if (_state == UnitState::JUMPIDLE)
	{
		_image = IMAGEMANAGER->findImage("WardenJump");

		_image->setY(_Collider[BaseEnum::UNIT].top - 175);
		if (_isLeft == 1)
		{
			_image->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left-85);
		}
		else
		{
			_image->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left-150);
		}

		if (0.1f + _fram >= TIMEMANAGER->getWorldTime())
		{
			return;
		}

		_fram = TIMEMANAGER->getWorldTime();
		if (_image->getFrameX() < _image->getMaxFrameX())
		{
			_image->setFrameX(_image->getFrameX() + 1);
		}
		else
		{
			_image->setFrameX(0);
		}
	}
	else if (_state == UnitState::ATTACK)
	{
		_image = IMAGEMANAGER->findImage("WardenAttack");

		_image->setY(_Collider[BaseEnum::UNIT].top - 175);
		if (_isLeft == 1)
		{
			_image->setFrameY(0);
			_image->setX(_Collider[BaseEnum::UNIT].left - 125);
		}
		else
		{
			_image->setFrameY(1);
			_image->setX(_Collider[BaseEnum::UNIT].left - 350);
		}

		if (0.1f + _fram >= TIMEMANAGER->getWorldTime())
		{
			return;
		}
		_fram = TIMEMANAGER->getWorldTime();

		if(_isLeft == 1)
		{ 
			if (_image->getFrameX() > 0)
			{
				_image->setFrameX(_image->getFrameX() - 1);
			}
		}
		else
		{
			if (_image->getFrameX() < _image->getMaxFrameX())
			{
				_image->setFrameX(_image->getFrameX() + 1);
			}
		}
	}
	else if (_state == UnitState::DIE)
	{
		_image = IMAGEMANAGER->findImage("WardenDead");
		_image->setY(_Collider[BaseEnum::UNIT].top - 225);

		if (_isLeft == 1)
		{
			_image->setX(_Collider[BaseEnum::UNIT].left -510);
		}
		else
		{
			_image->setX(_Collider[BaseEnum::UNIT].left - 125);
		}

		if (0.1f + _fram >= TIMEMANAGER->getWorldTime()) return;
		_fram = TIMEMANAGER->getWorldTime();

		if (_isLeft == -1)
		{
			if (_image->getFrameX() < _image->getMaxFrameX())
			{
				_image->setFrameX(_image->getFrameX() + 1);
			}
		}
		else
		{
			if (_image->getFrameX() > 0)
			{
				_image->setFrameX(_image->getFrameX() - 1);
			}
		}
	}
}

void BossWarden::_updateIdle()
{
	if (_pattenDely <= TIMEMANAGER->getWorldTime())
	{ _state = UnitState::END; }
}

void BossWarden::_updateJump()
{
	if (_state == UnitState::JUMPATTACK && IMAGEMANAGER->findImage("WardenJump")->getFrameX() < 9 )
	{ 
		return; 
	}

	if (_state != UnitState::JUMP && _state != UnitState::DIE)
	{
		if (_isLeft == -1 && _Collider[BaseEnum::UNIT].left >= 10)
		{
			_Collider[BaseEnum::UNIT].left += _isLeft * GAMESPEED;
			_Collider[BaseEnum::UNIT].right += _isLeft * GAMESPEED;
		}
		else if (_isLeft == 1 && _Collider[BaseEnum::UNIT].right <= floor[0]->right- 110)
		{
			_Collider[BaseEnum::UNIT].left += _isLeft * GAMESPEED;
			_Collider[BaseEnum::UNIT].right += _isLeft * GAMESPEED;
		}
	}

	_jump["Weight"] += -1 * 0.05f;
	_Collider[BaseEnum::UNIT].top += -1 * _jump["Weight"];
	_Collider[BaseEnum::UNIT].bottom += -1 * _jump["Weight"];

	RECT tamp;
	for (int i = 0; i < floor.size(); i++)
	{
		if (IntersectRect(&tamp, &_Collider[BaseEnum::UNIT], floor[i]))
		{
			stateFloor = *floor[i];
			for (auto iter = _jump.begin(); iter != _jump.end(); ++iter)
			{
				iter->second = 0;
			}

			if (_state == UnitState::JUMPATTACK)
			{
				_state = UnitState::JUMPIDLE;
				smash.push_back({ stateFloor, Image() });
				smash.back().first.top -= 20;
			}
			else
			{
				if (_state != UnitState::DIE)
				{
					_state = UnitState::END;
				}
			}
		}
	}
}

void BossWarden::_updateJumpIdle()
{
	if (_image->getFrameX() >= _image->getMaxFrameX())
	{
		_state = UnitState::END;
	}
}

void BossWarden::_updateAttack()
{
	if (_isLeft == -1)
	{
		if (_image->getFrameX() < 15)	 return;
	}
	else
	{
		if (_image->getFrameX() > 7)	return;
	}

	if (0.15f + _pattenDely >= TIMEMANAGER->getWorldTime()) return;
	_pattenDely = TIMEMANAGER->getWorldTime();
	
	if (smash.size() > 4)
	{
		if (_isLeft == -1)
		{
			if (_image->getFrameX() >= _image->getMaxFrameX())
			{
				_state = UnitState::END;
				IMAGEMANAGER->findImage("WardenAttack")->setFrameX(0);
				smash.clear();
			}
		}
		else
		{
			if (_image->getFrameX() <= 0)
			{
				_state = UnitState::END;
				IMAGEMANAGER->findImage("WardenAttack")->setFrameX(0);
				smash.clear();
			}
		}

		return;
	}

	pair<RECT, Image> result;
	effect.push_back({ 0,new Image });
	effect.back().first = TIMEMANAGER->getWorldTime();
	effect.back().second->init("Resources/Images/Boss/tutoBossEffect.bmp", 2560, 128, 20, 1,true,RGB(0,0,255));

	if (smash.size() == 0)
	{

		if (_isLeft != -1)
		{
			result.first = { _Collider[BaseEnum::UNIT].right, _Collider[BaseEnum::UNIT].bottom - 50,
				  _Collider[BaseEnum::UNIT].right + 100, _Collider[BaseEnum::UNIT].bottom };
			effect.back().second->setX(result.first.left);
			effect.back().second->setY(stateFloor.top - effect.back().second->getFrameHeight());
		}
		else
		{
			result.first = { _Collider[BaseEnum::UNIT].left-100, _Collider[BaseEnum::UNIT].bottom - 50,
							  _Collider[BaseEnum::UNIT].left, _Collider[BaseEnum::UNIT].bottom };
			effect.back().second->setX(result.first.left + (result.first.right - result.first.left)-100);
			effect.back().second->setY(stateFloor.top-effect.back().second->getFrameHeight());
		}
	}
	else
	{
		if (_isLeft != -1)
		{
			result.first = { smash.back().first.right, smash.back().first.bottom - 50, smash.back().first.right + 100, smash.back().first.bottom };
			effect.back().second->setX(result.first.left);
			effect.back().second->setY(stateFloor.top - effect.back().second->getFrameHeight());
		}
		else
		{
			result.first = { smash.back().first.left-100, smash.back().first.bottom -50, smash.back().first.left, smash.back().first.bottom };
			effect.back().second->setX(result.first.left + (result.first.right - result.first.left)-100);
			effect.back().second->setY(stateFloor.top - effect.back().second->getFrameHeight());
		}
	}
	smash.push_back(result);
}

void BossWarden::_inputEffect()
{
	for (int i = 0; i < effect.size(); i++)
	{
		if (0.05f + effect[i].first >= TIMEMANAGER->getWorldTime())
		{
			continue;
		}
		effect[i].first = TIMEMANAGER->getWorldTime();

		if (effect[i].second->getFrameX() < effect[i].second->getMaxFrameX())
		{
			effect[i].second->setFrameX(effect[i].second->getFrameX() + 1);
		}
		else
		{
			effect.erase(effect.begin() + i);
			break;
		}
	}
}

