#pragma once
#include "GameNode.h"
#include "Characters.h"// �÷��̾� Ŭ���� 
#include "ProgressBar.h"
#include "ImageClass.h"


struct tagPotion
{
	int PotionIndex; // �̹��� position x
	int healing; // ȸ����ġ
	bool use; // ��뿩�� 
};
class UIScene : public GameNode
{
private:
	ImageClass* _img; 

	BaseData* _pData; // �÷��̾� Ŭ���� ������
	ProgressBar* _hpBar;
	float _hp;
	float _mp;

	int potionLv;
	int potionIdx;
	tagPotion potion;

public:
	UIScene() {}
	~UIScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

