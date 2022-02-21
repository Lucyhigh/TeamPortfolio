#pragma once
#include "GameNode.h"

class BossScene1 : public GameNode
{
private:


public:
	BossScene1();
	~BossScene1() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

