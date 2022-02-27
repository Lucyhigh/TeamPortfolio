#include "Stdafx.h"
#include "Item.h"

HRESULT Item::init(void)
{
	/*
	_index = index;
	_category = category;
	_state = state;
	_posX = posX;
	_posY = posY;
	// _frameXNum; // 이미지 시트에서 이미지 위치 
	// _frameYNum;
	_name = name;
	_script = script;
	_equip = equip;
	_hp = hp;
	_mp = mp;
	_att = att;
	_dff = dff;

	*/


	return S_OK;
}

void Item::release(void)
{
}

void Item::update(void)
{
}

void Item::render(void)
{
}

void Item::setItemData(int index, Category category, ItemState state, float posX, float posY, 
	string name, string script, bool equip, int hp, int mp, int att, int dff)
{
	_index = index;
	_category = category;
	_state = state;
	_posX = posX;
	_posY = posY;
	// _frameXNum; // 이미지 시트에서 이미지 위치 
	// _frameYNum;
	_name = name;
	_script = script;
	_equip = equip;
	_hp = hp;
	_mp = mp;
	_att = att;
	_dff = dff;
}
