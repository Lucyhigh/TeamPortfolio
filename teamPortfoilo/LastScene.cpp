#include "Stdafx.h"
#include "LastScene.h"

HRESULT LastScene::init(void)
{
	_image = IMAGEMANAGER->findImage("������ �׽�Ʈ���");

	_pixel = new PixelCollision;
	_pixel->init(100,1790,"������ �ȼ�");

    _textAlpha = 0;
    _alpha = 0;
    _bgAlpha = 0;

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
	_pixel->update("������ �ȼ�");
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
	//IMAGEMANAGER->render("������ �޹��", getMemDC(),
	//	-_camera->getScreenRect().left,
	//	-_camera->getScreenRect().top);
	IMAGEMANAGER->render("������ �׽�Ʈ���", getMemDC(), 0, 0,
		_camera->getScreenRect().left, 
		_camera->getScreenRect().top,
		WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->alphaRender("�����̹���2", getMemDC(), 0, 0, _bgAlpha);

	_pixel->render();
	IMAGEMANAGER->render("������ �չ��", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);
	IMAGEMANAGER->render("������ �չ��2", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);

    IMAGEMANAGER->alphaRender("����ȯ", getMemDC(), 0, 0, _alpha);
	_camera->render();
}
