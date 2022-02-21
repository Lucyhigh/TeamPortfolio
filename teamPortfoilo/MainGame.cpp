#include "stdafx.h"
#include "MainGame.h"
#pragma region include Scene
//UI
#include "ImageClass.h"
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
	_collider = new ColliderManager();

	//플레이어값
	_player = new PlayerCharacter();
	GAMEMANAGER->setPlayer(_player);

	ImageClass temp = ImageClass();
	temp.init();

#pragma region SceneManager

	// UI : title, system(), inventory(skill, item, equip ...) 
	//SCENEMANAGER->addScene("Title", new TitleScene);
	//SCENEMANAGER->addScene("Option", new OptionScene);


	// Stage1
	SCENEMANAGER->addScene("Start", new StartScene);
	SCENEMANAGER->addScene("Boss1", new BossScene1);
	
	// Stage2
	SCENEMANAGER->addScene("Boss2", new BossScene2);
	SCENEMANAGER->addScene("Field1", new FieldScene1);
	SCENEMANAGER->addScene("Ending", new EndingScene);

	
#pragma endregion 
	// 테스트용 씬체인저
	SCENEMANAGER->changeScene("Boss1");

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	// 이미지클래스 릴리즈 필요한가?
}

void MainGame::update(void) // 갱신
{
	_collider->update();
	SCENEMANAGER->update();
	GameNode::update();
}

void MainGame::render(void) // 그려줘
{
	//검은색 빈 비트맵
	//PatBlt() : 사각형 영역을 브러쉬로 채우는 함수
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	TIMEMANAGER->render(getMemDC());
	// ※ 씬 이미지 출력 ※
	SCENEMANAGER->render();
	this->getBackBuffer()->render(getHDC()); //백버퍼의 내용을 HDC에 그린다.
}