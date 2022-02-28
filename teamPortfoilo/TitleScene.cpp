#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
	_anyButton = true;
	_title = false;
	
	// ANYBUTTON ------------
	_pushButton = false;

	int w = IMAGEMANAGER->findImage("AnyButtonLogo")->getWidth();
	int h = IMAGEMANAGER->findImage("AnyButtonLogo")->getHeight();
	_logoRc = RectMakeCenter(CENTER_X,CENTER_Y,w,h);

	_alpha = 255;

	// TITLE ------------
	_ani = new AniSceneTitle;
	_ani->init();
	_menuIndex = 0;


	return S_OK;
}

void TitleScene::release(void)
{
	SAFE_DELETE(_ani);
}

void TitleScene::update(void)
{
	if (!_pushButton)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_pushButton = true;
		}
	}
	else
	{
		_alpha--;
		if (_alpha <= 0)
		{
			_alpha = 0;
			_title = true;
		}
	}


	if (_title)
	{
		IMAGEMANAGER->findImage("titleMenu")->setFrameY(0);
		IMAGEMANAGER->findImage("titleMenu")->setFrameX(0);

		_ani->update();

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuIndex--;
			if (_menuIndex < 0) _menuIndex = 2;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuIndex++;
			if (_menuIndex > 2) _menuIndex = 0;
		}
		IMAGEMANAGER->findImage("titleMenu")->setFrameX(_menuIndex);
	}

	// Title-Menu select
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (_menuIndex == 0)SCENEMANAGER->changeScene("Save");
		if (_menuIndex == 1)SCENEMANAGER->changeScene("Option");

	}
		if (_menuIndex == 2)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) PostQuitMessage(0);
		}

}

void TitleScene::render(void)
{
	if (_anyButton)
	{
		IMAGEMANAGER->findImage("AnyButtonBg")->render(getMemDC());
		IMAGEMANAGER->findImage("AnyButtonLogo")->alphaRender(getMemDC(), _logoRc.left, _logoRc.top, _alpha);

	}


	if (_title)
	{
		_ani->render();
		IMAGEMANAGER->findImage("titleMenu")->frameRender(getMemDC(), WINSIZE_X - 200, CENTER_Y + 150);
		_ani->render(WINSIZE_X - 150, CENTER_Y + 100 + (_menuIndex * 40));
	}


	
}