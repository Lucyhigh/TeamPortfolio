#pragma once
#include "GameNode.h"
#include "Item.h"

#define ROSARYMAX 3
#define RELICMAX 0
#define QUESTMAX 1
#define MEACULPAMAX 1
#define BIBLEMAX 1
#define COLLECTIONMAX 1

class ItemManager : public GameNode
{
private:
	typedef vector<Item*> vItem;
	typedef vector<Item*>::iterator viItem;

	vItem _vItem;
	viItem _viItem;

public:
	ItemManager();
	~ItemManager() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void render(int categoryIndex);

	void setItem(void);
	void removeItem(int arrNum);

	vector<Item*> getItem(void) { return _vItem; }
};

