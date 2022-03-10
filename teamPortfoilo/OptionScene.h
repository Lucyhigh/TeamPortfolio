#pragma once
#include "GameNode.h"

#define TITLEMENU 7
#define INMENU 10

struct tagOptionSlot
{
	int num; 
	float x; 
	float y;
	Image* onImg;
	bool select;
};

class OptionScene : public GameNode
{
private:
	bool _isTitleMenu;

	vector<tagOptionSlot> _vTOption;
	vector<tagOptionSlot>::iterator _viTOption;
	int _TOptinIndex; 
	tagOnlyText _TitleText[TITLEMENU];

	vector<tagOptionSlot> _vIOption;
	vector<tagOptionSlot>::iterator _viIOption;
	int _IOptinIndex; 
	tagOnlyText _InGameText[INMENU];

public:
	OptionScene() :
		_TitleText
	{	
		L"옵션",
		L"게임",
		L"접근성",
		L"동영상",
		L"사운드",
		L"수락",
		L"뒤로",
	},
	 _InGameText
	{
		L"옵션",
		L"게임",
		L"접근성",
		L"동영상",
		L"사운드",
		L"게임 플레이 팁",
		L"메인 메뉴로 나가기",
		L"게임 계속하기",
		L"수락",
		L"뒤로",
	}
	{}
	~OptionScene() {}

	HRESULT init(void);
	HRESULT init(bool isTitleMenu);
	void release(void);
	void update(void);
	void render(void);

	void setIsTitleOption(bool state) {  _isTitleMenu = state; }
	void selectTOption(int optionIndex);
	void selectIOption(int optionIndex);
	void showTOption(void);
	void showIOption(void);
};

