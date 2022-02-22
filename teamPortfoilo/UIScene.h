#pragma once
#include "GameNode.h"
#include "Characters.h"// 플레이어 클래스 
#include "ProgressBar.h"
#include "ImageClass.h"


struct tagPotion
{
	int PotionIndex; // 이미지 position x
	int healing; // 회복수치
	bool use; // 사용여부 
};
class UIScene : public GameNode
{
private:
	ImageClass* _img; 

	BaseData* _pData; // 플레이어 클래스 데이터
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

