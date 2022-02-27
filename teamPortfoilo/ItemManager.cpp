#include "Stdafx.h"
#include "ItemManager.h"

HRESULT ItemManager::init(void)
{

	vector<string> vData = TEXTDATAMANAGER->loadFstream("Resources/Item.csv");

	for (int i = 0; i < vData.size(); i++)
	{
		Item* ItemData = new Item;
		ItemData->_index = atoi(vData[i].c_str());
		ItemData->_category = static_cast<Category>(atoi(vData[i + 1].c_str()));
		ItemData->_state = ItemState::NONE;
		ItemData->_posX = 0;
		ItemData->_posY = 0;
		//	ItemData->_frameXNum; // 이미지 시트에서 이미지 위치 
		//	ItemData->_frameYNum;
		ItemData->_name = vData[i + 3].c_str();
		ItemData->_script = vData[i + 4].c_str();
		ItemData->_equip = false;
		ItemData->_hp = atoi(vData[i + 6].c_str());
		ItemData->_mp = atoi(vData[i + 7].c_str());
		ItemData->_att = atoi(vData[i + 8].c_str());
		ItemData->_dff = atoi(vData[i + 9].c_str());

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

void ItemManager::setItem(void)
{
}

void ItemManager::removeItem(int arrNum)
{
	SAFE_DELETE(_vItem[arrNum]);
	_vItem.erase(_vItem.begin() + arrNum);

}
