#include "Stdafx.h"
#include "PixelScene.h"

HRESULT PixelScene::init(void)
{
	_image = IMAGEMANAGER->findImage("�����׾� �ȼ�");
	//IMAGEMANAGER->findImage("�����׾� �׽�Ʈ���");

	_pixel = new PixelCollision;
	_pixel->init();

	_camera = new Camera;
	_camera->init();
	_camera->setLimitsX(CENTER_X, _image->getWidth());
	_camera->setLimitsY(CENTER_Y, _image->getHeight());

	return S_OK;
}

void PixelScene::release(void)
{
	SAFE_DELETE(_pixel);

	_camera->release();
	SAFE_DELETE(_camera);
}

void PixelScene::update(void)
{
	_pixel->update();
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

void PixelScene::render(void)
{
	//cout << _camera->getScreenRect().left << " " << _camera->getScreenRect().top << endl;

	IMAGEMANAGER->render("�����׾� �׽�Ʈ���", getMemDC(), 0, 0,
		_camera->getScreenRect().left, _camera->getScreenRect().top,
		WINSIZE_X, WINSIZE_Y);

	/*IMAGEMANAGER->render("�����׾� �ȼ�", getMemDC(), 0, 0,
		_camera->getScreenRect().left, _camera->getScreenRect().top,
		WINSIZE_X, WINSIZE_Y);*/

	_camera->render();
	//IMAGEMANAGER->findImage("�����׾� �ȼ�")->render(getMemDC());
	//IMAGEMANAGER->findImage("�����׾� �׽�Ʈ���")->render(getMemDC());
	_pixel->render();
}
