#pragma once
#include "GameNode.h"
#include "ColliderManager.h"
#include "Camera.h"

class Boss3Scene : public GameNode
{
private:

public:
	Boss3Scene() {}
	~Boss3Scene() {}

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

