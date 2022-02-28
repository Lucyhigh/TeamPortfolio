#include "Stdafx.h"
#include "PixelCollision.h"

HRESULT PixelCollision::init(void)
{

	//_image = IMAGEMANAGER->addImage("ÇÈ¼¿ ÅÊÅ©", "Resources/Images/Object/Tank.bmp", 70, 60, true, RGB(255, 0, 255));

   // floor0 = new RECT{ 0, 600, _bgImage->getWidth(),670 };
   // _floor.push_back(floor0);
	
    _x = CENTER_X + 250;
    _y = CENTER_Y + 100;
    GAMEMANAGER->getPlayer()->ObjectInit({ _x, _y}, _floor);
	//_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
    _probeY = _y + GAMEMANAGER->getPlayer()->getHeight() / 2;

    return S_OK;
}

void PixelCollision::release(void)
{
    SAFE_DELETE(_image);
}

void PixelCollision::update(void)
{
    if (KEYMANAGER->isStayKeyDown(VK_RIGHT))_x += 1.0f;
    if (KEYMANAGER->isStayKeyDown(VK_LEFT))_x -= 1.0f;

    //YÃà Å½Áö
    _probeY = _y + _image->getHeight() / 2;

    for (int i = _probeY - 30; i < _probeY + 30; i++)
    {
        COLORREF color = GetPixel(IMAGEMANAGER->findImage("¿ÀÇÁ´×¾À ÇÈ¼¿")->getMemDC(), _x, i);

        int r = GetRValue(color);
        int g = GetGValue(color);
        int b = GetBValue(color);

        if (!(r == 255 && g == 0 && b == 255))
        {
            _y = i - _image->getHeight() / 2;
            break;
        }
    }
	GAMEMANAGER->getPlayer()->ObjectUpdate();
   // GAMEMANAGER->getPlayer()->setCameraRect(_camera->getScreenRect());
	//_rc = RectMakeCenter(_x, _y, _image->getWidth(), _image->getHeight());
	//_rc = RectMakeCenter(_x, _y, GAMEMANAGER->getPlayer()->getWidth(), GAMEMANAGER->getPlayer()->getHeight());//
}

void PixelCollision::render(void)
{
    //_image->render(getMemDC(), _rc.left, _rc.top);
	GAMEMANAGER->getPlayer()->ObjectRender();
    if (KEYMANAGER->isToggleKey(VK_F1))
    {
        Rectangle(getMemDC(), _x, _probeY, _x + 10, _probeY + 10);
    }
}