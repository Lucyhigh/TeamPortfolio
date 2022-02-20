#pragma once
#include "SingletonBase.h"
#include "PlayerCharacter.h"

class GameManger : public SingletonBase<GameManger>
{
	private:
		static BaseData* player;
		static vector<BaseData*> monster;

	public:
		GameManger();
		~GameManger();

		static void setPlayer(BaseData* User) { player = User; }
		static BaseData* getPlayer() { return player; }
		static void clearPlayer() { player = nullptr; }
		
		static void setMonster(vector<BaseData*> Monster) { monster = Monster; }
		static vector<BaseData*> getMonster() { return monster; }
		static void clearMonster() { monster.clear(); }
};
