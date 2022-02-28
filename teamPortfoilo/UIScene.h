#pragma once
#include "GameNode.h"
#include "ProgressBar.h"
#include "Inventory.h"

// ������ġ �������� Ȯ��
struct tagPotion
{
	POINT pos;
	Image* on;
	Image* off;
//	int Idx; // ���Ƿ��� frameX Index
	bool use; // ��뿩�� 
};

class UIScene : public GameNode
{
private:

	// HpMp ���� �»�� UI 
	ProgressBar* _hpBar;
	float _hp;
	float _mp;

	int _potionLv;
	int _potionMax;
	vector<tagPotion> _vPotion;
	vector<tagPotion>::reverse_iterator _rviPotion;


	Inventory* _inven;
	bool _openInventory;

	// ��������Ʈ ���� ���� UI
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
	// ���Ǻ� ȸ�� �Ǵ� ���׷��̵�
	void setPotion(int Lv, int Max, tagPotion potion);

	
	void showPoint(bool openInventory);
	
};

