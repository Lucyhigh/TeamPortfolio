#pragma once
#include "GameNode.h"
#include "Characters.h"

class BossIsadora;

class FirePillar : public BaseData , GameNode
{
	enum class UnitState
	{
		CHARGE , DIE
	};

	UnitState _state;
	BossIsadora* _isadora;
	POINT _outPoint;
	vector<pair<Image, Animation*>> effect;
	float _dely;

	void _updateFireball();
	void _updateEffect();
	POINT _fireballMid(int);
	

	vector<Animation*> pairSmash;

	Animation* _framFirePillar;
	void _framFirePillarDie();

public:
	FirePillar();
	~FirePillar();
	HRESULT init( POINT, BossIsadora*);
	void release(void);
	void update(void);
	void render(void);
};

