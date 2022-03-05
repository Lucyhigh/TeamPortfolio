#include "Stdafx.h"
#include "BossUI.h"

HRESULT BossUI::init(void)
{

	_hp = (float)GAMEMANAGER->getMonster()[0]->getHp(BaseEnum::STATE); // 543
	_hpBar = new ProgressBarBoss;
	_hpBar->init(_hp); // init(_hp);

	_alpha = 300;
	_isBossDead = false;

	_count = 0;
	return S_OK;
}

HRESULT BossUI::init(int hp)
{

	_hp = (float)GAMEMANAGER->getMonster()[0]->getHp(BaseEnum::STATE); // n번째 보스
	_hpBar = new ProgressBarBoss;
	_hpBar->init(hp);

	_alpha = 300;
	_isBossDead = false;
	return S_OK;
}

void BossUI::release(void)
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void BossUI::update(void)
{

	_hp = (float)GAMEMANAGER->getMonster()[0]->getHp(BaseEnum::STATE); // 543
	_hpBar->setBossHpGauge(_hp);
	_hpBar->update();

	if (_hpBar->getHpWidth() <= 0)
	{
		_isBossDead = true;
	}

	if (_isBossDead)
	{
		if (KEYMANAGER->isToggleKey('Z')) 		cout << _count << endl;

		_count++;
		if (_count >= 1200)
		{
			_alpha -= 0.1;
			if (_alpha <= 0) _alpha = 0;
		}

	}


}

void BossUI::render(void)
{
	_hpBar->render();

	if (_isBossDead)
	{
		IMAGEMANAGER->findImage("bDieBg")->alphaRender(getMemDC(), _alpha*0.5);
		IMAGEMANAGER->findImage("bDie")->alphaRender(getMemDC(), _alpha);
	}
}
