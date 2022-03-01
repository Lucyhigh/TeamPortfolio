#include "Stdafx.h"
#include "ItemManager.h"

HRESULT ItemManager::init(void)
{

	vector<string> vData = TEXTDATAMANAGER->load("Resources/Item.txt");

	for (int i = 0; i < vData.size(); i += 12)
	{
		Item* ItemData = new Item;
		ItemData->_index = atoi(vData[i].c_str());
		ItemData->_category = static_cast<Category>(atoi(vData[i + 1].c_str()));
		ItemData->_state = static_cast<ItemState>(atoi(vData[i + 2].c_str()));
		ItemData->_name = vData[i + 3].c_str();
		ItemData->_script = vData[i + 4].c_str();
		ItemData->_equip = false;
		ItemData->_hp = atoi(vData[i + 6].c_str());
		ItemData->_mp = atoi(vData[i + 7].c_str());
		ItemData->_att = atoi(vData[i + 8].c_str());
		ItemData->_dff = atoi(vData[i + 9].c_str());
		// 이미지 관련 ------------------------------------------------------------------
		ItemData->_iconX = atoi(vData[i + 10].c_str()); // 아이콘이미지 위치(프레임xy)
		ItemData->_iconY = atoi(vData[i + 11].c_str());
		ItemData->_iconImg = IMAGEMANAGER->findImage("items"); // 아이템 아이콘 이미지 조정 
		ItemData->_iconImg->setFrameX(ItemData->_iconX);
		ItemData->_iconImg->setFrameY(ItemData->_iconY);
		ItemData->_slotImg = IMAGEMANAGER->findImage("items"); // 아이템 슬롯 이미지 조정 
		ItemData->_slotImg->setFrameX(atoi(vData[i + 2].c_str()));
		ItemData->_slotImg->setFrameY(0);

		ItemData->_posX = 0 ; // 아이템 이미지 위치. 
		ItemData->_posY = 0;
		ItemData->_equipPosX = 0 ; // 아이템 이미지 위치. 
		ItemData->_equipPosY = 0 ;
		_vItem.push_back(ItemData);
	}


	return S_OK;
}

void ItemManager::release(void)
{
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->release();
		SAFE_DELETE(*_viItem);
	}
}

void ItemManager::update(void)
{
	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->update();
	}
}

void ItemManager::render(void)
{

	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		(*_viItem)->render();
	}
}

void ItemManager::render(int categoryIndex)
{

	_viItem = _vItem.begin();
	for (; _viItem != _vItem.end(); ++_viItem)
	{
		int i = (int)(*_viItem)->_category;
		if (categoryIndex == i)
		{
			(*_viItem)->render();
		}
	}
}

void ItemManager::setItem(void)
{
}

void ItemManager::removeItem(int arrNum)
{
	SAFE_DELETE(_vItem[arrNum]);
	_vItem.erase(_vItem.begin() + arrNum);

}
