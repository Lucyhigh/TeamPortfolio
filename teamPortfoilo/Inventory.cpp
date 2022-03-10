#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
	_ani = new AniSceneItem;
	_ani->init();

	_im = new ItemManager;
	_im->init();

	// max 7 
	_categoryIndex = 1;
	_selection = 0; //방향키로 선택중
	_cateMax = 0;
	_cateItemMax = 0;


	_x = 0;
	_y = 0;
	return S_OK;
}

void Inventory::release(void)
{
	_ani->release();

	_im->release();
	SAFE_DELETE(_im);
}

void Inventory::update(void)
{
	_ani->update();

	if (KEYMANAGER->isOnceKeyDown('Q'))
	{
		_categoryIndex--;
		if (_categoryIndex <= 1) _categoryIndex = 1;
		_selection = 0;
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_categoryIndex++;
		if (_categoryIndex >= 7) _categoryIndex = 7;
		_selection = 0;
	}

	// 범위 및 변수 수정 
	switch (_categoryIndex)
	{
	case 1:
		if (KEYMANAGER->isOnceKeyDown('A') && _selection >= 1)
		{
			_selection--;
		}
		else if (KEYMANAGER->isOnceKeyDown('D') && _selection <= 6)
		{
			_selection++;
		}
		else if (KEYMANAGER->isOnceKeyDown('S') && _selection + 8 <= 15)
		{
			_selection += 8;
		}
		else if (KEYMANAGER->isOnceKeyDown('W') && _selection - 8 >= 1)
		{
			_selection -= 8;
		}
		else { ; }
		
		// 체크 범위는 각 카테고리에 등록된 아이템 수량만큼(item의 categoryIndex) 
		_cateItemMax = ROSARYMAX;
	//	if (_selection > _cateItemMax) { ; }
	//	else { checkSelect(_categoryIndex, _selection); }

		break;

	case 3:
		if (KEYMANAGER->isOnceKeyDown('A') && _selection >= 0)
		{
			_selection--;
		}
		else if (KEYMANAGER->isOnceKeyDown('D') && _selection <= 4)
		{
			_selection++;
		}
		else if (KEYMANAGER->isOnceKeyDown('S') && _selection + 5 <= 15)
		{
			_selection += 5;
		}
		else if (KEYMANAGER->isOnceKeyDown('W') && _selection - 5 >= 0)
		{
			_selection -= 5;
		}
		else { ; }
		break;
	}



	// select한 아이템의 표시 
	checkSelect(_categoryIndex, _selection);

	_im->update();

	int i = 0;
	int j = 0;
	if (_selection < 7)
	{
		//i = _selection;
		j = 0;
	}
	else
	{
		switch (_selection)
		{
		case 8:  
		//	i = _selection - 8;
			j = 1;
			break;
		case 15:  
		//	i = _selection - 15;
			j = 2;
			break;
		}
	}

	if (KEYMANAGER->isToggleKey('Z'))
	{
	}

	if (_categoryIndex == 1 || _categoryIndex == 2 || _categoryIndex == 4 || _categoryIndex == 5 || _categoryIndex == 7)
	{
		//_x = 172 + (i * 64);
		_x = 172 + (_selection * 64);
		_y = 425 + (j * 62);
	}
	if (_categoryIndex == 3)
	{
		//_x = 695 + (i * 64);
		_x = 695 + (_selection * 64);
		_y = 135 + (j * 62);
	}



	if (KEYMANAGER->isOnceKeyDown(VK_F10))
	{
		//_im->getItem()[1]->setItemState(ItemState::HAVE);
		//_im->getItem()[2]->setItemState(ItemState::HAVE);
		//_im->getItem()[4]->setItemState(ItemState::HAVE);
		//_im->getItem()[6]->setItemState(ItemState::HAVE);
	}
}

