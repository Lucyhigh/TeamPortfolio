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
	// 입력 
	int _isLeft, _isMove, _isLook;
	UnitState _oldState;
	UnitState _state;
	float _Fram;
	bool _prayer;
	pair<bool, Animation*> _imageAni;

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
	Image* _effect;

	// 기타 
	// int _point; // 소지 포인트 여기? 임시로 UI에서 사용.

	  //카메라 
	  //Image* _image;
	  //RECT _rcPlayer;

	RECT _cameraRect;

	//캐릭터 위치 겟셋

	//void setPlayerPosX(float x);
	//void setPlayerPosY(float y);

   //RECT getPlayerRect();
	//void setCameraRect(RECT rect);

public:
	//기본 
	void setPrayer(bool);
	UnitState getState();
	void setCameraRect(RECT rect);
	PlayerCharacter();
	~PlayerCharacter();

	HRESULT init(POINT, vector<RECT*>);
	void release(void);
	void update(void);
	void render(void);

};