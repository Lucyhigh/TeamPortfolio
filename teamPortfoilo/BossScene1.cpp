#include "Stdafx.h"
#include "BossScene1.h"

HRESULT BossScene1::init(void)
{
	_collider = new ColliderManager();
    _image = IMAGEMANAGER->findImage("보스1배경");

	floor0 = new RECT { 0, 600, _image->getWidth(),670};
	floor1 = new RECT{ _image->getWidth(), 0, _image->getWidth()+100, 1000 };
	floor2 = new RECT{ 0, 0, -100, 1000 };

	_floor.push_back(floor0);
	_floor.push_back(floor1);
	_floor.push_back(floor2);

	GAMEMANAGER->getPlayer()->ObjectInit({ 0,0 }, _floor);
	boss = new BossWarden();
	boss->init({ 0,0 }, _floor);
	_monster.push_back(boss);
	GAMEMANAGER->setMonster(_monster);

    _camera = new Camera;
    _camera->init();
    _camera->setLimits(CENTER_X, _image->getWidth()); //좌우 카메라 이동 제한

	return S_OK;
}

void BossScene1::release(void)
{
	for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{ 
		GAMEMANAGER->getMonster()[i]->ObjectrRelease();
	}

	GAMEMANAGER->getPlayer()->ObjectrRelease();

    _camera->release();
    SAFE_DELETE(_camera);
}

void BossScene1::update(void)
{
	_collider->update();
	for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{ 
		GAMEMANAGER->getMonster()[i]->ObjectUpdate(); 
	}

    if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON) || GAMEMANAGER->getPlayer()->getPoint().x <= 0)
    {
        SCENEMANAGER->changeScene("BeforeBoss1");
    }

    POINT cameraPos;
	cameraPos.x = GAMEMANAGER->getPlayer()->getPoint().x;
    cameraPos.y = _camera->getCameraPos().y;

    _camera->setCameraPos(cameraPos);
    _camera->update();

	GAMEMANAGER->getPlayer()->setCameraRect(_camera->getScreenRect());
	GAMEMANAGER->getPlayer()->ObjectUpdate();
}

void BossScene1::render(void)
{
    IMAGEMANAGER->render("보스1배경", getMemDC(), 0, 0,
                         _camera->getScreenRect().left, _camera->getScreenRect().top,
                         _camera->getScreenRect().right, _camera->getScreenRect().bottom);
   
	for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{ 
		GAMEMANAGER->getMonster()[i]->ObjectRender(); 
	}

	for (int i = 0; i < _floor.size(); i++)
	{
		Rectangle(getMemDC(),_floor[i]->left -_camera->getScreenRect().left, _floor[i]->top -_camera->getScreenRect().top,
            _floor[i]->right-_camera->getScreenRect().left, _floor[i]->bottom - _camera->getScreenRect().top);
	}

	GAMEMANAGER->getPlayer()->ObjectRender();
	_collider->render();
	_camera->render();
}
