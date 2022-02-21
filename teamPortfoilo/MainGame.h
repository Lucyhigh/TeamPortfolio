#pragma once
#include "GameNode.h"
#include "ColliderManager.h"

class MainGame : public GameNode
{
private:
	BaseData* _player;
	ColliderManager* _collider;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() {}
	~MainGame() {}
};