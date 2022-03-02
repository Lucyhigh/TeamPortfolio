#include "Stdafx.h"
#include "EndingScene.h"

HRESULT EndingScene::init(void)
{
    _textIndex = 0;
    _textAlpha = 0.0f;
    _timer = 0;
    _alpha = 0;
    _textBufferCnt = 0;
    return S_OK;
}

void EndingScene::release(void)
{
}

void EndingScene::update(void)
{
    _timer += TIMEMANAGER->getElapsedTime();
    if (KEYMANAGER->isOnceKeyDown(VK_SPACE) && _textIndex < 3 && _alpha >= 200)
    {
        _textAlpha = 0;
        _alpha = 0;
        _textIndex++;
    }
    _alpha += 1.0f;
    _textAlpha += 2.0f;
    if (_textAlpha >= 255) _textAlpha = 255;
    cout << _textIndex << " , " << _textAlpha << endl;
}

void EndingScene::render(void)
{
    const int SCRIPT_MAX_LENGTH = 20;
    SetTextAlign(getMemDC(), TA_CENTER);
    FONTMANAGER->drawText(getMemDC(), CENTER_X, WINSIZE_Y*0.84, "둥근모꼴", 30, 100, _text[_textIndex].text,
        SCRIPT_MAX_LENGTH, RGB(136, 127, 77));
    //IMAGEMANAGER->alphaRender("텍스트창", getMemDC(), _textAlpha);
    if (wcslen(_text[_textIndex].text) > SCRIPT_MAX_LENGTH)
    {
        FONTMANAGER->drawText(getMemDC(), CENTER_X, WINSIZE_Y*0.90, "둥근모꼴", 30, 100,
            _text[_textIndex].text + SCRIPT_MAX_LENGTH,
            (SCRIPT_MAX_LENGTH < wcslen(_text[_textIndex].text)) ?
            wcslen(_text[_textIndex].text) - SCRIPT_MAX_LENGTH : SCRIPT_MAX_LENGTH,
            RGB(136, 127, 77));
    }
}
