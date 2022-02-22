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
	// 타이틀 이미지 
	IMAGEMANAGER->addImage("AnyButtonBg", "Resources/Images/BackGround/UI/anyButtonBg.bmp", 1200, 675, MGT);
	IMAGEMANAGER->addImage("AnyButtonLogo", "Resources/Images/BackGround/UI/anyButtonLogo2.bmp", 720,308, MGT);
	// 타이틀 애니메이션 이미지 640*360 (*1.875)-> 1200 * 640
	IMAGEMANAGER->addFrameImage("titleBg", "Resources/Images/BackGround/UI/titleBg.bmp", 18000,675,15,1, MGT);
	IMAGEMANAGER->addFrameImage("titleMain", "Resources/Images/BackGround/UI/titleMain.bmp", 16800, 675, 14, 1, MGT);
	IMAGEMANAGER->addFrameImage("titleEffect", "Resources/Images/BackGround/UI/titleEffect.bmp", 52800, 675, 44, 1, MGT);


	// UI Image
	IMAGEMANAGER->addFrameImage("메뉴창", "Resources/Images/BackGround/UI/menuDisplay.bmp", 3600, 675, 3, 1, MGT);

	IMAGEMANAGER->addImage("인벤 메아쿨파", "Resources/Images/BackGround/UI/InventoryWeaponTap.bmp", 1200, 675, MGT);
	IMAGEMANAGER->addImage("인벤 기도문", "Resources/Images/BackGround/UI/InventoryBibleTap.bmp", 1200, 675, MGT);
	IMAGEMANAGER->addImage("인벤 묵주", "Resources/Images/BackGround/UI/InventoryRosaryTap.bmp", 1200, 675, MGT);

	// AniScene Text BG
	IMAGEMANAGER->addImage("GreenCorn", "Resources/Images/BackGround/Animation/shot1_0.bmp", 553,675, MGT); //640*781

#pragma endregion



#pragma region Stage Scene
	IMAGEMANAGER->addImage("씬1배경", "Resources/Images/BackGround/bg1.bmp", 1200, 675);
	IMAGEMANAGER->addImage("씬2배경", "Resources/Images/BackGround/bg2.bmp", 1200, 675);
	IMAGEMANAGER->addImage("씬3배경", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

	// 수정 및 자리 잡은 이미지 
	//IMAGEMANAGER->addImage("BossStage2_Bg", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

	

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
