 #include "Stdafx.h"
#include "Characters.h"

#pragma region  BaseData Class

	#pragma region 정보

		int BaseData::getHp(BaseEnum getData)
		{
			if (getData == BaseEnum::STATE) { return _hp[BaseEnum::STATE]; }
			else if (getData == BaseEnum::MAX) { return _hp[BaseEnum::MAX]; }
			else return GETERROR;
		}

		int BaseData::getMp(BaseEnum getData)
		{
			if (getData == BaseEnum::STATE) { return _mp[BaseEnum::STATE]; }
			else if (getData == BaseEnum::MAX) { return _mp[BaseEnum::MAX]; }
			else return GETERROR;
		}

	#pragma endregion

	#pragma region 충돌체(위치)

		RECT BaseData::getCollider()
		{ 
            return _Collider[BaseEnum::UNIT]; 
        }
		void BaseData::setCollider(RECT rect)
		{
            _Collider[BaseEnum::UNIT] = rect; 
        }
        int BaseData::getWidth()
        {
            return  _Collider[BaseEnum::UNIT].right - _Collider[BaseEnum::UNIT].left;
        }
        int BaseData::getHeight()
        {
            return  _Collider[BaseEnum::UNIT].top - _Collider[BaseEnum::UNIT].bottom;
        }

		RECT BaseData::getStateFloor()
		{ return stateFloor; }

		void BaseData::setAttack(bool attack)
		{
			_isAttack = attack;
		}

	#pragma endregion

	#pragma region 공격

		vector<pair<RECT, Image>> BaseData::getSmash()
		{
			return smash; 
		}

		void BaseData::clearSmash(int size = 0) 
		{ 
			smash.clear();
		}

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

