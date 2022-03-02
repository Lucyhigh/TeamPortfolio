#include "Stdafx.h"
#include "LastScene.h"

HRESULT LastScene::init(void)
{
	_image = IMAGEMANAGER->findImage("��Ʈ�� �ٴ�");

	_pixel = new PixelCollision;
	_pixel->init(100,1790,"��Ʈ�� �ȼ�");

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
	//cout << _pixel->getX() << ", " << _pixel->getY() << ", " << _count << endl;
	
	if ( _pixel->getX() >= _image->getWidth() - 400)
	{
		
		_pixel->setX(_image->getWidth() - 400);
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
    _pixel->update("��Ʈ�� �ȼ�");
}

void LastScene::render(void)
{
    float bg1Speed = 0.9;
    RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
    IMAGEMANAGER->loopRender("��Ʈ�� �޹��", getMemDC(), &rc1,
        _camera->getScreenRect().left * bg1Speed,
        _camera->getScreenRect().top * bg1Speed);

//    IMAGEMANAGER->alphaRender("�����̹���1", getMemDC(), 0, 0, _bgAlpha);//���ǽ�

	_pixel->render();
    IMAGEMANAGER->render("��Ʈ�� �ٴ�", getMemDC(),
        -_camera->getScreenRect().left,
        -_camera->getScreenRect().top);

	IMAGEMANAGER->render("��Ʈ�� �չ��", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);
	IMAGEMANAGER->render("��Ʈ�� �չ��2", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);

    IMAGEMANAGER->alphaRender("����ȯ", getMemDC(), 0, 0, _alpha);
	_camera->render();
}