#include "Stdafx.h"
#include "ColliderManager.h"
#include "Camera.h"
#include "BossScene2.h"

BossScene2::BossScene2(){
}


HRESULT BossScene2::init(void)
{
	_backGround = IMAGEMANAGER->findImage("Boss2BG");
	_floor.resize(3);
	_floor[0] = new RECT{ 0, 525, _backGround->getWidth(),670 };
	_floor[1] = new RECT{ -100, 0, 0, _backGround->getHeight() };
	_floor[2] = new RECT{ _backGround->getWidth(), 0, _backGround->getWidth()+100, _backGround->getHeight() };
	GAMEMANAGER->getPlayer()->ObjectInit({ 400,CENTER_Y }, _floor);

	_collider = new ColliderManager();

	_camera = new Camera();
	_camera->init();
	_camera->setLimitsX(CENTER_X, _backGround->getWidth());
	_camera->setLimitsY(CENTER_Y, _backGround->getHeight());

	isdora = new BossIsadora();
	isdora->init({ _backGround->getWidth() / 2,CENTER_Y }, _floor);
	GAMEMANAGER->setMonster(isdora);

	_bossHp = new BossUI;
	_bossHp->init();

	return S_OK;
}

void BossScene2::release(void)
{
	_bossHp->release();
	SAFE_DELETE(_bossHp);
}

void BossScene2::update(void)
{
	_cameraPos = { GAMEMANAGER->getPlayer()->getPoint().x, _camera->getCameraPos().y };
	_camera->setCameraPos(_cameraPos);
	_camera->update();

	GAMEMANAGER->getPlayer()->setCameraRect(_camera->getScreenRect());
	GAMEMANAGER->getPlayer()->ObjectUpdate();

	for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{
		GAMEMANAGER->getMonster()[i]->ObjectUpdate();
	}

	_collider->update();
	GAMEMANAGER->getUI()->update();
	_bossHp->update();
}

void BossScene2::render(void)
{
	_backGround->render(getMemDC(),0,0);

	for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{ GAMEMANAGER->getMonster()[i]->ObjectRender(); }

	GAMEMANAGER->getPlayer()->ObjectRender();

	GAMEMANAGER->getUI()->render();
	_bossHp->render();
}
