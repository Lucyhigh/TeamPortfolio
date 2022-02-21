#pragma once
#include "GameNode.h"

class StartScene : public GameNode
{
private:


public:
	StartScene();
	~StartScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};