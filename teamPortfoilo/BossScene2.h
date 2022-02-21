#pragma once
#include "GameNode.h"

class BossScene2 : public GameNode
{
private:

public:
	BossScene2();
	~BossScene2() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

