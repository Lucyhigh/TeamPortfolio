#include "Stdafx.h"
#include "Boss2BeforeScene.h"

HRESULT Boss2BeforeScene::init(void)
{
	_image = IMAGEMANAGER->findImage("보스2전 배경");
	_npcsimage = IMAGEMANAGER->findImage("SandNPCStanding");
	_npcimage = IMAGEMANAGER->findImage("SandNPC");

	floor0 = new RECT{ 0, 630, _image->getWidth(), 670 };//
	floor1 = new RECT{ _image->getWidth(), 0, _image->getWidth() + 100, _image->getHeight() };
	floor2 = new RECT{ 0, 0, 100, _image->getHeight() };//

	_floor.push_back(floor0);
	_floor.push_back(floor1);
	_floor.push_back(floor2);

	GAMEMANAGER->getPlayer()->ObjectInit({ 100,630 }, _floor);//

	_camera = new Camera;
	_camera->init();
	_camera->setLimitsX(CENTER_X, _image->getWidth());
	_camera->setLimitsY(CENTER_Y, _image->getHeight());

	_count = 0;

	_indexA = _indexB = 0;

	return S_OK;
}

void Boss2BeforeScene::release(void)
{
	GAMEMANAGER->getPlayer()->ObjectrRelease();

	_camera->release();
	SAFE_DELETE(_camera);
}

void Boss2BeforeScene::update(void)
{
	_count++;

	if (GAMEMANAGER->getPlayer()->getPoint().x >= _image->getWidth() - 100)
	{
		SCENEMANAGER->changeScene("Boss2");
	}

	POINT cameraPos;
	cameraPos.x = GAMEMANAGER->getPlayer()->getPoint().x;
	cameraPos.y = _camera->getCameraPos().y;

	_camera->setCameraPos(cameraPos);
	_camera->update();

	GAMEMANAGER->getPlayer()->setCameraRect(_camera->getScreenRect());
	GAMEMANAGER->getPlayer()->ObjectUpdate();
	GAMEMANAGER->getUI()->update();

	if (_count % 20 == 0)
	{
		_indexA++;
		if (_indexA >= _npcimage->getMaxFrameX())
		{
			_indexA = 0;
			_indexB++;
			if (_indexB >= _npcimage->getMaxFrameX())
			{
				_indexB = 0;
			}
		}
	}
}

void Boss2BeforeScene::render(void)
{
	IMAGEMANAGER->render("보스2전 배경", getMemDC(), 0, 0,
		_camera->getScreenRect().left,
		_camera->getScreenRect().top,
		WINSIZE_X, WINSIZE_Y);

	IMAGEMANAGER->frameRender("SandNPC", getMemDC(), WINSIZE_X - 500, WINSIZE_Y - 100, _indexA, _indexB);

	GAMEMANAGER->getPlayer()->ObjectRender();

	IMAGEMANAGER->render("보스2전 FrontDoor", getMemDC(), -_camera->getScreenRect().left, 0);

	_camera->render();

	GAMEMANAGER->getUI()->render();
}