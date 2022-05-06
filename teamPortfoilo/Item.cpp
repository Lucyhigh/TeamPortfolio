#include "Stdafx.h"
#include "Item.h"

HRESULT Item::init(void)
{

	return S_OK;
}

void Item::release(void)
{
	//_ani->release();
}

void Item::update(void)
{
	//_ani->update();
}

void Item::render(void)
{
	draw();
}

void Item::draw(void)
{
	if (_state == ItemState::NONE) 
	{
		_slotImg->frameRender(getMemDC(), _posX, _posY, 2, 0);
		_iconImg->frameRender(getMemDC(), _posX, _posY, _iconX, _iconY);

	}
	else 
	{
		switch (_state)
		{
		case ItemState::HAVE:
			_slotImg->frameRender(getMemDC(), _posX, _posY, 1, 0);
			break;
		case ItemState::SELECT:
			_slotImg->frameRender(getMemDC(), _posX, _posY, 6, 0);
			break;
		case ItemState::MEACULPANONE:
			_slotImg->frameRender(getMemDC(), _posX, _posY, 6, 0);
			break;
		}
		_iconImg->frameRender(getMemDC(), _posX, _posY, _iconX, _iconY);
	}
	if (_state == ItemState::SELECT)
	{ 
		_slotImg->frameRender(getMemDC(), _posX, _posY, 0, 0);
	}
}

void Item::setItemState(ItemState state)
{
	_state = state;
}

void Item::setEquip(bool state, float x, float y)
{
	_equip = state;
	_equipPosX = x;
	_equipPosY = y;
}

void Item::setItem(float posX, float posY)
{
	_posX = posX; 
	_posY = posY;
}
