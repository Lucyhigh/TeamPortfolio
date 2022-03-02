#include "Stdafx.h"
#include "Boss1BeforeScene.h"

HRESULT Boss1BeforeScene::init(void)
{
    _mapImage = IMAGEMANAGER->findImage("보스1전배경");
    _objectImage = IMAGEMANAGER->findImage("stand");
	_symbolImage = IMAGEMANAGER->findImage("SymbolObj");
	_breakSymbolImage = IMAGEMANAGER->findImage("breakSymbolObj");
	_SkeletonImage = IMAGEMANAGER->findImage("breakableSkeleton");
    IMAGEMANAGER->findImage("보스1전FrontDoor");
    IMAGEMANAGER->findImage("버튼");
	IMAGEMANAGER->findImage("k");

    floor0 = new RECT{ 0, 600, _mapImage->getWidth(), 670 };
    floor1 = new RECT{ 1100, 0, 1300, 1000 };
    floor2 = new RECT{ 0, 0, 100, 1000 };
    _floor.push_back(floor0);
    //_floor.push_back(floor1);
    //_floor.push_back(floor2);
    GAMEMANAGER->getPlayer()->ObjectInit({ 0,0 }, _floor);

    _x = _mapImage->getWidth()*0.5;
    _y = WINSIZE_Y - 170;
    _ObjectRc = RectMakeCenter(_x, _y, _objectImage->getFrameWidth(), _objectImage->getFrameHeight());

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
    _camera->setLimits(CENTER_X, _mapImage->getWidth());

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
    _count++;
    POINT cameraPos;
    cameraPos.x = GAMEMANAGER->getPlayer()->getPoint().x;
    cameraPos.y = _camera->getCameraPos().y;

    _camera->setCameraPos(cameraPos);
    _camera->update();
    GAMEMANAGER->getPlayer()->setCameraRect(_camera->getScreenRect());
    GAMEMANAGER->getPlayer()->ObjectUpdate();

    if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) || GAMEMANAGER->getPlayer()->getPoint().x >= _mapImage->getWidth())
    {
    	SCENEMANAGER->changeScene("Boss1");
    }

    int objectPosX = _ObjectRc.left - _camera->getScreenRect().left;
    int objectPosY = _ObjectRc.top - _camera->getScreenRect().top;

    int objectCenterX = (_ObjectRc.left + _ObjectRc.right) * 0.5;
    int objectCenterY = (_ObjectRc.top + _ObjectRc.bottom) * 0.5;
    if (getDistance(objectCenterX, objectCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 200)
    {
        if (KEYMANAGER->isToggleKey('E'))
        {
            _indexA++;
            //자동 세이브 
            //체력 포션 풀로 채워짐
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


   /* cout << GAMEMANAGER->getPlayer()->getPoint().x <<" 거리 :"<<
        getDistance(objectCenterX, objectCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y)
        <<" indexA: "<< _indexA << endl;*/

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
    IMAGEMANAGER->render("보스1전배경", getMemDC(), 0, 0,
                                       _camera->getScreenRect().left, _camera->getScreenRect().top,
									   WINSIZE_X, WINSIZE_Y);

    for (int i = 0; i < _floor.size(); i++)
    {
        Rectangle(getMemDC(), _floor[i]->left, _floor[i]->top, _floor[i]->right, _floor[i]->bottom);
    }

    GAMEMANAGER->getPlayer()->ObjectRender();

    int objectPosX = _ObjectRc.left - _camera->getScreenRect().left;
    int objectPosY = _ObjectRc.top - _camera->getScreenRect().top;
    int objectPosCenterX = ((_ObjectRc.left + _ObjectRc.right) * 0.5 ) - _camera->getScreenRect().left;

    int objectCenterX = (_ObjectRc.left + _ObjectRc.right) * 0.5;
    int objectCenterY = (_ObjectRc.top + _ObjectRc.bottom) * 0.5;
	IMAGEMANAGER->frameRender("stand", getMemDC(), objectPosX, objectPosY);
    if (getDistance(objectCenterX, objectCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 200)
    {
        IMAGEMANAGER->render("버튼", getMemDC(), objectPosCenterX-40, objectPosY - 30);
        if (KEYMANAGER->isToggleKey('E'))
        {
            if (_ptMouse.x > CENTER_X - 300 && _ptMouse.y > CENTER_Y)
            {
                //IMAGEMANAGER->render("선택창2", getMemDC(), CENTER_X - 300, CENTER_Y - 250);
            }
            else
            {
                //IMAGEMANAGER->render("선택창1", getMemDC(), CENTER_X - 300, CENTER_Y - 250);
            }
        }
        else
        {
        }
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

    IMAGEMANAGER->render("보스1전FrontDoor", getMemDC(), -_camera->getScreenRect().left,0);
    _camera->render();
}
