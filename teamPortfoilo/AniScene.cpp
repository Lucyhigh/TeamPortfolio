#include "Stdafx.h"
#include "AniScene.h"


HRESULT AniScene::init(void)
{
	_aniImg = IMAGEMANAGER->findImage("");

	_animationA = new Animation;
//	_animationA->init(_image->getWidth(), _image->getHeight(), 110, 67);

	_animationA->setDefPlayFrame(false, true);
	_animationA->setFPS(12);

	return S_OK;
}

void AniScene::release(void)
{
	_animationA->release();
	SAFE_DELETE(_animationA);
}

void AniScene::update(void)
{
	
	_animationA->AniStart();
	
	_animationA->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void AniScene::render(void)
{
	//_image->aniRender(getMemDC(), CENTER_X - 50, CENTER_Y, _animationA);
}

