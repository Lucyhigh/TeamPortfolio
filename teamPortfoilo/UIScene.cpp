#include "Stdafx.h"
#include "UIScene.h"

HRESULT UIScene::init(void)
{
	// 플레이어 정보 
	_hp = (float)GAMEMANAGER->getPlayer()->getHp(BaseEnum::STATE); // 136
	_mp = (float)GAMEMANAGER->getPlayer()->getMp(BaseEnum::STATE); // 96
	
	_potionLv = 0 ; // _pData->getPotionLevel(); // 프레임 x 
	switch (_potionLv)
	{
	case 0:
		_potionMax = 2; 
		break;
	case 1:
		_potionMax = 3;
		break;
	case 2:
		_potionMax = 4;
		break;
	}
	
	// ---------------여기까지 연동 필요

#pragma region Hp Mp Potion
	_hpBar = new ProgressBar;
	_hpBar->init(136, 50);
	_point = 10000;

	// 포션 
	for (int i = 0; i < _potionMax; i++)
	{
		tagPotion potion;
		ZeroMemory(&potion, sizeof(tagPotion));

		potion.pos.x = _hpBar->getHpMpBar().x + 100 + ( 25 * i ) ;
		potion.pos.y = _hpBar->getHpMpBar().y + 55 ;
		potion.on = new Image;
		potion.on->init("Resources/Images/UI/hpPotionOn.bmp", potion.pos.x, potion.pos.y, 57, 27,3,1,MGT);
		potion.off = new Image;
		potion.off->init("Resources/Images/UI/hpPotionOff.bmp", potion.pos.x, potion.pos.y, 57, 27, 3, 1, MGT);
		potion.use = false;
		_vPotion.push_back(potion);
	}
#pragma endregion 


	//--------------------인벤토리 테스트

	_inven = new Inventory();
	_inven->init();

	return S_OK;
}

void UIScene::release(void)
{
	_hpBar->release();
	SAFE_DELETE(_hpBar);

	_rviPotion = _vPotion.rbegin();
	for (; _rviPotion != _vPotion.rend(); _rviPotion++)
	{
		SAFE_DELETE(_rviPotion->on);
		SAFE_DELETE(_rviPotion->off);
	}
	_vPotion.clear();

	_inven->release();
	SAFE_DELETE(_inven);
}

void UIScene::update(void)
{
	if (_hp >= 0)	_hp -= 0.03f;
	if (_mp >= 0)	_mp -= 0.01f;

	_hp = GAMEMANAGER->getPlayer()->getHp(BaseEnum::STATE); // 136
	_mp = GAMEMANAGER->getPlayer()->getHp(BaseEnum::STATE); // 116

	_hpBar->setPlayerHpGauge(_hp);
	_hpBar->setPlayerMpGauge(_mp);

	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		usePotion();
	}

	_hpBar->update();

	_inven->update();
	if (KEYMANAGER->isOnceKeyDown('I')) _openInventory = true;
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) _openInventory = false;

}

void UIScene::render(void)
{
	_hpBar->render();
	showPotion();

	if (_openInventory)
	{
		_inven->render();
	}

	showPoint(_openInventory);
}

void UIScene::usePotion()
{
	// 마지막 포션부터 비우기 위해 reverse_iterator 사용
	_rviPotion = _vPotion.rbegin();
	for (; _rviPotion != _vPotion.rend(); ++_rviPotion)
	{
		if ( _rviPotion->use) continue;
		_rviPotion->use = true;
		
		int hpUp = 0;
		switch (_potionLv)
		{
		case 0 : 
			hpUp = 30;
			break;
		case 1:
			hpUp = 50;
			break;
		case 2:
			hpUp = 100;
			break;
		}
		GAMEMANAGER->getPlayer()->setHp(_rviPotion->use, hpUp);
		break;
	}
}

void UIScene::showPotion(void)
{
	_rviPotion = _vPotion.rbegin();
	for (; _rviPotion != _vPotion.rend(); ++_rviPotion)
	{
		if(_rviPotion->use)
		{
			_rviPotion->off->frameRender(getMemDC(), _rviPotion->pos.x, _rviPotion->pos.y, _potionLv,0);
		}
		if (!_rviPotion->use)
		{
			_rviPotion->on->frameRender(getMemDC(), _rviPotion->pos.x, _rviPotion->pos.y,_potionLv, 0);
		}
	}
}


void UIScene::showPoint(bool openInventory)
{
	if (openInventory == true)
	{
	// 소지금 오른쪽 정렬
	SetTextAlign(getMemDC(), TA_RIGHT);

	FONTMANAGER->drawTextValue(getMemDC(), _point,					 // 변수
		1060, IMAGEMANAGER->findImage("point")->getY() -20,			 // 위치
		"둥근모꼴", 23, 100, RGB(171, 154, 63));						 // 폰트
	}
	else
	{
		IMAGEMANAGER->findImage("point")->render(getMemDC(),
			(WINSIZE_X - 30) - IMAGEMANAGER->findImage("point")->getWidth(), IMAGEMANAGER->findImage("point")->getY());

		// 소지금 오른쪽 정렬
		SetTextAlign(getMemDC(), TA_RIGHT);

		FONTMANAGER->drawTextValue(getMemDC(), _point,					 // 변수
			1100, IMAGEMANAGER->findImage("point")->getY() + 27,		 // 위치
			"둥근모꼴", 25, 100, RGB(171, 154, 63));						 // 폰트

	}
}

void UIScene::setPotion()
{
	_rviPotion = _vPotion.rbegin();
	for (; _rviPotion != _vPotion.rend(); ++_rviPotion)
	{
		_rviPotion->use = false;
	}
}