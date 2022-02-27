#pragma once
#include "GameNode.h"
#include "ItemManager.h"


class Inventory :public GameNode
{
private:
	ItemManager* _im;

	int _categoryIndex;

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

