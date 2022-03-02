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
    _timer += 0.1f;
    if (_timer > 30)
    {
        if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _textIndex < 3 && _bgAlpha >= 200)
        {
            _textAlpha = 0;
            _bgAlpha = 0;
            _alpha = 255;
            _textIndex++;
            if (_textIndex >= 3)
            {
                _timer = 0;
            }
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
        if (_timer > 180)
        {
            SCENEMANAGER->changeScene("Title");
        }
    }
}

void EndingScene::render(void)
{
    switch (_textIndex)
    {
    case 0:
        IMAGEMANAGER->alphaRender("엔딩이미지2", getMemDC(), 0, 0, _bgAlpha);
        break;
    case 1:
        IMAGEMANAGER->alphaRender("엔딩이미지3", getMemDC(), 0, 0, _bgAlpha);
        break;
    case 2:
        IMAGEMANAGER->alphaRender("엔딩이미지4", getMemDC(), 0, 0, _bgAlpha);
        break;
    case 3:
        IMAGEMANAGER->alphaRender("엔딩이미지5", getMemDC(), 0, 0, _bgAlpha);
        break;
    }

    IMAGEMANAGER->alphaRender("컷전환", getMemDC(), 0, WINSIZE_Y - 150, _textAlpha);

    const int SCRIPT_MAX_LENGTH = 20;
    SetTextAlign(getMemDC(), TA_CENTER);
    FONTMANAGER->drawText(getMemDC(), CENTER_X, WINSIZE_Y*0.84, "둥근모꼴", 30, 100, _text[_textIndex].text,
        SCRIPT_MAX_LENGTH, RGB(136, 127, 77));
    if (wcslen(_text[_textIndex].text) > SCRIPT_MAX_LENGTH)
    {
        FONTMANAGER->drawText(getMemDC(), CENTER_X, WINSIZE_Y*0.90, "둥근모꼴", 30, 100,
            _text[_textIndex].text + SCRIPT_MAX_LENGTH,
            (SCRIPT_MAX_LENGTH < wcslen(_text[_textIndex].text)) ?
            wcslen(_text[_textIndex].text) - SCRIPT_MAX_LENGTH : SCRIPT_MAX_LENGTH,
            RGB(136, 127, 77));
    }

    IMAGEMANAGER->alphaRender("컷전환", getMemDC(), 0, 0, _alpha);
}
