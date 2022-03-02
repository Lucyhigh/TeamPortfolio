#include "Stdafx.h"
#include "LastScene.h"

HRESULT LastScene::init(void)
{
	_image = IMAGEMANAGER->findImage("¶ó½ºÆ®¾À ¹Ù´Ú");

	_pixel = new PixelCollision;
	_pixel->init(100,1790,"¶ó½ºÆ®¾À ÇÈ¼¿");

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

void LastScene::release(void)
{
	SAFE_DELETE(_pixel);

	_camera->release();
	SAFE_DELETE(_camera);
}

void LastScene::update(void)
{
	if ( _pixel->getX() >= _image->getWidth() - 400)
	{
        _count++;
		_pixel->setX(_image->getWidth() - 400);
		
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
    _pixel->update("¶ó½ºÆ®¾À ÇÈ¼¿");
}

void LastScene::render(void)
{
    float bgSpeed = 0.9;
    RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
    IMAGEMANAGER->loopRender("¶ó½ºÆ®¾À µŞ¹è°æ", getMemDC(), &rc1,
        _camera->getScreenRect().left * bgSpeed,
        _camera->getScreenRect().top * bgSpeed);


    IMAGEMANAGER->render("¶ó½ºÆ®¾À ¹Ù´Ú", getMemDC(),
        -_camera->getScreenRect().left,
        -_camera->getScreenRect().top);
	_pixel->render();

	IMAGEMANAGER->render("¶ó½ºÆ®¾À ¾Õ¹è°æ", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);
	IMAGEMANAGER->render("¶ó½ºÆ®¾À ¾Õ¹è°æ2", getMemDC(),
		-_camera->getScreenRect().left,
		-_camera->getScreenRect().top);

    IMAGEMANAGER->alphaRender("ÄÆÀüÈ¯", getMemDC(), 0, 0, _alpha);
	_camera->render();
}