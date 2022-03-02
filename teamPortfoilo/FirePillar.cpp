#include "Stdafx.h"
#include "BossIsadora.h"
#include "FirePillar.h"

FirePillar::FirePillar()
{
	ObjectrRelease = bind(&FirePillar::release, this);
	ObjectUpdate = bind(&FirePillar::update, this);
	ObjectRender = bind(&FirePillar::render, this);
}

FirePillar::~FirePillar()
{ 

}

HRESULT FirePillar::init(POINT mid, BossIsadora* tag)
{
	_Collider[BaseEnum::UNIT] = { mid.x - 40, mid.y - 300, mid.x + 40, mid.y };
	_outPoint = { getPoint().x ,_Collider[BaseEnum::UNIT].top };
	_isadora = tag;
	stateFloor = _isadora->getStateFloor();
	_dely = TIMEMANAGER->getWorldTime();

	_image = IMAGEMANAGER->findImage("bIsiFirePillar");
	_image->setX(_Collider[BaseEnum::UNIT].left -10);
	_image->setY(_Collider[BaseEnum::UNIT].top-25);

	_framFirePillar = new Animation();
	_framFirePillar->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
	_framFirePillar->setPlayFrame(0,9, false, true);
	_framFirePillar->setFPS(9, 2);
	_framFirePillar->AniStart();
	return S_OK;
}

void FirePillar::release(void)
{

}


void FirePillar::update(void)
{
	if (TIMEMANAGER->getElapsedTime() >= 0.0f)
	{
		_framFirePillar->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	}

	if (_isadora->getHp(BaseEnum::STATE) == 0)
	{
		_framFirePillarDie();
		return;
	}

	_updateFireball();
	_updateEffect();

	if (_isadora->pillarDelly == false) { return; }
	if (2.0f + _dely > TIMEMANAGER->getWorldTime()) { return; }
	_dely = TIMEMANAGER->getWorldTime();
	
	/*
	smash.push_back({ RECT{0,0,0,0}, Image() });
	smash.back().second.init("Resources/Images/Monster/Boss_Isidora/isidoraFireBallLoop.bmp", 600, 64, 12, 1, MGT);
	smash.back().first = RectMakeCenter(getPoint().x, _Collider[BaseEnum::UNIT].top, 40, 40);
	smash.back().second.setX(smash.back().first.left-5);
	smash.back().second.setY(smash.back().first.top-12);

	pairSmash.push_back(new Animation());
	pairSmash.back()->init(smash.back().second.getWidth(), smash.back().second.getHeight(), smash.back().second.getFrameWidth(), smash.back().second.getFrameHeight());
	pairSmash.back()->setDefPlayFrame(false, true);
	pairSmash.back()->setFPS(10,1); 
	pairSmash.back()->AniStart();
	*/
}

void FirePillar::render(void)
{
	float imageX = _image->getX() - GAMEMANAGER->getPlayer()->getCamareRect().left;
	float imageY = _image->getY() - GAMEMANAGER->getPlayer()->getCamareRect().top;
	_image->aniRender(getMemDC(), imageX, imageY, _framFirePillar);

	for (int i = 0; i < smash.size(); i++)
	{
		float effectX = smash[i].first.left - GAMEMANAGER->getPlayer()->getCamareRect().left;
		float effectY = smash[i].first.top - GAMEMANAGER->getPlayer()->getCamareRect().top;
		smash[i].second.aniRender(getMemDC(), effectX, effectY, pairSmash[i]);
	}

	for (int i = 0; i < effect.size(); i++)
	{
		float effectX = effect[i].first.getX() - GAMEMANAGER->getPlayer()->getCamareRect().left;
		float effectY = effect[i].first.getY() - GAMEMANAGER->getPlayer()->getCamareRect().top;
		effect[i].first.aniRender(getMemDC(), effectX, effectY, effect[i].second);
	}
}

POINT FirePillar::_fireballMid(int num)
{
	return POINT{ (smash[num].first.right + smash[num].first.left) / 2, (smash[num].first.bottom + smash[num].first.top) / 2 };
}

// ∫“≤…¿« ¿Ãµø
void FirePillar::_updateFireball()
{
	float angle;
	POINT mid;
	RECT temp;
	for (int i = 0; i < smash.size(); i++)
	{
		mid = _fireballMid(i);
		angle = atan2f(mid.x - GAMEMANAGER->getPlayer()->getPoint().x, mid.y - (stateFloor.top)) * 180 / 3.1415f;
		mid.x += cos(angle) * GAMESPEED;
		mid.y += -sinf(angle) * GAMESPEED;

		smash[i].first = RectMakeCenter(mid.x, mid.y, 40, 40);
		smash[i].second.setX(smash[i].first.left - 5);
		smash[i].second.setY(smash[i].first.top - 12);

		pairSmash[i]->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

		if (IntersectRect(&temp, &smash[i].first, &GAMEMANAGER->getPlayer()->getCollider()))
		{
			GAMEMANAGER->getPlayer()->setHit(1);
			effect.push_back({ Image(),new Animation() });
			effect.back().first.init("Resources/Images/Monster/Boss_Isidora/IsidoraProjectileOut.bmp", 200, 192, 4, 3, MGT);
			effect.back().first.setX(smash[i].second.getX());
			effect.back().first.setY(smash[i].second.getY());
			effect.back().second->init(effect.back().first.getWidth(), effect.back().first.getHeight(), effect.back().first.getFrameWidth(), effect.back().first.getFrameHeight());
			effect.back().second->setDefPlayFrame(false, false);
			effect.back().second->setFPS(12, 2);
			effect.back().second->AniStart();
			smash.erase(smash.begin() + i);
			pairSmash.erase(pairSmash.begin() + i);
			return;
		}

		if (IntersectRect(&temp, &smash[i].first, &stateFloor))
		{
			effect.push_back({ Image(),new Animation() });
			effect.back().first.init("Resources/Images/Monster/Boss_Isidora/IsidoraProjectileOut.bmp", 200, 192, 4, 3, MGT);
			effect.back().first.setX(smash[i].second.getX());
			effect.back().first.setY(smash[i].second.getY());
			effect.back().second->init(effect.back().first.getWidth(), effect.back().first.getHeight(),effect.back().first.getFrameWidth(), effect.back().first.getFrameHeight());
			effect.back().second->setDefPlayFrame(false, false);
			effect.back().second->setFPS(12, 2);
			effect.back().second->AniStart();
			smash.erase(smash.begin() + i);
			pairSmash.erase(pairSmash.begin() + i);
			return;
		}
	}
}

void FirePillar::_updateEffect()
{
	for (int i = 0; i < effect.size(); i++)
	{
		effect[i].second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

		if (effect[i].second->isPlay() == false)
		{
			effect.erase(effect.begin() + i);
			break;
		}
	}
}

void FirePillar::_framFirePillarDie()
{
	static bool once = true;
	if (once)
	{
		once = false;
		_image = IMAGEMANAGER->findImage("bIsiFirePillarDie");
		_image->setX(_Collider[BaseEnum::UNIT].left - 10);
		_image->setY(_Collider[BaseEnum::UNIT].top - 25);
		_framFirePillar = new Animation();
		_framFirePillar->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());
		_framFirePillar->setPlayFrame(0, 10, false, false);
		_framFirePillar->setFPS(10, 4);
		_framFirePillar->AniStart();
	}
}
