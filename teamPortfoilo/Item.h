#pragma once
#include "GameNode.h"
#include "AniScene.h"

enum class Category
{
	// inventory cateNum
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
	NONE, HAVE, SELECT, MEACULPANONE
};

class Item : public GameNode
{
public:
	AniSceneItem* _ani; // outlineAnimation

	Image* _slotImg;  
	Image* _iconImg;
	Image* _equipImg;

	int _index;				// all item index 
	int _cateIndex;			// categoty index
	Category _category;		// Y frame 
	ItemState _state;		// standard NONE
	string _name;			// file inOut 
	string _script;			// file inOut 
	bool _equip;  
	bool _isSelect;
	int _hp; 
	int _mp;
	int _att;
	int _dff;
	int _iconX;				// icon image position in bmp
	int _iconY;
	float _posX;			// image position in inventory
	float _posY;
	float _equipPosX;		// equip item show position
	float _equipPosY;
	string _script2;		// quest item script
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
