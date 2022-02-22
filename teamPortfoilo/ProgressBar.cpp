#include "Stdafx.h"
#include "ProgressBar.h"

// 0222 �̻��
/* 
HRESULT ProgressBar::init(int x, int y, int width, int height)
{
	_x = x;
	_y = y;
	_rc = RectMakeCenter(_x, _y, width, height);
	//�����̴� �ǽð� ��
	_progressBarUp = IMAGEMANAGER->addImage("BarUp", "Resources/Images/Object/HpBarUp.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));
	//���� ����Ʈ�� �ִ� ��
	_progressBarDown = IMAGEMANAGER->addImage("BarDown", "Resources/Images/Object/HpBarDown.bmp",
		0, 0, width, height, true, RGB(255, 0, 255));

	width = _progressBarUp->getWidth();
	return S_OK;
}
*/ 


HRESULT ProgressBar::init(float hp, float mp)
{
	// UI���� ũ�� ���� ���� �ʿ� 
	_hpPos.x = 108;
	_hpPos.y = 47;

	_mpPos.x = 128;
	_mpPos.y = 66;

	// �÷��̾�� ���� �ʿ� 
	_hpWidth = hp;
	_mpWidth = mp;


	// �̹���Ŭ�������� ����
	IMAGEMANAGER->addImage("pHpBarEmpty", "Resources/Images/UI/UI_emptyHpBar.bmp", 143, 58, MGT);
	IMAGEMANAGER->addImage("pHpBarCover", "Resources/Images/UI/UI_upperHpBar.bmp", 143, 58, MGT);
	IMAGEMANAGER->addImage("pHp", "Resources/Images/UI/UI_Hp_gauge.bmp", 4, 4);
	IMAGEMANAGER->addImage("pMp", "Resources/Images/UI/UI_Mp_gauge.bmp", 4, 4);
	IMAGEMANAGER->addImage("pMpFull", "Resources/Images/UI/UI_fullMp_gauge.bmp", 4, 4);
	IMAGEMANAGER->addImage("pMpFullEffect", "Resources/Images/UI/UI_fullMp_gauge_effect.bmp", 8, 4);
	IMAGEMANAGER->addFrameImage("hpPotionOff", "Resources/Images/UI/hpPotionOff.bmp", 45, 21, 3, 1, MGT);
	IMAGEMANAGER->addFrameImage("hpPotionOn", "Resources/Images/UI/hpPotionOn.bmp", 45, 21, 3, 1, MGT);
	IMAGEMANAGER->addImage("point", "Resources/Images/UI/point.bmp", 84, 42, MGT); //84,42

	_hpBarBg = IMAGEMANAGER->findImage("pHpBarEmpty");
	_hpBarCover = IMAGEMANAGER->findImage("pHpBarCover");
	_hpBar = IMAGEMANAGER->findImage("pHp");
	_mpBar = IMAGEMANAGER->findImage("pMp");

	_hpMaxWidth = hp;

	return S_OK;
}


void ProgressBar::release(void)
{
}

void ProgressBar::update(void)
{
	//_rc = RectMakeCenter(_x, _y, _progressBarDown->getWidth(), _progressBarDown->getHeight());
	if (_hpWidth >= _hpMaxWidth)  _hpWidth = _hpMaxWidth;
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

	//��ġȮ�ο�
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

