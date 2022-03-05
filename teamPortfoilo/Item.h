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
	Image* _equipImg;

	int _index; // 전체 아이템 중 n번째 아이템 순번. 나중에 조건문에 넣을 대상 
	int _cateIndex; // 카테고리의 n번째 아이템
	Category _category; // Y 프레임 
	ItemState _state; // 기본 NONE
	string _name;	// 파일입출력 
	string _script;  // 파일입출력 
	bool _equip; // true면 각 카테고리의 장비 위치에도 이미지 노출 , 스킬이면 해금 
	bool _isSelect;
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
	string _script2;  // 퀘스트 아이템 상세 설명
	//LPCWSTR  _testScript;
public:
	Item() {}
	virtual ~Item() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void draw(void);

	Category getCategory() { return _category; }
	ItemState getState() { return _state; }
	int getIndex() { return _index; }
	int getCateIndex() { return _cateIndex; }
	string getName() { return _name; }
	string getScript() { return _script; }
	//LPCWSTR getTextScript() { return _testScript; }
	bool getEquip() { return _equip; }
	bool getSelect() { return _isSelect; }

	// 아이템상태(습득,선택) / 장착여부 / 아이템 이미지 위치 
	void setItemState(ItemState state);
	void setItem(float posX, float posY);
	void setEquip(bool state, float x, float y);
	void setSelect(bool state) { _isSelect = state; }


};
