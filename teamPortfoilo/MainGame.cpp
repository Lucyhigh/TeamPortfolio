#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void) //초기화
{
	GameNode::init(TRUE);
	TIMEMANAGER->init();
	// 테스트 렉트값 
	_floor.push_back(&reference[0]);

	//플레이어값
	player = new PlayerCharacter();
	player->init({ 0,600 }, _floor);
	_player = player;
	mon = new BossWarden();
	mon->init({ 0,0 }, _floor);
	mon->setCollider(RECT{ 800,350,900,450 });
	_monster.push_back(mon);

	GAMEMANAGER->setPlayer(_player);
	GAMEMANAGER->setMonster(_monster);
	_collider = new ColliderManager();
	return S_OK;
}

void MainGame::release(void)
{

	GameNode::release();
}

void MainGame::update(void) // 갱신
{
	_player->ObjectUpdate();
	for (int i = 0; i < _monster.size(); i++) { _monster[i]->ObjectUpdate(); }
	_collider->update();

	GameNode::update();
}

void MainGame::render(void) // 그려줘
{
	//검은색 빈 비트맵
	//PatBlt() : 사각형 영역을 브러쉬로 채우는 함수
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	for (int i = 0; i < _monster.size(); i++) { _monster[i]->ObjectRender(); }
	_player->ObjectRender();

	for (int i = 0; i < _floor.size(); i++)
	{
		Rectangle(getMemDC(), _floor[i]->left, _floor[i]->top, _floor[i]->right, _floor[i]->bottom);
	}

	this->getBackBuffer()->render(getHDC()); //백버퍼의 내용을 HDC에 그린다.
}