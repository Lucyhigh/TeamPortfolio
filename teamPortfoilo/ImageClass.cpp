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
	IMAGEMANAGER->addFrameImage("꼬깔점프", "Resources/Images/Player/p_jump.bmp", 1120, 158, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔슬라이드", "Resources/Images/Player/p_slide.bmp", 1455, 144, 15, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔어택0", "Resources/Images/Player/p_attack.bmp", 1260, 144, 9, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔어택0", "Resources/Images/Player/p_attack0.bmp", 1260, 144, 9, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔어택1", "Resources/Images/Player/p_attack1.bmp", 725, 144, 5, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔어택2", "Resources/Images/Player/p_attack2.bmp", 2600, 170, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔상단어택", "Resources/Images/Player/p_upattack.bmp", 972, 148, 12, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔점프어택", "Resources/Images/Player/p_jumpattack.bmp", 1510, 200, 10, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔점프어택이펙트", "Resources/Images/Player/p_jumpattack_ef.bmp", 604, 200, 4, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔상단어택이펙트", "Resources/Images/Player/p_upattack_ef.bmp", 320, 300, 4, 2, MGT);
	IMAGEMANAGER->addFrameImage("공격이펙트", "Resources/Images/Player/effectTwo.bmp", 792, 164, 6, 2, MGT);
#pragma endregion


#pragma region BossImage
	IMAGEMANAGER->addFrameImage("수호자대기", "Resources/Images/Boss/BossWardenIdle.bmp", 1650*2, 334*2, 10, 2, MGT);
	IMAGEMANAGER->addFrameImage("수호자점프", "Resources/Images/Boss/BassWardenJump.bmp", 5425*2, 414*2, 25, 2, MGT);
	IMAGEMANAGER->addFrameImage("수호자공격", "Resources/Images/Boss/tutoBossAttack.bmp", 8280 * 2, 430 * 2, 24, 2, MGT);
	IMAGEMANAGER->addFrameImage("수호자죽음", "Resources/Images/Boss/tutoBossDead.bmp", 20384 * 2, 494 * 2, 49, 2, MGT);
#pragma endregion


#pragma region FieldMonsterImage

#pragma endregion


#pragma region UI Scene 
	// 타이틀 이미지 
	IMAGEMANAGER->addImage("AnyButton", "Resources/Images/BackGround/UI/anyButtonBg.bmp", 1200, 675);
	// 타이틀 애니메이션 이미지 640*360
	IMAGEMANAGER->addImage("titleBg", "Resources/Images/Object/titleBg.bmp", 9600,360,15,1, MGT);
	IMAGEMANAGER->addImage("titleMain", "Resources/Images/Object/titleMain.bmp", 8960, 360, 14, 1, MGT);
	IMAGEMANAGER->addImage("titleEffect", "Resources/Images/Object/titleEffect.bmp", 28160, 360, 44, 1, MGT);

	IMAGEMANAGER->addFrameImage("메뉴", "Resources/Images/cornObject/menu.bmp", 272, 360, 2, 1, MGT);
	IMAGEMANAGER->addFrameImage("메뉴창", "Resources/Images/cornObject/menuDisplay.bmp", 3600, 675, 3, 1, MGT);

	IMAGEMANAGER->addImage("상점 메아쿨파", "Resources/Images/BackGround/StoreWeaponTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("상점 기도문", "Resources/Images/BackGround/StoreBibleTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("상점 묵주", "Resources/Images/BackGround/StoreRosaryTap.bmp", 1200, 675);

	IMAGEMANAGER->addImage("인벤 메아쿨파", "Resources/Images/BackGround/InventoryWeaponTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("인벤 기도문", "Resources/Images/BackGround/InventoryBibleTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("인벤 묵주", "Resources/Images/BackGround/InventoryRosaryTap.bmp", 1200, 675);


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
