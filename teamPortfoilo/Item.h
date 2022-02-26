#pragma once

enum class Category
{
	// 인벤토리 순서
	NONE, ROSARY, RELIC, QUEST, MEACULPA, BIBLE, SKILL, COLLECTION
};

class Item
{
public:
	Item() {}
	~Item() {}

	int index;
	Category type;
	string name;
	string script;
	int imageNum;


	void setItemData();

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