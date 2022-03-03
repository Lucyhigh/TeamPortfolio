#include "Stdafx.h"
#include "StartScene.h"

StartScene::StartScene(){
}


HRESULT StartScene::init(void)
{

	return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
	GAMEMANAGER->getUI()->update();
}

void StartScene::render(void)
{
	IMAGEMANAGER->findImage("StartBg")->render(getMemDC(),0,0);

	IMAGEMANAGER->findImage("StartBgTop")->render(getMemDC(),0,0);

	GAMEMANAGER->getUI()->render();
}
