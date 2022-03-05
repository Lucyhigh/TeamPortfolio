#pragma once
#include "GameNode.h"

// 대기 / 유도탄 / 순간이동 / 공중이동 / 낫 공격 / 불기둥

class FirePillar;

class BossIsadora : public  BaseData ,GameNode 
{
	private:
		enum class UnitState
		{
			IDLE,
			TRUNATTACK, 
			FIREPILLARATTACK_0,
			FIREPILLARATTACK_1,
			DIE, END, START
		};

		int _isLeft;
		int _isWarp;
		
		pair<POINT,POINT> warpPoint;
		UnitState _state;
		UnitState _oldState;
		FirePillar* _pillar;
		
		int _inputSide();
		void _inputPatten();
		void _inputEffect();
		void _inputWarpPoint();
		void _inputImageXY();

		void _inputAnimation();
		map<UnitState,function<void()>> _pattenFunc;
		Animation* _pattenAni;
		vector<float> _pattenSub;
		vector<pair<Image, Animation*>> _effect;
		float _pattenDely;
		
		void _pattenStart();
		void _pattenDie();
		void _pattenIdle();
		void _pattenWarp();
		void _pattenTurnAttack();
		void _pattenFirePollar(UnitState,POINT);
		void _pattenFirePollarAttack0();
		void _pattenFirePollarAttack1();

		
		void clearSmash(int) override;
		void setHit(int) override;
	public:
		BossIsadora();
		~BossIsadora();
		HRESULT init(POINT, vector<RECT*>);
		void release(void);
		void update(void);
		void render(void);

		bool pillarDelly;
		FirePillar* getPillar()
		{
			return _pillar;
		};
};

