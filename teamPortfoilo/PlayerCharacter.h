#pragma once
#include "GameNode.h"
#include "Characters.h"

class PlayerCharacter : public BaseData, GameNode
{
	enum class UnitState
	{	
		UNITNULL, IDLE, JUMP,
		SLIDE, PARING,
		JUMPATTACK, JUMPATTACK_DOUBLE,
		ATTACK, ATTACK_DOUBLE,
		DOWNATTACK, UPATTACK,
	};

	private:
		// �Է� 
		int _isLeft, _isMove, _isLook;
		UnitState _oldState;
		UnitState _state;

		// ��ǲ
		UnitState _inputKey(int);
		void _inputUpdate();
		void _inputAnimation();

		//������Ʈ
		void _updateFloor();
		int _updateSide();
		void _updateSlide();
		void _updateMove();
		void _updateAttack();
		bool _updateHit();
		function<void()> _updateSpace;

		// ���� 
		map<string, float> _jump = { { "Unit",0 }, { "Weight",0 } };
		map<string, float> _slide = { { "State",0 }, { "Max",100 } };
		void _updataJump();

		// �ٴ�
		vector<RECT*> _floor;
public:
		//�⺻ 
		PlayerCharacter();
		~PlayerCharacter();
		HRESULT init(POINT,vector<RECT*>);
		void release(void);
		void update(void);
		virtual void render(void);
};