 #include "Stdafx.h"
#include "Characters.h"

#pragma region  BaseData Class

	#pragma region ����

		// hp ����
		int BaseData::getHp(BaseEnum getData)
		{
			if (getData == BaseEnum::STATE) { return _hp[BaseEnum::STATE]; }
			else if (getData == BaseEnum::MAX) { return _hp[BaseEnum::MAX]; }
			else return GETERROR;
		}

		// mp ����
		int BaseData::getMp(BaseEnum getData)
		{
			if (getData == BaseEnum::STATE) { return _mp[BaseEnum::STATE]; }
			else if (getData == BaseEnum::MAX) { return _mp[BaseEnum::MAX]; }
			else return GETERROR;
		}

	#pragma endregion

	#pragma region �浹ü(��ġ)

		// �浹ü(��ġ) ����
		RECT BaseData::getCollider()
		{ 
            return _Collider[BaseEnum::UNIT]; 
        }
		// �浹ü(��ġ) ���� ����
		void BaseData::setCollider(RECT rect)
		{
            _Collider[BaseEnum::UNIT] = rect; 
        }
        //�浹ü ����
        int BaseData::getWidth()
        {
            return  _Collider[BaseEnum::UNIT].right - _Collider[BaseEnum::UNIT].left;
        }
        //�浹ü ����
        int BaseData::getHeight()
        {
            return  _Collider[BaseEnum::UNIT].top - _Collider[BaseEnum::UNIT].bottom;
        }

		// ���� ��� �ִ� ����
		RECT BaseData::getStateFloor()
		{ return stateFloor; }

		void BaseData::setAttack(bool attack)
		{
			_isAttack = attack;
		}

	#pragma endregion

	#pragma region ����

		// ���� ����
		vector<pair<RECT, Image>> BaseData::getSmash()
		{
			return smash; 
		}

		// ���� ���� �ʱ�ȭ
		void BaseData::clearSmash(int size = 0) 
		{ 
			smash.clear();
		}

		// ���� �Է� ( ������ ++ ) 
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

