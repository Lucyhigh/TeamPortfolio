#pragma once
#include "GameNode.h"
#include "ProgressBar.h"

class BossUI : public GameNode
{
private:
	// Hp �߾� UI 
	ProgressBar* _hpBar;
	float _hp;

public:
	BossUI() {}
	~BossUI() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

