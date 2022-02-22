#include "Stdafx.h"
#include "UIScene.h"

HRESULT UIScene::init(void)
{
	_img = new ImageClass;
	_img->init();

	// 플레이어 정보 연동 필요 
	_pData = new BaseData;
	_hp = _pData->getHp(BaseEnum::STATE); // 136
	_mp = _pData->getMp(BaseEnum::STATE); // 116

	potionLv = 2;// _pData->getPotionLevel(); // 프레임 x 
	//potionIdx = _pData->getPotionCount(); // 포션 그리기 수량 

	// ---------------여기까지 

	_hpBar = new ProgressBar;
	_hpBar->init(_hp, _mp);

	// 벡터로 수정
	potion.healing = 50;
	potion.PotionIndex = potionIdx;
	potion.use = false;


	return S_OK;
}

void UIScene::release(void)
{

	_hpBar->release();
	SAFE_DELETE(_hpBar);

	
}

void UIScene::update(void)
{
	if (_hp >= 0)	_hp -= 0.03f;
	if (_mp >= 0)	_mp -= 0.01f;


	_hpBar->setPlayerHpGauge(_hp);
	_hpBar->setPlayerMpGauge(_mp);

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		//for (int i = 0; i < potionIdx; i++)
		{
			potion.use = true;
		}

		// 회복 후 일정시간 hp소모 안됨. 수정할 것 
		_hp += 50;
		_hpBar->setPlayerHpGauge(_hp);
	}

	_hpBar->update();
}

void UIScene::render(void)
{
	IMAGEMANAGER->findImage("point")->render(getMemDC(), IMAGEMANAGER->findImage("point")->getX(), IMAGEMANAGER->findImage("point")->getY());

	//for (int i = 0; i < potionIdx; i++)
	{
		// 기본 빈병 그리기 
	//	IMAGEMANAGER->findImage("hpPotionOff")->frameRender(getMemDC(),
	//		IMAGEMANAGER->findImage("hpPotionOff")->getX(), IMAGEMANAGER->findImage("hpPotionOff")->getY(), potionLv, 0);

		// 안마신 포션이 있다면 온
		if (!potion.use)
		{
	//		IMAGEMANAGER->findImage("hpPotionOn")->frameRender(getMemDC(),
	//			IMAGEMANAGER->findImage("hpPotionOn")->getX(), IMAGEMANAGER->findImage("hpPotionOn")->getY(), potionLv, 0);
		}
	}

	_hpBar->render();
}
