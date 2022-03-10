#pragma once
#include "GameNode.h"
#include "ProgressBar.h"
#include "Inventory.h"
#include "OptionScene.h"

struct tagPotion
{
	POINT pos;
	Image* on;
	Image* off;
	bool use; 
};

class UIScene : public GameNode
{
private:
	ProgressBar* _hpBar;
	float _hp;
	float _mp;

	int _potionLv;
	int _potionMax;
	vector<tagPotion> _vPotion;
	vector<tagPotion>::reverse_iterator _rviPotion;
	Inventory* _inven;
	OptionScene* _option;
	
	int _point;
	bool _openInventory;
	bool _openOption;
    
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

