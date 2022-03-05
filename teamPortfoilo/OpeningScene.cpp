#include "Stdafx.h"
#include "OpeningScene.h"

HRESULT OpeningScene::init(void)
{
	_image = IMAGEMANAGER->findImage("�����׾� �ٴ�");

	_pixel = new PixelCollision;
	_pixel->init(_image->getWidth()/2-150, 455, "�����׾� �ȼ�");

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
	cout << _ptMouse.y << endl;

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
	_pixel->update("�����׾� �ȼ�");
}

void OpeningScene::render(void)
{
	float bgSpeed = 0.9;
	RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->loopRender("�����׾� �޹��", getMemDC(), &rc1,
		_camera->getScreenRect().left * bgSpeed,
		_camera->getScreenRect().top * bgSpeed);

	IMAGEMANAGER->render("�����׾� �ٴ�", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);

	_pixel->render();

	if (!_pixel->getWakeUp())
	{
		IMAGEMANAGER->render("k", getMemDC(),
			_pixel->getX() - _camera->getScreenRect().left-5,
			_pixel->getY() - _camera->getScreenRect().top - 100);
	}

	IMAGEMANAGER->render("�����׾� �ս�ü", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);
	IMAGEMANAGER->render("�����׾� �չ�", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);


	_camera->render();
}