void Inventory::render(void)
{
	for (int i = 0; i < _im->getItem().size(); i++)
	{

		SetTextAlign(getMemDC(), TA_LEFT);
		switch (_categoryIndex)
		{

		case 1:
			IMAGEMANAGER->findImage("inven1")->render(getMemDC(), 0, 0);

			if (_im->getItem()[i]->getState() == ItemState::NONE)
			{
			}

			if (_im->getItem()[i]->getState() == ItemState::HAVE)
			{
			}

			if (_im->getItem()[i]->getState() == ItemState::SELECT)
			{
				// 선택안됬으면 컨티뉴
			//	if (!_im->getItem()[i]->getSelect()) continue;

				{
					// 아이템 설명 할 것 
					// selected Item Name
					FONTMANAGER->drawText(getMemDC(), 275, 170,
						"둥근모꼴", 25, 100, _im->getItem()[i]->getName(), _im->getItem()[i]->getName().size(), BTEXT);

					// selected Item Script
					FONTMANAGER->drawText(getMemDC(), 195, 225,
						"둥근모꼴", 22, 100, _im->getItem()[i]->getScript(),
						_im->getItem()[i]->getScript().size(),
						MTEXT);


					// 버튼 위치
					IMAGEMANAGER->findImage("enter")->render(getMemDC(), 340, 355);
					IMAGEMANAGER->findImage("space")->render(getMemDC(), 495, 355);

					if (_im->getItem()[i]->getEquip())
					{
						// 장착했다면 해제
						FONTMANAGER->drawText(getMemDC(), 340 + 70, 360,
							"둥근모꼴", 25, 100, _InvenTEXT[1].text, wcslen(_InvenTEXT[1].text), BTEXT);
					}
					else
					{
						// 아니면 장착 
						FONTMANAGER->drawText(getMemDC(), 340 + 70, 360,
							"둥근모꼴", 25, 100, _InvenTEXT[0].text, wcslen(_InvenTEXT[0].text), BTEXT);
					}
					// 선택된 아이템의 설명 출력
					FONTMANAGER->drawText(getMemDC(), 495 + 70, 360,
						"둥근모꼴", 25, 100, _InvenTEXT[2].text, wcslen(_InvenTEXT[2].text), BTEXT);
				}
			}

			FONTMANAGER->drawText(getMemDC(), 275, 170,
				"둥근모꼴", 25, 100, rosary[_selection].name, wcslen(rosary[_selection].name), BTEXT);

			// selected Item Script
			FONTMANAGER->drawText(getMemDC(), 195, 225,	"둥근모꼴", 22, 100, rosary[_selection].script,
				((20 > wcslen(rosary[_selection].script)) ? wcslen(rosary[_selection].script) :20),	MTEXT);

			if (wcslen(rosary[_selection].script) > 20)
			{
				FONTMANAGER->drawText(getMemDC(), 195, 255, "둥근모꼴", 22, 100, rosary[_selection].script + 20,
					(20 < wcslen(rosary[_selection].script)) ?
					wcslen(rosary[_selection].script) - 20: wcslen(rosary[_selection].script),	MTEXT);
			}


			break;
		case 2:
			IMAGEMANAGER->findImage("inven2")->render(getMemDC(), 0, 0);
		

		


		case 3:
			IMAGEMANAGER->findImage("inven3")->render(getMemDC(), 0, 0);


			FONTMANAGER->drawText(getMemDC(), 275, 170,
				"둥근모꼴", 25, 100, quest[_selection].name, wcslen(quest[_selection].name), BTEXT);

			// selected Item Script
			FONTMANAGER->drawText(getMemDC(), 195, 225, "둥근모꼴", 22, 100, quest[_selection].script,
				((20 > wcslen(quest[_selection].script)) ? wcslen(quest[_selection].script) : 20), MTEXT);

			if (wcslen(quest[_selection].script) > 20)
			{
				FONTMANAGER->drawText(getMemDC(), 195, 255, "둥근모꼴", 22, 100, quest[_selection].script + 20,
					(20 < wcslen(quest[_selection].script)) ?
					wcslen(quest[_selection].script) - 20 : wcslen(quest[_selection].script), MTEXT);
			}

			break;
		case 4:
			IMAGEMANAGER->findImage("inven4")->render(getMemDC(), 0, 0);

			FONTMANAGER->drawText(getMemDC(), 275, 170,
				"둥근모꼴", 25, 100, meaculpa[_selection].name, wcslen(meaculpa[_selection].name), BTEXT);

			// selected Item Script
			FONTMANAGER->drawText(getMemDC(), 195, 225, "둥근모꼴", 22, 100, meaculpa[_selection].script,
				((20 > wcslen(meaculpa[_selection].script)) ? wcslen(meaculpa[_selection].script) : 20), MTEXT);

			if (wcslen(quest[_selection].script) > 20)
			{
				FONTMANAGER->drawText(getMemDC(), 195, 255, "둥근모꼴", 22, 100, meaculpa[_selection].script + 20,
					(20 < wcslen(meaculpa[_selection].script)) ?
					wcslen(meaculpa[_selection].script) - 20 : wcslen(meaculpa[_selection].script), MTEXT);
			}

			break;
		case 5:
			IMAGEMANAGER->findImage("inven5")->render(getMemDC(), 0, 0);
			FONTMANAGER->drawText(getMemDC(), 275, 170,
				"둥근모꼴", 25, 100, bible[_selection].name, wcslen(bible[_selection].name), BTEXT);

			// selected Item Script
			FONTMANAGER->drawText(getMemDC(), 195, 225, "둥근모꼴", 22, 100, bible[_selection].script,
				((20 > wcslen(bible[_selection].script)) ? wcslen(bible[_selection].script) : 20), MTEXT);

			if (wcslen(quest[_selection].script) > 20)
			{
				FONTMANAGER->drawText(getMemDC(), 195, 255, "둥근모꼴", 22, 100, bible[_selection].script + 20,
					(20 < wcslen(bible[_selection].script)) ?
					wcslen(bible[_selection].script) - 20 : wcslen(bible[_selection].script), MTEXT);
			}
			break;
		case 6:
			IMAGEMANAGER->findImage("inven6")->render(getMemDC(), 0, 0);

			break;
		case 7:
			IMAGEMANAGER->findImage("inven7")->render(getMemDC(), 0, 0);

			FONTMANAGER->drawText(getMemDC(), 275, 170,
				"둥근모꼴", 25, 100, collection[_selection].name, wcslen(collection[_selection].name), BTEXT);

			// selected Item Script
			FONTMANAGER->drawText(getMemDC(), 195, 225, "둥근모꼴", 22, 100, collection[_selection].script,
				((20 > wcslen(collection[_selection].script)) ? wcslen(collection[_selection].script) : 20), MTEXT);

			if (wcslen(collection[_selection].script) > 20)
			{
				FONTMANAGER->drawText(getMemDC(), 195, 255, "둥근모꼴", 22, 100, collection[_selection].script + 20,
					(20 < wcslen(collection[_selection].script)) ?
					wcslen(collection[_selection].script) - 20 : wcslen(collection[_selection].script), MTEXT);
			}
			break;
		}



		// 카테고리 인덱스를 넣어서, 해당 카테고리 아이템만 그릴 수 있도록 수정 
		// 함수 내부에서 카테고리 인덱스에 맞는 아이템만 출력 	
		_im->render(_categoryIndex);


	}

	if (_categoryIndex != 6) 	IMAGEMANAGER->findImage("items")->frameRender(getMemDC(), _x, _y, 0, 0); // 선택아이템은 테두리 강조

}

