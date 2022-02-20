#include "stdafx.h"
#include "MainGame.h"

//	신매니저 
// 텍스트데이터 매니져
// 타임 매니저
// 픽셀 콜리전
// 프로그래스바

HRESULT MainGame::init(void) //초기화
{
	GameNode::init(TRUE);

	// 테스트 렉트값 
	floor.push_back(&reference[0]);
	floor.push_back(&reference[1]);

	//플레이어값
	player = new PlayerCharacter();
	player->init({ 0,0 }, floor);

	mon = new BaseData();
	mon->setCollider(RECT{ 800,350,900,450 });
	monster.push_back(mon);

	collider = new ColliderManager();
	collider->init(player, monster);

	TIMEMANAGER->init();

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();	
}

void MainGame::update(void) // 갱신
{
	GameNode::update();
	collider->update();
	player->update();
}

void MainGame::render(void) // 그려줘
{
	//검은색 빈 비트맵
	//PatBlt() : 사각형 영역을 브러쉬로 채우는 함수
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	TIMEMANAGER->render(getMemDC());
		
	for (int i = 0; i < monster.size(); i++)
	{ Rectangle(getMemDC(), monster[i]->getCollider().left, monster[i]->getCollider().top, monster[i]->getCollider().right, monster[i]->getCollider().bottom); }
	
	player->render();

	for (int i = 0; i < floor.size(); i++)
	{ Rectangle(getMemDC(), floor[i]->left, floor[i]->top, floor[i]->right, floor[i]->bottom); }
	
	this->getBackBuffer()->render(getHDC()); //백버퍼의 내용을 HDC에 그린다.
}