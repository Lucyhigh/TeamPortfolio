#include "Stdafx.h"
#include "Item.h"


HRESULT Item::init(void)
{
	//_ani = new AniSceneItem;
	//_ani->init();

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
		// 슬롯 Y 프레임 0 고정 
		_slotImg->frameRender(getMemDC(), _posX, _posY, 2, 0);
		_iconImg->frameRender(getMemDC(), _posX, _posY, _iconX, _iconY);

	}
	else 
	{
		switch (_state)
		{
			// 있다면 그리기 
		case ItemState::HAVE:
			_slotImg->frameRender(getMemDC(), _posX, _posY, 1, 0);

			break;
		case ItemState::SELECT:
			_slotImg->frameRender(getMemDC(), _posX, _posY, 6, 0);

		//	_ani->render(_posX, _posY); // 선택아이템은 테두리 강조

			break;
		case ItemState::MEACULPANONE:
			_slotImg->frameRender(getMemDC(), _posX, _posY, 6, 0);

			break;
		}
		//_iconImg->render(getMemDC(), _posX, _posY, _iconX *57, _iconY *57,57,57);
		_iconImg->frameRender(getMemDC(), _posX, _posY, _iconX, _iconY);
	}
	if (_state == ItemState::SELECT)
	{ 
		_slotImg->frameRender(getMemDC(), _posX, _posY, 0, 0); // 선택아이템은 테두리 강조
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
	_posX = posX; // 인벤토리에서 아이템 위치 
	_posY = posY;
}
