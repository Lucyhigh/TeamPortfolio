#include "Stdafx.h"
#include "StartScene.h"

StartScene::StartScene(){}

HRESULT StartScene::init(void)
{
	_ui = new UIScene;
	_ui->init();

	return S_OK;
}

void StartScene::release(void)
{
	_ui->release();
	SAFE_DELETE(_ui);
}

void StartScene::update(void)
{
	_ui->update();
}

void StartScene::render(void)
{
	IMAGEMANAGER->findImage("StartBg")->render(getMemDC(),0,0);

	IMAGEMANAGER->findImage("StartBgTop")->render(getMemDC(),0,0);

	_ui->render();
}
