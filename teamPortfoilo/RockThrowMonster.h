#pragma once
#include "GameNode.h"
#include "Characters.h"

#define PLAYER_CENTER	(GAMEMANAGER->getPlayer()->getCollider().right - GAMEMANAGER->getPlayer()->getCollider().left) / 2 + GAMEMANAGER->getPlayer()->getCollider().left
#define MONSTER_CENTER	(_Collider[BaseEnum::UNIT].right - _Collider[BaseEnum::UNIT].left) / 2 + _Collider[BaseEnum::UNIT].left

class RockThrowMonster : BaseData, GameNode
{
	enum class UnitState
	{
		IDLE, THROW, HURT, DIE, END
	};
	
private:
	POINT pointMake{ (GAMEMANAGER->getPlayer()->getCollider().right - GAMEMANAGER->getPlayer()->getCollider().left) / 2 + GAMEMANAGER->getPlayer()->getCollider().left,  };

	int _isLeft, _isLook;
	bool _throw;
	UnitState _state;

	void _inputPatten();
	void _inputAnimation();

	int _updateSide();
	void _updateFloor();
	void _updateLook();

	vector<function<void()>> _pattenFunc;
	float _pattenDely;
	void _updateIdle();
	void _updateThrow();

public:
	HRESULT init(POINT, vector<RECT*>);
	void release(void);
	void update(void);
	void render(void);

	RockThrowMonster();
	~RockThrowMonster();
};