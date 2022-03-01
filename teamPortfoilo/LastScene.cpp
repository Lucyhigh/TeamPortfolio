#include "Stdafx.h"
#include "LastScene.h"

HRESULT LastScene::init(void)
{
	_image = IMAGEMANAGER->findImage("������ �׽�Ʈ���");

	_pixel = new PixelCollision;
	_pixel->init(0,0,"������ �ȼ�");

	_camera = new Camera;
	_camera->init();
	_camera->setLimitsX(CENTER_X, _image->getWidth());
	_camera->setLimitsY(CENTER_Y, _image->getHeight());
	/*
	������ �ٴ�", "R
	������ �׽�Ʈ���
	������ �޹��", 
	������ �չ��", 
	������ �ȼ�", "R
	
	*/
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
	_pixel->update("������ �ȼ�");
	if ( _pixel->getX() >= _image->getWidth())
	{
		//SCENEMANAGER->changeScene("BeforeBoss1");
	}
	else if (_pixel->getX() <= 100)
	{
		_pixel->setX(100);
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
	IMAGEMANAGER->render("������ �׽�Ʈ���", getMemDC(), 0, 0,
		_camera->getScreenRect().left, _camera->getScreenRect().top,
		WINSIZE_X, WINSIZE_Y);

	_camera->render();
	_pixel->render();
}
