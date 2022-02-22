#pragma once
#include "GameNode.h"
#include "BossWarden.h"

class BossScene1 : public GameNode
{
private:
	vector<BaseData*> _monster;
	vector<RECT*> _floor;

	BossWarden* boss;
	RECT* floor0;
	RECT* floor1;
	RECT* floor2;
public:
	BossScene1();
	~BossScene1();

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

