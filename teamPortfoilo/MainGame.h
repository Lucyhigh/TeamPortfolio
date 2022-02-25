#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	PlayerCharacter* _player;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() {}
	~MainGame() {}
};