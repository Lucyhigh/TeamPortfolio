#include "Stdafx.h"
#include "BossUI.h"

HRESULT BossUI::init(void)
{

	// _hp = (float)GAMEMANAGER->getMonster()->getHp(BaseEnum::STATE); // 136
	_hpBar = new ProgressBar;
	_hpBar->init(136, 50);


	return S_OK;
}

void BossUI::release(void)
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void BossUI::update(void)
{
	_hp = GAMEMANAGER->getPlayer()->getHp(BaseEnum::STATE); // 136
	_hpBar->setPlayerHpGauge(_hp);
	_hpBar->update();
}

void BossUI::render(void)
{
	_hpBar->render();
}
