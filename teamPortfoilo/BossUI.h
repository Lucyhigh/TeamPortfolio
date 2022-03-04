#pragma once
#include "GameNode.h"
#include "ProgressBar.h"

class BossUI : public GameNode
{
private:
	// Hp Áß¾Ó UI 
	ProgressBarBoss* _hpBar;
	float _hp;

	float _alpha;
	bool _isBossDead;
	bool _imgEnd;
	int _count;

public:
	BossUI() {}
	~BossUI() {}

	HRESULT init(void);
	HRESULT init(int hp);
	void release(void);
	void update(void);
	void render(void);

};

