#include "Stdafx.h"
#include "StartScene.h"

StartScene::StartScene(){
}


HRESULT StartScene::init(void)
{
	// �̹���Ŭ���� �����ϸ� ��������
	IMAGEMANAGER->addImage("StartBG", "Resources/Images/BackGround/bg1.bmp", 1200, 675);

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
	IMAGEMANAGER->findImage("StartBG")->render(getMemDC());


	_ui->render();
}
