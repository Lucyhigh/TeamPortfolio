#pragma once
#include "GameNode.h"
#include "Characters.h"

class BossWarden : public BaseData, GameNode
{
	enum class UnitState
	{ IDLE, JUMPATTACK, ATTACK, JUMPIDLE, JUMP, START, DIE, END };

	private:
		int _isLeft, _isLook;
		UnitState _state;
		map<string, float> _jump = { { "Unit",0 }, { "Weight",0 } };

		void _inputPatten();
		void _inputAnimation();
		void _inputEffect();

		int _updateSide();
		void _updateFloor();
		void _updateLook();

		vector<function<void()>> _pattenFunc;
		float _pattenDely;
		void _updateStart() {};
		void _updateDie() {};
		void _updateIdle();
		void _updateJump();
		void _updateJumpIdle();
		void _updateAttack();

		float _fram;
		vector<pair<float,Image*>> effect;

		void clearSmash(int) override;
		void setHit(int) override;
	public:
		BossWarden();
		~BossWarden();
		HRESULT init(POINT, vector<RECT*>);
		void release(void);
		void update(void);
		void render(void);
};

