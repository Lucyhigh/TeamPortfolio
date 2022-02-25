#include "Stdafx.h"
#include "BossScene1.h"

BossScene1::BossScene1() { }
BossScene1::~BossScene1() { }

HRESULT BossScene1::init(void)
{
	_collider = new ColliderManager();
	floor0 = new RECT{ 0, 600, 1200, 1000 };
	floor1 = new RECT{ 1200, 0, 1300, 1000 };
	floor2 = new RECT{ -100, 0, 0, 1000 };
	_floor.push_back(floor0);
	_floor.push_back(floor1);
	_floor.push_back(floor2);
	GAMEMANAGER->getPlayer()->ObjectInit({ 0,0 }, _floor);

	boss = new BossWarden();
	boss->init({ 0,0 }, _floor);
	_monster.push_back(boss);
	GAMEMANAGER->setMonster(_monster);
	return S_OK;
}

void BossScene1::release(void)
{
	for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{ GAMEMANAGER->getMonster()[i]->ObjectrRelease(); }
	GAMEMANAGER->getPlayer()->ObjectrRelease();
}

void BossScene1::update(void)
{
	_collider->update();
	for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{ GAMEMANAGER->getMonster()[i]->ObjectUpdate(); }
	GAMEMANAGER->getPlayer()->ObjectUpdate();
}

void BossScene1::render(void)
{
	int i = 0;
	for(i=0;i<_floor.size(); i++)
	{ Rectangle(getMemDC(), _floor[i]->left, _floor[i]->top, _floor[i]->right, _floor[i]->bottom); }

	for (i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{ GAMEMANAGER->getMonster()[i]->ObjectRender(); }
	
	GAMEMANAGER->getPlayer()->ObjectRender();
	_collider->render();
}
