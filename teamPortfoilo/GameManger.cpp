#include "Stdafx.h"
#include "GameManger.h"

PlayerCharacter* GameManger::player;
vector<BaseData*> GameManger::monster;

GameManger::GameManger() { }
GameManger::~GameManger() { }

void GameManger::init()
{ player = new PlayerCharacter(); }
