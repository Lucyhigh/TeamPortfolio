#include "Stdafx.h"
#include "ImageClass.h"

#define WINSIZE 1200,675

HRESULT ImageClass::init(void)
{
	// �̹����� ���� ���⿡ ���� 
	// IMAGEMANAGER->addImage();
	// Ű���� ��������! (��������)

#pragma region PlayerImage
	IMAGEMANAGER->addFrameImage("������", "Resources/Images/Player/p_idle.bmp", 1664, 146, 13, 2, MGT);
	IMAGEMANAGER->addFrameImage("�����̵�", "Resources/Images/Player/p_move.bmp", 1106, 140, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("��������", "Resources/Images/Player/p_jump.bmp", 1120, 158, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("���򽽶��̵�", "Resources/Images/Player/p_slide.bmp", 1455, 144, 15, 2, MGT);
	IMAGEMANAGER->addFrameImage("�������0", "Resources/Images/Player/p_attack.bmp", 1260, 144, 9, 2, MGT);
	IMAGEMANAGER->addFrameImage("�������0", "Resources/Images/Player/p_attack0.bmp", 1260, 144, 9, 2, MGT);
	IMAGEMANAGER->addFrameImage("�������1", "Resources/Images/Player/p_attack1.bmp", 725, 144, 5, 2, MGT);
	IMAGEMANAGER->addFrameImage("�������2", "Resources/Images/Player/p_attack2.bmp", 2600, 170, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("�����ܾ���", "Resources/Images/Player/p_upattack.bmp", 972, 148, 12, 2, MGT);
	IMAGEMANAGER->addFrameImage("������������", "Resources/Images/Player/p_jumpattack.bmp", 1510, 200, 10, 2, MGT);
	IMAGEMANAGER->addFrameImage("����������������Ʈ", "Resources/Images/Player/p_jumpattack_ef.bmp", 604, 200, 4, 2, MGT);
	IMAGEMANAGER->addFrameImage("�����ܾ�������Ʈ", "Resources/Images/Player/p_upattack_ef.bmp", 320, 300, 4, 2, MGT);
	IMAGEMANAGER->addFrameImage("��������Ʈ", "Resources/Images/Player/effectTwo.bmp", 792, 164, 6, 2, MGT);
#pragma endregion


#pragma region BossImage

	IMAGEMANAGER->addFrameImage("��ȣ�ڴ��", "Resources/Images/Boss/BossWardenIdle.bmp", 1650*2, 334*2, 10, 2, MGT);
	IMAGEMANAGER->addFrameImage("��ȣ������", "Resources/Images/Boss/BassWardenJump.bmp", 5425*2, 414*2, 25, 2, MGT);
	IMAGEMANAGER->addFrameImage("��ȣ�ڰ���", "Resources/Images/Boss/tutoBossAttack.bmp", 8280 * 2, 430 * 2, 24, 2, MGT);
	IMAGEMANAGER->addFrameImage("��ȣ������", "Resources/Images/Boss/tutoBossDead.bmp", 20384 * 2, 494 * 2, 49, 2, MGT);

#pragma endregion

	// �÷��̾� / ���� / �ʵ� / UI / Item / �ִϸ��̼� ��

	// �׽�Ʈ�� �̹��� 
	IMAGEMANAGER->addImage("���̺�", "Resources/test/save.bmp", 1200, 675);
	IMAGEMANAGER->addImage("�޴�", "Resources/test/menu.bmp", 1200, 675);

	// ================================================================================================================

#pragma region PlayerImage

	// �׽�Ʈ�� �̹��� 
	IMAGEMANAGER->addFrameImage("������", "Resources/Images/Player/p_idle.bmp", 1664 * 1.9, 146*1.9, 13, 2, MGT);
	IMAGEMANAGER->addFrameImage("�����̵�", "Resources/Images/Player/p_move.bmp", 1106 * 1.9, 140*1.9, 14, 2, MGT);

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

	// Ÿ��Ʋ �̹��� 
	IMAGEMANAGER->addImage("AnyButton", "Resources/Images/BackGround/UI/anyButtonBg.bmp", 1200, 675);
	// Ÿ��Ʋ �ִϸ��̼� �̹��� 640*360
	IMAGEMANAGER->addImage("titleBg", "Resources/Images/Object/titleBg.bmp", 9600,360,15,1, MGT);
	IMAGEMANAGER->addImage("titleMain", "Resources/Images/Object/titleMain.bmp", 8960, 360, 14, 1, MGT);
	IMAGEMANAGER->addImage("titleEffect", "Resources/Images/Object/titleEffect.bmp", 28160, 360, 44, 1, MGT);

	IMAGEMANAGER->addFrameImage("�޴�", "Resources/Images/cornObject/menu.bmp", 272, 360, 2, 1, MGT);
	IMAGEMANAGER->addFrameImage("�޴�â", "Resources/Images/cornObject/menuDisplay.bmp", 3600, 675, 3, 1, MGT);

	IMAGEMANAGER->addImage("���� �޾�����", "Resources/Images/BackGround/StoreWeaponTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("���� �⵵��", "Resources/Images/BackGround/StoreBibleTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("���� ����", "Resources/Images/BackGround/StoreRosaryTap.bmp", 1200, 675);

	IMAGEMANAGER->addImage("�κ� �޾�����", "Resources/Images/BackGround/InventoryWeaponTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("�κ� �⵵��", "Resources/Images/BackGround/InventoryBibleTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("�κ� ����", "Resources/Images/BackGround/InventoryRosaryTap.bmp", 1200, 675);

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
	IMAGEMANAGER->addFrameImage("alter", "Resources/Images/Object/UI/menuNoButton.bmp", 272,304, MGT); // �ӽ�

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
    IMAGEMANAGER->addImage("�����׾� �ٴ�", "Resources/Images/BackGround/openingScenefloor.bmp", 4150, 1694, MGT);
    IMAGEMANAGER->addImage("�����׾� �׽�Ʈ���", "Resources/Images/BackGround/openingSceneAll.bmp", 4150, 1694);
    IMAGEMANAGER->addImage("�����׾� �޹��", "Resources/Images/BackGround/openingSceneLastBG.bmp", 4150, 1694);
    IMAGEMANAGER->addImage("�����׾� �ս�ü", "Resources/Images/BackGround/openingSceneFrontBody.bmp", 4150, 1694, MGT);
    IMAGEMANAGER->addImage("�����׾� �չ�", "Resources/Images/BackGround/openingSceneFrontDoor.bmp", 4150, 1694, MGT);
	IMAGEMANAGER->addImage("�����׾� �ȼ�", "Resources/Images/BackGround/openingScenePixel.bmp", 4150, 1694, MGT);

	IMAGEMANAGER->addImage("��1���", "Resources/Images/BackGround/bg1.bmp", 1200, 675);
	IMAGEMANAGER->addImage("����1�� ���", "Resources/Images/BackGround/boss1beforeScene.bmp", 4360, 675);
	IMAGEMANAGER->addImage("����1�� FrontDoor", "Resources/Images/BackGround/boss1beforeSceneFrontDoor.bmp", 4360, 675,MGT);
	IMAGEMANAGER->addImage("����1�� �ٴ�", "Resources/Images/BackGround/boss1beforeSceneFloor.bmp", 4360, 675,MGT);

	IMAGEMANAGER->addImage("����1 �ٴ�", "Resources/Images/BackGround/boss1floor.bmp", 2460, 675, MGT);
	IMAGEMANAGER->addImage("����1 �޹��", "Resources/Images/BackGround/boss1LastBG.bmp", 1200, 675);
	IMAGEMANAGER->addImage("����1 �޽�ü", "Resources/Images/BackGround/boss1bodysBG.bmp", 2460, 675,MGT);
	IMAGEMANAGER->addImage("����1 �ս�ü", "Resources/Images/BackGround/boss1FrontBody.bmp", 2460, 675,MGT);
	IMAGEMANAGER->addImage("����1 �չ�", "Resources/Images/BackGround/boss1FrontDoor.bmp", 2460, 675,MGT);

	IMAGEMANAGER->addImage("��2���", "Resources/Images/BackGround/bg2.bmp", 1200, 675);
	IMAGEMANAGER->addImage("��3���", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

	IMAGEMANAGER->addImage("��Ʈ�� �ٴ�", "Resources/Images/BackGround/endingfloor.bmp", 5000, 1862, MGT);
	IMAGEMANAGER->addImage("��Ʈ�� �׽�Ʈ���", "Resources/Images/BackGround/endingAll.bmp", 5000, 1862);//
	IMAGEMANAGER->addImage("��Ʈ�� �޹��", "Resources/Images/BackGround/endingBG.bmp", 5000, 1862);
	IMAGEMANAGER->addImage("��Ʈ�� �չ��", "Resources/Images/BackGround/endingFG.bmp", 5000, 1862, MGT);
	IMAGEMANAGER->addImage("��Ʈ�� �չ��2", "Resources/Images/BackGround/endingFG2.bmp", 5000, 1862, MGT);
	IMAGEMANAGER->addImage("��Ʈ�� �ȼ�", "Resources/Images/BackGround/endingScenePixel.bmp", 5000, 1862, MGT);

	IMAGEMANAGER->addImage("�����̹���1", "Resources/Images/Animation/endingl.bmp", WINSIZE_X,WINSIZE_Y);
	IMAGEMANAGER->addImage("�����̹���2", "Resources/Images/Animation/ending2.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addImage("�����̹���3", "Resources/Images/Animation/ending3.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addImage("�����̹���4", "Resources/Images/Animation/ending4.bmp", WINSIZE_X, WINSIZE_Y);
    IMAGEMANAGER->addImage("�����̹���5", "Resources/Images/Animation/ending5.bmp", WINSIZE_X,WINSIZE_Y);
    IMAGEMANAGER->addImage("����ȯ", "Resources/Images/Animation/sceneChange.bmp", WINSIZE_X,WINSIZE_Y);


	// ���� �� �ڸ� ���� �̹��� 
	IMAGEMANAGER->addImage("BossStage2_Bg", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

#pragma endregion



#pragma region Item
	// ���� - �޾������� ����
	IMAGEMANAGER->addImage("���� ���� On", "Resources/Images/item/weaponOn_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("���� ���� Off", "Resources/Images/item/weaponOff_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("�μ��� ���� On", "Resources/Images/item/weaponOn_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("�μ��� ���� Off", "Resources/Images/item/weaponOff_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("��Ƴ��� ���� On", "Resources/Images/item/weaponOn_03.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("��Ƴ��� ���� Off", "Resources/Images/item/weaponOff_03.bmp", 60, 60, MGT);

	// �� - �⵵��
	IMAGEMANAGER->addImage("01 �⵵�� On", "Resources/Images/item/bibleOn_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("01 �⵵�� Off", "Resources/Images/item/bibleOff_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("02 �⵵�� On", "Resources/Images/item/bibleOn_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("02 �⵵�� Off", "Resources/Images/item/bibleOff_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("03 �⵵�� On", "Resources/Images/item/bibleOn_03.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("03 �⵵�� Off", "Resources/Images/item/bibleOff_03.bmp", 60, 60, MGT);

	// �Ǽ����� - ����
	IMAGEMANAGER->addImage("01 ���� On", "Resources/Images/item/rosaryOn_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("01 ���� Off", "Resources/Images/item/rosaryOff_01.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("02 ���� On", "Resources/Images/item/rosaryOn_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("02 ���� Off", "Resources/Images/item/rosaryOff_02.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("03 ���� On", "Resources/Images/item/rosaryOn_03.bmp", 60, 60, MGT);
	IMAGEMANAGER->addImage("03 ���� Off", "Resources/Images/item/rosaryOff_04.bmp", 60, 60, MGT);

#pragma region UI Object
	// etc : Resources/Images/UI/������ �Ǵ� �̹���
	// system
	IMAGEMANAGER->addFrameImage("lodingIcon", "Resources/Images/UI/LoadingSpinningIco.bmp", 500, 500, 5, 5, MGT); // 500,500
	IMAGEMANAGER->addFrameImage("titleSelecte", "Resources/Images/UI/alliedCherub.bmp", 560, 420,4,3, MGT); // 280,210
	IMAGEMANAGER->addImage("saveOn", "Resources/Images/UI/saveOn.bmp", 848 , 112, MGT); // 385,51
	IMAGEMANAGER->addImage("saveOff", "Resources/Images/UI/saveOff.bmp", 848, 112, MGT); // 385,51
	IMAGEMANAGER->addImage("saveNoData", "Resources/Images/UI/saveNoData.bmp", 848, 112, MGT); // 385,51
	IMAGEMANAGER->addImage("AreaBg", "Resources/Images/UI/message_area.bmp", 1200,131, MGT); // ��������� ��ܾ��ķ���
	IMAGEMANAGER->addImage("optionSelect", "Resources/Images/UI/optionSelect.bmp", 16,31, MGT); // �ɼǸ޴� ���ý� ��� 


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

#pragma region Object

    IMAGEMANAGER->addImage("��ư", "Resources/Images/Object/buttomE.bmp", 35 * 1.9, 38 * 1.9, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("deosgracias", "Resources/Images/Object/deosgracias.bmp", 1664, 1536, 13, 6, MGT); // 128,256
    IMAGEMANAGER->addFrameImage("stand", "Resources/Images/Object/priedieuStand.bmp", 924, 310, 7, 1, MGT); // 462, 155
    IMAGEMANAGER->addFrameImage("itemObj", "Resources/Images/Object/itemObject.bmp", 260, 91, 10, 1, MGT); // 260,91

#pragma endregion


#pragma region Item

	// Ŭ���θ���ũ ���
	IMAGEMANAGER->addFrameImage("items", "Resources/Images/item/items.bmp", 510*1.9, 510 * 1.9,17,17, MGT); // 510,510->969,969
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
