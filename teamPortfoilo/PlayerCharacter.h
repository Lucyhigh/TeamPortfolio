#pragma once
#include "GameNode.h"
#include "Characters.h"

class PlayerCharacter : public BaseData, GameNode
{
	enum class UnitState
	{	
		RUN,UNITNULL, IDLE_0, IDLE_1, JUMP,
		SLIDE, PARING,
		JUMPATTACK, JUMPATTACK_DOUBLE,
		ATTACK, ATTACK_DOUBLE,
		DOWNATTACK, UPATTACK,
	};

	private:
		// 입력 
		int _isLeft, _isMove, _isLook;
		UnitState _oldState;
		UnitState _state;

		// 인풋
		UnitState _inputKey(int);
		void _inputUpdate();
		void _inputAnimation();

		//업데이트
		void _updateFloor();
		int _updateSide();
		void _updateSlide();
		void _updateMove();
		void _updateAttack();
		bool _updateHit();
		function<void()> _updateSpace;

		// 점프 
		map<string, float> _jump = { { "Unit",0 }, { "Weight",0 } };
		map<string, float> _slide = { { "State",0 }, { "Max",100 } };
		void _updataJump();

public:
		//기본 
		PlayerCharacter();
		~PlayerCharacter();
		HRESULT init(POINT,vector<RECT*>);
		void release(void);
		void update(void);
		void render(void);
};