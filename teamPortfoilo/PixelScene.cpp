#include "Stdafx.h"
#include "PixelScene.h"

HRESULT PixelScene::init(void)
{
    _image = IMAGEMANAGER->findImage("¿ÀÇÁ´×¾À Å×½ºÆ®¹è°æ");
    IMAGEMANAGER->findImage("¿ïÅüºÒÅü")->render(getMemDC());
    _pixel = new PixelCollision;
    _pixel->init();
    return S_OK;
}

void PixelScene::release(void)
{
    SAFE_DELETE(_pixel);
}

void PixelScene::update(void)
{
    _pixel->update();
}

void PixelScene::render(void)
{
    IMAGEMANAGER->findImage("¿ïÅüºÒÅü")->render(getMemDC());
    IMAGEMANAGER->findImage("¿ÀÇÁ´×¾À Å×½ºÆ®¹è°æ")->render(getMemDC());
    _pixel->render();
}
