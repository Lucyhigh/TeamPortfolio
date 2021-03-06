#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
	_ani = new AniSceneItem;
	_ani->init();

	_im = new ItemManager;
	_im->init();
 
	_categoryIndex = 1;
	_selection = 0;
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
		
		_cateItemMax = ROSARYMAX;

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

	checkSelect(_categoryIndex, _selection);

	_im->update();

	int i = 0;
	int j = 0;
	if (_selection < 7)
	{
		j = 0;
	}
	else
	{
		switch (_selection)
		{
		case 8:  
			j = 1;
			break;
		case 15:  
			j = 2;
			break;
		}
	}

	if (KEYMANAGER->isToggleKey('Z'))
	{
	}

	if (_categoryIndex == 1 || _categoryIndex == 2 || _categoryIndex == 4 || _categoryIndex == 5 || _categoryIndex == 7)
	{
		_x = 172 + (_selection * 64);
		_y = 425 + (j * 62);
	}
	if (_categoryIndex == 3)
	{
		_x = 695 + (_selection * 64);
		_y = 135 + (j * 62);
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
				{
					FONTMANAGER->drawText(getMemDC(), 275, 170,
						"????????", 25, 100, _im->getItem()[i]->getName(), _im->getItem()[i]->getName().size(), BTEXT);

					FONTMANAGER->drawText(getMemDC(), 195, 225,
						"????????", 22, 100, _im->getItem()[i]->getScript(),
						_im->getItem()[i]->getScript().size(),
						MTEXT);


					IMAGEMANAGER->findImage("enter")->render(getMemDC(), 340, 355);
					IMAGEMANAGER->findImage("space")->render(getMemDC(), 495, 355);

					if (_im->getItem()[i]->getEquip())
					{
						FONTMANAGER->drawText(getMemDC(), 340 + 70, 360,
							"????????", 25, 100, _InvenTEXT[1].text, wcslen(_InvenTEXT[1].text), BTEXT);
					}
					else
					{
						FONTMANAGER->drawText(getMemDC(), 340 + 70, 360,
							"????????", 25, 100, _InvenTEXT[0].text, wcslen(_InvenTEXT[0].text), BTEXT);
					}
					FONTMANAGER->drawText(getMemDC(), 495 + 70, 360,
						"????????", 25, 100, _InvenTEXT[2].text, wcslen(_InvenTEXT[2].text), BTEXT);
				}
			}

			FONTMANAGER->drawText(getMemDC(), 275, 170,
				"????????", 25, 100, rosary[_selection].name, wcslen(rosary[_selection].name), BTEXT);

			FONTMANAGER->drawText(getMemDC(), 195, 225,	"????????", 22, 100, rosary[_selection].script,
				((20 > wcslen(rosary[_selection].script)) ? wcslen(rosary[_selection].script) :20),	MTEXT);

			if (wcslen(rosary[_selection].script) > 20)
			{
				FONTMANAGER->drawText(getMemDC(), 195, 255, "????????", 22, 100, rosary[_selection].script + 20,
					(20 < wcslen(rosary[_selection].script)) ?
					wcslen(rosary[_selection].script) - 20: wcslen(rosary[_selection].script),	MTEXT);
			}
			break;
		case 2:
			IMAGEMANAGER->findImage("inven2")->render(getMemDC(), 0, 0);
			break;

		case 3:
			IMAGEMANAGER->findImage("inven3")->render(getMemDC(), 0, 0);

			FONTMANAGER->drawText(getMemDC(), 275, 170,
				"????????", 25, 100, quest[_selection].name, wcslen(quest[_selection].name), BTEXT);

			
			FONTMANAGER->drawText(getMemDC(), 195, 225, "????????", 22, 100, quest[_selection].script,
				((20 > wcslen(quest[_selection].script)) ? wcslen(quest[_selection].script) : 20), MTEXT);

			if (wcslen(quest[_selection].script) > 20)
			{
				FONTMANAGER->drawText(getMemDC(), 195, 255, "????????", 22, 100, quest[_selection].script + 20,
					(20 < wcslen(quest[_selection].script)) ?
					wcslen(quest[_selection].script) - 20 : wcslen(quest[_selection].script), MTEXT);
			}

			break;
		case 4:
			IMAGEMANAGER->findImage("inven4")->render(getMemDC(), 0, 0);

			FONTMANAGER->drawText(getMemDC(), 275, 170,
				"????????", 25, 100, meaculpa[_selection].name, wcslen(meaculpa[_selection].name), BTEXT);

			
			FONTMANAGER->drawText(getMemDC(), 195, 225, "????????", 22, 100, meaculpa[_selection].script,
				((20 > wcslen(meaculpa[_selection].script)) ? wcslen(meaculpa[_selection].script) : 20), MTEXT);

			if (wcslen(quest[_selection].script) > 20)
			{
				FONTMANAGER->drawText(getMemDC(), 195, 255, "????????", 22, 100, meaculpa[_selection].script + 20,
					(20 < wcslen(meaculpa[_selection].script)) ?
					wcslen(meaculpa[_selection].script) - 20 : wcslen(meaculpa[_selection].script), MTEXT);
			}

			break;
		case 5:
			IMAGEMANAGER->findImage("inven5")->render(getMemDC(), 0, 0);
			FONTMANAGER->drawText(getMemDC(), 275, 170,
				"????????", 25, 100, bible[_selection].name, wcslen(bible[_selection].name), BTEXT);

			
			FONTMANAGER->drawText(getMemDC(), 195, 225, "????????", 22, 100, bible[_selection].script,
				((20 > wcslen(bible[_selection].script)) ? wcslen(bible[_selection].script) : 20), MTEXT);

			if (wcslen(quest[_selection].script) > 20)
			{
				FONTMANAGER->drawText(getMemDC(), 195, 255, "????????", 22, 100, bible[_selection].script + 20,
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
				"????????", 25, 100, collection[_selection].name, wcslen(collection[_selection].name), BTEXT);

			
			FONTMANAGER->drawText(getMemDC(), 195, 225, "????????", 22, 100, collection[_selection].script,
				((20 > wcslen(collection[_selection].script)) ? wcslen(collection[_selection].script) : 20), MTEXT);

			if (wcslen(collection[_selection].script) > 20)
			{
				FONTMANAGER->drawText(getMemDC(), 195, 255, "????????", 22, 100, collection[_selection].script + 20,
					(20 < wcslen(collection[_selection].script)) ?
					wcslen(collection[_selection].script) - 20 : wcslen(collection[_selection].script), MTEXT);
			}
			break;
		}	
		_im->render(_categoryIndex);
	}

	if (_categoryIndex != 6) 	IMAGEMANAGER->findImage("items")->frameRender(getMemDC(), _x, _y, 0, 0);
}


bool Inventory::checkSelect(int invenCategoryIndex, int selectionNum)
{

	for (int i = 0; i < _cateItemMax; i++)
	{
		int _oldState;
		_oldState = (int)_im->getItem()[selectionNum + 1]->getState();

		if (_im->getItem()[selectionNum + 1]->getCateIndex() == selectionNum)
		{
			_im->getItem()[selectionNum + 1]->setSelect(true);
		}
		break;

	}
	if (invenCategoryIndex == (int)_im->getItem()[selectionNum + 1]->getCategory())
	{
		int _oldState;
		_oldState = (int)_im->getItem()[selectionNum + 1]->getState();
		return true;
	}
}