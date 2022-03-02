#include "Stdafx.h"
#include "LastScene.h"

HRESULT LastScene::init(void)
{
	_image = IMAGEMANAGER->findImage("엔딩씬 테스트배경");

	_pixel = new PixelCollision;
	_pixel->init(100,1790,"엔딩씬 픽셀");

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
	cout << _pixel->getX() <<", "<< _pixel->getY() << endl;
	_pixel->update("엔딩씬 픽셀");
	if ( _pixel->getX() >= _image->getWidth()-100)
	{
		//엔딩이미지로 전환
		//_pixel->setX(_image->getWidth() - 100);
		//_count++;
		if (_count > 10)
		{
			//다른 엔딩씬으로 넘어감
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
	/*IMAGEMANAGER->render("엔딩씬 뒷배경", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);*/
	IMAGEMANAGER->render("엔딩씬 테스트배경", getMemDC(), 0, 0,
		_camera->getScreenRect().left, 
		_camera->getScreenRect().top,
		WINSIZE_X, WINSIZE_Y);
	_pixel->render();
	IMAGEMANAGER->render("엔딩씬 앞배경", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);
	IMAGEMANAGER->render("엔딩씬 앞배경2", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);
	_camera->render();
}
