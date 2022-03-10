 #include "Stdafx.h"
#include "Characters.h"

#pragma region  BaseData Class

	#pragma region 정보

		// hp 정보
		int BaseData::getHp(BaseEnum getData)
		{
			if (getData == BaseEnum::STATE) { return _hp[BaseEnum::STATE]; }
			else if (getData == BaseEnum::MAX) { return _hp[BaseEnum::MAX]; }
			else return GETERROR;
		}

		// mp 정보
		int BaseData::getMp(BaseEnum getData)
		{
			if (getData == BaseEnum::STATE) { return _mp[BaseEnum::STATE]; }
			else if (getData == BaseEnum::MAX) { return _mp[BaseEnum::MAX]; }
			else return GETERROR;
		}

	#pragma endregion

	#pragma region 충돌체(위치)

		// 충돌체(위치) 정보
		RECT BaseData::getCollider()
		{ 
            return _Collider[BaseEnum::UNIT]; 
        }
		// 충돌체(위치) 정보 변경
		void BaseData::setCollider(RECT rect)
		{
            _Collider[BaseEnum::UNIT] = rect; 
        }
        //충돌체 넓이
        int BaseData::getWidth()
        {
            return  _Collider[BaseEnum::UNIT].right - _Collider[BaseEnum::UNIT].left;
        }
        //충돌체 높이
        int BaseData::getHeight()
        {
            return  _Collider[BaseEnum::UNIT].top - _Collider[BaseEnum::UNIT].bottom;
        }

		// 현재 밟고 있는 발판
		RECT BaseData::getStateFloor()
		{ return stateFloor; }

		void BaseData::setAttack(bool attack)
		{
			_isAttack = attack;
		}

	#pragma endregion

	#pragma region 공격

		// 공격 범위
		vector<pair<RECT, Image>> BaseData::getSmash()
		{
			return smash; 
		}

		// 공격 범위 초기화
		void BaseData::clearSmash(int size = 0) 
		{ 
			smash.clear();
		}

		// 공격 입력 ( 데미지 ++ ) 
		void BaseData::setHit(int damage)
		{ 
			_isHit = 1;
		}

		POINT BaseData::getPoint()
		{
			return POINT{ (_Collider[BaseEnum::UNIT].right + _Collider[BaseEnum::UNIT].left) / 2,
						(_Collider[BaseEnum::UNIT].bottom + _Collider[BaseEnum::UNIT].top) / 2 };
		}

	#pragma endregion

