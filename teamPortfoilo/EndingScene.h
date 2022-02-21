#pragma once
#include "GameNode.h"

class EndingScene :public GameNode
{
private:


public:
	EndingScene();
	~EndingScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

