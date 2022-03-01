#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
	_im = new ItemManager;
	_im->init();

	// max 7 
	_categoryIndex = 1;
	_selection = 0; //����Ű�� ������
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

	// ���� �� ���� ���� 
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
	cout << "�⺻���� ----------------------------- " <<endl;
	for(int i = 0; i < _im->getItem().size();i++)
	{
	SetTextAlign(getMemDC(), TA_LEFT);
	switch (_categoryIndex)
	{

	case 1 :

		IMAGEMANAGER->findImage("inven1")->render(getMemDC(), 0, 0);
		if (_im->getItem()[i]->getState() == ItemState::NONE)
		{
			cout << "1 ���� -- " << endl;
			cout << "----------------" << endl;
			// ������ ���� �� �� 
			// selected Item Name
			FONTMANAGER->drawText(getMemDC(), 275,170,
				"�ձٸ��", 25, 100, _im->getItem()[i]->getName(), _im->getItem()[i]->getName().size(), BTEXT);

			cout << _im->getItem()[i]->getName() << endl;

			// selected Item Script
			FONTMANAGER->drawText(getMemDC(), 195,225,
				"�ձٸ��", 22, 100, _im->getItem()[i]->getScript(), _im->getItem()[i]->getScript().size(), MTEXT);
			
			cout << _im->getItem()[i]->getScript() << endl;

			// ��ư ��ġ . ����Ʈ���� �����ʿ�  -500  // +135
			IMAGEMANAGER->findImage("enter")->render(getMemDC(),340, 355);
			IMAGEMANAGER->findImage("space")->render(getMemDC(),495, 355);

			if (_im->getItem()[i]->getEquip())
			{
				// �����ߴٸ� ����
				FONTMANAGER->drawText(getMemDC(), 340 + 70, 360,
					"�ձٸ��", 25, 100, _InvenTEXT[1].text, wcslen(_InvenTEXT[1].text), BTEXT);
			}
			else
			{
				// �ƴϸ� ���� 
				FONTMANAGER->drawText(getMemDC(), 340 + 70, 360,
					"�ձٸ��", 25, 100, _InvenTEXT[0].text, wcslen(_InvenTEXT[0].text), BTEXT);
			}
			// ���õ� �������� ���� ���
			FONTMANAGER->drawText(getMemDC(), 495 + 70, 360,
				"�ձٸ��", 25, 100, _InvenTEXT[2].text, wcslen(_InvenTEXT[2].text), BTEXT);

		}

		if (_im->getItem()[i]->getState() == ItemState::HAVE)
		{
		}

		if(_im->getItem()[i]->getState() == ItemState::SELECT)
		{
		
		}


		break;
	case 2:
		cout << "2 ���� -- " << endl;

		IMAGEMANAGER->findImage("inven2")->render(getMemDC(), 0, 0);
		break;
	case 3:
		cout << "3 ���� -- " << endl;
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
	

	// ī�װ� �ε����� �־, �ش� ī�װ� �����۸� �׸� �� �ֵ��� ���� 
	// �Լ� ���ο��� ī�װ� �ε����� �´� �����۸� ��� 	
	_im->render(_categoryIndex);


	}





	
}





// ��� ������ �ɷ�ġ �ݿ�
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
// ������� ���� �ʿ�

