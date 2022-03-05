#pragma once
#include "GameNode.h"

#define TITLEMENU 6
#define INMENU 9


struct tagOptionSlot
{
	int num; // �����̹��� ����
	float x; // �����̹��� ��ǥ 
	float y;
	Image* onImg;
	bool select; // ���ÿ���
};

// �ɼ� : ������, ���� 
// ������ - â���(Ǯ��ũ��/â), �ػ�(�⺻(1200*675/ �߰�2����..?)
// ���� - ��ü����, �������, ȿ������, �������� ����
class OptionSceneTITLE : public GameNode
{
private:
	bool _isTitleMenu; // Ÿ��Ʋ���� �޴� ����?

	// Title option ------------------------------------------------------------
	vector<tagOptionSlot> _vTOption;
	vector<tagOptionSlot>::iterator _viTOption;
	int _TOptinIndex; // ������, �Ҹ�, ���
	tagOnlyText _TitleText[TITLEMENU];

public:
	OptionSceneTITLE() :
		_TitleText
	{	
		L"����",
		L"���ټ�",
		L"������",
		L"����",
		L"����",
		L"�ڷ�",
	}
	{}
	~OptionSceneTITLE() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// option : T - Title / I - InGame
	void setIsTitleOption(bool state) {  _isTitleMenu = state; } // �ܺο��� �ɼ����� ���� �� 
	void selectOption(int optionIndex);
	void showOption(void);


};


class OptionScene : public GameNode
{
private:

	// InGame option ------------------------------------------------------------
	vector<tagOptionSlot> _vIOption;
	vector<tagOptionSlot>::iterator _viIOption;
	int _IOptinIndex; // ������, �Ҹ�, ���
	tagOnlyText _InGameText[INMENU];

public:
	OptionScene() :
	_InGameText
	{
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
	void release(void);
	void update(void);
	void render(void);

	// option : T - Title / I - InGame
	void selectIOption(int optionIndex);
	void showIOption(void);

};

