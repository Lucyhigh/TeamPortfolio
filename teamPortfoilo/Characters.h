#pragma once

enum class BaseEnum
{ STATE, MAX, IMAGE, UNIT, SUB };

class BaseData
{
	protected:

		#pragma region  정보
		
			// 유닛의 이미지
			map<char*,Image*> _image;
			// hp 정보 
			map<BaseEnum, int> _hp = { {BaseEnum::STATE, 0}, {BaseEnum::MAX, 0} };
			// mp 정보
			map<BaseEnum, int> _mp = { {BaseEnum::STATE, 0}, {BaseEnum::MAX, 0} };

		#pragma endregion

		#pragma region  충돌체 (위치)

			// 충돌체 정보 
			map<BaseEnum, RECT> _Collider = { {BaseEnum::IMAGE,{0,0,0,0} }, {BaseEnum::UNIT,{0,0,0,0}} };

			// 지형
			vector<RECT*> floor;
			
			// 현재 밟고 있는 위치
			RECT stateFloor;

		#pragma endregion

		#pragma region  공격

			// 데미지 정보 
			map<BaseEnum, int> _damage = { {BaseEnum::STATE, 0}, {BaseEnum::MAX, 0} };
			// 공격 충돌체 
			vector<pair<RECT, Image*>> smash;
			// 공격을 맞았는 지 
			int _isHit;

		#pragma endregion

	public:

		function<void()> ObjectUpdate;
		function<void()> ObjectRender;

		#pragma region 정보
		
			// hp 정보
			int getHp(BaseEnum getData);
			// mp 정보
			int getMp(BaseEnum getData);

		#pragma endregion

		#pragma region 충돌체(위치)

			// 충돌체(위치) 정보
			RECT getCollider();
			// 충돌체(위치) 정보 변경
			void setCollider(RECT rect);
	
			// 현재 밟고 있는 발판
			RECT getStateFloor();

		#pragma endregion

		#pragma region 공격
	
			// 공격 범위
			vector<pair<RECT, Image*>> getSmash();
			// 공격 범위 초기화
			virtual void clearSmash(int);
	
			// 공격 입력 ( 데미지 1 ) 
			void setHit();
			// 공격 입력 ( 데미지 ++ ) 
			void setHit(int damage);

		#pragma endregion

};
