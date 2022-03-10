#include "Stdafx.h"
#include "MainGame.h"

#pragma region include Scene
#include "ImageClass.h"
#include "TitleScene.h"
#include "SaveScene.h"
#include "OptionScene.h"
#include "TempSoundTest.h"
#include "UIScene.h"
#include "OpeningScene.h"
#include "Boss1BeforeScene.h"
#include "BossScene1.h"
#include "Boss2BeforeScene.h"
#include "LastScene.h"
#include "EndingScene.h"
#pragma endregion 

HRESULT MainGame::init(void) 
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

	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->addScene("Save", new SaveScene);
	SCENEMANAGER->addScene("Option", new OptionScene);

	SCENEMANAGER->addScene("Opening", new OpeningScene);
	SCENEMANAGER->addScene("BeforeBoss1", new Boss1BeforeScene);
	SCENEMANAGER->addScene("Boss1", new BossScene1);

	SCENEMANAGER->addScene("BeforeBoss2", new Boss2BeforeScene);
	SCENEMANAGER->addScene("Last", new LastScene);
	SCENEMANAGER->addScene("Ending", new EndingScene);


	SCENEMANAGER->changeScene("Opening");

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	SCENEMANAGER->release();
}

void MainGame::update(void)
{
	SCENEMANAGER->update();
	GameNode::update();

	SCENEMANAGER->update();

	TempSoundTest sound = TempSoundTest();
	sound.update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	TIMEMANAGER->render(getMemDC());
	SCENEMANAGER->render();
	this->getBackBuffer()->render(getHDC());
}