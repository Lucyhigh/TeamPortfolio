#pragma once
#include "GameNode.h"
#include "PlayerCharacter.h"
#include "ColliderManager.h"

class MainGame : public GameNode
{
	private:
		PlayerCharacter* player;
		vector<BaseData*> monster;
		vector<RECT*> floor;
		ColliderManager* collider;

		// 테스트용 
		vector<RECT> reference = { { 500,450,1000,1000 }, { 0, 650,1100,1000 } };
		BaseData* mon;
	public:
		HRESULT init(void);
		void release(void);
		void update(void);
		void render(void);

		MainGame() {}
		~MainGame() {}
};