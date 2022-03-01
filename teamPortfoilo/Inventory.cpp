#include "Stdafx.h"
#include "Inventory.h"

HRESULT Inventory::init(void)
{
	_im = new ItemManager;
	_im->init();

	// max 7 
	_categoryIndex = 1;

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
	}
	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		_categoryIndex++;
		if (_categoryIndex >= 7) _categoryIndex = 7;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		// 8개 단위 
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		// 8개 단위 
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		// 1개 단위 
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		// 1개 단위 
	}

	_im->update();
}

void Inventory::render(void)
{
	for(int i = 0; i < _im->getItem().size();i++)
	{
	switch (_categoryIndex)
	{
	case 1 :
		IMAGEMANAGER->findImage("inven1")->render(getMemDC(), 0, 0);

		if(_im->getItem()[i]->getState == ItemState::SELECT)
		{
			// 아이템 설명 할 것 
			// selected Item Name
			FONTMANAGER->drawText2(getMemDC(), 420 ,245,
				"둥근모꼴", 40, 100, _im->getItem()[i]->getName() , _im->getItem()[i]->getName().size(), MTEXT);

			// selected Item Script
			FONTMANAGER->drawText2(getMemDC(), 315, 345,
				"둥근모꼴", 25, 100, _im->getItem()[i]->getScript(), _im->getItem()[i]->getScript().size(), MTEXT);

			// 버튼 위치 . 퀘스트템은 수정필요 
			IMAGEMANAGER->findImage("enter")->render(getMemDC(), CENTER_X + 120, WINSIZE_Y - 100);
			IMAGEMANAGER->findImage("esc")->render(getMemDC(), CENTER_X + 355, WINSIZE_Y - 100);

			if (_im->getItem()[i]->getEquip())
			{
				// 장착했다면 해제
				FONTMANAGER->drawText(getMemDC(), (CENTER_X + 50) + IMAGEMANAGER->findImage("enter")->getWidth() + 25, WINSIZE_Y - 98,
					"둥근모꼴", 25, 100, _InvenTEXT[1].text, wcslen(_InvenTEXT[1].text), BTEXT);
			}
			else 
			{
				// 아니면 장착 
				FONTMANAGER->drawText(getMemDC(), (CENTER_X + 50) + IMAGEMANAGER->findImage("enter")->getWidth() + 25, WINSIZE_Y - 98,
					"둥근모꼴", 25, 100, _InvenTEXT[0].text, wcslen(_InvenTEXT[0].text), BTEXT);
			}

			FONTMANAGER->drawText(getMemDC(), (CENTER_X + 285) + IMAGEMANAGER->findImage("space")->getWidth() + 25, WINSIZE_Y - 98,
				"둥근모꼴", 25, 100, _InvenTEXT[2].text, wcslen(_InvenTEXT[2].text), BTEXT);

		}
		break;
	case 2:
		IMAGEMANAGER->findImage("inven2")->render(getMemDC(), 0, 0);
		break;
	case 3:
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
