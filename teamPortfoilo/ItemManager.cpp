#include "Stdafx.h"
#include "ItemManager.h"

ItemManager::ItemManager()
{
	vector<string> vData = TEXTDATAMANAGER->load("Resources/Item.txt");

	for (int i = 0; i < vData.size(); i += 12)
	{
		for (int i = 0; i < vData.size(); i += 13)
		{
			Item* ItemData = new Item;
			ItemData->_index = atoi(vData[i].c_str());
			ItemData->_cateIndex = atoi(vData[i + 1].c_str());
			ItemData->_category = static_cast<Category>(atoi(vData[i + 2].c_str()));
			ItemData->_state = static_cast<ItemState>(atoi(vData[i + 3].c_str()));
			ItemData->_name = vData[i + 4].c_str();
			ItemData->_script = vData[i + 5].c_str();
			ItemData->_equip = false;
			ItemData->_isSelect = false;
			ItemData->_hp = atoi(vData[i + 6].c_str());
			ItemData->_mp = atoi(vData[i + 7].c_str());
			ItemData->_att = atoi(vData[i + 8].c_str());
			ItemData->_dff = atoi(vData[i + 9].c_str());
			ItemData->_script2 = vData[i + 12].c_str();

			ItemData->_iconX = atoi(vData[i + 10].c_str()); 
			ItemData->_iconY = atoi(vData[i + 11].c_str());
			ItemData->_iconImg = IMAGEMANAGER->findImage("items"); 
			ItemData->_iconImg->setFrameX(ItemData->_iconX);
			ItemData->_iconImg->setFrameY(ItemData->_iconY);
			ItemData->_slotImg = IMAGEMANAGER->findImage("items"); 
			ItemData->_slotImg->setFrameX(atoi(vData[i + 3].c_str()));
			ItemData->_slotImg->setFrameY(0);
			ItemData->_equipImg = IMAGEMANAGER->findImage("items"); 
			
			int j = 0;
			switch (ItemData->_category)
			{
			case Category::ROSARY:
				if (ItemData->_cateIndex < 8)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 1;
					j = 0;
				}
				else if (ItemData->_cateIndex < 16)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 9;
					j = 1;
				}
				else if (ItemData->_cateIndex < 24)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 17;
					j = 2;
				}
				ItemData->_posX = 172 + (ItemData->_cateIndex * 64);
				ItemData->_posY = 425 + (j * 62);
				break;
			case Category::RELIC:
				ItemData->_posX = 172 + (ItemData->_cateIndex * 57 + 7);
				ItemData->_posY = 425;
				break;
			case Category::QUEST:
				if (ItemData->_cateIndex < 5)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 1;
					j = 0;
				}
				else if (ItemData->_cateIndex < 10)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 5;
					j = 1;
				}
				else if (ItemData->_cateIndex < 15)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 10;
					j = 2;
				}
				else if (ItemData->_cateIndex < 20)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 15;
					j = 3;
				}
				else if (ItemData->_cateIndex < 25)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 20;
					j = 4;
				}
				else if (ItemData->_cateIndex < 30)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 25;
					j = 5;
				}
				else if (ItemData->_cateIndex < 35)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 30;
					j = 6;
				}
				ItemData->_posX = 695 + (ItemData->_cateIndex * 64);
				ItemData->_posY = 135;
				break;
			case Category::MEACULPA:
				if (ItemData->_cateIndex < 8)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 1;
					j = 0;
				}
				else if (ItemData->_cateIndex < 11)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 9;
					j = 1;
				}
				ItemData->_posX = 172 + (ItemData->_cateIndex * 64);
				ItemData->_posY = 425 + (j * 62);
				break;
			case Category::BIBLE:
				if (ItemData->_cateIndex < 8)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 1;
					j = 0;
				}
				else if (ItemData->_cateIndex < 16)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 9;
					j = 1;
				}
				else if (ItemData->_cateIndex < 17)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 17;
					j = 2;
				}
				ItemData->_posX = 172 + (ItemData->_cateIndex * 64);
				ItemData->_posY = 427 + (j * 62);
				break;
			case Category::SKILL:
				break;
			case Category::COLLECTION:
				if (ItemData->_cateIndex < 8)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 1;
					j = 0;
				}
				else if (ItemData->_cateIndex < 16)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 9;
					j = 1;
				}
				else if (ItemData->_cateIndex < 24)
				{
					ItemData->_cateIndex = ItemData->_cateIndex - 17;
					j = 2;
				}
				ItemData->_posX = 172 + (ItemData->_cateIndex * 64);
				ItemData->_posY = 425 + (j * 62);
				break;
			}

			ItemData->_equipPosX = 0; 
			ItemData->_equipPosY = 0;
			_vItem.push_back(ItemData);
		}
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