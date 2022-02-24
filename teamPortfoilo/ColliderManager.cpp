#include "Stdafx.h"
#include "ColliderManager.h"
#include "Characters.h"
class BaseData;

ColliderManager::ColliderManager() { }
ColliderManager::~ColliderManager() { }

void ColliderManager::update(void)
{ 
	smashCollider();
	bodyCollider();
}

void ColliderManager::smashCollider()
{
	int smash = GAMEMANAGER->getPlayer()->getSmash().size();
	if ( smash > 0)
	{ 
		RECT temp;
		for (int i = 0; i < smash; i++)
		{
			for (int h = 0; h < GAMEMANAGER->getMonster().size(); h++)
			{
				if (IntersectRect(&temp, &GAMEMANAGER->getPlayer()->getSmash()[i].first, &GAMEMANAGER->getMonster()[h]->getCollider()))
				{ 
					GAMEMANAGER->getMonster()[h]->setHit(); 
					GAMEMANAGER->getPlayer()->clearSmash(i);
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
				GAMEMANAGER->getPlayer()->setHit();
				GAMEMANAGER->getMonster()[i]->clearSmash(i);
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






