#include "Stdafx.h"
#include "TitleScene.h"

<<<<<<< HEAD


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
	//script = L"�ƹ� ��ư�̳� ��������";

	// SAVE ------------

=======
HRESULT TitleScene::init(void)
{
	_onTitle = ANYBUTTON;
>>>>>>> origin/SongYeeun-camera


	return S_OK;
}

void TitleScene::release(void)
{
<<<<<<< HEAD
	SAFE_DELETE(_img);
	SAFE_DELETE(_ani);
=======
>>>>>>> origin/SongYeeun-camera
}

void TitleScene::update(void)
{
<<<<<<< HEAD
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
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) )//&& _titleName == TITLE && _menuIndex == 0)
	{
		SCENEMANAGER->changeScene("Start");
		//_titleName = SAVE;
	}
	}
	// Title-Menu  
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

=======
>>>>>>> origin/SongYeeun-camera
}

void TitleScene::render(void)
{
<<<<<<< HEAD
	if (_titleName == ANYBUTTON)
	{
		IMAGEMANAGER->findImage("AnyButtonBg")->render(getMemDC());
		IMAGEMANAGER->findImage("AnyButtonLogo")->alphaRender(getMemDC(), _logoRc.left, _logoRc.top, _alpha);

		//FONTMANAGER->drawText(getMemDC(), CENTER_X-150, _logoRc.bottom+10, "�ձٸ��", 25, 100, script,
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
		IMAGEMANAGER->findImage("���̺�")->render(getMemDC());

	}


	if (_titleName == OPTION)
	{
		IMAGEMANAGER->findImage("�޴�")->render(getMemDC());

	}
=======
	if (_onTitle == ANYBUTTON)
	{
		IMAGEMANAGER->findImage("AnyButton")->render(getMemDC());
		RGB(171, 124, 117);
			//�ƹ� ��ư�̳� ��������

	}

>>>>>>> origin/SongYeeun-camera
	
}
