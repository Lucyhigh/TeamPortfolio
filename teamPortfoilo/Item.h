#pragma once
#include "GameNode.h"
#include "AniScene.h"

enum class Category
{
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
	AniSceneItem* _ani; 

	Image* _slotImg;  
	Image* _iconImg;
	Image* _equipImg;

	int _index;			
	int _cateIndex;		
	Category _category;	
	ItemState _state;	
	string _name;		
	string _script;		
	bool _equip;  
	bool _isSelect;
	int _hp; 
	int _mp;
	int _att;
	int _dff;
	int _iconX;				
	int _iconY;
	float _posX;			
	float _posY;
	float _equipPosX;		
	float _equipPosY;
	string _script2;		
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
	bool getEquip() { return _equip; }
	bool getSelect() { return _isSelect; }

	void setItemState(ItemState state);
	void setItem(float posX, float posY);
	void setEquip(bool state, float x, float y);
	void setSelect(bool state) { _isSelect = state; }
};
