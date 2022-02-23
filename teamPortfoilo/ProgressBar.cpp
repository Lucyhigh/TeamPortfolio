#include "Stdafx.h"
#include "ProgressBar.h"

// 0222 미사용
/* 
HRESULT ProgressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, width, height);
	//움직이는 실시간 바
	_progressBarUp = IMAGEMANAGER->addImage("BarUp", "Resources/Images/Object/HpBarUp.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));
	//고정 디폴트로 있는 바
	_progressBarDown = IMAGEMANAGER->addImage("BarDown", "Resources/Images/Object/HpBarDown.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));

	width = _progressBarUp->getWidth();
	return S_OK;
}
*/ 


HRESULT ProgressBar::init(float hp, float mp)
{
	
	// 플레이어와 연동 필요 + 능력치도~~ 
	_hpWidth = hp;
	_mpWidth = mp;

	_hpMaxWidth = hp;
	_mpMaxWidth = mp;

	// 여기서 이미지 관리
	IMAGEMANAGER->addImage("pHp", "Resources/Images/UI/UI_Hp_gauge.bmp", _hpWidth, 6);
	IMAGEMANAGER->addImage("pMp", "Resources/Images/UI/UI_Mp_gauge.bmp", _mpWidth, 6);
	IMAGEMANAGER->addImage("pMpFull", "Resources/Images/UI/UI_fullMp_gauge.bmp", _mpWidth, 6);
	//IMAGEMANAGER->addImage("pMpFullEffect", "Resources/Images/UI/UI_fullMp_gauge_effect.bmp", 12, 6);
	_hpBarBg = IMAGEMANAGER->findImage("pHpBarEmpty");
	_hpBarCover = IMAGEMANAGER->findImage("pHpBarCover");
	_hpBar = IMAGEMANAGER->findImage("pHp");
	_mpBar = IMAGEMANAGER->findImage("pMp");

	// UI변동 크기 사용시 조정 필요 
	_hpPos.x = _hpBarBg->getX()+78;
	_hpPos.y = _hpBarBg->getY()+17;

	_mpPos.x = _hpPos.x + 45;
	_mpPos.y = _hpPos.y + 19;

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
	/*
	_progressBarDown->render(getMemDC(), _rc.left + _progressBarDown->getWidth() / 2,
		_y + _progressBarDown->getHeight() / 2,
		0, 0, _progressBarDown->getWidth(), _progressBarDown->getHeight());
	_progressBarUp->render(getMemDC(), _rc.left + _progressBarDown->getWidth() / 2,
		_y + _progressBarDown->getHeight() / 2,
		0, 0, _width, _progressBarDown->getHeight());
	*/

	_hpBarBg->render(getMemDC(), IMAGEMANAGER->findImage("pHpBarEmpty")->getX(), IMAGEMANAGER->findImage("pHpBarEmpty")->getY());
	_hpBar->render(getMemDC(), _hpPos.x, _hpPos.y, 0, 0, _hpWidth, _hpBar->getHeight());
	_mpBar->render(getMemDC(), _mpPos.x, _mpPos.y, 0, 0, _mpWidth, _mpBar->getHeight());
	_hpBarCover->render(getMemDC(), IMAGEMANAGER->findImage("pHpBarCover")->getX(), IMAGEMANAGER->findImage("pHpBarCover")->getY());

	//위치확인용
	//Rectangle(getMemDC(), _hpPos.x, _hpPos.y, _hpPos.x + _hpWidth, _hpPos.y + _hpBar->getHeight());
	//Rectangle(getMemDC(), _mpPos.x, _mpPos.y, _mpPos.x + _mpWidth, _mpPos.y + _mpBar->getHeight());

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

