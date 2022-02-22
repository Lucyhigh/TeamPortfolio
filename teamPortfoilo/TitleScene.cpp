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
	_logoRc = RectMakeCenter(CENTER_X,WINSIZE_Y*0.4,w,h);

	_alpha = 0;
	_menuIndex = 0;

	// Text
	//script = L"아무 버튼이나 누르세요";


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

	IMAGEMANAGER->findImage("titleMenu")->setFrameY(0);
	IMAGEMANAGER->findImage("titleMenu")->setFrameX(0);
	if (_titleName == TITLE)
	{
		_ani->update();

	
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuIndex--;
			if (_menuIndex < 0) _menuIndex = 2;
			IMAGEMANAGER->findImage("titleMenu")->setFrameX(_menuIndex);

		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuIndex++;
			if (_menuIndex > 2) _menuIndex = 0;
			IMAGEMANAGER->findImage("titleMenu")->setFrameX(_menuIndex);
		}


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
		IMAGEMANAGER->findImage("titleMenu")->frameRender(getMemDC(),WINSIZE_X - 150, CENTER_Y+50 );
		_ani->render();

	}

	
}
