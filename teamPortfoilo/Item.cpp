#include "Stdafx.h"
#include "Item.h"

HRESULT Item::init(void)
{
	IMAGEMANAGER->addFrameImage("items", "Resources/Images/item/items.bmp", 510 * 1.9, 510 * 1.9, 17, 17, MGT); // 510,510->969,969
	IMAGEMANAGER->addImage("item", "Resources/Images/item/items.bmp", 510 * 1.9, 510 * 1.9, MGT); // 510,510->969,969



	//_img = IMAGEMANAGER->findImage("items");
	//_test = IMAGEMANAGER->findImage("item");
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
	draw();
}

void Item::draw(void)
{
	if (_state == ItemState::NONE) 
	{
		// 인벤에 없는 상태 

		// 테스트 용 그리기 

		cout << "-----------" << endl;
		_img->frameRender(getMemDC(),_slotX,_slotY);
	//	_test->render(getMemDC());
	}
	else 
	{
		// 있다면 그리기 
		_img->render(getMemDC(),CENTER_X,CENTER_Y ,_slotX*40, _slotY*40,40,40);

	}
}


void Item::setItemData(int index, Category category, ItemState state, float posX, float posY, 
	string name, string script, bool equip, int hp, int mp, int att, int dff)
{
	_index = index;
	_category = category;
	_state = state;
	_slotX = posX;
	_slotY = posY;
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
