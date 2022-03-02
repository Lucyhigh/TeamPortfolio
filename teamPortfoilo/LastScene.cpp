#include "Stdafx.h"
#include "LastScene.h"

HRESULT LastScene::init(void)
{
	_image = IMAGEMANAGER->findImage("¿£µù¾À Å×½ºÆ®¹è°æ");

	_pixel = new PixelCollision;
	_pixel->init(100,1790,"¿£µù¾À ÇÈ¼¿");

	_camera = new Camera;
	_camera->init();
	_camera->setLimitsX(CENTER_X, _image->getWidth());
	_camera->setLimitsY(CENTER_Y, _image->getHeight());
	_count = 0;
	return S_OK;
}

void LastScene::release(void)
{
	SAFE_DELETE(_pixel);

	_camera->release();
	SAFE_DELETE(_camera);
}

void LastScene::update(void)
{
	cout << _pixel->getX() << ", " << _pixel->getY() << ", " << _count << endl;
	_pixel->update("¿£µù¾À ÇÈ¼¿");
	if ( _pixel->getX() >= _image->getWidth() - 300)
	{
		
		_pixel->setX(_image->getWidth() - 300);
        _count++;
        if (_count > 30)
        {
            SCENEMANAGER->changeScene("Ending");
        }

	}
	else if (_pixel->getX() <= 100)
	{
		_pixel->setX(100);
	}

	if (_pixel->getX() > 3900)
	{
		_pixel->setX(_pixel->getX() - 0.8);
		if (_pixel->getX() > 4000)
		{
			_pixel->setX(_pixel->getX() - 0.95);
            
		}
	}
	POINT cameraPos;
	cameraPos.x = _pixel->getX();
	cameraPos.y = _pixel->getY();

	_camera->setCameraPos(cameraPos);
	_camera->update();

	_pixel->setCameraRect(_camera->getScreenRect());
}

void LastScene::render(void)
{
	/*IMAGEMANAGER->render("¿£µù¾À µÞ¹è°æ", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);*/
	IMAGEMANAGER->render("¿£µù¾À Å×½ºÆ®¹è°æ", getMemDC(), 0, 0,
		_camera->getScreenRect().left, 
		_camera->getScreenRect().top,
		WINSIZE_X, WINSIZE_Y);
	_pixel->render();
	IMAGEMANAGER->render("¿£µù¾À ¾Õ¹è°æ", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);
	IMAGEMANAGER->render("¿£µù¾À ¾Õ¹è°æ2", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);
	_camera->render();
}
