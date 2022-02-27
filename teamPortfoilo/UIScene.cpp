#include "Stdafx.h"
#include "UIScene.h"

HRESULT UIScene::init(void)
{
	// 플레이어 정보 
	_hp = GAMEMANAGER->getPlayer()->getHp(BaseEnum::STATE); // 136
	_mp = GAMEMANAGER->getPlayer()->getMp(BaseEnum::STATE); // 116
	
	_potionLv =1 ; // _pData->getPotionLevel(); // 프레임 x 
	_potionMax = 2; // 초기 : 0단계 포션 2개 
	
	// ---------------여기까지 연동 필요

#pragma region Hp Mp Potion
	_hpBar = new ProgressBar;
	_hpBar->init(136, _mp);
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

	if (KEYMANAGER->isOnceKeyDown(VK_F2))
	{
		usePotion();
		_hp += 50; // setHp를 usePotion함수 안으로 넣을 것 
		_hpBar->setPlayerHpGauge(_hp);
	}

	_hpBar->update();

	_inven->update();
	if (KEYMANAGER->isOnceKeyDown('I')) _openInventory = true;
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) _openInventory = false;

}

void UIScene::render(void)
{
	_hpBar->render();
	showPoint();
	showPotion();

	// 추후 인벤토리등에서 정렬이 이상할때 확인
	//SetTextAlign(getMemDC(), TA_LEFT);

	if (_openInventory)
	{
		_inven->render();
	}

}

void UIScene::usePotion()
{
	// 마지막 포션부터 비우기 위해 reverse_iterator 사용
	_rviPotion = _vPotion.rbegin();
	for (; _rviPotion != _vPotion.rend(); ++_rviPotion)
	{
		if ( _rviPotion->use) continue;
		_rviPotion->use = true;
		// 플레이어 hp회복 함수 추가할 것
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


void UIScene::showPoint(void)
{
	IMAGEMANAGER->findImage("point")->render(getMemDC(),
		(WINSIZE_X - 30) - IMAGEMANAGER->findImage("point")->getWidth(), IMAGEMANAGER->findImage("point")->getY());

	// 소지금 오른쪽 정렬
	SetTextAlign(getMemDC(), TA_RIGHT);

	FONTMANAGER->drawTextValue(getMemDC(), _point,					 // 변수
		1100, IMAGEMANAGER->findImage("point")->getY() + 27,		 // 위치
		"둥근모꼴", 25, 100, RGB(171, 154, 63));						 // 폰트
}

