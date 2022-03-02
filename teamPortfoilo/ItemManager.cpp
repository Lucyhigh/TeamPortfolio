#include "Stdafx.h"
#include "ItemManager.h"

ItemManager::ItemManager()
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
		ItemData->_iconImg = IMAGEMANAGER->findImage("items"); // 아이템 아이콘 프레임 
		ItemData->_iconImg->setFrameX(ItemData->_iconX);
		ItemData->_iconImg->setFrameY(ItemData->_iconY);
		ItemData->_slotImg = IMAGEMANAGER->findImage("items"); // 아이템 슬롯 프레임(기본 미습득) 
		ItemData->_slotImg->setFrameX(atoi(vData[i + 2].c_str()));
		ItemData->_slotImg->setFrameY(0);

		switch (ItemData->_category)
		{
		case Category::NONE:
			break;
		case Category::ROSARY:
			break;
		case Category::RELIC:
			break;
		case Category::QUEST:
			break;
		case Category::MEACULPA:
			break;
		case Category::BIBLE:
			break;
		case Category::SKILL:
			break;
		case Category::COLLECTION:
			break;
		default:
			break;
		}

		//ItemData->_posX = 0; // 아이템 이미지 위치 -> 카테고리에 따라 다르게. 
		//ItemData->_posY = 0;
		ItemData->_posX = 172;
		ItemData->_posY = 425;
		ItemData->_equipPosX = 0; // 아이템 이미지 위치. 
		ItemData->_equipPosY = 0;
		_vItem.push_back(ItemData);
	}

}

HRESULT ItemManager::init(void)
{

	

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
			cout <<"아이템 카테고리+렌더 체크 : " << (*_viItem)->getName() << categoryIndex << " , " << i << endl;

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


