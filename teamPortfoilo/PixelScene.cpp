#include "Stdafx.h"
#include "PixelScene.h"

HRESULT PixelScene::init(void)
{
    _image = IMAGEMANAGER->findImage("�����׾� �׽�Ʈ���");
    IMAGEMANAGER->findImage("��������")->render(getMemDC());
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
    IMAGEMANAGER->findImage("��������")->render(getMemDC());
    IMAGEMANAGER->findImage("�����׾� �׽�Ʈ���")->render(getMemDC());
    _pixel->render();
}
