#include "stdafx.h"
#include "StartScene.h"


HRESULT StartScene::init(void)
{
	IMAGEMANAGER->addImage("����ȭ��", "Resources/Images/BackGround/bgAll.bmp", 1280, 800);
	//IMAGEMANAGER->addImage("�ؽ�Ʈ ����", "Resources/Images/Object/StartText.bmp", 1000, 100, true, RGB(255, 0, 255));
	_alpha = _bgAlpha = 0;
	_isAlphaIncrese = false;
	return S_OK;
}

void StartScene::release(void)
{
}

void StartScene::update(void)
{
	_bgAlpha += 0.5f;
	if (_bgAlpha >= 255) _bgAlpha = 255;

	if (_alpha == 0 || _alpha == 255) _isAlphaIncrese = !_isAlphaIncrese;		//�� ������
	if (_isAlphaIncrese) _alpha += 1.0f; else _alpha -= 1.5;					//�� ������
}

void StartScene::render(void)
{
	IMAGEMANAGER->alphaRender("����ȭ��", getMemDC(), 0, 0, _bgAlpha);

	if (_bgAlpha >= 160)
	{
		//IMAGEMANAGER->alphaRender("�ؽ�Ʈ ����", getMemDC(), 130, WINSIZE_Y / 2, 255);
	}
}
