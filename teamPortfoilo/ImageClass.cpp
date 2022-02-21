#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
	// 이미지를 전부 여기에 저장 
	// IMAGEMANAGER->addImage();
	// 키값은 영문으로! (수정예정)

#pragma region PlayerImage
	IMAGEMANAGER->addFrameImage("꼬깔대기", "Resources/Images/Player/p_idle.bmp", 1664, 146, 13, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔이동", "Resources/Images/Player/p_move.bmp", 1106, 140, 14, 2, MGT);
#pragma endregion


#pragma region BossImage

#pragma endregion


#pragma region FieldMonsterImage

#pragma endregion


#pragma region UI Scene 
	IMAGEMANAGER->addImage("AnyButton", "Resources/Images/BackGround/UI/anyButtonBg.bmp", 1200, 675);

	IMAGEMANAGER->addFrameImage("메뉴", "Resources/Images/cornObject/menu.bmp", 272, 360, 2, 1, MGT);
	IMAGEMANAGER->addFrameImage("메뉴창", "Resources/Images/cornObject/menuDisplay.bmp", 3600, 675, 3, 1, MGT);

	IMAGEMANAGER->addImage("상점 메아쿨파", "Resources/Images/BackGround/StoreWeaponTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("상점 기도문", "Resources/Images/BackGround/StoreBibleTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("상점 묵주", "Resources/Images/BackGround/StoreRosaryTap.bmp", 1200, 675);

	IMAGEMANAGER->addImage("인벤 메아쿨파", "Resources/Images/BackGround/InventoryWeaponTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("인벤 기도문", "Resources/Images/BackGround/InventoryBibleTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("인벤 묵주", "Resources/Images/BackGround/InventoryRosaryTap.bmp", 1200, 675);

	// 애니메이션 이미지 
	IMAGEMANAGER->addImage("꼬끼리", "Resources/Images/Object/Elephant.bmp", 660, 268, true, RGB(255, 0, 255));

#pragma endregion



#pragma region Stage Scene
	IMAGEMANAGER->addImage("씬1배경", "Resources/Images/BackGround/bg1.bmp", 1200, 675);
	IMAGEMANAGER->addImage("씬2배경", "Resources/Images/BackGround/bg2.bmp", 1200, 675);
	IMAGEMANAGER->addImage("씬3배경", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

	// 수정 및 자리 잡은 이미지 
	IMAGEMANAGER->addImage("BossStage2_Bg", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

	

#pragma endregion



#pragma region Item
	// 무기 - 메아쿨파의 심장
	IMAGEMANAGER->addImage("오일 심장 On", "Resources/Images/item/weaponOn_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("오일 심장 Off", "Resources/Images/item/weaponOff_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("인센스 심장 On", "Resources/Images/item/weaponOn_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("인센스 심장 Off", "Resources/Images/item/weaponOff_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("녹아내린 심장 On", "Resources/Images/item/weaponOn_03.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("녹아내린 심장 Off", "Resources/Images/item/weaponOff_03.bmp", 60, 60, MGT);

	// 방어구 - 기도문
	IMAGEMANAGER->addImage("01 기도문 On", "Resources/Images/item/bibleOn_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("01 기도문 Off", "Resources/Images/item/bibleOff_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("02 기도문 On", "Resources/Images/item/bibleOn_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("02 기도문 Off", "Resources/Images/item/bibleOff_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("03 기도문 On", "Resources/Images/item/bibleOn_03.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("03 기도문 Off", "Resources/Images/item/bibleOff_03.bmp", 60, 60, MGT);

	// 악세서리 - 묵주
	IMAGEMANAGER->addImage("01 묵주 On", "Resources/Images/item/rosaryOn_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("01 묵주 Off", "Resources/Images/item/rosaryOff_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("02 묵주 On", "Resources/Images/item/rosaryOn_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("02 묵주 Off", "Resources/Images/item/rosaryOff_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("03 묵주 On", "Resources/Images/item/rosaryOn_03.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("03 묵주 Off", "Resources/Images/item/rosaryOff_04.bmp", 60, 60, MGT);




#pragma endregion

	return S_OK;
}

ImageClass::ImageClass()
{
}

ImageClass::~ImageClass()
{
}
