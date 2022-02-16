#include "Stdafx.h"
#include "ColliderManager.h"
#include "Characters.h"

ColliderManager::ColliderManager() { }
ColliderManager::~ColliderManager() { }

void ColliderManager::init(BaseData* user, vector<BaseData*> monster)
{
	_user = user;
	_monster = monster;
}

void ColliderManager::update(void)
{ 
	smashCollider();
	bodyCollider();
}

void ColliderManager::smashCollider()
{
	int smash = _user->getSmash().size();
	if ( smash > 0)
	{ 
		RECT temp;
		for (int i = 0; i < smash; i++)
		{
			for (int h = 0; h < _monster.size(); h++)
			{
				if (IntersectRect(&temp, &_user->getSmash()[i].first, &_monster[h]->getCollider()))
				{ 
					_monster[h]->setHit(); 
					_user->clearSmash();
					return;
				}
			}
		}
	}
	
	for (int i = 0; i < _monster.size(); i++)
	{
		smash = _monster[i]->getSmash().size();
		for (int h = 0; h < smash; h++)
		{
			RECT temp;
			if (IntersectRect(&temp, &_user->getCollider(), &_monster[i]->getSmash()[h].first))
			{
				_user->setHit(); 
				_monster[i]->clearSmash();
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






