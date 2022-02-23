#include "Stdafx.h"
#include "StartScene.h"

StartScene::StartScene(){
}


HRESULT StartScene::init(void)
{
<<<<<<< HEAD
	// 이미지클래스 연결하면 삭제예정
	IMAGEMANAGER->addImage("StartBG", "Resources/Images/BackGround/bg1.bmp", 1200, 675);

	_ui = new UIScene;
	_ui->init();

=======
>>>>>>> origin/SongYeeun-camera
	return S_OK;
}

void StartScene::release(void)
{
<<<<<<< HEAD
	_ui->release();
	SAFE_DELETE(_ui);
=======
>>>>>>> origin/SongYeeun-camera
}

void StartScene::update(void)
{
<<<<<<< HEAD
	_ui->update();
=======
>>>>>>> origin/SongYeeun-camera
}

void StartScene::render(void)
{
<<<<<<< HEAD
	IMAGEMANAGER->findImage("StartBG")->render(getMemDC());


	_ui->render();
=======
>>>>>>> origin/SongYeeun-camera
}
