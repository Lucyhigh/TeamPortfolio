#include "Stdafx.h"
#include "OpeningScene.h"

HRESULT OpeningScene::init(void)
{
	_image = IMAGEMANAGER->findImage("�����׾� �ٴ�");
	IMAGEMANAGER->findImage("�����׾� �ս�ü");
	IMAGEMANAGER->findImage("�����׾� �չ�"); 
	IMAGEMANAGER->findImage("�����׾� �޹��");

	IMAGEMANAGER->findImage("�����׾� �׽�Ʈ���");

	_pixel = new PixelCollision;
	_pixel->init(1680,944, "�����׾� �ȼ�");

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
	_pixel->update("�����׾� �ȼ�");
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

	IMAGEMANAGER->render("�����׾� �ٴ�", getMemDC(), 0, 0,
		_camera->getScreenRect().left, _camera->getScreenRect().top,
		WINSIZE_X, WINSIZE_Y);
	RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->loopRender("�����׾� �޹��", getMemDC(),&rc1, _pixel->getX(), _pixel->getY());
	IMAGEMANAGER->render("�����׾� �ս�ü", getMemDC() ,- _camera->getScreenRect().left, 0);
	IMAGEMANAGER->render("�����׾� �չ�", getMemDC(), -_camera->getScreenRect().left, 0);
	_camera->render();
	_pixel->render();
}
