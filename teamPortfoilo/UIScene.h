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

	// 소지포인트 관련 우상단 UI
	int _point;

public:
	UIScene() {}
	~UIScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void usePotion();
	void showPotion(void);
	// 포션병 회복 또는 업그레이드
	void setPotion(int Lv, int Max, tagPotion potion);

	
	void showPoint(bool openInventory);
	
};

