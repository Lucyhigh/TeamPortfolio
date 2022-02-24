#include "Stdafx.h"
#include "StartScene.h"

StartScene::StartScene(){
}


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

	// 플레이어 몬스터 오브젝트 여기 그리기 



	IMAGEMANAGER->findImage("StartBgTop")->render(getMemDC(),0,0);



	_ui->render();
	// 인벤토리 이미지 테스트 
	IMAGEMANAGER->findImage("inven7")->render(getMemDC(), 0, 0);
}
