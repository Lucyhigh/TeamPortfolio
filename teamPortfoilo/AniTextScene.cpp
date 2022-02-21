#include "Stdafx.h"
#include "AniTextScene.h"


HRESULT AniTextScene::init(void)
{

	_count     = 0;
	_moveCount = 0;
	_nameIndex = 0;
	_textIndex = 0;
	_alpha = 0;

	_npc = NPC::NONE ;

	return S_OK;
}

void AniTextScene::release(void)
{
}

void AniTextScene::update(void)
{
	_npc = NPC::GREENCORN;

	_count++;
	if (_count % 25 == 0)
	{
		_textIndex++;
		cout << "½ºÅµÀº ¿£ÅÍ" << endl;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		_textIndex++ ;
	}


}

void AniTextScene::render(void)
{

	const int SCRIPT_MAX_LENGTH = 55;
	if (_npc == NPC::GREENCORN &&  _textIndex < 3 )
	{
		FONTMANAGER->drawText(getMemDC(), WINSIZE_X*0.22, WINSIZE_Y*0.84, 
			"µÕ±Ù¸ð²Ã", 30, 100, _text[_textIndex].script,
			SCRIPT_MAX_LENGTH , RGB(255, 255, 255));
	}


}
