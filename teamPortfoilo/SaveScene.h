#pragma once
#include "GameNode.h"
#include "Text.h"
 
enum saveSlotState
{
	NONE, ON, OFF
};
 
struct tagSaveSlot
{
	int num;  
	saveSlotState state;
	float x;  
	float y;
	Image* noneImg;
	Image* onImg;
	Image* offImg;
	float posEndX;
	bool select;  
};

class SaveScene : public GameNode
{
private:

	vector<tagSaveSlot> _vSave;
	vector<tagSaveSlot>::iterator _viSave;
	int _saveIndex;  
	int _tempPoint = 1060;  
	tagOnlyText _saveMenuText[4];

public:
	SaveScene():_saveMenuText
	{
		L"새 게임",
		L"계속",
		L"뒤로",
		L"삭제"
	}
	{}
	~SaveScene() {}


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void selectSaveData(int saveIndex);
	void showSaveData(void);
	void addSaveData(int num);
	void loadSaveData(int num);
};

