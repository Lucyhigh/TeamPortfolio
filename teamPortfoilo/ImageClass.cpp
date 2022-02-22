#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
	// �̹����� ���� ���⿡ ���� 
	// IMAGEMANAGER->addImage();
	// Ű���� ��������! (��������)
	// �÷��̾� / ���� / �ʵ� / UI / Item / �ִϸ��̼� ��

#pragma region PlayerImage
	IMAGEMANAGER->addFrameImage("������", "Resources/Images/Player/p_idle.bmp", 1664, 146, 13, 2, MGT);
	IMAGEMANAGER->addFrameImage("�����̵�", "Resources/Images/Player/p_move.bmp", 1106, 140, 14, 2, MGT);
#pragma endregion

#pragma region BossImage

#pragma endregion

#pragma region FieldMonsterImage

#pragma endregion

#pragma region Stage Scene
	// Stage 1
	IMAGEMANAGER->addImage("StartBG", "Resources/Images/BackGround/bg1.bmp", 1200, 675);

	// Stage 2
	IMAGEMANAGER->addImage("Field1BG", "Resources/Images/BackGround/bg2.bmp", 1200, 675);
	IMAGEMANAGER->addImage("Boss2BG", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

#pragma endregion

#pragma region Stage Object NPC
	IMAGEMANAGER->addFrameImage("alter", "Resources/Images/Object/UI/menuNoButton.bmp", 272,304, MGT);

#pragma endregion

#pragma region UI Scene 
	// BG : Resources/Images/BackGround/UI
	// BG : 640*360 (*1.875)-> 1200 * 640

	// Title ANYBUTTON
	IMAGEMANAGER->addImage("AnyButtonBg", "Resources/Images/BackGround/UI/anyButtonBg.bmp", 1200, 675, MGT);
	IMAGEMANAGER->addImage("AnyButtonLogo", "Resources/Images/BackGround/UI/anyButtonLogo2.bmp", 720,308, MGT);
	
	// Title TITLE
	IMAGEMANAGER->addFrameImage("titleBg", "Resources/Images/BackGround/UI/titleBg.bmp", 18000,675,15,1, MGT);
	IMAGEMANAGER->addFrameImage("titleMain", "Resources/Images/BackGround/UI/titleMain.bmp", 16800, 675, 14, 1, MGT);
	IMAGEMANAGER->addFrameImage("titleEffect", "Resources/Images/BackGround/UI/titleEffect.bmp", 52800, 675, 44, 1, MGT);
	IMAGEMANAGER->addFrameImage("titleMenu", "Resources/Images/UI/titleMenu.bmp", 273, 117, 3, 1, MGT);

	// UI BackGround
	IMAGEMANAGER->addFrameImage("�޴�â", "Resources/Images/BackGround/UI/menuDisplay.bmp", 3600, 675, 3, 1, MGT);
	IMAGEMANAGER->addImage("�κ� �޾�����", "Resources/Images/BackGround/UI/InventoryWeaponTap.bmp", 1200, 675, MGT);
	IMAGEMANAGER->addImage("�κ� �⵵��", "Resources/Images/BackGround/UI/InventoryBibleTap.bmp", 1200, 675, MGT);
	IMAGEMANAGER->addImage("�κ� ����", "Resources/Images/BackGround/UI/InventoryRosaryTap.bmp", 1200, 675, MGT);

#pragma endregion

#pragma region UI Object
	// etc : Resources/Images/UI/������ �Ǵ� �̹���
	IMAGEMANAGER->addFrameImage("titleSelecte", "Resources/Images/UI/alliedCherub.bmp", 280, 210,4,3, MGT);


#pragma endregion


#pragma region Item
	// Resources/Images/item

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
