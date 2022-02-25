#pragma once
#include "GameNode.h"
#include "Characters.h"

#define PLAYER_CENTER	(GAMEMANAGER->getPlayer()->getCollider().right + GAMEMANAGER->getPlayer()->getCollider().left) / 2
#define MONSTER_CENTER	(_Collider[BaseEnum::UNIT].right + _Collider[BaseEnum::UNIT].left) / 2

class KnifeMonster : public BaseData, GameNode
{
	enum class UnitState
	{
		IDLE, MOVE, DIE, END
	};

private:

	int _isLeft;
	UnitState _state;

	void _inputPatten();
	void _inputAnimation();

	int _updateSide();
	void _updateFloor();
	void _updateLook();

	vector<function<void()>> _pattenFunc;
	float _pattenDely;
	void _updateIdle();

public:
	HRESULT init(POINT, vector<RECT*>);
	void release(void);
	void update(void);
	void render(void);

	KnifeMonster();
	~KnifeMonster();
};
