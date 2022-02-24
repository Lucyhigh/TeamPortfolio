#pragma once
#include "GameNode.h"
#include "PlayerCharacter.h"
#include "BossWarden.h"
#include "ColliderManager.h"
#include "KnifeMonster.h"

class MainGame : public GameNode
{
private:
	BaseData* _player;
	vector<BaseData*> _monster;
	vector<RECT*> _floor;
	ColliderManager* _collider;

	// 테스트용 
	vector<RECT> reference = { { 0,600,1200,1000 } };
	BossWarden* mon;
	PlayerCharacter* player;
	KnifeMonster* knifeMon;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() {}
	~MainGame() {}
};