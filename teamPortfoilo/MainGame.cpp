#include "stdafx.h"
#include "MainGame.h"
#pragma region include Scene
//UI
#include "ImageClass.h"
#include "TitleScene.h"
#include "SaveScene.h"
#include "OptionScene.h"
#include "TempSoundTest.h"
#include "UIScene.h"
//Stage
#include "StartScene.h"
#include "OpeningScene.h"//
#include "Boss1BeforeScene.h"
#include "BossScene1.h"
#include "BossScene2.h"
#include "FieldScene1.h"
#include "LastScene.h"
#include "EndingScene.h"
#pragma endregion 



HRESULT MainGame::init(void) //�ʱ�ȭ
{
	GameNode::init(TRUE);

	ImageClass imageClass = ImageClass();
	imageClass.init();

	TempSoundTest sound = TempSoundTest();
	sound.init();

	TIMEMANAGER->init();

	_player = new PlayerCharacter();
	GAMEMANAGER->setPlayer(_player);

	_ui = new UIScene();
	_ui->init();
	GAMEMANAGER->setUI(_ui);

#pragma region SceneManager

	// UI : title, system(), inventory(skill, item, equip ...) 
	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->addScene("Save", new SaveScene);
	SCENEMANAGER->addScene("Option", new OptionScene);

	// Stage1
	SCENEMANAGER->addScene("Start", new StartScene);
	SCENEMANAGER->addScene("Opening", new OpeningScene);
	SCENEMANAGER->addScene("BeforeBoss1", new Boss1BeforeScene);
	SCENEMANAGER->addScene("Boss1", new BossScene1);


	
	// Stage2
	SCENEMANAGER->addScene("Boss2", new BossScene2);
	SCENEMANAGER->addScene("Field1", new FieldScene1);
	SCENEMANAGER->addScene("Last", new LastScene);
	SCENEMANAGER->addScene("Ending", new EndingScene);

	
#pragma endregion 

	SCENEMANAGER->changeScene("Boss2");
	return S_OK;
}

void MainGame::release(void)
{

	GameNode::release();
	SCENEMANAGER->release();
}

void MainGame::update(void) // ����
{
	SCENEMANAGER->update();
	GameNode::update();

	SCENEMANAGER->update();

	TempSoundTest sound = TempSoundTest();
	sound.update();

}

void MainGame::render(void) // �׷���
{
	//������ �� ��Ʈ��
	 //PatBlt() : �簢�� ������ �귯���� ä��� �Լ�
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	TIMEMANAGER->render(getMemDC());

	// �� �� �̹��� ��� ��
	SCENEMANAGER->render();

	this->getBackBuffer()->render(getHDC()); //������� ������ HDC�� �׸���.

}