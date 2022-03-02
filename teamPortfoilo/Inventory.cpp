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


	_im->update();
}

void Inventory::render(void)
{
	_im->getItem()[1]->getCategory();
		//= _vTOption.begin() + 1; // 0�� Ÿ��Ʋ �� 
	for (; _viTOption != _vTOption.end() - 2; _viTOption++) // 2�� ����, �ڷ� 
	{
	switch (_categoryIndex)
	{
	case 1 :
		IMAGEMANAGER->findImage("inven1")->render(getMemDC(), 0, 0);

		// ������ ���� �� �� 
		FONTMANAGER->drawText(getMemDC(), _viTOption->x, _viTOption->y,
			"�ձٸ��", 25, 100, _TitleText[_viTOption->num].text, wcslen(_TitleText[_viTOption->num].text), MTEXT);


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
	}
	// ��ư ��ġ . ����Ʈ���� �����ʿ� 
	IMAGEMANAGER->findImage("enter")->render(getMemDC(), CENTER_X + 120, WINSIZE_Y - 100);
	IMAGEMANAGER->findImage("esc")->render(getMemDC(), CENTER_X + 355, WINSIZE_Y - 100);

	// ����, �ڷ� 
	_viTOption = _vTOption.end() - 2;
	FONTMANAGER->drawText(getMemDC(), (CENTER_X + 120) + IMAGEMANAGER->findImage("enter")->getWidth() + 25, WINSIZE_Y - 98,
		"�ձٸ��", 25, 100, _TitleText[_viTOption->num].text, wcslen(_TitleText[_viTOption->num].text), BTEXT);

	_viTOption = _vTOption.end() - 1;
	FONTMANAGER->drawText(getMemDC(), (CENTER_X + 355) + IMAGEMANAGER->findImage("esc")->getWidth() + 25, WINSIZE_Y - 98,
		"�ձٸ��", 25, 100, _TitleText[_viTOption->num].text, wcslen(_TitleText[_viTOption->num].text), BTEXT);


	// ī�װ� �ε����� �־, �ش� ī�װ� �����۸� �׸� �� �ֵ��� ���� 
	_im->render(_categoryIndex);



	
}
