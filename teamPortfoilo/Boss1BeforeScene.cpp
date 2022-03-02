#include "Stdafx.h"
#include "Boss1BeforeScene.h"

HRESULT Boss1BeforeScene::init(void)
{
    _mapImage = IMAGEMANAGER->findImage("����1�����");
    _objectImage = IMAGEMANAGER->findImage("stand");
   
    floor0 = new RECT{ 0, 600, _mapImage->getWidth(), 670 };
    floor1 = new RECT{ _mapImage->getWidth(), 0, _mapImage->getWidth()+100, _mapImage->getHeight() };
    floor2 = new RECT{ 0, 0, 100, _mapImage->getHeight() };
    _floor.push_back(floor0);
    _floor.push_back(floor1);
    _floor.push_back(floor2);

    GAMEMANAGER->getPlayer()->ObjectInit({ 0,0 }, _floor);

    _x = _mapImage->getWidth()*0.5;
    _y = WINSIZE_Y - 170;
    _ObjectRc = RectMakeCenter(_x, _y, _objectImage->getFrameWidth(), _objectImage->getFrameHeight());
	_ui = new UIScene;
	_ui->init();
    _camera = new Camera;
    _camera->init();
    _camera->setLimitsX(CENTER_X, _mapImage->getWidth());
    _camera->setLimitsY(CENTER_Y, _mapImage->getHeight());

    _indexA = 0;

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
}

void Boss1BeforeScene::render(void)
{
    int objectPosX = _ObjectRc.left - _camera->getScreenRect().left;
    int objectPosY = _ObjectRc.top - _camera->getScreenRect().top;
    int objectPosCenterX = ((_ObjectRc.left + _ObjectRc.right) * 0.5 ) - _camera->getScreenRect().left;

    int objectCenterX = (_ObjectRc.left + _ObjectRc.right) * 0.5;
    int objectCenterY = (_ObjectRc.top + _ObjectRc.bottom) * 0.5;

	float bgSpeed = 0.02;
	RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
    IMAGEMANAGER->render("����1�����", getMemDC(), 0, 0,
                                       _camera->getScreenRect().left,
									   _camera->getScreenRect().top,
									   WINSIZE_X, WINSIZE_Y);

    GAMEMANAGER->getPlayer()->ObjectRender();

    IMAGEMANAGER->frameRender("stand", getMemDC(), objectPosX, objectPosY);

    if (getDistance(objectCenterX, objectCenterY, GAMEMANAGER->getPlayer()->getPoint().x, GAMEMANAGER->getPlayer()->getPoint().y) < 200)
    {
        IMAGEMANAGER->render("��ư", getMemDC(), objectPosCenterX-40, objectPosY - 30);
        if (KEYMANAGER->isToggleKey('E'))
        {
            if (_ptMouse.x > CENTER_X - 300 && _ptMouse.y > CENTER_Y)
            {
                //IMAGEMANAGER->render("����â2", getMemDC(), CENTER_X - 300, CENTER_Y - 250);
            }
            else
            {
                //IMAGEMANAGER->render("����â1", getMemDC(), CENTER_X - 300, CENTER_Y - 250);
            }
        }
        else
        {
        }
    }
	
    IMAGEMANAGER->render("����1��FrontDoor", getMemDC(), -_camera->getScreenRect().left,0);
    _camera->render();
}
