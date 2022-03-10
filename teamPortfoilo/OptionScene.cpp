#include "Stdafx.h"
#include "OptionScene.h"

HRESULT OptionScene::init(void)
{
	_isTitleMenu = true;

	for (int i = 0; i < TITLEMENU; i++)
	{
		tagOptionSlot optionInfo;
		optionInfo.num = i;
		optionInfo.x = 340;
		optionInfo.y = 140 + (i * 57);
		optionInfo.onImg = new Image;
		optionInfo.onImg->init("Resources/Images/UI/optionSelect.bmp", optionInfo.x, optionInfo.y, 16, 31, MGT);
		optionInfo.select = false;
		_vTOption.push_back(optionInfo);
	}
	_TOptinIndex = 1;

	for (int i = 0; i < INMENU; i++)
	{
		tagOptionSlot optionInfo;
		optionInfo.num = i;
		optionInfo.x = 340;
		optionInfo.y = 140 + (i * 57);
		optionInfo.onImg = new Image;
		optionInfo.onImg->init("Resources/Images/UI/optionSelect.bmp", optionInfo.x, optionInfo.y, 16, 31, MGT);
		optionInfo.select = false;
		_vIOption.push_back(optionInfo);
	}
	_IOptinIndex = 1;

	return S_OK;
}


HRESULT OptionScene::init(bool isTitleMenu)
{
	
	_isTitleMenu = false;

	for (int i = 0; i < TITLEMENU; i++)
	{
		tagOptionSlot optionInfo;
		optionInfo.num = i;
		optionInfo.x = 340;
		optionInfo.y = 140 + (i * 57);
		optionInfo.onImg = new Image;
		optionInfo.onImg->init("Resources/Images/UI/optionSelect.bmp", optionInfo.x, optionInfo.y, 16, 31, MGT);
		optionInfo.select = false;
		_vTOption.push_back(optionInfo);
	}
	_TOptinIndex = 1;

	for (int i = 0; i < INMENU; i++)
	{
		tagOptionSlot optionInfo;
		optionInfo.num = i;
		optionInfo.x = 340;
		optionInfo.y = 140 + (i * 57);
		optionInfo.onImg = new Image;
		optionInfo.onImg->init("Resources/Images/UI/optionSelect.bmp", optionInfo.x, optionInfo.y, 16, 31, MGT);
		optionInfo.select = false;
		_vIOption.push_back(optionInfo);
	}
	_IOptinIndex = 1;

	return S_OK;
}

void OptionScene::release(void)
{
	_viTOption = _vTOption.begin();
	for (; _viTOption != _vTOption.end(); _viTOption++)
	{
		SAFE_DELETE(_viTOption->onImg);
	}
	_vTOption.clear();

	_viIOption = _vIOption.begin();
	for (; _viIOption != _vIOption.end(); _viIOption++)
	{
		SAFE_DELETE(_viIOption->onImg);
	}
	_vIOption.clear();
}

void OptionScene::update(void)
{

	if( _isTitleMenu)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_TOptinIndex--;
			if (_TOptinIndex < 1) _TOptinIndex = TITLEMENU - 3;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_TOptinIndex++;
			if (_TOptinIndex > TITLEMENU - 3) _TOptinIndex = 1;
		}

		selectTOption(_TOptinIndex);
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_IOptinIndex--;
			if (_IOptinIndex < 1) _IOptinIndex = TITLEMENU - 3;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_IOptinIndex++;
			if (_IOptinIndex > TITLEMENU - 3) _IOptinIndex = 1;
		}

		selectIOption(_IOptinIndex);
	}
}

void OptionScene::render(void)
{
	IMAGEMANAGER->findImage("menuOptionBg")->render(getMemDC());

	if (_isTitleMenu)	showTOption();
	else showIOption();
}

void OptionScene::selectTOption( int optionIndex)
{
	_viTOption = _vTOption.begin();
	for (; _viTOption != _vTOption.end(); _viTOption++)
	{
		if (_viTOption->num == optionIndex) _viTOption->select = true;
		else _viTOption->select = false;
	}
}

