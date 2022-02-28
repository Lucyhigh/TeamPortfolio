#include "Stdafx.h"
#include "ImageClass.h"

#define WINSIZE 1200,675

HRESULT ImageClass::init(void)
{
	// 이미지를 전부 여기에 저장 
	// IMAGEMANAGER->addImage();
	// 키값은 영문으로! (수정예정)
	// 플레이어 / 몬스터 / 필드 / UI / Item / 애니메이션 순

	// 테스트용 이미지 
	IMAGEMANAGER->addImage("세이브", "Resources/test/save.bmp", 1200, 675);
	IMAGEMANAGER->addImage("메뉴", "Resources/test/menu.bmp", 1200, 675);

	// ================================================================================================================

#pragma region PlayerImage
	// 테스트용 이미지 
	IMAGEMANAGER->addFrameImage("꼬깔대기", "Resources/Images/Player/p_idle.bmp", 1664, 146, 13, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔이동", "Resources/Images/Player/p_move.bmp", 1106, 140, 14, 2, MGT);

	// Player 
	IMAGEMANAGER->addFrameImage("pIdle", "Resources/Images/Player/p_idle.bmp", 1664, 146, 13, 2, MGT);
	IMAGEMANAGER->addFrameImage("pMove", "Resources/Images/Player/p_move.bmp", 1106, 140, 14, 2, MGT);
	// PlayerAttack threeCombo(Att1~3) , etc ...
	IMAGEMANAGER->addFrameImage("pAtt1", "Resources/Images/Player/playerAttOneAddEffet.bmp", 1260,144, 9, 2, MGT);
	IMAGEMANAGER->addFrameImage("pAtt2", "Resources/Images/Player/playerAttOneAddEffet.bmp", 725, 144, 9, 2, MGT);
	IMAGEMANAGER->addFrameImage("pAtt3", "Resources/Images/Player/playerAttOneAddEffet.bmp", 2600, 144, 9, 2, MGT);
	IMAGEMANAGER->addFrameImage("pUpAtt", "Resources/Images/Player/playerUpwardAtt.bmp", 972, 148, 12, 2, MGT);
	IMAGEMANAGER->addFrameImage("pJumpAtt", "Resources/Images/Player/playerJumpAttack.bmp", 1510, 200, 10, 2, MGT);
	IMAGEMANAGER->addFrameImage("pAttEnd", "Resources/Images/Player/playerAttFinish.bmp", 594,148, 9, 2, MGT);
	// PlayerJump
	IMAGEMANAGER->addFrameImage("pFronJumpOn", "Resources/Images/Player/playerAttFinish.bmp", 1120, 158, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("pJumpOn", "Resources/Images/Player/playerJumpOn.bmp", 235, 162, 5, 2, MGT);
	IMAGEMANAGER->addFrameImage("pJumpOff", "Resources/Images/Player/playerJumpOff.bmp", 328, 150,4, 2, MGT);
	// Player etc... 
	IMAGEMANAGER->addFrameImage("pSliding", "Resources/Images/Player/playerSliding.bmp", 1455, 144, 15, 2, MGT);

	// Player Effect
	IMAGEMANAGER->addFrameImage("pDust", "Resources/Images/Player/Effect/Dust.bmp", 450, 40, 5,1,  MGT);
	IMAGEMANAGER->addFrameImage("pAttEffect", "Resources/Images/Player/Effect/twoComboEffect.bmp", 792,164,6,2  , MGT);
	IMAGEMANAGER->addFrameImage("pJumpAttEffect", "Resources/Images/Player/Effect/jumpAttackEffect.bmp", 604,200, 4,2 , MGT);
	IMAGEMANAGER->addFrameImage("pUpAttEffect", "Resources/Images/Player/Effect/upWardAttSlash.bmp", 320, 100,4,1,   MGT);


#pragma endregion

#pragma region BossImage
	// Tutorial -> bTuto
	IMAGEMANAGER->addFrameImage("bTutoIdle", "Resources/Images/Monster/Boss_Tutorial/tutoBossIdle.bmp", 1650,334, 10, 2, MGT);
	IMAGEMANAGER->addFrameImage("bTutoAtt", "Resources/Images/Monster/Boss_Tutorial/tutoBossJumpAttack.bmp", 5425, 414, 25, 1, MGT);
	IMAGEMANAGER->addFrameImage("bTutoDead", "Resources/Images/Monster/Boss_Tutorial/tutoBossDead.bmp", 20384, 494, 49, 1, MGT);
	IMAGEMANAGER->addFrameImage("bTutoEffect", "Resources/Images/Monster/Boss_Tutorial/tutoBossEffect.bmp", 640, 512, 5,4, MGT); // 5*4 ani

	// Isidora -> bIsi
	IMAGEMANAGER->addFrameImage("bIsiIntro", "Resources/Images/Monster/Boss_Isidora/isidoraIntro.bmp", 13056, 256, 51, 4, MGT); // 5*1


#pragma endregion

#pragma region FieldMonsterImage

#pragma endregion

#pragma region Stage Scene
	// Stage 1
	//IMAGEMANAGER->addImage("StartBG", "Resources/Images/BackGround/bg1.bmp", WINSIZE);
	IMAGEMANAGER->addImage("StartBg", "Resources/Images/BackGround/boss1beforeScene.bmp", 4360,675, MGT); //start Scene
	IMAGEMANAGER->addImage("StartBgTop", "Resources/Images/BackGround/boss1beforeSceneFrontDoor.bmp", 4360, 675, MGT); //start Scene


	// Stage 2
	IMAGEMANAGER->addImage("Field1BG", "Resources/Images/BackGround/bg2.bmp", WINSIZE);
	IMAGEMANAGER->addImage("Boss2BG", "Resources/Images/BackGround/bg3.bmp", WINSIZE);

#pragma endregion

#pragma region Stage Object NPC
	IMAGEMANAGER->addFrameImage("alter", "Resources/Images/Object/UI/menuNoButton.bmp", 272,304, MGT); // 임시

#pragma endregion

#pragma region UI Scene 
	// BG : Resources/Images/BackGround/UI
	// BG : 640*360 (*1.875)-> 1200 * 640

	// Title ANYBUTTON
	IMAGEMANAGER->addImage("AnyButtonBg", "Resources/Images/BackGround/UI/anyButtonBg.bmp", WINSIZE, MGT);
	IMAGEMANAGER->addImage("AnyButtonLogo", "Resources/Images/BackGround/UI/anyButtonLogo2.bmp", 720,308, MGT);
	
	// Title TITLE
	IMAGEMANAGER->addFrameImage("titleBg", "Resources/Images/BackGround/UI/titleBg.bmp", 18000,675,15,1, MGT);
	IMAGEMANAGER->addFrameImage("titleMain", "Resources/Images/BackGround/UI/titleMain.bmp", 16800, 675, 14, 1, MGT);
	IMAGEMANAGER->addFrameImage("titleEffect", "Resources/Images/BackGround/UI/titleEffect.bmp", 52800, 675, 44, 1, MGT);
	IMAGEMANAGER->addFrameImage("titleMenu", "Resources/Images/UI/titleMenu.bmp", 273, 117, 3, 1, MGT);

	// UI BackGround
	IMAGEMANAGER->addImage("menuSaveBg", "Resources/Images/BackGround/UI/menuSaveBg.bmp", WINSIZE);
	IMAGEMANAGER->addImage("menuOptionBg", "Resources/Images/BackGround/UI/menuOptionBg.bmp", WINSIZE);

	IMAGEMANAGER->addImage("inven1", "Resources/Images/BackGround/UI/Inventory1_rosary.bmp", WINSIZE);
	IMAGEMANAGER->addImage("inven2", "Resources/Images/BackGround/UI/Inventory2_relic.bmp", WINSIZE);
	IMAGEMANAGER->addImage("inven3", "Resources/Images/BackGround/UI/Inventory3_quest.bmp", WINSIZE);
	IMAGEMANAGER->addImage("inven4", "Resources/Images/BackGround/UI/Inventory4_meaculpa.bmp", WINSIZE);
	IMAGEMANAGER->addImage("inven5", "Resources/Images/BackGround/UI/Inventory5_bible.bmp", WINSIZE);
	IMAGEMANAGER->addImage("inven6", "Resources/Images/BackGround/UI/Inventory6_skill.bmp", WINSIZE);
	IMAGEMANAGER->addImage("inven7", "Resources/Images/BackGround/UI/Inventory7_collection.bmp", WINSIZE);

	// UI Top Image : playerDie, bossDie ....
	IMAGEMANAGER->addImage("pDie", "Resources/Images/UI/Top/die.bmp", 1200, 675 ); 
	IMAGEMANAGER->addImage("bDie", "Resources/Images/UI/Top/bossDefeat.bmp", 1200, 675); 


#pragma endregion

#pragma region UI Object
	// etc : Resources/Images/UI/폴더명 또는 이미지
	// system
	IMAGEMANAGER->addFrameImage("lodingIcon", "Resources/Images/UI/LoadingSpinningIco.bmp", 500, 500, 5, 5, MGT); // 500,500
	IMAGEMANAGER->addFrameImage("titleSelecte", "Resources/Images/UI/alliedCherub.bmp", 560, 420,4,3, MGT); // 280,210
	IMAGEMANAGER->addImage("saveOn", "Resources/Images/UI/saveOn.bmp", 848 , 112, MGT); // 385,51
	IMAGEMANAGER->addImage("saveOff", "Resources/Images/UI/saveOff.bmp", 848, 112, MGT); // 385,51
	IMAGEMANAGER->addImage("saveNoData", "Resources/Images/UI/saveNoData.bmp", 848, 112, MGT); // 385,51
	IMAGEMANAGER->addImage("AreaBg", "Resources/Images/UI/message_area.bmp", 1200,131, MGT); // 지역변경시 상단알파렌더
	IMAGEMANAGER->addImage("optionSelect", "Resources/Images/UI/optionSelect.bmp", 16,31, MGT); // 옵션메뉴 선택시 출력 


	// Animation 
	IMAGEMANAGER->addFrameImage("itemSelect", "Resources/Images/UI/selectItem.bmp", 120,120, 4,4, MGT);
	IMAGEMANAGER->addFrameImage("stand", "Resources/Images/UI/priedieuStand.bmp", 462, 155, 7, 1 , MGT); // 462, 155
	IMAGEMANAGER->addFrameImage("itemObj", "Resources/Images/UI/itemObject.bmp", 260, 91, 10, 1, MGT); // 260,91

	
	// player
	IMAGEMANAGER->addImage("pHpBarEmpty", "Resources/Images/UI/UI_emptyHpBar.bmp", 40, 40, 222, 90, MGT);
	IMAGEMANAGER->addImage("pHpBarCover", "Resources/Images/UI/UI_upperHpBar.bmp", 40, 40, 222, 90, MGT);
	IMAGEMANAGER->addFrameImage("hpPotionOff", "Resources/Images/UI/hpPotionOff.bmp", 57,27, 3,1, MGT);
	IMAGEMANAGER->addFrameImage("hpPotionOn", "Resources/Images/UI/hpPotionOn.bmp", 57, 27, 3, 1, MGT);
	IMAGEMANAGER->addImage("point", "Resources/Images/UI/point.bmp", 0,45, 160,80, MGT); //84,42


	// button
	IMAGEMANAGER->addImage("e", "Resources/Images/UI/Button/E.bmp", 35,38, MGT); //35,38
	IMAGEMANAGER->addImage("k", "Resources/Images/UI/Button/K.bmp", 35, 38, MGT); //35,38
	IMAGEMANAGER->addImage("esc", "Resources/Images/UI/Button/ESC.bmp", 39,35, MGT); //20,18
	IMAGEMANAGER->addImage("enter", "Resources/Images/UI/Button/ENTER.bmp", 56,35,  MGT); //29,18
	IMAGEMANAGER->addImage("space", "Resources/Images/UI/Button/SPACE.bmp", 56, 35, MGT); //29,18


	
#pragma endregion


#pragma region Item
	// Resources/Images/item

	// 클리핑마스크 사용
	IMAGEMANAGER->addFrameImage("items", "Resources/Images/item/items.bmp", 510*1.9, 510 * 1.9,17,17, MGT); // 510,510->969,969
	IMAGEMANAGER->addImage("item", "Resources/Images/item/items.bmp", 510 * 1.9, 510 * 1.9, MGT); // 510,510->969,969

	IMAGEMANAGER->addFrameImage("itemsCursor", "Resources/Images/item/ItemCursorAlt.bmp", 150 * 1.9, 90 * 1.9,5,3, MGT); // 150,90->171



#pragma endregion


#pragma region AnimationCutScene
	// AniScene Text BG
	// Resources/Images/Animation
	IMAGEMANAGER->addImage("GreenCorn", "Resources/Images/Animation/shot1_0.bmp", 553, 675, MGT); //640*781

#pragma endregion

	return S_OK;
}

ImageClass::ImageClass()
{
}

ImageClass::~ImageClass()
{
}
