#include "Stdafx.h"
#include "EndingScene.h"

HRESULT EndingScene::init(void)
{
	_textIndex = 0;
	_textAlpha = 0;
	_alpha = 255;
	_bgAlpha = 0;
	_timer = 0.0f;
	return S_OK;
}

void EndingScene::release(void)
{
}

void EndingScene::update(void)
{
	TEMPSOUNDMANAGER->stopMp3WithKey("Peldanos");
	TEMPSOUNDMANAGER->playSoundWithKey("Geli");

	_timer += 0.1f;
	if (_timer > 30)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _textIndex < 3 && _bgAlpha >= 200)
		{
			_textAlpha = 0;
			_bgAlpha = 0;
			_alpha = 255;
			_textIndex++;
		}

		_alpha -= 1;
		_bgAlpha += 1;
		_textAlpha += 2;
		if (_bgAlpha >= 255) _bgAlpha = 255;
		if (_alpha <= 0) _alpha = 0;
		if (_textAlpha >= 100) _textAlpha = 100;
	}
	if (_textIndex >= 3)
	{
		if (_timer > 500)
		{
			SCENEMANAGER->changeScene("Title");
			TEMPSOUNDMANAGER->stopMp3WithKey("Geli");
		}
	}
}

void EndingScene::render(void)
{
	switch (_textIndex)
	{
	case 0:
		IMAGEMANAGER->alphaRender("EndingScene2", getMemDC(), 0, 0, _bgAlpha);
		break;
	case 1:
		IMAGEMANAGER->alphaRender("EndingScene3", getMemDC(), 0, 0, _bgAlpha);
		break;
	case 2:
		IMAGEMANAGER->alphaRender("EndingScene4", getMemDC(), 0, 0, _bgAlpha);
		break;
	case 3:
		IMAGEMANAGER->alphaRender("EndingScene5", getMemDC(), 0, 0, _bgAlpha);
		break;
	}

	IMAGEMANAGER->alphaRender("changeScene", getMemDC(), 0, WINSIZE_Y - 150, _textAlpha);

	const int SCRIPT_MAX_LENGTH = 20;
	SetTextAlign(getMemDC(), TA_CENTER);
	FONTMANAGER->drawText(getMemDC(), CENTER_X, WINSIZE_Y*0.84, "µÕ±Ù¸ð²Ã", 30, 100, _text[_textIndex].text,
		SCRIPT_MAX_LENGTH, RGB(136, 127, 77));
	if (wcslen(_text[_textIndex].text) > SCRIPT_MAX_LENGTH)
	{
		FONTMANAGER->drawText(getMemDC(), CENTER_X, WINSIZE_Y*0.90, "µÕ±Ù¸ð²Ã", 30, 100,
			_text[_textIndex].text + SCRIPT_MAX_LENGTH,
			(SCRIPT_MAX_LENGTH < wcslen(_text[_textIndex].text)) ?
			wcslen(_text[_textIndex].text) - SCRIPT_MAX_LENGTH : SCRIPT_MAX_LENGTH,
			RGB(136, 127, 77));
	}
	if (_textIndex < 3)
	{
		IMAGEMANAGER->alphaRender("enter", getMemDC(), WINSIZE_X*0.90, WINSIZE_Y*0.90, _textAlpha + 70);
	}
	IMAGEMANAGER->alphaRender("changeScene", getMemDC(), 0, 0, _alpha);
}
