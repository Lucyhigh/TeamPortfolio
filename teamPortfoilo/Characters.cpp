#include "Stdafx.h"
#include "Characters.h"

#pragma region  BaseData Class

	#pragma region ����

		// hp ����
		int BaseData::getHp(BaseEnum getData)
		{
			if (getData == BaseEnum::STATE) { return _hp[BaseEnum::STATE]; }
			else if (getData == BaseEnum::STATE) { return _hp[BaseEnum::MAX]; }
			else return GETERROR;
		}

		// mp ����
		int BaseData::getMp(BaseEnum getData)
		{
			if (getData == BaseEnum::STATE) { return _mp[BaseEnum::STATE]; }
			else if (getData == BaseEnum::STATE) { return _mp[BaseEnum::MAX]; }
			else return GETERROR;
		}

	#pragma endregion

	#pragma region �浹ü(��ġ)

		// �浹ü(��ġ) ����
		RECT BaseData::getCollider()
		{ return _Collider[BaseEnum::UNIT]; }
		// �浹ü(��ġ) ���� ����
		void BaseData::setCollider(RECT rect)
		{ _Collider[BaseEnum::UNIT] = rect; }

		// ���� ��� �ִ� ����
		RECT BaseData::getStateFloor()
		{ return stateFloor; }

	#pragma endregion

	#pragma region ����

		// ���� ����
		vector<pair<RECT, Image*>> BaseData::getSmash()
		{ return smash; }
		// ���� ���� �ʱ�ȭ
		void BaseData::clearSmash()
		{ smash.clear(); }

		// ���� �Է� ( ������ 1 ) 
		void BaseData::setHit()
		{ _isHit = 1; }
		// ���� �Է� ( ������ ++ ) 
		void BaseData::setHit(int damage)
		{ _isHit = damage; }

	#pragma endregion

#pragma endregion

