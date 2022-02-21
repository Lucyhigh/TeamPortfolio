#include "Stdafx.h"
#include "GameManger.h"

BaseData* GameManger::player;
vector<BaseData*> GameManger::monster;

GameManger::GameManger() { }
GameManger::~GameManger() { }

void GameManger::init()
{ player = new PlayerCharacter(); }
