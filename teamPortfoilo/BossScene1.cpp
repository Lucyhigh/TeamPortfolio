#include "Stdafx.h"
#include "BossScene1.h"

HRESULT BossScene1::init(void)
{
	_collider = new ColliderManager();
    _image = IMAGEMANAGER->findImage("보스1 바닥");

	floor0 = new RECT { 0, 630, _image->getWidth(),670};
	floor1 = new RECT{ 0, 0, 100, _image->getHeight() };
	floor2 = new RECT{ _image->getWidth()-70, 0, _image->getWidth(), _image->getHeight() };
	
	//floor1 = new RECT{ _image->getWidth(), 0, _image->getWidth()+100, 1000 };
	//floor2 = new RECT{ 0, 0, -100, 1000 };

	_floor.push_back(floor0);
	_floor.push_back(floor1);
	_floor.push_back(floor2);

	GAMEMANAGER->getPlayer()->ObjectInit({ 100,600 }, _floor);
	
	//boss = new BossWarden();
	//boss->init({ _image->getWidth()/2,CENTER_Y }, _floor);
	//_monster.push_back(boss);
	//GAMEMANAGER->setMonster(_monster);

    _camera = new Camera;
    _camera->init();
    _camera->setLimitsX(CENTER_X, _image->getWidth()); 
    _camera->setLimitsY(CENTER_Y, _image->getHeight()); 

	_bossHp = new BossUI;
	_bossHp->init();
  
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

	_bossHp->release();
	SAFE_DELETE(_bossHp);
}

void BossScene1::update(void)
{
	_collider->update();
	for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{ 
		GAMEMANAGER->getMonster()[i]->ObjectUpdate(); 
	}

    if ( GAMEMANAGER->getPlayer()->getPoint().x <= 100)
    {
        SCENEMANAGER->changeScene("BeforeBoss1");
    }
	if (GAMEMANAGER->getPlayer()->getPoint().x >= _image->getWidth() - 100)
	{
		SCENEMANAGER->changeScene("BeforeBoss2");
	}
    POINT cameraPos;
	cameraPos.x = GAMEMANAGER->getPlayer()->getPoint().x;
    cameraPos.y = _camera->getCameraPos().y;

    _camera->setCameraPos(cameraPos);
    _camera->update();

	GAMEMANAGER->getPlayer()->setCameraRect(_camera->getScreenRect());
	GAMEMANAGER->getPlayer()->ObjectUpdate();
	GAMEMANAGER->getUI()->update();
	_bossHp->update();
}

void BossScene1::render(void)
{
	float bg1Speed = 0.01;
	float bg2Speed = 0.02;
	RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
	IMAGEMANAGER->loopRender("보스1 뒷배경", getMemDC(), &rc1, 
											_camera->getScreenRect().left * bg1Speed, 
											_camera->getScreenRect().top * bg1Speed);

	IMAGEMANAGER->loopRender("보스1 뒷시체", getMemDC(), &rc1, 
											_camera->getScreenRect().left * bg2Speed,
											_camera->getScreenRect().top * bg2Speed);

    IMAGEMANAGER->render("보스1 바닥", getMemDC(), 0, 0,
                         _camera->getScreenRect().left, 
						 _camera->getScreenRect().top,
						 WINSIZE_X, WINSIZE_Y);
   
	for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
	{ 
		GAMEMANAGER->getMonster()[i]->ObjectRender(); 
	}

	GAMEMANAGER->getPlayer()->ObjectRender();
	IMAGEMANAGER->render("보스1 앞문", getMemDC(), -_camera->getScreenRect().left, 0);
	IMAGEMANAGER->render("보스1 앞시체", getMemDC(), -_camera->getScreenRect().left, 0);
	_collider->render();
	_camera->render();

	for (int i = 0; i < _floor.size(); i++)
	{
		//Rectangle(getMemDC(),_floor[i]->left, _floor[i]->top, _floor[i]->right, _floor[i]->bottom);
	}

	SetTextAlign(getMemDC(), TA_CENTER);
	LPCWSTR script = L"침묵의 비탄 파수꾼";
	FONTMANAGER->drawText(getMemDC(), CENTER_X, WINSIZE_Y - 90, "둥근모꼴", 22, 200,
		script, wcslen(script), RGB(175, 175, 115));

	GAMEMANAGER->getUI()->render();
	_bossHp->render();
}

/*
#include "Stdafx.h"
#include "BossScene1.h"

HRESULT BossScene1::init(void)
{
    _collider = new ColliderManager();
    _image = IMAGEMANAGER->findImage("보스1 바닥");

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
    _camera->setLimitsX(CENTER_X, _image->getWidth()); //좌우 카메라 이동 제한

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
    float bgSpeed = 0.02;
    RECT rc1 = { 0,0, WINSIZE_X, WINSIZE_Y };
    IMAGEMANAGER->loopRender("보스1 뒷배경", getMemDC(), &rc1,
        _camera->getScreenRect().left*bgSpeed,
        _camera->getScreenRect().left*bgSpeed);//
    IMAGEMANAGER->loopRender("보스1 뒷시체", getMemDC(), &rc1,
        _camera->getScreenRect().left*bgSpeed,
        _camera->getScreenRect().left*bgSpeed);//

    IMAGEMANAGER->render("보스1 바닥", getMemDC(), 0, 0,
                         _camera->getScreenRect().left, _camera->getScreenRect().top,
                         WINSIZE_X, WINSIZE_Y);

    for (int i = 0; i < GAMEMANAGER->getMonster().size(); i++)
    {
        //GAMEMANAGER->getMonster()[i]->ObjectRender();
    }

    GAMEMANAGER->getPlayer()->ObjectRender();
    IMAGEMANAGER->render("보스1 앞문", getMemDC(), -_camera->getScreenRect().left, 0);
    IMAGEMANAGER->render("보스1 앞시체", getMemDC(), -_camera->getScreenRect().left, 0);
    _collider->render();
    _camera->render();
}

*/