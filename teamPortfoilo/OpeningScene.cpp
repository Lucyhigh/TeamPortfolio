#include "Stdafx.h"
#include "OpeningScene.h"

HRESULT OpeningScene::init(void)
{
	_image = IMAGEMANAGER->findImage("¿ÀÇÁ´×¾À ¹Ù´Ú");

	_pixel = new PixelCollision;
	_pixel->init(1680, 944, "¿ÀÇÁ´×¾À ÇÈ¼¿");

    _textAlpha = 0;
    _alpha = 0;
    _bgAlpha = 0;
    _count = 0;


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
	TEMPSOUNDMANAGER->stopMp3WithKey("Peldanos");
	TEMPSOUNDMANAGER->playSoundWithKey("Luto");

	if (_pixel->getX() >= _image->getWidth())
	{
		SCENEMANAGER->changeScene("BeforeBoss1");
		TEMPSOUNDMANAGER->stopMp3WithKey("Luto");
	}
	else if (_pixel->getX() <= 390)
	{
		_pixel->setX(390);
	}

    POINT cameraPos;
    cameraPos.x = _pixel->getX();
    cameraPos.y = _pixel->getY();

    _camera->setCameraPos(cameraPos);
    _camera->update();

    _pixel->setCameraRect(_camera->getScreenRect());
    _pixel->update("¿ÀÇÁ´×¾À ÇÈ¼¿");
}

void OpeningScene::render(void)
{
	float bgSpeed = 0.9;
	RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->loopRender("¿ÀÇÁ´×¾À µÞ¹è°æ", getMemDC(),&rc1, 
											_camera->getScreenRect().left * bgSpeed,
											_camera->getScreenRect().top * bgSpeed);

  IMAGEMANAGER->render("¿ÀÇÁ´×¾À ¹Ù´Ú", getMemDC(),
                                            -_camera->getScreenRect().left,
                                            -_camera->getScreenRect().top);

	_pixel->render();

	//if (!_pixel->getWakeUp())
	{
	}
	cout << _pixel->getX() << " , " << _image->getWidth()*0.4 << endl;

	IMAGEMANAGER->render("¿ÀÇÁ´×¾À ¾Õ½ÃÃ¼", getMemDC(), 
											-_camera->getScreenRect().left,
											-_camera->getScreenRect().top);
	IMAGEMANAGER->render("¿ÀÇÁ´×¾À ¾Õ¹®", getMemDC(), 
											-_camera->getScreenRect().left, 
											-_camera->getScreenRect().top);

	IMAGEMANAGER->render("k", getMemDC(), 
							 _pixel->getX() -_camera->getScreenRect().left,
							 _pixel->getY() -_camera->getScreenRect().top - 100);
	_camera->render();
}
