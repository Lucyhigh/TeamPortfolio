#pragma once

enum class BaseEnum
{ STATE, MAX, IMAGE, UNIT, SUB };

class BaseData
{
	protected:

		#pragma region  ����
		
			// ������ �̹���
			Image* _image;
			// hp ���� 
			map<BaseEnum, int> _hp = { {BaseEnum::STATE, 136}, {BaseEnum::MAX, 136} };
			// mp ����
			map<BaseEnum, int> _mp = { {BaseEnum::STATE, 116}, {BaseEnum::MAX, 116} };

		#pragma endregion

		#pragma region  �浹ü (��ġ)

			// �浹ü ���� 
			map<BaseEnum, RECT> _Collider = { {BaseEnum::IMAGE,{0,0,0,0} }, {BaseEnum::UNIT,{0,0,0,0}} };

			// ����
			vector<RECT*> floor;
			
			// ���� ��� �ִ� ��ġ
			RECT stateFloor;

		#pragma endregion

		#pragma region  ����

			// ������ ���� 
			map<BaseEnum, int> _damage = { {BaseEnum::STATE, 0}, {BaseEnum::MAX, 0} };
			// ���� �浹ü 
			vector<pair<RECT, Image*>> smash;
			// ������ �¾Ҵ� �� 
			int _isHit;

		#pragma endregion

	public:

		function<void(POINT, vector<RECT*>)> ObjectInit;
		function<void()> ObjectrRelease;
		function<void()> ObjectUpdate;
		function<void()> ObjectRender;
		

		#pragma region ����
		
			// hp ����
			int getHp(BaseEnum getData);
			// mp ����
			int getMp(BaseEnum getData);

		#pragma endregion

		#pragma region �浹ü(��ġ)

			// �浹ü(��ġ) ����
			RECT getCollider();
			// �浹ü(��ġ) ���� ����
			void setCollider(RECT rect);
	
			// ���� ��� �ִ� ����
			RECT getStateFloor();

		#pragma endregion

		#pragma region ����
	
			// ���� ����
			vector<pair<RECT, Image*>> getSmash();
			// ���� ���� �ʱ�ȭ
			virtual void clearSmash(int);
	
			// ���� �Է� ( ������ 1 ) 
			void setHit();
			// ���� �Է� ( ������ ++ ) 
			void setHit(int damage);

		#pragma endregion

			// �߰� �� 
			POINT getPoint()
			{ return POINT{ _Collider[BaseEnum::UNIT].left + ((_Collider[BaseEnum::UNIT].right + _Collider[BaseEnum::UNIT].left) / 2), (_Collider[BaseEnum::UNIT].bottom - _Collider[BaseEnum::UNIT].top) / 2 }; }

};
