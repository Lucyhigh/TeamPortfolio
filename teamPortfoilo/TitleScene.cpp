#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
	_onTitle = ANYBUTTON;


	return S_OK;
}

void TitleScene::release(void)
{
}

void TitleScene::update(void)
{
}

void TitleScene::render(void)
{
	if (_onTitle == ANYBUTTON)
	{
		IMAGEMANAGER->findImage("AnyButton")->render(getMemDC());
		RGB(171, 124, 117);
			//아무 버튼이나 누르세요

	}

	
}
