#pragma once
#include "GameNode.h"
#include "ItemManager.h"

#define INVENTEXT 3
#define ITEMTEXT 8
#define SCRIPT_MAX_LENGTH 20

class Inventory :public GameNode
{
private:

	AniSceneItem* _ani; // 아이템 선택시 테두리 애니메이션

	ItemManager* _im;

	int _categoryIndex;
	int _cateMax;
	tagOnlyText _InvenTEXT[INVENTEXT];
	

	tagText rosary[ROSARYMAX+5];
	tagText relic[3];
	tagText quest[3];
	tagText meaculpa[3];
	tagText bible[3];
	tagText skill[3];
	tagText collection[3];


	int _selection;

	int _cateItemMax;

	float _x, _y;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


	Inventory() : _InvenTEXT
	{
		L"장착",
		L"해제",
		L"지식",
	},
	rosary
	{
		L"비둘기 뼈",L"구멍이 뚫린 새의 두개골. 부서지기 쉬우나 참회자의 방어력을 약간 올려준다.",
		L"성스러운 화장의 불씨",L"화장하고 남은 불씨. 참회자의 방어력을 올려준다.",
		L"은포도",L"은으로 만든 포도알. 참회자의 방어력을 상당량 올려준다.",
		L" ",L" ",
				L" ",L" ",
						L" ",L" ",
								L" ",L" ",
										L" ",L" "

	},
	relic{	L" ",L" ",
			L" ",L" ",
			L" ",L" " },
	quest{
		L"가시",L"데오그라시아스의 작은 선물. 칼의 턱 아래. 뒤틀린 자의 조각상에 박혀있다.",
		L"진정한 매장의 끈",L"땋은 밧줄끈에 참된 매장 훈장의 문장이 새겨진 낡은 청동 메달이 걸려있다.",
		L" ",L" ",
	},
	meaculpa{ L"오일의 심장",L"참회자의 힘을 증가시켜 공격력을 약간 올려준다." ,
	L" ",L" ",
	L" ",L" " },
	bible{ L"빛의 데블라",L"참회자의 자리에 천상의 빛을 소환한다."
	L" ",L" ",
	L" ",L" " },
	skill{ L" ",L" ",
		  L" ",L" ",
		  L" ",L" " },
	collection{ L"양조장 Zicher의 경추뼈",L"카타드라의 첫 번째 창 연단 위에서 발견한 경추뼈"
	L" ",L" ",
	L" ",L" " }
	{}
	~Inventory() {}

	// 아이템상태(습득,선택) / 장착여부 / 아이템 이미지 위치 
							// 현재 카테고리 , 현재 선택중인 슬롯 
	bool checkSelect(int invenCategoryIndex, int selectionNum); // 선택했는지?
	//void setItem(ItemState state);
	//void setItem(float posX, float posY);
	void setEquip(bool state, float x, float y);
	void setSelect() { _selection = 0; }

};

