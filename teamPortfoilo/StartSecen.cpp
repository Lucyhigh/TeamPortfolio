#include "Stdafx.h"
#include "StartScene.h"

StartScene::StartScene(){
}


HRESULT StartScene::init(void)
{
	// 이미지클래스 연결하면 삭제예정
	IMAGEMANAGER->addImage("StartBG", "Resources/Images/BackGround/bg1.bmp", 1200, 675);

	return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
}

void StartScene::render(void)
{
	IMAGEMANAGER->findImage("StartBG")->render(getMemDC());
}
