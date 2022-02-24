#pragma once
#include "GameNode.h"
#include "AniScene.h"

// O , X , Button TEXT COLOR
#define OTEXT RGB(254, 211, 17)
#define XTEXT RGB(134, 118, 53)
#define BTEXT RGB(136,127,77)

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

class TitleScene : public GameNode
{
private :
	AniSceneTitle* _ani;
	LPCWSTR script;

	sceneName _titleName;

	RECT _logoRc;

	bool _pushButton;
	int _alpha;
	int _menuIndex;

	// SAVE ------------
	// ���嵥���� : ������, ��������Ʈ, �÷��̽ð�, ���� ���൵ ? 
	vector<tagSaveSlot> _vSave;
//	vector<tagSaveSlot, vector<string>> _vSave;
	vector<tagSaveSlot>::iterator _viSave;
	int _saveIndex;
	int _tempPoint = 1060; // �׽�Ʈ�� �ӽ� ����Ʈ

	
public:
	TitleScene() {}
	~TitleScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	void selectSaveData(int saveIndex);
	void showSaveData(void);
	void addSaveData(int num);
	void loadSaveData(int num);
};
