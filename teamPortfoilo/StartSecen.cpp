#include "Stdafx.h"
#include "StartScene.h"

StartScene::StartScene(){
}


HRESULT StartScene::init(void)
{
	// �̹���Ŭ���� �����ϸ� ��������
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
