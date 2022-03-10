#pragma once

enum class BaseEnum
{
	STATE, MAX, IMAGE, UNIT, SUB
};

class BaseData
{
protected:

#pragma region  정보

	Image* _image;
	map<BaseEnum, int> _hp = { {BaseEnum::STATE, 0}, {BaseEnum::MAX, 0} };
	map<BaseEnum, int> _mp = { {BaseEnum::STATE, 0}, {BaseEnum::MAX, 0} };

#pragma endregion

#pragma region  충돌체 (위치)

	map<BaseEnum, RECT> _Collider = { {BaseEnum::IMAGE,{0,0,0,0} }, {BaseEnum::UNIT,{0,0,0,0}} };

	vector<RECT*> floor;

	RECT stateFloor;

#pragma endregion

#pragma region  공격

	map<BaseEnum, int> _damage = { {BaseEnum::STATE, 0}, {BaseEnum::MAX, 0} };
	vector<pair<RECT, Image>> smash;
	int _isHit;

	bool _isAttack;

#pragma endregion

public:

	function<void(POINT, vector<RECT*>)> ObjectInit;
	function<void()> ObjectrRelease;
	function<void()> ObjectUpdate;
	function<void()> ObjectRender;

#pragma region 정보

	int getHp(BaseEnum getData);
	int getMp(BaseEnum getData);

#pragma endregion

#pragma region 충돌체(위치)

	RECT getCollider();
	void setCollider(RECT rect);
	int getWidth();
	int getHeight();
	RECT getStateFloor();

#pragma endregion

#pragma region 공격

	vector<pair<RECT, Image>> getSmash();
	virtual void clearSmash(int);
	virtual void setHit(int damage);

#pragma endregion

	void setAttack(bool attack);

	POINT getPoint();

	void setHp(bool UpAndDown, int num)
	{
		if (UpAndDown == true)
		{
			_hp[BaseEnum::STATE] += num;
		}
		else
		{
			_hp[BaseEnum::STATE] -= num;
		}
	}
};
