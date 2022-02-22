#include "stdafx.h"
#include "MainGame.h"
#pragma region include Scene
//UI
#include "TitleScene.h"
#include "OptionScene.h"
//Stage
#include "StartScene.h"
#include "BossScene1.h"
#include "BossScene2.h"
#include "FieldScene1.h"
#include "EndingScene.h"
#pragma endregion 


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
	//mon->setCollider(RECT{ 800,350,900,450 });
	_monster.push_back(mon);

	GAMEMANAGER->setPlayer(_player);
	GAMEMANAGER->setMonster(_monster);
	_collider = new ColliderManager();

	

#pragma region SceneManager

	// UI : title, system(), inventory(skill, item, equip ...) 
	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->addScene("Option", new OptionScene);

	// Stage1
	SCENEMANAGER->addScene("Start", new StartScene);
	SCENEMANAGER->addScene("Boss1", new BossScene1);
	
	// Stage2
	SCENEMANAGER->addScene("Boss2", new BossScene2);
	SCENEMANAGER->addScene("Field1", new FieldScene1);
	SCENEMANAGER->addScene("Ending", new EndingScene);

	
#pragma endregion 
	// 테스트용 씬체인저
	SCENEMANAGER->changeScene("Start");

	return S_OK;
}

void MainGame::release(void)
{

	GameNode::release();
	// 이미지클래스 릴리즈 필요한가?
	SCENEMANAGER->release();
}

void MainGame::update(void) // 갱신
{
	_player->ObjectUpdate();
	for (int i = 0; i < _monster.size(); i++) { _monster[i]->ObjectUpdate(); }
	_collider->update();

	GameNode::update();

	SCENEMANAGER->update();

}

void MainGame::render(void) // 그려줘
{
	//검은색 빈 비트맵
	//PatBlt() : 사각형 영역을 브러쉬로 채우는 함수
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	TIMEMANAGER->render(getMemDC());
	
	// ※ 씬 이미지 출력 ※
	SCENEMANAGER->render();

	for (int i = 0; i < _monster.size(); i++) { _monster[i]->ObjectRender(); }
	_player->ObjectRender();

	for (int i = 0; i < _floor.size(); i++)
	{
		Rectangle(getMemDC(), _floor[i]->left, _floor[i]->top, _floor[i]->right, _floor[i]->bottom);
	}
	
	char str[254];
	sprintf_s(str, "%d", GAMEMANAGER->getPlayer()->getHp(BaseEnum::STATE));
	TextOut(getMemDC(), 1000, 10, str, strlen(str));




	this->getBackBuffer()->render(getHDC()); //백버퍼의 내용을 HDC에 그린다.
}