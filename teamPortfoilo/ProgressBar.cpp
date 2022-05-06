#include "Stdafx.h"
#include "ProgressBar.h"


#pragma region player HP

HRESULT ProgressBar::init(float hp, float mp)
{
	
	_hpWidth = hp;
	_mpWidth = mp;

	_hpMaxWidth = GAMEMANAGER->getPlayer()->getHp(BaseEnum::MAX);
	_mpMaxWidth = GAMEMANAGER->getPlayer()->getMp(BaseEnum::MAX);

	IMAGEMANAGER->addImage("pHp", "Resources/Images/UI/UI_Hp_gauge.bmp", _hpMaxWidth, 6);
	IMAGEMANAGER->addImage("pMp", "Resources/Images/UI/UI_Mp_gauge.bmp", _mpMaxWidth, 6);
	IMAGEMANAGER->addImage("pMpFull", "Resources/Images/UI/UI_fullMp_gauge.bmp", _mpMaxWidth, 6);
	_hpBarBg = IMAGEMANAGER->findImage("pHpBarEmpty");
	_hpBarCover = IMAGEMANAGER->findImage("pHpBarCover");
	_hpBar = IMAGEMANAGER->findImage("pHp");
	_mpBar = IMAGEMANAGER->findImage("pMp");

	_hpPos.x = _hpBarBg->getX()+78;
	_hpPos.y = _hpBarBg->getY()+17;

	_mpPos.x = _hpPos.x + 45;
	_mpPos.y = _hpPos.y + 19;

	return S_OK;
}

HRESULT ProgressBar::init(float hp)
{

	_hpWidth = hp;
	_hpMaxWidth = hp;

	_hpBarBg = IMAGEMANAGER->findImage("bHpBarEmpty");
	_hpBarCover = IMAGEMANAGER->findImage("bHpBarCover");

	_hpPos.x = _hpBarBg->getX() + 78;
	_hpPos.y = _hpBarBg->getY() + 17;

	return S_OK;
}


void ProgressBar::release(void)
{
}

void ProgressBar::update(void)
{

	//_rc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(), _progressBarDown->getHeight());
	if (_hpWidth >= _hpMaxWidth)  _hpWidth = _hpMaxWidth;
	if (_mpWidth >= _mpMaxWidth)  _mpWidth = _mpMaxWidth;


}

void ProgressBar::render(void)
{

	_hpBarBg->render(getMemDC(), IMAGEMANAGER->findImage("pHpBarEmpty")->getX(), IMAGEMANAGER->findImage("pHpBarEmpty")->getY());
	_hpBar->render(getMemDC(), _hpPos.x, _hpPos.y, 0, 0, _hpWidth, _hpBar->getHeight());
	_mpBar->render(getMemDC(), _mpPos.x, _mpPos.y, 0, 0, _mpWidth, _mpBar->getHeight());
	_hpBarCover->render(getMemDC(), IMAGEMANAGER->findImage("pHpBarCover")->getX(), IMAGEMANAGER->findImage("pHpBarCover")->getY());

}

void ProgressBar::setGauge(float currentScore, float maxScore)
{
	_width = (currentScore / maxScore) * _progressBarDown->getWidth();
}


void ProgressBar::setPlayerHpGauge(float hpScore)
{
	_hpWidth = hpScore;
}

void ProgressBar::setPlayerMpGauge(float mpScore)
{
	_mpWidth = mpScore;

}

POINT ProgressBar::getHpMpBar()
{
	POINT pos;
	pos.x = IMAGEMANAGER->findImage("pHpBarEmpty")->getX();
	pos.y = IMAGEMANAGER->findImage("pHpBarEmpty")->getY();

	return pos;
}
#pragma endregion


#pragma region Boss HP

HRESULT ProgressBarBoss::init(float hp)
{
	_hpWidth = hp;
	_hpWidthB = hp; 
	_hpMaxWidth = hp;

	_hpBarBg = IMAGEMANAGER->findImage("bHpBarEmpty");
	_hpBarCover = IMAGEMANAGER->findImage("bHpBarCover");
	_hpBarTop = IMAGEMANAGER->findImage("bHpBarT");
	_hpBarbottom = IMAGEMANAGER->findImage("bHpBarB");

	_hpPos.x = _hpBarBg->getX() + 62;
	_hpPos.y = _hpBarBg->getY() + 26;

	return S_OK;
}

void ProgressBarBoss::release(void)
{
}

void ProgressBarBoss::update(void)
{
	if (_hpWidth < _hpWidthB) _hpWidthB -= 0.3f;
	if (_hpWidthB - _hpWidth > 100)_hpWidthB -= 0.6f;

}

void ProgressBarBoss::render(void)
{
	_hpBarBg->render(getMemDC(),IMAGEMANAGER->findImage("bHpBarEmpty")->getX(),
		IMAGEMANAGER->findImage("bHpBarEmpty")->getY());
	
	_hpBarbottom->render(getMemDC(), _hpPos.x, _hpPos.y, 0, 0, _hpWidthB, _hpBarbottom->getHeight());
	_hpBarTop->render(getMemDC(), _hpPos.x, _hpPos.y, 0, 0, _hpWidth, _hpBarbottom->getHeight());
	
	_hpBarCover->render(getMemDC(), IMAGEMANAGER->findImage("bHpBarCover")->getX(),
		IMAGEMANAGER->findImage("bHpBarEmpty")->getY());
}

void ProgressBarBoss::setGauge(float currentScore, float maxScore)
{
}

void ProgressBarBoss::setBossHpGauge(float hpScore)
{
	_hpWidth = hpScore;
}

POINT ProgressBarBoss::getHpMpBar()
{
	return POINT();
}


#pragma endregion