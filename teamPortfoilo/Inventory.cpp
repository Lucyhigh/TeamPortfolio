#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
	_im = new ItemManager;
	_im->init();

	// max 7 
	_categoryIndex = 1;
	_selection = 0; //방향키로 선택중
	return S_OK;
}

void Inventory::release(void)
{
	_im->release();
	SAFE_DELETE(_im);
}

void Inventory::update(void)
{
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
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT) && _selection != 0)
	{
		_selection--;
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_RIGHT) && _selection < 15)
	{
		_selection++;
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_DOWN) && _selection + 8 <= 15)
	{
		_selection += 8;
	}
	else if (KEYMANAGER->isOnceKeyDown(VK_UP) && _selection - 8 >= 0)
	{
		_selection -= 8;
	}

	_im->update();
}

void Inventory::render(void)
{
	cout << "기본렌더 ----------------------------- " <<endl;
	for(int i = 0; i < _im->getItem().size();i++)
	{
	SetTextAlign(getMemDC(), TA_LEFT);
	switch (_categoryIndex)
	{

	case 1 :

		IMAGEMANAGER->findImage("inven1")->render(getMemDC(), 0, 0);
		if (_im->getItem()[i]->getState() == ItemState::NONE)
		{
			cout << "1 묵주 -- " << endl;
			cout << "----------------" << endl;
			// 아이템 설명 할 것 
			// selected Item Name
			FONTMANAGER->drawText(getMemDC(), 275,170,
				"둥근모꼴", 25, 100, _im->getItem()[i]->getName(), _im->getItem()[i]->getName().size(), BTEXT);

			cout << _im->getItem()[i]->getName() << endl;

			// selected Item Script
			FONTMANAGER->drawText(getMemDC(), 195,225,
				"둥근모꼴", 22, 100, _im->getItem()[i]->getScript(), _im->getItem()[i]->getScript().size(), MTEXT);
			
			cout << _im->getItem()[i]->getScript() << endl;

			// 버튼 위치 . 퀘스트템은 수정필요  -500  // +135
			IMAGEMANAGER->findImage("enter")->render(getMemDC(),340, 355);
			IMAGEMANAGER->findImage("space")->render(getMemDC(),495, 355);

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

		if (_im->getItem()[i]->getState() == ItemState::HAVE)
		{
		}

		if(_im->getItem()[i]->getState() == ItemState::SELECT)
		{
		
		}


		break;
	case 2:
		cout << "2 유물 -- " << endl;

		IMAGEMANAGER->findImage("inven2")->render(getMemDC(), 0, 0);
		break;
	case 3:
		cout << "3 퀘템 -- " << endl;
		IMAGEMANAGER->findImage("inven3")->render(getMemDC(), 0, 0);
		break;
	case 4:
		IMAGEMANAGER->findImage("inven4")->render(getMemDC(), 0, 0);
		break;
	case 5:
		IMAGEMANAGER->findImage("inven5")->render(getMemDC(), 0, 0);
		break;
	case 6:
		IMAGEMANAGER->findImage("inven6")->render(getMemDC(), 0, 0);
		break;
	case 7:
		IMAGEMANAGER->findImage("inven7")->render(getMemDC(), 0, 0);
		break;


	default:
		break;



	}
	

	// 카테고리 인덱스를 넣어서, 해당 카테고리 아이템만 그릴 수 있도록 수정 
	// 함수 내부에서 카테고리 인덱스에 맞는 아이템만 출력 	
	_im->render(_categoryIndex);


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

