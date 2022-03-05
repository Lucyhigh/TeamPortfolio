#pragma once
#include "GameNode.h"
#include "ProgressBar.h"
#include "Inventory.h"

// 포션위치 수정여부 확인
struct tagPotion
{
	POINT pos;
	Image* on;
	Image* off;
//	int Idx; // 포션레벨 frameX Index
	bool use; // 사용여부 
};

class UIScene : public GameNode
{
private:

	// HpMp 관련 좌상단 UI 
	ProgressBar* _hpBar;
	float _hp;
	float _mp;

	int _potionLv;
	int _potionMax;
	vector<tagPotion> _vPotion;
	vector<tagPotion>::reverse_iterator _rviPotion;


	Inventory* _inven;
	bool _openInventory;
	bool _openOption;

	// 소지포인트 관련 우상단 UI
	int _point;


private:

	int _popupAlpha;
	bool _firstPotion;


public:
	UIScene() {}
	~UIScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void usePotion();
	void showPotion(void);
	void setPotion();
	void showPoint(bool openInventory);
	void showPopup();

	void openOption(bool state) { _openOption = state; }
	
};

