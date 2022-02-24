#include "Stdafx.h"
#include "Boss1BeforeScene.h"

HRESULT Boss1BeforeScene::init(void)
{
    _mapImage = IMAGEMANAGER->findImage("보스1전배경");
    IMAGEMANAGER->findImage("보스1전FrontDoor");
    _objectImage = IMAGEMANAGER->findImage("stand");
    IMAGEMANAGER->findImage("버튼");
    _x = 1000;
    _y = WINSIZE_Y - 120;
    _ObjectRc = RectMakeCenter(_x, _y, _objectImage->getFrameWidth(), _objectImage->getFrameHeight());

    floor0 = new RECT{ 0, 600, _mapImage->getWidth(), 670 };
    floor1 = new RECT{ 1100, 0, 1300, 1000 };
    floor2 = new RECT{ 0, 0, 100, 1000 };
    _floor.push_back(floor0);
    //_floor.push_back(floor1);
    //_floor.push_back(floor2);
    GAMEMANAGER->getPlayer()->ObjectInit({ 0,0 }, _floor);
    _camera = new Camera;
    _camera->init();
    _camera->setLimits(CENTER_X, _mapImage->getWidth());
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
    POINT cameraPos;
    cameraPos.x = GAMEMANAGER->getPlayer()->getPoint().x;
    cameraPos.y = _camera->getCameraPos().y;

    _camera->setCameraPos(cameraPos);
    _camera->update();
    GAMEMANAGER->getPlayer()->setCameraRect(_camera->getScreenRect());
    GAMEMANAGER->getPlayer()->ObjectUpdate();
    cout << GAMEMANAGER->getPlayer()->getPoint().x << endl;
    if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) || GAMEMANAGER->getPlayer()->getPoint().x >= _mapImage->getWidth())
    {
    	SCENEMANAGER->changeScene("Boss1");
    }
}

void Boss1BeforeScene::render(void)
{
    IMAGEMANAGER->render("보스1전배경", getMemDC(), 0, 0,
                                       _camera->getScreenRect().left, _camera->getScreenRect().top,
                                       _camera->getScreenRect().right, _camera->getScreenRect().bottom);

    for (int i = 0; i < _floor.size(); i++)
    {
        Rectangle(getMemDC(), _floor[i]->left, _floor[i]->top, _floor[i]->right, _floor[i]->bottom);
    }

    GAMEMANAGER->getPlayer()->ObjectRender();
    IMAGEMANAGER->render("보스1전FrontDoor", getMemDC());
    _camera->render();
}
