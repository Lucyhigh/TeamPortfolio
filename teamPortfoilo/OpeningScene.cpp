#include "Stdafx.h"
#include "OpeningScene.h"

HRESULT OpeningScene::init(void)
{
	_image = IMAGEMANAGER->findImage("¿ÀÇÁ´×¾À Å×½ºÆ®¹è°æ");

	_pixel = new PixelCollision;
	_pixel->init(1680,944, "¿ÀÇÁ´×¾À ÇÈ¼¿");

	_camera = new Camera;
	_camera->init();
	_camera->setLimitsX(CENTER_X, _image->getWidth());
	_camera->setLimitsY(CENTER_Y, _image->getHeight());

	return S_OK;
}

void OpeningScene::release(void)
{
	SAFE_DELETE(_pixel);

	_camera->release();
	SAFE_DELETE(_camera);
}

void OpeningScene::update(void)
{
	_pixel->update("¿ÀÇÁ´×¾À ÇÈ¼¿");
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) || _pixel->getX() >= _image->getWidth())
	{
		SCENEMANAGER->changeScene("BeforeBoss1");
	}
	else if (_pixel->getX() <= 390)
	{
		_pixel->setX(390);
	}

	POINT cameraPos;
	cameraPos.x = _pixel->getX();
	cameraPos.y = _pixel->getY();// _camera->getCameraPos().y;

	_camera->setCameraPos(cameraPos);
	_camera->update();

	_pixel->setCameraRect(_camera->getScreenRect());

}

void OpeningScene::render(void)
{
	//cout << _camera->getScreenRect().left << " " << _camera->getScreenRect().top << endl;

	IMAGEMANAGER->render("¿ÀÇÁ´×¾À Å×½ºÆ®¹è°æ", getMemDC(), 0, 0,
		_camera->getScreenRect().left, _camera->getScreenRect().top,
		WINSIZE_X, WINSIZE_Y);

	_camera->render();
	_pixel->render();
}
