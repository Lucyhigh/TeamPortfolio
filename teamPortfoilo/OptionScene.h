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
		L"�ɼ�",
		L"����",
		L"���ټ�",
		L"������",
		L"����",
		L"����",
		L"�ڷ�",
	},
	 _InGameText
	{
		L"�ɼ�",
		L"����",
		L"���ټ�",
		L"������",
		L"����",
		L"���� �÷��� ��",
		L"���� �޴��� ������",
		L"���� ����ϱ�",
		L"����",
		L"�ڷ�",
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

