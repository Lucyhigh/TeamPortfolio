#include "Stdafx.h"
#include "BossScene1.h"

HRESULT BossScene1::init(void)
{
	_collider = new ColliderManager();
    _image = IMAGEMANAGER->findImage("����1 �ٴ�");

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
    _camera->setLimitsX(CENTER_X, _image->getWidth()); 
    _camera->setLimitsY(CENTER_X, _image->getHeight()); 
  
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

    if ( GAMEMANAGER->getPlayer()->getPoint().x <= 50)
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
	float bg1Speed = 0.01;
	float bg2Speed = 0.02;
	RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->loopRender("����1 �޹��", getMemDC(), &rc1, 
											_camera->getScreenRect().left * bg1Speed, 
											_camera->getScreenRect().top * bg1Speed);

	IMAGEMANAGER->loopRender("����1 �޽�ü", getMemDC(), &rc1, 
											_camera->getScreenRect().left * bg2Speed,
											_camera->getScreenRect().top * bg2Speed);

    IMAGEMANAGER->render("����1 �ٴ�", getMemDC(), 0, 0,
                         _camera->getScreenRect().left, 
						 _camera->getScreenRect().top,
						 WINSIZE_X, WINSIZE_Y);
   
	for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{ 
		GAMEMANAGER->getMonster()[i]->ObjectRender(); 
	}

	GAMEMANAGER->getPlayer()->ObjectRender();
	IMAGEMANAGER->render("����1 �չ�", getMemDC(), -_camera->getScreenRect().left, 0);
	IMAGEMANAGER->render("����1 �ս�ü", getMemDC(), -_camera->getScreenRect().left, 0);
	//_collider->render();
	_camera->render();
}