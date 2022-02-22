#include "Stdafx.h"
#include "AniScene.h"

#pragma region TitleScene Animation
HRESULT AniSceneTitle::init(void)
{
	_aITitleBg = IMAGEMANAGER->findImage("titleBg");
	_aITitleMain = IMAGEMANAGER->findImage("titleMain");
	_aITitleEff = IMAGEMANAGER->findImage("titleEffect");

	_aMTitleBg = new Animation;
	_aMTitleBg->init(_aITitleBg->getWidth(), _aITitleBg->getHeight(), 1200,675);
	_aMTitleMain = new Animation;
	_aMTitleMain->init(_aITitleMain->getWidth(), _aITitleMain->getHeight(), 1200, 675);
	_aMTitleEff = new Animation;
	_aMTitleEff->init(_aITitleEff->getWidth(), _aITitleEff->getHeight(), 1200, 675);

	_aMTitleBg->setDefPlayFrame(false, true);
	_aMTitleMain->setDefPlayFrame(false, true);
	_aMTitleEff->setDefPlayFrame(false, true);
	_aMTitleBg->setFPS(5);
	_aMTitleMain->setFPS(3);
	_aMTitleEff->setFPS(5);

	_aMTitleBg->AniStart();
	_aMTitleMain->AniStart();
	_aMTitleEff->AniStart();

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
}

void AniSceneTitle::update(void)
{
		

	_aMTitleBg->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_aMTitleMain->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
	_aMTitleEff->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
}

void AniSceneTitle::render(void)
{
	_aITitleBg->aniRender(getMemDC(), 0,0, _aMTitleBg);
	_aITitleMain->aniRender(getMemDC(),0,0, _aMTitleMain);
	_aITitleEff->aniRender(getMemDC(), 0,0, _aMTitleEff);

}
#pragma endregion


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
