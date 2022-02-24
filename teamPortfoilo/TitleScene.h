#pragma once
#include "GameNode.h"
#include "AniScene.h"
#include "Text.h"

#define OPTIONMENU 6

#pragma region enum struct ...

enum sceneName
{
	ANYBUTTON,TITLE, SAVE, OPTION
};

// ������ �����Ͱ� ������ On/Off ǥ��
enum saveSlotState
{ NONE,ON,OFF};

// ���嵥���� - �÷��̾ �⵵�뿡�� ��ȣ�ۿ� �� ������ ���� 
// �� UI������ ������ �� �ְ�
struct tagSaveSlot
{
	int num; // �����̹��� ����
	saveSlotState state;
	float x; // �����̹��� ��ǥ 
	float y;
	Image* noneImg;
	Image* onImg;
	Image* offImg;
	float posEndX;
	bool select; // ���ÿ���
};

struct tagOptionSlot
{
	int num; // �����̹��� ����
	float x; // �����̹��� ��ǥ 
	float y;
	Image* onImg;
	bool select; // ���ÿ���
};

#pragma endregion

class TitleScene : public GameNode
{
private :

	sceneName _titleName;
	// ANYBUTTON --------------------------------------------------------
	RECT _logoRc;
	bool _pushButton;
	int _alpha;
	
	// TITLE -------------------------------------------------------------
	AniSceneTitle* _ani;
	int _menuIndex; // ����, �ɼ�, ������ 

	// SAVE --------------------------------------------------------------
			// ���嵥���� : ������, ��������Ʈ, �÷��̽ð�, ���� ���൵ ? 
	vector<tagSaveSlot> _vSave;
//	vector<tagSaveSlot, vector<string>> _vSave; // ������� �����͸� ���� �� �ְ� ������ �� 
	vector<tagSaveSlot>::iterator _viSave;
	int _saveIndex; // ���̺꽽�� 1, 2, 3
	int _tempPoint = 1060; // �׽�Ʈ�� �ӽ� ����Ʈ
	tagOnlyText _saveMenuText[3];
	
	// OPTION ------------------------------------------------------------
	vector<tagOptionSlot> _vOption;
	vector<tagOptionSlot>::iterator _viOption;
	int _optinIndex; // ������, �Ҹ�, ���
	tagOnlyText _optionText[OPTIONMENU];

public:
	TitleScene() : _saveMenuText
	{
		L"�� ����",
		L"���",
		L"�ڷ�"
	},
		_optionText // �ӽ� �޴� ���
	{
		L"�ɼ�", // �޴����� (�ɼ�, ����, ������, ���� ��
		L"����", 
		L"������", 
		L"����",
		L"����", // ����޴� : ���� 
		L"�ڷ�",
	}{}

	~TitleScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// save
	void selectSaveData(int saveIndex);
	void showSaveData(void);
	void addSaveData(int num);
	void loadSaveData(int num);

	// option
	void selectOption(int optionIndex);
	void showOption(void);
};
