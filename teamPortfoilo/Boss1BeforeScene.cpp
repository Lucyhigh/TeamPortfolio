#include "Stdafx.h"
#include "Boss1BeforeScene.h"

HRESULT Boss1BeforeScene::init(void)
{
    _mapImage = IMAGEMANAGER->findImage("보스1전 바닥");
    _objectImage = IMAGEMANAGER->findImage("stand");
	_symbolImage = IMAGEMANAGER->findImage("SymbolObj");
	_breakSymbolImage = IMAGEMANAGER->findImage("breakSymbolObj");
	_SkeletonImage = IMAGEMANAGER->findImage("breakableSkeleton");


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

	_ui = new UIScene;
	_ui->init();

	_x = _mapImage->getWidth()*0.25;
	_y = WINSIZE_Y - 100;
	_SymbolRc = RectMakeCenter(_x, _y, _symbolImage->getFrameWidth(), _symbolImage->getFrameHeight());

	_x = _mapImage->getWidth()*0.25 + 20;
	_y = WINSIZE_Y - 125;
	_breakSymbolRc = RectMakeCenter(_x, _y, _breakSymbolImage->getFrameWidth(), _breakSymbolImage->getFrameHeight());

	_x = _mapImage->getWidth() * 0.75 + 380;
	_y = WINSIZE_Y - 225;
	_SkeletonRc = RectMakeCenter(_x, _y, _SkeletonImage->getFrameWidth(), _SkeletonImage->getFrameHeight());
	
    _camera = new Camera;
    _camera->init();
    _camera->setLimitsX(CENTER_X, _mapImage->getWidth());
    _camera->setLimitsY(CENTER_Y, _mapImage->getHeight());

    _indexA = _indexB = _indexC = _indexD = 0;
    _count = 0;

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
    
    if (GAMEMANAGER->getPlayer()->getPoint().x >= _mapImage->getWidth()-100)
    {
    	SCENEMANAGER->changeScene("Boss1");
    }

    int objectPosX = _ObjectRc.left - _camera->getScreenRect().left;
    int objectPosY = _ObjectRc.top - _camera->getScreenRect().top;

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

	_symbolPosX = _SymbolRc.left - _camera->getScreenRect().left;
	_symbolPosY = _SymbolRc.top - _camera->getScreenRect().top;

	_symbolCenterX = (_SymbolRc.left + _SymbolRc.right) * 0.5;
	_symbolCenterY = (_SymbolRc.top + _SymbolRc.bottom) * 0.5;

	if (getDistance(_symbolCenterX, _symbolCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 100)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_isBreak = true;
		}
	}

	_breaksymbolPosX = _breakSymbolRc.left - _camera->getScreenRect().left;
	_breaksymbolPosY = _breakSymbolRc.top - _camera->getScreenRect().top;

	_skeletonPosX = _SkeletonRc.left - _camera->getScreenRect().left;
	_skeletonPosY = _SkeletonRc.top - _camera->getScreenRect().top;

	_skeletonCenterX = (_SkeletonRc.left + _SkeletonRc.right) * 0.5;
	_skeletonCenterY = (_SkeletonRc.top + _SkeletonRc.bottom) * 0.5;

	if (getDistance(_skeletonCenterX, _skeletonCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 300)
	{
		if (KEYMANAGER->isStayKeyDown('A'))
		{
			_isBreakS = true;
		}
	}

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
}

void Boss1BeforeScene::render(void)
{
    int objectPosX = _ObjectRc.left - _camera->getScreenRect().left;
    int objectPosY = _ObjectRc.top - _camera->getScreenRect().top;
    int objectPosCenterX = ((_ObjectRc.left + _ObjectRc.right) * 0.5 ) - _camera->getScreenRect().left;

    int objectCenterX = (_ObjectRc.left + _ObjectRc.right) * 0.5;
    int objectCenterY = (_ObjectRc.top + _ObjectRc.bottom) * 0.5;

	float bgSpeed = 0.9;
	RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
	
    IMAGEMANAGER->loopRender("보스1 뒷배경", getMemDC(), &rc1,
        _camera->getScreenRect().left * bgSpeed,
        _camera->getScreenRect().top * bgSpeed);

    IMAGEMANAGER->render("보스1전 바닥", getMemDC(), 0, 0,
                                       _camera->getScreenRect().left,
									   _camera->getScreenRect().top,
									   WINSIZE_X, WINSIZE_Y);

    IMAGEMANAGER->frameRender("stand", getMemDC(), objectPosX, objectPosY);


    if (getDistance(objectCenterX, objectCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 200)
    {
        IMAGEMANAGER->render("버튼", getMemDC(), objectPosCenterX-40, objectPosY - 30);
    }

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

    IMAGEMANAGER->render("보스1전FrontDoor", getMemDC(), -_camera->getScreenRect().left,0);
    _camera->render();
}
