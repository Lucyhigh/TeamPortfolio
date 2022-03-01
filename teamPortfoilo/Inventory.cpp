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
	switch (_categoryIndex)
	{
	case 1 :
		IMAGEMANAGER->findImage("inven1")->render(getMemDC(), 0, 0);
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
	_im->render();



	
}
