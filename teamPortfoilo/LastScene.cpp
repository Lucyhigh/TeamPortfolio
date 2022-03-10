
#include "Stdafx.h"
#include "LastScene.h"

HRESULT LastScene::init(void)
{
    _image = IMAGEMANAGER->findImage("LastSceneFloor");
    _frameNpcImage = IMAGEMANAGER->findImage("frameNpc");

    _pixel = new PixelCollision;
    _pixel->init(100, 1790, "LastScenePixel");

    _textAlpha = 0;
    _bgAlpha = 0;
    _count = 0;
    _isTalk = false;
    _indexA = _indexB = _indexCount = 0;

    _camera = new Camera;
    _camera->init();
    _camera->setLimitsX(CENTER_X, _image->getWidth());
    _camera->setLimitsY(CENTER_Y, _image->getHeight());

    _x = _image->getWidth() * 0.1;
    _y = 1710;
    _npcRc = RectMakeCenter(_x, _y, _frameNpcImage->getFrameWidth(), _frameNpcImage->getFrameHeight());


	_areaTextOn = false;
	_areaTextAlpha = 0;

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

	if (_areaTextOn)
	{
		_areaTextAlpha -= 0.05f;
		if (_areaTextAlpha <= 0) _areaTextAlpha = 0;
	}
	else
	{
		_areaTextAlpha++;
		if (_areaTextAlpha >= 255)
		{
			_areaTextAlpha = 255; _areaTextOn = true;
		}
	}

    TEMPSOUNDMANAGER->stopMp3WithKey("Peldanos");
    TEMPSOUNDMANAGER->playSoundWithKey("La");

    if (_pixel->getX() >= _image->getWidth() - 400)
    {
        _camera->setLimitsY(_image->getWidth() - 500, _image->getHeight());
        _count++;
        _pixel->setX(_image->getWidth() - 400);

        if (_count > 50)
        {
            SCENEMANAGER->changeScene("Ending");
            TEMPSOUNDMANAGER->stopMp3WithKey("La");
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

    _npcRcCenterX = (_npcRc.left + _npcRc.right) * 0.5;
    _npcRcCenterY = (_npcRc.top + _npcRc.bottom) * 0.5;
    // cout << _npcRcCenterX << " , " << _npcRcCenterY <<endl;

    if (getDistance(_npcRcCenterX, _npcRcCenterY, _pixel->getX(), _pixel->getY()) < 200)
    {
        if (KEYMANAGER->isOnceKeyDown('E'))
        {
            if (!_isTalk)
            {
                _isTalk = true;
            }
        }
    }
    else
    {
        _isTalk = false;
    }

    POINT cameraPos;
    cameraPos.x = _pixel->getX();
    cameraPos.y = _pixel->getY();

    _camera->setCameraPos(cameraPos);
    _camera->update();

    _pixel->setCameraRect(_camera->getScreenRect());
    _pixel->update("LastScenePixel");

    _indexCount++;
    if (_indexCount % 20 == 0)
    {
        _indexA++;
        _indexCount = 0;
        if (_indexA >= _frameNpcImage->getMaxFrameX())
        {
            _indexA = 0;
            _indexB++;
            if (_indexB >= _frameNpcImage->getMaxFrameX())
            {
                _indexB = 0;
            }
        }
    }
    if (_isTalk)
    {
        if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
        {
            if (_textIndex + 1 == TEXTNUM)
            {
                _isTalk = false;
                return;
            }
            _textIndex++;
            _textAlpha = 0;
            _bgAlpha = 0;

        }
    }
    _textAlpha += 2;
    if (_bgAlpha >= 255) _bgAlpha = 255;
    if (_textAlpha >= 100) _textAlpha = 100;


}

void LastScene::render(void)
{
    float bgSpeed = 0.9;
    RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
    IMAGEMANAGER->loopRender("LastSceneBack", getMemDC(), &rc1,
        _camera->getScreenRect().left * bgSpeed,
        _camera->getScreenRect().top * bgSpeed);


    IMAGEMANAGER->render("LastSceneFloor", getMemDC(),
        -_camera->getScreenRect().left,
        -_camera->getScreenRect().top);

    _npcPosX = _npcRc.left - _camera->getScreenRect().left;
    _npcPosY = _npcRc.top - _camera->getScreenRect().top;

    _npcRcCenterX = (_npcRc.left + _npcRc.right) * 0.5;
    _npcRcCenterY = (_npcRc.top + _npcRc.bottom) * 0.5;

    IMAGEMANAGER->frameRender("frameNpc", getMemDC(), _npcPosX, _npcPosY, _indexA, _indexB);

    _pixel->render();

    IMAGEMANAGER->render("LastSceneFront", getMemDC(),
        -_camera->getScreenRect().left,
        -_camera->getScreenRect().top);
    IMAGEMANAGER->render("LastSceneFront2", getMemDC(),
        -_camera->getScreenRect().left,
        -_camera->getScreenRect().top);

    _camera->render();

    if (getDistance(_npcRcCenterX, _npcRcCenterY, _pixel->getX(), _pixel->getY()) < 200)
    {
        if (!_isTalk)
        {
            IMAGEMANAGER->render("e", getMemDC(), _npcPosX + 43, _npcPosY - 7);
        }
        else
        {
            IMAGEMANAGER->alphaRender("changeScene", getMemDC(), 0, WINSIZE_Y - 150, _textAlpha);
            const int SCRIPT_MAX_LENGTH = 20;
            SetTextAlign(getMemDC(), TA_CENTER);
            FONTMANAGER->drawText(getMemDC(), CENTER_X, WINSIZE_Y*0.84, "µÕ±Ù¸ð²Ã", 30, 100, _text[_textIndex].text,
                SCRIPT_MAX_LENGTH, RGB(186, 177, 127));
            if (wcslen(_text[_textIndex].text) > SCRIPT_MAX_LENGTH)
            {
                FONTMANAGER->drawText(getMemDC(), CENTER_X, WINSIZE_Y*0.90, "µÕ±Ù¸ð²Ã", 30, 100,
                    _text[_textIndex].text + SCRIPT_MAX_LENGTH,
                    (SCRIPT_MAX_LENGTH < wcslen(_text[_textIndex].text)) ?
                    wcslen(_text[_textIndex].text) - SCRIPT_MAX_LENGTH : SCRIPT_MAX_LENGTH,
                    RGB(186, 177, 127));
            }
            IMAGEMANAGER->alphaRender("enter", getMemDC(), WINSIZE_X*0.90, WINSIZE_Y*0.90, _textAlpha + 70);
        }
    }

    IMAGEMANAGER->findImage("area4")->alphaRender(getMemDC(), 0, 130, _areaTextAlpha);
}
