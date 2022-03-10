#include "Stdafx.h"
#include "BossUI.h"

HRESULT BossUI::init(void)
{

	_hp = (float)GAMEMANAGER->getMonster()[0]->getHp(BaseEnum::STATE); // 543
	_hpBar = new ProgressBarBoss;
	_hpBar->init(_hp); // init(_hp);

	_alpha = 255;
	_alphaBack = false;
	_isBossDead = false;

	_count = 0;
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
		_count++;
		if (_count >= 600)
		{
			_alpha -= 0.3f;
			if (_alpha <= 0)
			{
				_alpha = 0;
				_isBossDead = false;
			}
		}
	}

}

void BossUI::render(void)
{
	_hpBar->render();

	if (_isBossDead && _count >= 200)
	{
		IMAGEMANAGER->findImage("bDieBg")->alphaRender(getMemDC(), _alpha*0.5);
		IMAGEMANAGER->findImage("bDie")->alphaRender(getMemDC(), _alpha);
	}
}
