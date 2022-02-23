#include "stdafx.h"
#include "MainGame.h"
#pragma region include Scene
//UI
<<<<<<< HEAD
=======
#include "ImageClass.h"
>>>>>>> origin/SongYeeun-camera
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
<<<<<<< HEAD
	GAMEMANAGER->setMonster(_monster);
	_collider = new ColliderManager();

	
=======

	ImageClass temp = ImageClass();
	temp.init();
>>>>>>> origin/SongYeeun-camera

#pragma region SceneManager

	// UI : title, system(), inventory(skill, item, equip ...) 
<<<<<<< HEAD
	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->addScene("Option", new OptionScene);
=======
	//SCENEMANAGER->addScene("Title", new TitleScene);
	//SCENEMANAGER->addScene("Option", new OptionScene);

>>>>>>> origin/SongYeeun-camera

	// Stage1
	SCENEMANAGER->addScene("Start", new StartScene);
	SCENEMANAGER->addScene("Boss1", new BossScene1);
	
	// Stage2
	SCENEMANAGER->addScene("Boss2", new BossScene2);
	SCENEMANAGER->addScene("Field1", new FieldScene1);
	SCENEMANAGER->addScene("Ending", new EndingScene);

	
#pragma endregion 
	// 테스트용 씬체인저
<<<<<<< HEAD
	SCENEMANAGER->changeScene("Title");
=======
	SCENEMANAGER->changeScene("Boss1");
>>>>>>> origin/SongYeeun-camera

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	// 이미지클래스 릴리즈 필요한가?
<<<<<<< HEAD
	SCENEMANAGER->release();
=======
>>>>>>> origin/SongYeeun-camera
}

void MainGame::update(void) // 갱신
{
	_collider->update();
	SCENEMANAGER->update();
	GameNode::update();

	SCENEMANAGER->update();

}

void MainGame::render(void) // 그려줘
{
	//검은색 빈 비트맵
	//PatBlt() : 사각형 영역을 브러쉬로 채우는 함수
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	TIMEMANAGER->render(getMemDC());
<<<<<<< HEAD
	
	

	for (int i = 0; i < _monster.size(); i++) { _monster[i]->ObjectRender(); }
	_player->ObjectRender();

	for (int i = 0; i < _floor.size(); i++)
	{
		Rectangle(getMemDC(), _floor[i]->left, _floor[i]->top, _floor[i]->right, _floor[i]->bottom);
	}
	
	char str[254];
	sprintf_s(str, "%d", GAMEMANAGER->getPlayer()->getHp(BaseEnum::STATE));
	TextOut(getMemDC(), 1000, 10, str, strlen(str));

	// ※ 씬 이미지 출력 ※
	SCENEMANAGER->render();


=======
	// ※ 씬 이미지 출력 ※
	SCENEMANAGER->render();
>>>>>>> origin/SongYeeun-camera
	this->getBackBuffer()->render(getHDC()); //백버퍼의 내용을 HDC에 그린다.
}