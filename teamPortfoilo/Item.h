#pragma once
#include "GameNode.h"

enum class Category
{
	// 인벤토리 순서
	NONE, 
	ROSARY, 
	RELIC, 
	QUEST, 
	MEACULPA, 
	BIBLE, 
	
	SKILL, COLLECTION
};

enum class ItemState
{
	// 미습득, 습득, 선택, 메아쿨파 미선택
	NONE, HAVE, SELECT, MEACULPANONE
};

/*
struct tagItemInfo
{
	int index; // 아이템 순번. 나중에 조건문에 넣을 대상
	int imageNum; // Y 프레임
	Category type;
	ItemState state; // 기본 NONE
	float posX; // 슬롯 위치 - 반복문으로 인벤토리에 자리잡기 -> 스위치문으로 카테고리에 따라 자리 바꾸기
	float posY;
	string name;	// 파일입출력
	string script;  // 파일입출력
	bool equip; // true면 각 카테고리의 장비 위치에도 이미지 노출 , 스킬이면 해금
};
*/

class Item : public GameNode
{
public:
	Image* _img; // 이미지 파일에서 클리핑 할 것. 

	int _index; // 아이템 순번. 나중에 조건문에 넣을 대상 
	Category _category; // Y 프레임 
	ItemState _state; // 기본 NONE
	float _posX; // 슬롯 위치 - 반복문으로 인벤토리에 자리잡기 -> 스위치문으로 카테고리에 따라 자리 바꾸기 
	float _posY;
	//	int _frameXNum; // 이미지 시트에서 이미지 위치 
	//	int _frameYNum;
	string _name;	// 파일입출력 
	string _script;  // 파일입출력 
	bool _equip; // true면 각 카테고리의 장비 위치에도 이미지 노출 , 스킬이면 해금 
	int _hp; // 장착여부에 따라 스탯 조정
	int _mp;
	int _att;
	int _dff;

	
public:
	Item() {}
	~Item() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void draw(void);
	void animation(void);

	void setItemData(int index,	Category category, ItemState state,	float posX, float posY,
	string name,string script,bool equip,int hp, int mp, int att, int dff );

	// 아이템 습득상태 변경

	// 아이템 선택여부 변경

	// 


};

/*
X 최대 17
--아이템 슬롯 Y1 
셀렉이면->에니메이션
아이템 설명칸에는 2번,
인벤토리 빈 아이템칸은 3번
인벤토리 선택 아이템칸은 7번

-------------
수집품 Y2~Y5
메아쿨파 Y7
기도문 Y8
유물 Y10~Y14
퀘스트아이템 Y15~Y18
*/