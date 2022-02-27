#pragma once
#include "GameNode.h"
#include "Item.h"

class ItemManager : public GameNode
{
private:
	typedef vector<Item*> vItem;
	typedef vector<Item*>::iterator viItem;

	vItem _vItem;
	viItem _viItem;

public:
	ItemManager() {}
	~ItemManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void setItem(void);
	void removeItem(int arrNum);

	vector<Item*> getMinions(void) { return _vItem; }
};

