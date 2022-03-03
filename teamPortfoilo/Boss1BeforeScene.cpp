#include "Stdafx.h"
#include "Boss1BeforeScene.h"

HRESULT Boss1BeforeScene::init(void)
{
    _mapImage = IMAGEMANAGER->findImage("º¸½º1Àü ¹Ù´Ú");
    _objectImage = IMAGEMANAGER->findImage("stand");
	_symbolImage = IMAGEMANAGER->findImage("SymbolObj");
	_breakSymbolImage = IMAGEMANAGER->findImage("breakSymbolObj");
	_SkeletonImage = IMAGEMANAGER->findImage("breakableSkeleton");
	_frameNpcImage = IMAGEMANAGER->findImage("frameNpc");

    floor0 = new RECT{ 0, 600, _mapImage->getWidth(), 670 };
    floor1 = new RECT{ _mapImage->getWidth(), 0, _mapImage->getWidth()+100, _mapImage->getHeight() };
    floor2 = new RECT{ 0, 0, 100, _mapImage->getHeight() };
    _floor.push_back(floor0);
    _floor.push_back(floor1);
    _floor.push_back(floor2);

    GAMEMANAGER->getPlayer()->ObjectInit({ 100,570 }, _floor);

	_x = _mapImage->getWidth()*0.5;
	_y = WINSIZE_Y - 170;
	_ObjectRc = RectMakeCenter(_x, _y, _objectImage->getFrameWidth(), _objectImage->getFrameHeight());

	_x = _mapImage->getWidth()*0.25;
	_y = WINSIZE_Y - 135;
	_SymbolRc = RectMakeCenter(_x, _y, _symbolImage->getFrameWidth(), _symbolImage->getFrameHeight());

	_x = _mapImage->getWidth()*0.25 + 20;
	_y = WINSIZE_Y - 170;
	_breakSymbolRc = RectMakeCenter(_x, _y, _breakSymbolImage->getFrameWidth(), _breakSymbolImage->getFrameHeight());

	_x = _mapImage->getWidth() * 0.75 + 380;
	_y = WINSIZE_Y - 225;
	_SkeletonRc = RectMakeCenter(_x, _y, _SkeletonImage->getFrameWidth(), _SkeletonImage->getFrameHeight());

	_x = _mapImage->getWidth() * 0.75 - 600;
	_y = WINSIZE_Y - 180;
	_npcRc = RectMakeCenter(_x, _y, _frameNpcImage->getFrameWidth(), _frameNpcImage->getFrameHeight());

	
    _camera = new Camera;
    _camera->init();
    _camera->setLimitsX(CENTER_X, _mapImage->getWidth());
    _camera->setLimitsY(CENTER_Y, _mapImage->getHeight());
	_isBreak = _isBreakEnd = _isBreakS = _isTalk = false;
    _indexA = _indexB = _indexC = _indexD = _indexE = _indexF = 0;
    _count = 0;
    _textAlpha = 0;
    _textIndex = 0;
    _alpha = 0;
    _bgAlpha = 0;

    return S_OK;
}

void Boss1BeforeScene::release(void)
{
    GAMEMANAGER->getPlayer()->ObjectrRelease();

    _camera->release();
    SAFE_DELETE(_camera);
}

