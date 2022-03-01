#pragma once
#include "GameNode.h"
#include "ItemManager.h"

#define INVENTEXT 3

class Inventory :public GameNode
{
private:
	ItemManager* _im;

	int _categoryIndex;
	tagOnlyText _InvenTEXT[INVENTEXT];

	int _selection;
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
	}
	{} 
	~Inventory() {}

};

