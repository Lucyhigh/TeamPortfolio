#pragma once
#include "GameNode.h"
#include "Characters.h"

class PlayerCharacter : public BaseData, public GameNode
{
public:
	enum class UnitState
	{
		RUN, UNITNULL, IDLE_0, IDLE_1, JUMP,
		SLIDE, PARING, PARYER, POTION,
		JUMPATTACK, JUMPATTACK_DOUBLE,
		ATTACK, ATTACK_DOUBLE, ATTACK_TRIPLE,
		UPATTACK,
	};

private:
	int _isLeft, _isMove, _isLook;
	UnitState _oldState;
	UnitState _state;
	float _Fram;
	bool _paryer;
	pair<bool, Animation*> _imageAni;

	UnitState _inputKey(int);
	void _inputUpdate();
	void _inputAnimation();

	void _updateFloor();
	int _updateSide();
	void _updateSlide();
	void _updateMove();
	void _updateAttack();
	bool _updateHit();
	function<void()> _updateSpace;

	map<string, float> _jump = { { "Unit",0 }, { "Weight",0 } };
	map<string, float> _slide = { { "State",0 }, { "Max",100 } };
	void _updataJump();
	Image* _effect;
    RECT _cameraRect;

public:
		void setParyer(bool);
		UnitState getState();
		void setCameraRect(RECT rect);
		RECT getCamareRect() { return _cameraRect; }

		PlayerCharacter();
		~PlayerCharacter();
		HRESULT init(POINT, vector<RECT*>);
		void release(void);
		void update(void);
		void render(void);
};