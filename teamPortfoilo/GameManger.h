#pragma once
#include "SingletonBase.h"
#include "PlayerCharacter.h"

class GameManger : public SingletonBase<GameManger>
{
	private:
		 PlayerCharacter* player;
		 vector<BaseData*> monster;

	public:
		GameManger();
		~GameManger();
		void init();

		 PlayerCharacter* getPlayer() { return player; }
		 void setPlayer(PlayerCharacter* User) { player = User; }
		 void clearPlayer() { player = nullptr; }
		
		 vector<BaseData*> getMonster() { return monster; }
		 void setMonster(vector<BaseData*> Monster) { monster = Monster; }
		 void setMonster(BaseData* Monster) { monster.push_back(Monster); }
		 void clearMonster() { monster.clear(); }
		 void clearMonster(int num) { monster.erase(monster.begin()+num); }
};
