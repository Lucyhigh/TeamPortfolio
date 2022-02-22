#include "Stdafx.h"
#include "TitleScene.h"



HRESULT TitleScene::init(void)
{
	_img = new ImageClass;
	_img->init();

	_ani = new AniSceneTitle;
	_ani->init();

	_titleName = ANYBUTTON;
	_pushButton = false;

	int w = IMAGEMANAGER->findImage("AnyButtonLogo")->getWidth();
	int h = IMAGEMANAGER->findImage("AnyButtonLogo")->getHeight();
	_logoRc = RectMakeCenter(CENTER_X,CENTER_Y,w,h);

	_alpha = 0;
	_menuIndex = 0;

	// Text
	//script = L"아무 버튼이나 누르세요";

	// SAVE ------------



	return S_OK;
}

void TitleScene::release(void)
{
	SAFE_DELETE(_img);
	SAFE_DELETE(_ani);
}

void TitleScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) _pushButton = true;

	if (_pushButton)
	{
		_alpha++;
		if (_alpha >= 255)
		{
			_alpha = 255;
			_titleName = TITLE;
		}
	}

	if (_titleName == TITLE)
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
		cout << _menuIndex << endl;
	}
	// Title-Menu  
	if (KEYMANAGER->isOnceKeyDown('Q') )//&& _titleName == TITLE && _menuIndex == 0)
	{
		SCENEMANAGER->changeScene("Start");
		//_titleName = SAVE;
	}
//	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _titleName == TITLE && _menuIndex == 1)
	{
	//	_titleName = OPTION;
	}
	//if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _titleName == TITLE && _menuIndex == 2)
	{
		// PostQuitMessage(0);
	}

//	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _titleName == SAVE || _titleName == OPTION)
	{
//		_titleName = TITLE;
	}
	

	if (_titleName == SAVE)
	{
		
	}

	if (_titleName == OPTION)
	{
		
	}

}

void TitleScene::render(void)
{
	if (_titleName == ANYBUTTON)
	{
		IMAGEMANAGER->findImage("AnyButtonBg")->render(getMemDC());
		IMAGEMANAGER->findImage("AnyButtonLogo")->alphaRender(getMemDC(), _logoRc.left, _logoRc.top, _alpha);

		//FONTMANAGER->drawText(getMemDC(), CENTER_X-150, _logoRc.bottom+10, "둥근모꼴", 25, 100, script,
		//	wcslen(script), RGB(171, 124, 117));
	}

	if (_titleName == TITLE)
	{
		_ani->render();
		IMAGEMANAGER->findImage("titleMenu")->frameRender(getMemDC(),WINSIZE_X - 200, CENTER_Y+150 );
		_ani->render(WINSIZE_X - 150, CENTER_Y + 100 + (_menuIndex*40));
	}

	if (_titleName == SAVE)
	{
		IMAGEMANAGER->findImage("세이브")->render(getMemDC());

	}


	if (_titleName == OPTION)
	{
		IMAGEMANAGER->findImage("메뉴")->render(getMemDC());

	}
	
}
