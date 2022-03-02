#include "Stdafx.h"
#include "AniScene.h"

#pragma region TitleScene Animation
HRESULT AniSceneTitle::init(void)
{
	_aITitleBg = IMAGEMANAGER->findImage("titleBg");
	_aITitleMain = IMAGEMANAGER->findImage("titleMain");
	_aITitleEff = IMAGEMANAGER->findImage("titleEffect");
	_aITitleSelecte = IMAGEMANAGER->findImage("titleSelecte");

	_aMTitleBg = new Animation;
	_aMTitleBg->init(_aITitleBg->getWidth(), _aITitleBg->getHeight(), 1200,675);
	_aMTitleMain = new Animation;
	_aMTitleMain->init(_aITitleMain->getWidth(), _aITitleMain->getHeight(), 1200, 675);
	_aMTitleEff = new Animation;
	_aMTitleEff->init(_aITitleEff->getWidth(), _aITitleEff->getHeight(), 1200, 675);
	_aMTitleSelecte = new Animation;
	_aMTitleSelecte->init(_aITitleSelecte->getWidth(), _aITitleSelecte->getHeight(), 140,140);

	_aMTitleBg->setDefPlayFrame(false, true);
	_aMTitleBg->setFPS(5);
	_aMTitleMain->setDefPlayFrame(false, true);
	_aMTitleMain->setFPS(1);
	_aMTitleEff->setDefPlayFrame(false, true);
	_aMTitleEff->setFPS(2);
	_aMTitleSelecte->setDefPlayFrame(true, true);
	_aMTitleSelecte->setFPS(2);


	_aMTitleBg->AniStart();
	_aMTitleMain->AniStart();
	_aMTitleEff->AniStart();
	_aMTitleSelecte->AniStart();

	_isAniStart = false;
	return S_OK;
}

void AniSceneTitle::release(void)
{
	_aMTitleBg->release();
	SAFE_DELETE(_aMTitleBg);
	_aMTitleMain->release();
	SAFE_DELETE(_aMTitleMain);
	_aMTitleEff->release();
	SAFE_DELETE(_aMTitleEff);
	_aMTitleSelecte->release();
	SAFE_DELETE(_aMTitleSelecte);
}

void AniSceneTitle::update(void)
{
	_aMTitleBg->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_aMTitleMain->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_aMTitleEff->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_aMTitleSelecte->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void AniSceneTitle::render(void)
{
	_aITitleBg->aniRender(getMemDC(), 0, 0, _aMTitleBg);
	_aITitleMain->aniRender(getMemDC(), 0, 0, _aMTitleMain);
	_aITitleEff->aniRender(getMemDC(), 0, 0, _aMTitleEff);
}

void AniSceneTitle::render(int x, int y)
{
	_aITitleSelecte->aniRender(getMemDC(), x, y, _aMTitleSelecte);
}
#pragma endregion

#pragma region Item Select Animation
HRESULT AniSceneItem::init(void)
{
	_aIItemSelect = IMAGEMANAGER->findImage("itemsCursor");

	_aMItemSelect = new Animation;
	_aMItemSelect->init(_aIItemSelect->getWidth(), _aIItemSelect->getHeight(), 57,57);

	_aMItemSelect->setDefPlayFrame(false, true);
	_aMItemSelect->setFPS(3);

	_aMItemSelect->AniStart();

	return S_OK;
}

void AniSceneItem::release(void)
{
	_aMItemSelect->release();
	SAFE_DELETE(_aMItemSelect);
}

void AniSceneItem::update(void)
{
	_aMItemSelect->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

}

void AniSceneItem::render(int x, int y)
{
	_aIItemSelect->aniRender(getMemDC(), x, y, _aMItemSelect);

}
#pragma endregion

#pragma region AniScene
HRESULT AniScene::init(void)
{
	_aITitleBg = IMAGEMANAGER->findImage("titleBg");

	_aMTitleBg = new Animation;
	_aMTitleBg->init(_aITitleBg->getWidth(), _aITitleBg->getHeight(), 640, 360);

	_aMTitleBg->setDefPlayFrame(false, true);
	_aMTitleBg->setFPS(12);

	return S_OK;
}

void AniScene::release(void)
{
	_aMTitleBg->release();
	SAFE_DELETE(_aMTitleBg);
}

void AniScene::update(void)
{
	_aMTitleBg->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void AniScene::render(void)
{
	_aITitleBg->aniRender(getMemDC(), 0, 0, _aMTitleBg);
}

#pragma endregion


