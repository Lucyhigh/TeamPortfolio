#include "Stdafx.h"
#include "ImageClass.h"

#define WINSIZE 1200,675

HRESULT ImageClass::init(void)
{
	// ÀÌ¹ÌÁö¸¦ ÀüºÎ ¿©±â¿¡ ÀúÀå 
	// IMAGEMANAGER->addImage();
	// Å°°ªÀº ¿µ¹®À¸·Î! (¼öÁ¤¿¹Á¤)

#pragma region PlayerImage
	IMAGEMANAGER->addFrameImage("²¿±ò´ë±â", "Resources/Images/Player/p_idle.bmp", 1664, 146, 13, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±òÀÌµ¿", "Resources/Images/Player/p_move.bmp", 1106, 140, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±òÁ¡ÇÁ", "Resources/Images/Player/playerFrontJumpOn.bmp", 1120, 158, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±ò½½¶óÀÌµå", "Resources/Images/Player/playerSliding.bmp", 1455, 144, 15, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±ò¾îÅÃ0", "Resources/Images/Player/playerAttOneAddEffet.bmp", 1260, 144, 9, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±ò¾îÅÃ0", "Resources/Images/Player/playerAttOneAddEffet.bmp", 1260, 144, 9, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±ò¾îÅÃ1", "Resources/Images/Player/playerAttTwoAddEffe.bmp", 725, 144, 5, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±ò¾îÅÃ2", "Resources/Images/Player/playerAttThreeAddEffect.bmp", 2600, 170, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±ò»ó´Ü¾îÅÃ", "Resources/Images/Player/playerUpwardAtt.bmp", 972, 148, 12, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±òÁ¡ÇÁ¾îÅÃ", "Resources/Images/Player/playerJumpAttack.bmp", 1510, 200, 10, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±òÁ¡ÇÁ¾îÅÃÀÌÆåÆ®", "Resources/Images/Player/p_jumpattack_ef.bmp", 604, 200, 4, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±ò»ó´Ü¾îÅÃÀÌÆåÆ®", "Resources/Images/Player/p_upattack_ef.bmp", 320, 300, 4, 2, MGT);
	IMAGEMANAGER->addFrameImage("°ø°ÝÀÌÆåÆ®", "Resources/Images/Player/effectTwo.bmp", 792, 164, 6, 2, MGT);
#pragma endregion


#pragma region BossImage

	IMAGEMANAGER->addFrameImage("¼öÈ£ÀÚ´ë±â", "Resources/Images/Boss/BossWardenIdle.bmp", 1650*2, 334*2, 10, 2, MGT);
	IMAGEMANAGER->addFrameImage("¼öÈ£ÀÚÁ¡ÇÁ", "Resources/Images/Boss/BassWardenJump.bmp", 5425*2, 414*2, 25, 2, MGT);
	IMAGEMANAGER->addFrameImage("¼öÈ£ÀÚ°ø°Ý", "Resources/Images/Boss/tutoBossAttack.bmp", 8280 * 2, 430 * 2, 24, 2, MGT);
	IMAGEMANAGER->addFrameImage("¼öÈ£ÀÚÁ×À½", "Resources/Images/Boss/tutoBossDead.bmp", 20384 * 2, 494 * 2, 49, 2, MGT);

#pragma endregion

	// ÇÃ·¹ÀÌ¾î / ¸ó½ºÅÍ / ÇÊµå / UI / Item / ¾Ö´Ï¸ÞÀÌ¼Ç ¼ø

	// Å×½ºÆ®¿ë ÀÌ¹ÌÁö 
	IMAGEMANAGER->addImage("¼¼ÀÌºê", "Resources/test/save.bmp", 1200, 675);
	IMAGEMANAGER->addImage("¸Þ´º", "Resources/test/menu.bmp", 1200, 675);

	// ================================================================================================================

#pragma region PlayerImage

	// Å×½ºÆ®¿ë ÀÌ¹ÌÁö 
	IMAGEMANAGER->addFrameImage("²¿±ò´ë±â", "Resources/Images/Player/p_idle.bmp", 1664, 146, 13, 2, MGT);
	IMAGEMANAGER->addFrameImage("²¿±òÀÌµ¿", "Resources/Images/Player/p_move.bmp", 1106, 140, 14, 2, MGT);

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

#pragma region UI Scene 

	// Å¸ÀÌÆ² ÀÌ¹ÌÁö 
	IMAGEMANAGER->addImage("AnyButton", "Resources/Images/BackGround/UI/anyButtonBg.bmp", 1200, 675);
	// Å¸ÀÌÆ² ¾Ö´Ï¸ÞÀÌ¼Ç ÀÌ¹ÌÁö 640*360
	IMAGEMANAGER->addImage("titleBg", "Resources/Images/Object/titleBg.bmp", 9600,360,15,1, MGT);
	IMAGEMANAGER->addImage("titleMain", "Resources/Images/Object/titleMain.bmp", 8960, 360, 14, 1, MGT);
	IMAGEMANAGER->addImage("titleEffect", "Resources/Images/Object/titleEffect.bmp", 28160, 360, 44, 1, MGT);

	IMAGEMANAGER->addFrameImage("¸Þ´º", "Resources/Images/cornObject/menu.bmp", 272, 360, 2, 1, MGT);
	IMAGEMANAGER->addFrameImage("¸Þ´ºÃ¢", "Resources/Images/cornObject/menuDisplay.bmp", 3600, 675, 3, 1, MGT);


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
	IMAGEMANAGER->addFrameImage("alter", "Resources/Images/Object/UI/menuNoButton.bmp", 272,304, MGT); // ÀÓ½Ã

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


#pragma region Stage Scene
    IMAGEMANAGER->addImage("¿ÀÇÁ´× ÇÈ¼¿", "Resources/Images/BackGround/openingScenePixel.bmp", 4150, 1694, MGT);
    IMAGEMANAGER->addImage("¿ÀÇÁ´×¾À ¹Ù´Ú", "Resources/Images/BackGround/openingScenefloor.bmp", 4150, 1694, MGT);
    IMAGEMANAGER->addImage("¿ÀÇÁ´×¾À Å×½ºÆ®¹è°æ", "Resources/Images/BackGround/openingSceneAll.bmp", 4150, 1694);//
    IMAGEMANAGER->addImage("¿ÀÇÁ´×¾À µÞ¹è°æ", "Resources/Images/BackGround/openingSceneLastBG.bmp", 4150, 1694);
    IMAGEMANAGER->addImage("¿ÀÇÁ´×¾À ¾Õ½ÃÃ¼", "Resources/Images/BackGround/openingSceneFrontBody.bmp", 4150, 1694, MGT);
    IMAGEMANAGER->addImage("¿ÀÇÁ´×¾À ¾Õ¹®", "Resources/Images/BackGround/openingSceneFrontDoor.bmp", 4150, 1694, MGT);
	//IMAGEMANAGER->addImage("¿ÀÇÁ´×¾À ÇÈ¼¿", "Resources/Images/BackGround/openingScenePixel.bmp", 4150, 1694);// MGT);
	IMAGEMANAGER->addImage("¿ÀÇÁ´×¾À ÇÈ¼¿", "Resources/Images/BackGround/openingScenePixel.bmp", WINSIZE_X, WINSIZE_Y);// MGT);



	IMAGEMANAGER->addImage("¾À1¹è°æ", "Resources/Images/BackGround/bg1.bmp", 1200, 675);
	IMAGEMANAGER->addImage("º¸½º1Àü¹è°æ", "Resources/Images/BackGround/boss1beforeScene.bmp", 4360, 675);//
	IMAGEMANAGER->addImage("º¸½º1ÀüFrontDoor", "Resources/Images/BackGround/boss1beforeSceneFrontDoor.bmp", 4360, 675,MGT);//

	IMAGEMANAGER->addImage("º¸½º1 ¹Ù´Ú", "Resources/Images/BackGround/boss1floor.bmp", 2460, 675, MGT);// TODO
	IMAGEMANAGER->addImage("º¸½º1 µÞ¹è°æ", "Resources/Images/BackGround/boss1LastBG.bmp", 2460, 675);//
	IMAGEMANAGER->addImage("º¸½º1 µÞ½ÃÃ¼", "Resources/Images/BackGround/boss1bodysBG.bmp", 2460, 675,MGT);//
	IMAGEMANAGER->addImage("º¸½º1 ¾Õ½ÃÃ¼", "Resources/Images/BackGround/boss1FrontBody.bmp", 2460, 675,MGT);//
	IMAGEMANAGER->addImage("º¸½º1 ¾Õ¹®", "Resources/Images/BackGround/boss1FrontDoor.bmp", 2460, 675,MGT);//

	IMAGEMANAGER->addImage("¾À2¹è°æ", "Resources/Images/BackGround/bg2.bmp", 1200, 675);
	IMAGEMANAGER->addImage("¾À3¹è°æ", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

	// ¼öÁ¤ ¹× ÀÚ¸® ÀâÀº ÀÌ¹ÌÁö 
	IMAGEMANAGER->addImage("BossStage2_Bg", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

#pragma endregion


#pragma region UI Object
	// etc : Resources/Images/UI/Æú´õ¸í ¶Ç´Â ÀÌ¹ÌÁö
	// system
	IMAGEMANAGER->addFrameImage("lodingIcon", "Resources/Images/UI/LoadingSpinningIco.bmp", 500, 500, 5, 5, MGT); // 500,500
	IMAGEMANAGER->addFrameImage("titleSelecte", "Resources/Images/UI/alliedCherub.bmp", 560, 420,4,3, MGT); // 280,210
	IMAGEMANAGER->addImage("saveOn", "Resources/Images/UI/saveOn.bmp", 848 , 112, MGT); // 385,51
	IMAGEMANAGER->addImage("saveOff", "Resources/Images/UI/saveOff.bmp", 848, 112, MGT); // 385,51
	IMAGEMANAGER->addImage("saveNoData", "Resources/Images/UI/saveNoData.bmp", 848, 112, MGT); // 385,51
	IMAGEMANAGER->addImage("AreaBg", "Resources/Images/UI/message_area.bmp", 1200,131, MGT); // Áö¿ªº¯°æ½Ã »ó´Ü¾ËÆÄ·»´õ
	IMAGEMANAGER->addImage("optionSelect", "Resources/Images/UI/optionSelect.bmp", 16,31, MGT); // ¿É¼Ç¸Þ´º ¼±ÅÃ½Ã Ãâ·Â 


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

	// Object
    IMAGEMANAGER->addImage("¹öÆ°", "Resources/Images/Object/buttomE.bmp", 35 * 1.9, 38 * 1.9, MGT);
    IMAGEMANAGER->addFrameImage("stand", "Resources/Images/Object/priedieuStand.bmp", 924, 310, 7, 1, MGT); // 462, 155
    IMAGEMANAGER->addFrameImage("itemObj", "Resources/Images/Object/itemObject.bmp", 260, 91, 10, 1, MGT); // 260,91
	IMAGEMANAGER->addFrameImage("SymbolObj", "Resources/Images/Object/SymbolStatue.bmp", 162, 64, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("breakSymbolObj", "Resources/Images/Object/breakSymbolStatue.bmp", 550, 120, 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("breakableSkeleton", "Resources/Images/Object/breakableSkeleton.bmp", 756 * 1.7, 101 * 1.7, 14, 1, MGT);

	// Item
	// Å¬¸®ÇÎ¸¶½ºÅ© »ç¿ë
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
