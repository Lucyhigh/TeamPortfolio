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
/*
이동키입니다.

A키 ,D키    좌우 이동
SHIFT키     슬라이딩
SPACE BAR  점프
K키         공격
E키, K키    상호작용
I키 인벤토리 (인벤토리를 연 후 Q키, E키 인벤토리 좌우이동)

*/