void Boss1BeforeScene::update(void)
{
	_count++;
    
    if (GAMEMANAGER->getPlayer()->getPoint().x >= _mapImage->getWidth()-100)
    {
    	SCENEMANAGER->changeScene("Boss1");
    }

    int objectCenterX = (_ObjectRc.left + _ObjectRc.right) * 0.5;
    int objectCenterY = (_ObjectRc.top + _ObjectRc.bottom) * 0.5;
    if (getDistance(objectCenterX, objectCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 200)
    {
        if (KEYMANAGER->isOnceKeyDown('E'))
        {
			_indexA = 1;
			GAMEMANAGER->getPlayer()->setHp(GAMEMANAGER->getPlayer()->getHp(BaseEnum::MAX),136);
			_ui->setPotion();
        }
    }

	_symbolCenterX = (_SymbolRc.left + _SymbolRc.right) * 0.5;
	_symbolCenterY = (_SymbolRc.top + _SymbolRc.bottom) * 0.5;

	if (getDistance(_symbolCenterX, _symbolCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 100)
	{
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			_isBreak = true;
		}
	}

	_skeletonCenterX = (_SkeletonRc.left + _SkeletonRc.right) * 0.5;
	_skeletonCenterY = (_SkeletonRc.top + _SkeletonRc.bottom) * 0.5;

	if (getDistance(_skeletonCenterX, _skeletonCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 300)
	{
		if (KEYMANAGER->isOnceKeyDown('K'))
		{
			_isBreakS = true;
		}
	}

	_npcRcCenterX = (_npcRc.left + _npcRc.right) * 0.5;
	_npcRcCenterY = (_npcRc.top + _npcRc.bottom) * 0.5;

    if (getDistance(_npcRcCenterX, _npcRcCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 200)
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

    //cout << _isTalk << " , " << _npcRcCenterY << " , " << GAMEMANAGER->getPlayer()->getPoint().y << endl;//

    if (_indexA >= 1)
    {
        _indexA++;
        IMAGEMANAGER->findImage("stand")->setFrameY(1);
        if (_indexA >= 7)
        {
            _indexA = 1;
        }
        IMAGEMANAGER->findImage("stand")->setFrameX(_indexA);
    }
    else
    {
        IMAGEMANAGER->findImage("stand")->setFrameY(1);
        IMAGEMANAGER->findImage("stand")->setFrameX(_indexA);
    }

	POINT cameraPos;
	cameraPos.x = GAMEMANAGER->getPlayer()->getPoint().x;
	cameraPos.y = _camera->getCameraPos().y;

	_camera->setCameraPos(cameraPos);
	_camera->update();
	GAMEMANAGER->getPlayer()->setCameraRect(_camera->getScreenRect());
	GAMEMANAGER->getPlayer()->ObjectUpdate();

	if (!_isBreak)
	{
		if (_count % 15 == 0)
		{
			_indexB++;
			_count = 0;
			if (_indexB >= _symbolImage->getMaxFrameX())
			{
				_indexB = 0;
			}
		}
		IMAGEMANAGER->findImage("SymbolObj")->setFrameX(_indexB);
	}
	else
	{
		if (_count % 15 == 0)
		{
			_indexC++;
			_count = 0;
			if (_indexC >= _breakSymbolImage->getMaxFrameX())
			{
				_indexC = _breakSymbolImage->getMaxFrameX();
				_isBreakEnd = true;
			}
		}
		IMAGEMANAGER->findImage("breakSymbolObj")->setFrameX(_indexC);
	}

	if (_isBreakS)
	{
		if (_count % 20 == 0)
		{
			_indexD++;
			_count = 0; 
			if (_indexD >= _SkeletonImage->getMaxFrameX())
			{
				_indexD = _SkeletonImage->getMaxFrameX();
			}
		}
		IMAGEMANAGER->findImage("breakableSkeleton")->setFrameX(_indexD);
	}

	if (_count % 20 == 0)
	{
		_indexE++;
		if (_indexE >= _frameNpcImage->getMaxFrameX())
		{
			_indexE = 0;
			_indexF++;
			if (_indexF >= _frameNpcImage->getMaxFrameX())
			{
				_indexF = 0;
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
            _alpha = 255;
        }
    }
    _textAlpha += 2;
    if (_bgAlpha >= 255) _bgAlpha = 255;
    if (_alpha <= 0) _alpha = 0;
    if (_textAlpha >= 100) _textAlpha = 100;
}

void Boss1BeforeScene::render(void)
{
    int objectPosX = _ObjectRc.left - _camera->getScreenRect().left;
    int objectPosY = _ObjectRc.top - _camera->getScreenRect().top;
    int objectPosCenterX = ((_ObjectRc.left + _ObjectRc.right) * 0.5 ) - _camera->getScreenRect().left;

    int objectCenterX = (_ObjectRc.left + _ObjectRc.right) * 0.5;
    int objectCenterY = (_ObjectRc.top + _ObjectRc.bottom) * 0.5;

	_symbolPosX = _SymbolRc.left - _camera->getScreenRect().left;
	_symbolPosY = _SymbolRc.top - _camera->getScreenRect().top;

	_breaksymbolPosX = _breakSymbolRc.left - _camera->getScreenRect().left;
	_breaksymbolPosY = _breakSymbolRc.top - _camera->getScreenRect().top;

	_skeletonPosX = _SkeletonRc.left - _camera->getScreenRect().left;
	_skeletonPosY = _SkeletonRc.top - _camera->getScreenRect().top;

	_npcPosX = _npcRc.left - _camera->getScreenRect().left;
	_npcPosY = _npcRc.top - _camera->getScreenRect().top;

	float bgSpeed = 0.9;
	RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
	
    IMAGEMANAGER->loopRender("º¸½º1 µÞ¹è°æ", getMemDC(), &rc1,
        _camera->getScreenRect().left * bgSpeed,
        _camera->getScreenRect().top * bgSpeed);

    IMAGEMANAGER->render("º¸½º1Àü ¹Ù´Ú", getMemDC(), 0, 0,
                                       _camera->getScreenRect().left,
									   _camera->getScreenRect().top,
									   WINSIZE_X, WINSIZE_Y);

    IMAGEMANAGER->frameRender("stand", getMemDC(), objectPosX, objectPosY);

    if (getDistance(objectCenterX, objectCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 200)
    {
        IMAGEMANAGER->render("¹öÆ°", getMemDC(), objectPosCenterX-40, objectPosY - 50);
    }
	
    IMAGEMANAGER->frameRender("frameNpc", getMemDC(), _npcPosX, _npcPosY, _indexE, _indexF);

	int _symbolPosCenterX = ((_SymbolRc.left + _SymbolRc.right) * 0.5) - _camera->getScreenRect().left;

	if (!_isBreak)
	{
		IMAGEMANAGER->frameRender("SymbolObj", getMemDC(), _symbolPosX, _symbolPosY, _indexB, 0);
		if (getDistance(_symbolCenterX, _symbolCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 100)
		{
			IMAGEMANAGER->render("k", getMemDC(), _symbolPosCenterX - 10 , _symbolPosY - 60);

		}
	}

	if (_isBreak && ! _isBreakEnd)
	{
		IMAGEMANAGER->frameRender("breakSymbolObj", getMemDC(), _breaksymbolPosX, _breaksymbolPosY, _indexC, 0);
	}

	IMAGEMANAGER->frameRender("breakableSkeleton", getMemDC(), _skeletonPosX, _skeletonPosY, _indexD, 0);

    GAMEMANAGER->getPlayer()->ObjectRender();

    IMAGEMANAGER->render("º¸½º1ÀüFrontDoor", getMemDC(), -_camera->getScreenRect().left,0);

    _camera->render();

	if (getDistance(_npcRcCenterX, _npcRcCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 200)
	{
		if (!_isTalk)
		{
			IMAGEMANAGER->render("e", getMemDC(), objectPosCenterX + 470, objectPosY + 30);
		}
		else
		{
			IMAGEMANAGER->alphaRender("ÄÆÀüÈ¯", getMemDC(), 0, WINSIZE_Y - 150, _textAlpha);
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
		}
	}
}
