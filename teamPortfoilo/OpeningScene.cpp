#include "Stdafx.h"
#include "OpeningScene.h"

HRESULT OpeningScene::init(void)
{
	_image = IMAGEMANAGER->findImage("openingSceneFloor");

	_pixel = new PixelCollision;
	_pixel->init(_image->getWidth()/2-150, 455, "openingScenePixel");

	_textAlpha = 0;
	_alpha = 0;
	_bgAlpha = 0;
	_count = 0;

	_camera = new Camera;
	_camera->init();
	_camera->setLimitsX(CENTER_X, _image->getWidth());
	_camera->setLimitsY(CENTER_Y, _image->getHeight());



	_areaTextOn = false;
	_areaTextAlpha = 0;

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
	if (_areaTextOn)
	{
		_areaTextAlpha -= 0.05f;
		if (_areaTextAlpha <= 0) _areaTextAlpha = 0;
	}
	else
	{
		_areaTextAlpha++;
		if (_areaTextAlpha >= 255)
		{
			_areaTextAlpha = 255; _areaTextOn = true;
		}
	}


	TEMPSOUNDMANAGER->stopMp3WithKey("Peldanos");
	TEMPSOUNDMANAGER->playSoundWithKey("Luto");

	if (_pixel->getX() >= _image->getWidth())
	{
		SCENEMANAGER->changeScene("BeforeBoss1");
		TEMPSOUNDMANAGER->stopMp3WithKey("Luto");
	}
	else if (_pixel->getX() <= 300)
	{
		_pixel->setX(300);
	}

	POINT cameraPos;
	cameraPos.x = _pixel->getX();
	cameraPos.y = _pixel->getY();

	_camera->setCameraPos(cameraPos);
	_camera->update();

	_pixel->setCameraRect(_camera->getScreenRect());
	_pixel->update("openingScenePixel");

	GAMEMANAGER->getUI()->update();
}

void OpeningScene::render(void)
{
	float bgSpeed = 0.9;
	RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->loopRender("openingSceneLastBG", getMemDC(), &rc1,
		_camera->getScreenRect().left * bgSpeed,
		_camera->getScreenRect().top * bgSpeed);

	IMAGEMANAGER->render("openingSceneFloor", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);

	_pixel->render();

	if (!_pixel->getWakeUp())
	{
		IMAGEMANAGER->render("k", getMemDC(),
			_pixel->getX() - _camera->getScreenRect().left-5,
			_pixel->getY() - _camera->getScreenRect().top - 100);
	}

	IMAGEMANAGER->render("openingSceneFrontBody", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);
	IMAGEMANAGER->render("openingSceneFrontDoor", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);


	_camera->render();

	IMAGEMANAGER->findImage("area1")->alphaRender(getMemDC(), 0, 130, _areaTextAlpha);
	GAMEMANAGER->getUI()->render();
}
