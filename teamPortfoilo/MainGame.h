#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	PlayerCharacter* _player;
	UIScene* _ui;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() {}
	~MainGame() {}
};