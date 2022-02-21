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
		void init();

		static BaseData* getPlayer() { return player; }
		static void setPlayer(BaseData* User) { player = User; }
		static void clearPlayer() { player = nullptr; }
		
		static vector<BaseData*> getMonster() { return monster; }
		static void setMonster(vector<BaseData*> Monster) { monster = Monster; }
		static void clearMonster() { monster.clear(); }
		static void clearMonster(int num) { monster.erase(monster.begin()+num); }
};
