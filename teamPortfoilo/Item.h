#pragma once
#include "GameNode.h"
#include "AniScene.h"

enum class Category
{
	// 인벤토리 순서
	NONE, 
	ROSARY, 
	RELIC, 
	QUEST, 
	MEACULPA, 
	BIBLE, 
	
	SKILL, COLLECTION
};

enum class ItemState
{
	// 미습득, 습득, 선택, 메아쿨파 미선택
	NONE, HAVE, SELECT, MEACULPANONE
};

class Item : public GameNode
{
public:
	AniSceneItem* _ani; // 아이템 선택시 테두리 애니메이션

	Image* _slotImg; // 이미지 파일에서 클리핑 할 것. 
	Image* _iconImg;

	int _index; // 아이템 순번. 나중에 조건문에 넣을 대상 
	Category _category; // Y 프레임 
	ItemState _state; // 기본 NONE
	string _name;	// 파일입출력 
	string _script;  // 파일입출력 
	bool _equip; // true면 각 카테고리의 장비 위치에도 이미지 노출 , 스킬이면 해금 
	int _hp; // 장착여부에 따라 스탯 조정
	int _mp;
	int _att;
	int _dff;
	int _iconX; // 아이콘 이미지 위치 - 반복문으로 인벤토리에 자리잡기 -> 스위치문으로 카테고리에 따라 자리 바꾸기 
	int _iconY;
	float _posX; // 아이템 위치 
	float _posY;
	float _equipPosX; // 장착 아이템 위치 
	float _equipPosY;

public:
	Item() {}
	virtual ~Item() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void draw(void);
	virtual void animation(void);

	Category getCategory() { return _category; }
	ItemState getState() { return _state; }
	int getIndex() { return _index; }
	string getName() { return _name; }
	string getScript() { return _script; }
	bool getEquip() { return _equip; }


	// 아이템상태(습득,선택) / 장착여부 / 아이템 이미지 위치 
	virtual void setItem(ItemState state);
	virtual void setEquip(bool state);
	virtual void setItem(float posX, float posY);



};
