#pragma once
#include "SingletonBase.h"
#include "PlayerCharacter.h"

class GameManger : public SingletonBase<GameManger>
{
	private:
		static PlayerCharacter* player;
		static vector<BaseData*> monster;

	public:
		GameManger();
		~GameManger();
		void init();

		static PlayerCharacter* getPlayer() { return player; }
		static void setPlayer(PlayerCharacter* User) { player = User; }
		static void clearPlayer() { player = nullptr; }
		
		static vector<BaseData*> getMonster() { return monster; }
		static void setMonster(vector<BaseData*> Monster) { monster = Monster; }
		static void clearMonster() { monster.clear(); }
		static void clearMonster(int num) { monster.erase(monster.begin()+num); }
};