// 카테고리 확인 + 선택한 슬롯 확인 + 아이템의 카테고리 인덱스 확인 
// 선택되면 _isSelect true, 선택이아니면 false;
bool Inventory::checkSelect(int invenCategoryIndex, int selectionNum)
{

	// 각 카테고리의 아이템 갯수만큼 체크
	for (int i = 0; i < _cateItemMax; i++)
	{
		// 현재 아이템의 상태를 저장
		int _oldState;
		_oldState = (int)_im->getItem()[selectionNum + 1]->getState();

		if (_im->getItem()[selectionNum + 1]->getCateIndex() == selectionNum)
		{
			// 선택되면 isSelect = true; 
			_im->getItem()[selectionNum + 1]->setSelect(true);
		}
		break;

	}
	// 현재 카테고리와, 체크하려는 아이템의 카테고리가 동일하면 
	if (invenCategoryIndex == (int)_im->getItem()[selectionNum + 1]->getCategory())
	{
		// 현재 아이템의 상태를 저장
		int _oldState;
		_oldState = (int)_im->getItem()[selectionNum + 1]->getState();

		// 현재 아이템의 카테고리 인덱스와 선택슬롯이 동일하면 선택된 것. 
	//	if (_im->getItem()[selectionNum + 1]->getCateIndex() == selectionNum)
		{
			// 선택되면 isSelect = true; 
			//	_im->setItemSelect(true);
			return true;
		}
		//if (_im->getItem()[selectionNum + 1]->getCateIndex() != selectionNum)
		{
			// 선택이 아니면 isSelect = false + beforeState
			//_im->setItemSelect(false);
			//_im->setItemState(static_cast<ItemState>(_oldState));
		//	return false;
		}
	}
}



// 장비 장착시 능력치 반영
//================================

/*
void Inventory::setEquipment(int num)
{
	map<pair<Item::Sit, string>, Item::Data>::iterator iter = _equipment.begin();
	for (; iter != _equipment.end(); ++iter)
	{
		if (iter->first.first == get<0>(_items[num]))
		{
			if (iter->second.power[Item::Effect::DEBUFF] != 0)
			{
				GAMEMANAGER->player->_power -= iter->second.power[Item::Effect::DEBUFF];
			}
			if (iter->second.defense[Item::Effect::DEBUFF] != 0)
			{
				GAMEMANAGER->player->_defense -= iter->second.defense[Item::Effect::DEBUFF];
			}
			if (iter->second.health[Item::Effect::DEBUFF] != 0)
			{
				GAMEMANAGER->player->_health -= iter->second.health[Item::Effect::DEBUFF];
			}

			_items.push_back({ iter->first.first, iter->first.second,iter->second });
			_equipment.erase(iter);
			break;
		}
	}
	if (get<2>(_items[num]).power[Item::Effect::BUFF] != 0)
	{
		GAMEMANAGER->player->_power += get<2>(_items[num]).power[Item::Effect::BUFF];
	}
	if (get<2>(_items[num]).defense[Item::Effect::BUFF] != 0)
	{
		GAMEMANAGER->player->_defense += get<2>(_items[num]).defense[Item::Effect::BUFF];
	}
	if (get<2>(_items[num]).health[Item::Effect::BUFF] != 0)
	{
		GAMEMANAGER->player->_health += get<2>(_items[num]).health[Item::Effect::BUFF];
	}


	pair<Item::Sit, string> key = { get<0>(_items[num]), get<1>(_items[num]) };
	Item::Data data = get<2>(_items[num]);
	_equipment.insert({ key, data });
	_items.erase(_items.begin() + num);
}
*/
// 여기부터 수정 필요

