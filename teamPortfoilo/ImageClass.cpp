#include "Stdafx.h"
#include "ImageClass.h"

#define WINSIZE 1200,675

HRESULT ImageClass::init(void)
{
	// 이미지를 전부 여기에 저장 
	// IMAGEMANAGER->addImage();
	// 키값은 영문으로! (수정예정)

#pragma region PlayerImage
	IMAGEMANAGER->addFrameImage("꼬깔대기", "Resources/Images/Player/p_idle.bmp", 1664 * 2, 146* 2, 13, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔이동", "Resources/Images/Player/p_move.bmp", 1106 * 2, 140* 2, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔점프", "Resources/Images/Player/playerFrontJumpOn.bmp", 1120, 158, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔슬라이드", "Resources/Images/Player/playerSliding.bmp", 1455, 144, 15, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔어택0", "Resources/Images/Player/playerAttOneAddEffet.bmp", 1260, 144, 9, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔어택0", "Resources/Images/Player/playerAttOneAddEffet.bmp", 1260, 144, 9, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔어택1", "Resources/Images/Player/playerAttTwoAddEffe.bmp", 725, 144, 5, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔어택2", "Resources/Images/Player/playerAttThreeAddEffect.bmp", 2600, 170, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔상단어택", "Resources/Images/Player/playerUpwardAtt.bmp", 972, 148, 12, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔점프어택", "Resources/Images/Player/playerJumpAttack.bmp", 1510, 200, 10, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔점프어택이펙트", "Resources/Images/Player/p_jumpattack_ef.bmp", 604, 200, 4, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔상단어택이펙트", "Resources/Images/Player/p_upattack_ef.bmp", 320, 300, 4, 2, MGT);
	IMAGEMANAGER->addFrameImage("공격이펙트", "Resources/Images/Player/effectTwo.bmp", 792, 164, 6, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔기도", "Resources/Images/Player/playerParyer.bmp", 1404, 208, 18, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔포션", "Resources/Images/Player/playerPotion.bmp", 1900, 280, 19, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔기상", "Resources/Images/Player/p_risingFromFallen.bmp", 896 * 2, 768, 7, 6, MGT);
	
#pragma endregion


#pragma region BossImage

	IMAGEMANAGER->addFrameImage("수호자대기", "Resources/Images/Boss/BossWardenIdle.bmp", 1650*2, 334*2, 10, 2, MGT);
	IMAGEMANAGER->addFrameImage("수호자점프", "Resources/Images/Boss/BassWardenJump.bmp", 5425*2, 414*2, 25, 2, MGT);
	IMAGEMANAGER->addFrameImage("수호자공격", "Resources/Images/Boss/tutoBossAttack.bmp", 8280 * 2, 430 * 2, 24, 2, MGT);
	IMAGEMANAGER->addFrameImage("수호자죽음", "Resources/Images/Boss/tutoBossDead.bmp", 20384 * 2, 494 * 2, 49, 2, MGT);

#pragma endregion

	// 플레이어 / 몬스터 / 필드 / UI / Item / 애니메이션 순

	// 테스트용 이미지 
	IMAGEMANAGER->addImage("세이브", "Resources/test/save.bmp", 1200, 675);
	IMAGEMANAGER->addImage("메뉴", "Resources/test/menu.bmp", 1200, 675);

	// ================================================================================================================

#pragma region PlayerImage

	// 테스트용 이미지 
	IMAGEMANAGER->addFrameImage("꼬깔대기", "Resources/Images/Player/p_idle.bmp", 1664 * 1.9, 146*1.9, 13, 2, MGT);
	IMAGEMANAGER->addFrameImage("꼬깔이동", "Resources/Images/Player/p_move.bmp", 1106 * 1.9, 140*1.9, 14, 2, MGT);

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
	IMAGEMANAGER->addFrameImage("bIsiIntro", "Resources/Images/Monster/Boss_Isidora/isidoraIntro.bmp", 13056, 256, 51, 1, MGT); // 5*1
	IMAGEMANAGER->addFrameImage("blsiIdle", "Resources/Images/Monster/Boss_Isidora/Isidora_idleFinal.bmp", 1360, 2048, 4, 8, MGT);
	IMAGEMANAGER->addFrameImage("bIsiWarpOn", "Resources/Images/Monster/Boss_Isidora/Isidora_idleToVanishFinal.bmp", 1360, 2048, 4, 8, MGT); // 5*1	
	IMAGEMANAGER->addFrameImage("bIsiWarpOff", "Resources/Images/Monster/Boss_Isidora/Isidora_outToTwirlFinal.bmp", 1020, 1536, 3, 6, MGT); // 5*1	
	IMAGEMANAGER->addFrameImage("bIsiWarpAttack", "Resources/Images/Monster/Boss_Isidora/ishidora_attack_effect.bmp", 2040, 3072, 6, 12, MGT); // 5*1	
	IMAGEMANAGER->addFrameImage("blsiFirePillarAttack0", "Resources/Images/Monster/Boss_Isidora/Isidora_castSequenceFinal.bmp", 1700, 3072, 5, 12, MGT); // 5*1	
	IMAGEMANAGER->addFrameImage("blsiDie", "Resources/Images/Monster/Boss_Isidora/Isidora_deathV3.bmp", 3400, 6144, 10, 24, MGT); // 5*1	

	IMAGEMANAGER->addFrameImage("bIsiFireBall", "Resources/Images/Monster/Boss_Isidora/isidoraFireBallLoop.bmp", 600, 64, 12, 4, MGT); // 5*1
	IMAGEMANAGER->addFrameImage("bIsiFirePillar", "Resources/Images/Monster/Boss_Isidora/Isidora_brazierFullLoop.bmp", 400*2, 540*2, 4, 3, MGT); // 5*1
	IMAGEMANAGER->addFrameImage("bIsiFirePillarDie", "Resources/Images/Monster/Boss_Isidora/Isidora_brazierFullToHalf.bmp", 600*2, 360*2, 6, 2, MGT); // 5*1	  
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
	IMAGEMANAGER->addImage("pDie", "Resources/Images/UI/Top/die.bmp", 1200, 675);
	IMAGEMANAGER->addImage("bDieBg", "Resources/Images/UI/Top/bossDefeatBg.bmp", 1200, 675);
	IMAGEMANAGER->addImage("bDie", "Resources/Images/UI/Top/bossDefeat.bmp", 1200, 675, MGT);
#pragma endregion


#pragma region Stage Scene
    IMAGEMANAGER->addImage("오프닝씬 바닥", "Resources/Images/BackGround/openingScenefloor.bmp", 4150, 1694, MGT);
    IMAGEMANAGER->addImage("오프닝씬 테스트배경", "Resources/Images/BackGround/openingSceneAll.bmp", 4150, 1694);
    IMAGEMANAGER->addImage("오프닝씬 뒷배경", "Resources/Images/BackGround/openingSceneLastBG.bmp", 4150, 1694);
    IMAGEMANAGER->addImage("오프닝씬 앞시체", "Resources/Images/BackGround/openingSceneFrontBody.bmp", 4150, 1694, MGT);
    IMAGEMANAGER->addImage("오프닝씬 앞문", "Resources/Images/BackGround/openingSceneFrontDoor.bmp", 4150, 1694, MGT);
	IMAGEMANAGER->addImage("오프닝씬 픽셀", "Resources/Images/BackGround/openingScenePixel.bmp", 4150, 1694, MGT);

	IMAGEMANAGER->addImage("씬1배경", "Resources/Images/BackGround/bg1.bmp", 1200, 675);
	IMAGEMANAGER->addImage("보스1전 배경", "Resources/Images/BackGround/boss1beforeScene.bmp", 4360, 675);
	IMAGEMANAGER->addImage("보스1전 FrontDoor", "Resources/Images/BackGround/boss1beforeSceneFrontDoor.bmp", 4360, 675,MGT);
	IMAGEMANAGER->addImage("보스1전 바닥", "Resources/Images/BackGround/boss1beforeSceneFloor.bmp", 4360, 675,MGT);

	IMAGEMANAGER->addImage("보스1 바닥", "Resources/Images/BackGround/boss1floor.bmp", 2460, 675, MGT);
	IMAGEMANAGER->addImage("보스1 뒷배경", "Resources/Images/BackGround/boss1LastBG.bmp", 1200, 675);
	IMAGEMANAGER->addImage("보스1 뒷시체", "Resources/Images/BackGround/boss1bodysBG.bmp", 2460, 675,MGT);
	IMAGEMANAGER->addImage("보스1 앞시체", "Resources/Images/BackGround/boss1FrontBody.bmp", 2460, 675,MGT);
	IMAGEMANAGER->addImage("보스1 앞문", "Resources/Images/BackGround/boss1FrontDoor.bmp", 2460, 675,MGT);

	IMAGEMANAGER->addImage("씬2배경", "Resources/Images/BackGround/bg2.bmp", 1200, 675);
	IMAGEMANAGER->addImage("씬3배경", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

	IMAGEMANAGER->addImage("보스2전 배경", "Resources/Images/BackGround/Boss2before.bmp", 1200, 675);
	IMAGEMANAGER->addImage("보스2전 FrontDoor", "Resources/Images/BackGround/Boss2beforeFG.bmp", 1200, 675,MGT);

	IMAGEMANAGER->addImage("라스트씬 바닥", "Resources/Images/BackGround/endingfloor.bmp", 5000, 1862, MGT);
	IMAGEMANAGER->addImage("라스트씬 테스트배경", "Resources/Images/BackGround/endingAll.bmp", 5000, 1862);//
	IMAGEMANAGER->addImage("라스트씬 뒷배경", "Resources/Images/BackGround/endingBG.bmp", 5000, 1862);
	IMAGEMANAGER->addImage("라스트씬 앞배경", "Resources/Images/BackGround/endingFG.bmp", 5000, 1862, MGT);
	IMAGEMANAGER->addImage("라스트씬 앞배경2", "Resources/Images/BackGround/endingFG2.bmp", 5000, 1862, MGT);
	IMAGEMANAGER->addImage("라스트씬 픽셀", "Resources/Images/BackGround/endingScenePixel.bmp", 5000, 1862, MGT);

	IMAGEMANAGER->addImage("엔딩이미지1", "Resources/Images/Animation/endingl.bmp", WINSIZE_X,WINSIZE_Y);
	IMAGEMANAGER->addImage("엔딩이미지2", "Resources/Images/Animation/ending2.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addImage("엔딩이미지3", "Resources/Images/Animation/ending3.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addImage("엔딩이미지4", "Resources/Images/Animation/ending4.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addImage("엔딩이미지5", "Resources/Images/Animation/ending5.bmp", WINSIZE_X,WINSIZE_Y);
    IMAGEMANAGER->addImage("컷전환", "Resources/Images/Animation/sceneChange.bmp", WINSIZE_X,WINSIZE_Y);


	// 수정 및 자리 잡은 이미지 
	IMAGEMANAGER->addImage("BossStage2_Bg", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

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

	// Boss : T - Top, B - Bottom
	IMAGEMANAGER->addImage("bHpBarEmpty", "Resources/Images/UI/bossHPBarEmpty.bmp", CENTER_X - 332, WINSIZE_Y - 70, 664, 62, MGT);
	IMAGEMANAGER->addImage("bHpBarCover", "Resources/Images/UI/bossHPBarCover.bmp", CENTER_X - 332, WINSIZE_Y - 70, 664, 62, MGT);
	IMAGEMANAGER->addImage("bHpBarT", "Resources/Images/UI/bossHPBar.bmp", 320, WINSIZE_Y - 30, 543, 15, MGT);
	IMAGEMANAGER->addImage("bHpBarB", "Resources/Images/UI/bossHPBar2.bmp", 320, WINSIZE_Y - 30, 543, 15, MGT);


	// button
	IMAGEMANAGER->addImage("e", "Resources/Images/UI/Button/E.bmp", 35,38, MGT); //35,38
	IMAGEMANAGER->addImage("k", "Resources/Images/UI/Button/K.bmp", 35, 38, MGT); //35,38
	IMAGEMANAGER->addImage("esc", "Resources/Images/UI/Button/ESC.bmp", 39,35, MGT); //20,18
	IMAGEMANAGER->addImage("enter", "Resources/Images/UI/Button/ENTER.bmp", 56,35,  MGT); //29,18
	IMAGEMANAGER->addImage("space", "Resources/Images/UI/Button/SPACE.bmp", 56, 35, MGT); //29,18

#pragma region Object

	IMAGEMANAGER->addImage("버튼", "Resources/Images/Object/buttomE.bmp", 35 * 1.9, 38 * 1.9, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("deosgracias", "Resources/Images/Object/deosgracias.bmp", 1664, 1536, 13, 6, MGT); // 128,256
	IMAGEMANAGER->addFrameImage("stand", "Resources/Images/Object/priedieuStand.bmp", 924, 310, 7, 1, MGT); // 462, 155
	IMAGEMANAGER->addFrameImage("itemObj", "Resources/Images/Object/itemObject.bmp", 260, 91, 10, 1, MGT); // 260,91
	//IMAGEMANAGER->addFrameImage("SymbolObj", "Resources/Images/Object/SymbolStatue.bmp", 162 * 2, 64 * 2, 6, 1, MGT);
	IMAGEMANAGER->addFrameImage("SymbolObj", "Resources/Images/Object/SymbolStatue2.bmp", 162 * 2, 64 * 2, 6, 1, MGT);
	//IMAGEMANAGER->addFrameImage("breakSymbolObj", "Resources/Images/Object/breakSymbolStatue.bmp", 550 * 2, 120 * 2, 10, 1, MGT);
	IMAGEMANAGER->addFrameImage("breakSymbolObj", "Resources/Images/Object/breakSymbolStatue2.bmp", 550 * 2, 120 * 2, 10, 1, MGT);
	//IMAGEMANAGER->addFrameImage("breakableSkeleton", "Resources/Images/Object/breakableSkeleton.bmp", 756 * 2, 101 * 2, 14, 1, MGT);
	IMAGEMANAGER->addFrameImage("breakableSkeleton", "Resources/Images/Object/breakableSkeleton2.bmp", 756 * 2, 101 * 2, 14, 1, MGT);
	IMAGEMANAGER->addFrameImage("frameNpc", "Resources/Images/Object/deosgracias.bmp", 1664, 1536, 13, 6, MGT);
	IMAGEMANAGER->addFrameImage("SandNPCStanding", "Resources/Images/Object/sandNpcStand.bmp", 924, 840, 7, 7, MGT);
	//IMAGEMANAGER->addFrameImage("SandNPCStanding", "Resources/Images/Object/sandNpcStand2.bmp", 924, 840, 7, 7, MGT);
	IMAGEMANAGER->addFrameImage("SandNPC", "Resources/Images/Object/sandNpc.bmp", 927, 468, 7, 4, MGT);
	//IMAGEMANAGER->addFrameImage("SandNPC", "Resources/Images/Object/sandNpc2.bmp", 924, 476, 7, 4, MGT);

	// Item
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
