#pragma once
#include "GameNode.h"
#include "Characters.h"

class BossLady : public BaseData, GameNode
{
	enum class BossState
	{
		IDLE, JUMPATTACK, ATTACK, JUMPIDLE, JUMP, START, DIE, END
	};
private:
	Image* _image;
	RECT _rc;
	RECT* _floor;
	
	BossState _state;
	float _pattenDely;
	float _fram;//frame index
public:
	BossLady();
	~BossLady();
public:
	HRESULT init(POINT, vector<RECT*>);
	void release(void);
	void update(void);
	void render(void);
};