void OptionScene::showTOption(void)
{
	IMAGEMANAGER->findImage("enter")->render(getMemDC(), CENTER_X + 120, WINSIZE_Y - 100);
	IMAGEMANAGER->findImage("esc")->render(getMemDC(), CENTER_X + 355, WINSIZE_Y - 100);

	_viTOption = _vTOption.begin();
	FONTMANAGER->drawText(getMemDC(), _viTOption->x - 10, _viTOption->y - 5,
		"µÕ±Ù¸ð²Ã", 27, 100, _TitleText[_viTOption->num].text, wcslen(_TitleText[_viTOption->num].text), TTEXT);


	_viTOption = _vTOption.begin() + 1; 
	for (; _viTOption != _vTOption.end() - 2; _viTOption++)
	{
		SetTextAlign(getMemDC(), TA_LEFT);
		if (_viTOption->select) 
		{
			_viTOption->onImg->render(getMemDC(), _viTOption->x - 25, _viTOption->y - 2);

			FONTMANAGER->drawText(getMemDC(), _viTOption->x, _viTOption->y,
				"µÕ±Ù¸ð²Ã", 25, 100, _TitleText[_viTOption->num].text, wcslen(_TitleText[_viTOption->num].text), OTEXT);
		}
		if (!_viTOption->select)
		{
			FONTMANAGER->drawText(getMemDC(), _viTOption->x, _viTOption->y,
				"µÕ±Ù¸ð²Ã", 25, 100, _TitleText[_viTOption->num].text, wcslen(_TitleText[_viTOption->num].text), MTEXT);
		}
	}

	_viTOption = _vTOption.end() - 2;
	FONTMANAGER->drawText(getMemDC(), (CENTER_X + 120) + IMAGEMANAGER->findImage("enter")->getWidth() + 25, WINSIZE_Y - 98,
		"µÕ±Ù¸ð²Ã", 25, 100, _TitleText[_viTOption->num].text, wcslen(_TitleText[_viTOption->num].text), BTEXT);

	_viTOption = _vTOption.end() - 1;
	FONTMANAGER->drawText(getMemDC(), (CENTER_X + 355) + IMAGEMANAGER->findImage("esc")->getWidth() + 25, WINSIZE_Y - 98,
		"µÕ±Ù¸ð²Ã", 25, 100, _TitleText[_viTOption->num].text, wcslen(_TitleText[_viTOption->num].text), BTEXT);
}

void OptionScene::selectIOption(int optionIndex)
{
	_viIOption = _vIOption.begin();
	for (; _viIOption != _vIOption.end(); _viIOption++)
	{
		if (_viIOption->num == optionIndex) _viIOption->select = true;
		else _viTOption->select = false;
	}
}


void OptionScene::showIOption(void)
{
	IMAGEMANAGER->findImage("enter")->render(getMemDC(), CENTER_X + 120, WINSIZE_Y - 100);
	IMAGEMANAGER->findImage("esc")->render(getMemDC(), CENTER_X + 355, WINSIZE_Y - 100);

	_viIOption = _vIOption.begin();
	FONTMANAGER->drawText(getMemDC(), _viIOption->x - 10, _viIOption->y - 5,
		"µÕ±Ù¸ð²Ã", 27, 100, _InGameText[_viIOption->num].text, wcslen(_InGameText[_viIOption->num].text), TTEXT);


	_viIOption = _vIOption.begin() + 1; 
	for (; _viIOption != _vIOption.end() - 2; _viIOption++) 
	{
		SetTextAlign(getMemDC(), TA_LEFT);
		if (_viIOption->select)
		{
			_viIOption->onImg->render(getMemDC(), _viIOption->x - 25, _viIOption->y - 2);

			FONTMANAGER->drawText(getMemDC(), _viIOption->x, _viIOption->y,
				"µÕ±Ù¸ð²Ã", 25, 100, _InGameText[_viIOption->num].text, wcslen(_InGameText[_viIOption->num].text), OTEXT);
		}
		if (!_viIOption->select)
		{
			FONTMANAGER->drawText(getMemDC(), _viIOption->x, _viIOption->y,
				"µÕ±Ù¸ð²Ã", 25, 100, _InGameText[_viIOption->num].text, wcslen(_InGameText[_viIOption->num].text), MTEXT);
		}
	}

	_viIOption = _vIOption.end() - 2;
	FONTMANAGER->drawText(getMemDC(), (CENTER_X + 120) + IMAGEMANAGER->findImage("enter")->getWidth() + 25, WINSIZE_Y - 98,
		"µÕ±Ù¸ð²Ã", 25, 100, _InGameText[_viIOption->num].text, wcslen(_InGameText[_viIOption->num].text), BTEXT);

	_viIOption = _vIOption.end() - 1;
	FONTMANAGER->drawText(getMemDC(), (CENTER_X + 355) + IMAGEMANAGER->findImage("esc")->getWidth() + 25, WINSIZE_Y - 98,
		"µÕ±Ù¸ð²Ã", 25, 100, _InGameText[_viIOption->num].text, wcslen(_InGameText[_viIOption->num].text), BTEXT);
}