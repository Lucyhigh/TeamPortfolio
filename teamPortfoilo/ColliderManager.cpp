#include "Stdafx.h"
#include "ColliderManager.h"
#include "Characters.h"
#include "Image.h"
class BaseData;

ColliderManager::ColliderManager() { }
ColliderManager::~ColliderManager() { }

void ColliderManager::update(void)
{ 
	smashCollider();
	bodyCollider();

	if (_effect.size() != 0)
	{ 
		try
		{
			updateEffect();
		}
		catch (int a) { }
	}
}

void ColliderManager::render(void)
{
	for (int i = 0; i < _effect.size(); i++)
	{
		float x = _effect[i].second->getX() - GAMEMANAGER->getPlayer()->getCamareRect().left;
		float y = _effect[i].second->getY() - GAMEMANAGER->getPlayer()->getCamareRect().top;
		_effect[i].second->frameRender(getMemDC(), x, y, _effect[i].second->getFrameX(), _effect[i].second->getFrameY());
	}
}

inline void ColliderManager::smashCollider()
{
	int smash = GAMEMANAGER->getPlayer()->getSmash().size();
	if ( smash > 0)
	{ 
		RECT temp[3];
		for (int i = 0; i < smash; i++)
		{
			for (int h = 0; h < GAMEMANAGER->getMonster().size(); h++)
			{
				if (IntersectRect(&temp[0], &GAMEMANAGER->getPlayer()->getSmash()[i].first, &GAMEMANAGER->getMonster()[h]->getCollider()) && GAMEMANAGER->getMonster()[h]->getHp(BaseEnum::STATE) > 0)
				{ 
					RECT result = GAMEMANAGER->getPlayer()->getSmash()[i].first;
					addEffect(result);
					GAMEMANAGER->getPlayer()->clearSmash(i);
					GAMEMANAGER->getMonster()[h]->setHit(i);
					GAMEMANAGER->getPlayer()->setAttack(true);
					return;
				}
			}
		}
	}
	
	for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{
		smash = GAMEMANAGER->getMonster()[i]->getSmash().size();
		for (int h = 0; h < smash; h++)
		{
			RECT temp;

			if (IntersectRect(&temp, &GAMEMANAGER->getPlayer()->getCollider(), &GAMEMANAGER->getMonster()[i]->getSmash()[h].first))
			{
				if (GAMEMANAGER->getPlayer()->getState() != PlayerCharacter::UnitState::SLIDE)
				{
					addEffect(GAMEMANAGER->getPlayer()->getCollider());
					GAMEMANAGER->getPlayer()->setHit(1);
					GAMEMANAGER->getMonster()[i]->clearSmash(h);
					GAMEMANAGER->getMonster()[i]->setAttack(true);
				}
				return;
			}
		}
	}
}

void ColliderManager::bodyCollider()
{
	/*
	for (int i = 0; i < _monster.size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, &_user->getCollider(), &_monster[i]->getCollider()))
		{
			_user->setHit();
			return;
		}
	}
	*/
}

void ColliderManager::addEffect(RECT effect)
{
	_effect.push_back({ 0, new Image });
	_effect.back().second->init("Resources/images/Player/effectTwo.bmp",792,164,6,2,MGT);
	if (_effect.back().second != nullptr)
	{
		_effect.back().second->setY(effect.top);
		_effect.back().second->setX(effect.left - 60);
	}
}

void ColliderManager::updateEffect()
{
	for (int i = 0; i < _effect.size(); i++)
	{
		if (0.1f + _effect[i].first >= TIMEMANAGER->getWorldTime()) { continue; }
		_effect[i].first = TIMEMANAGER->getWorldTime();
		
		try
		{
			if (_effect[i].second->getFrameX() < _effect[i].second->getMaxFrameX())
			{
				_effect[i].second->setFrameX(_effect[i].second->getFrameX() + 1);
			}
			else
			{
				_effect.erase(_effect.begin() + i);
				break;
			}
		}
		catch (int a) 
		{
			a = 0;
		}
	}
}






