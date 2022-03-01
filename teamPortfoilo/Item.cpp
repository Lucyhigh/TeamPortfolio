#include "Stdafx.h"
#include "Item.h"

HRESULT Item::init(void)
{

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
		// �κ��� ���� ���� 

		// �׽�Ʈ �� �׸��� 

		cout << "-----------" << endl;
		// ���� Y ������ 0 ���� 
		switch (_state)
		{
		case ItemState::NONE:
			_slotImg->frameRender(getMemDC(), CENTER_X, CENTER_Y, 2, 0);

			break;
		case ItemState::HAVE:
			_slotImg->frameRender(getMemDC(), CENTER_X, CENTER_Y, 1, 0);

			break;
		case ItemState::SELECT:
			_slotImg->frameRender(getMemDC(), CENTER_X, CENTER_Y, 6, 0);

			break;
		case ItemState::MEACULPANONE:
			_slotImg->frameRender(getMemDC(), CENTER_X, CENTER_Y, 6, 0);

			break;
		}
	}
	else 
	{
		switch (_state)
		{
			// �ִٸ� �׸��� 
		case ItemState::HAVE:
			_slotImg->frameRender(getMemDC(), CENTER_X, CENTER_Y, 1, 0);

			break;
		case ItemState::SELECT:
			_slotImg->frameRender(getMemDC(), CENTER_X, CENTER_Y, 6, 0);

			break;
		case ItemState::MEACULPANONE:
			_slotImg->frameRender(getMemDC(), CENTER_X, CENTER_Y, 6, 0);

			break;
		}
		_iconImg->render(getMemDC(),CENTER_X,CENTER_Y ,_slotX*57, _slotY*57,57,57);
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
	// _frameXNum; // �̹��� ��Ʈ���� �̹��� ��ġ 
	// _frameYNum;
	_name = name;
	_script = script;
	_equip = equip;
	_hp = hp;
	_mp = mp;
	_att = att;
	_dff = dff;
}
