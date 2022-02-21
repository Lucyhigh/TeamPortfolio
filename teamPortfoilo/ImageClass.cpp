#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
	// �̹����� ���� ���⿡ ���� 
	// IMAGEMANAGER->addImage();
	// Ű���� ��������! (��������)

#pragma region PlayerImage
	IMAGEMANAGER->addFrameImage("������", "Resources/Images/Player/p_idle.bmp", 1664, 146, 13, 2, MGT);
	IMAGEMANAGER->addFrameImage("�����̵�", "Resources/Images/Player/p_move.bmp", 1106, 140, 14, 2, MGT);
#pragma endregion


#pragma region BossImage

#pragma endregion


#pragma region FieldMonsterImage

#pragma endregion


#pragma region UI Scene 
	IMAGEMANAGER->addImage("AnyButton", "Resources/Images/BackGround/UI/anyButtonBg.bmp", 1200, 675);

	IMAGEMANAGER->addFrameImage("�޴�", "Resources/Images/cornObject/menu.bmp", 272, 360, 2, 1, MGT);
	IMAGEMANAGER->addFrameImage("�޴�â", "Resources/Images/cornObject/menuDisplay.bmp", 3600, 675, 3, 1, MGT);

	IMAGEMANAGER->addImage("���� �޾�����", "Resources/Images/BackGround/StoreWeaponTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("���� �⵵��", "Resources/Images/BackGround/StoreBibleTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("���� ����", "Resources/Images/BackGround/StoreRosaryTap.bmp", 1200, 675);

	IMAGEMANAGER->addImage("�κ� �޾�����", "Resources/Images/BackGround/InventoryWeaponTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("�κ� �⵵��", "Resources/Images/BackGround/InventoryBibleTap.bmp", 1200, 675);
	IMAGEMANAGER->addImage("�κ� ����", "Resources/Images/BackGround/InventoryRosaryTap.bmp", 1200, 675);

	// �ִϸ��̼� �̹��� 
	IMAGEMANAGER->addImage("������", "Resources/Images/Object/Elephant.bmp", 660, 268, true, RGB(255, 0, 255));

#pragma endregion



#pragma region Stage Scene
	IMAGEMANAGER->addImage("��1���", "Resources/Images/BackGround/bg1.bmp", 1200, 675);
	IMAGEMANAGER->addImage("��2���", "Resources/Images/BackGround/bg2.bmp", 1200, 675);
	IMAGEMANAGER->addImage("��3���", "Resources/Images/BackGround/bg3.bmp", 1200, 675);

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




#pragma endregion

	return S_OK;
}

ImageClass::ImageClass()
{
}

ImageClass::~ImageClass()
{
}
