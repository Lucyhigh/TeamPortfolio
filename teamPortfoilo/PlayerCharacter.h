#pragma once
#include "GameNode.h"
#include "Characters.h"

class PlayerCharacter : public BaseData, public GameNode
{
public:
	enum class UnitState
	{
		RUN, UNITNULL, IDLE_0, IDLE_1, JUMP,
		SLIDE, PARING,
		JUMPATTACK, JUMPATTACK_DOUBLE,
		ATTACK, ATTACK_DOUBLE, ATTACK_TRIPLE,
		DOWNATTACK, UPATTACK,
	};

private:
	// �Է� 
	int _isLeft, _isMove, _isLook;
	UnitState _oldState;
	UnitState _state;
	float _Fram;
	pair<bool, Animation*> _imageAni;

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
	Image* _effect;

	// ��Ÿ 
	// int _point; // ���� ����Ʈ ����? �ӽ÷� UI���� ���.

	  //ī�޶� 
	  //Image* _image;
	  //RECT _rcPlayer;

	RECT _cameraRect;

	//ĳ���� ��ġ �ټ�

	//void setPlayerPosX(float x);
	//void setPlayerPosY(float y);

   //RECT getPlayerRect();
	//void setCameraRect(RECT rect);

public:
	//�⺻ 
	UnitState getState();
	void setCameraRect(RECT rect);
	PlayerCharacter();
	~PlayerCharacter();

	HRESULT init(POINT, vector<RECT*>);
	void release(void);
	void update(void);
	void render(void);

};
