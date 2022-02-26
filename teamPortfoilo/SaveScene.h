#pragma once
#include "GameNode.h"
#include "Text.h"


// ������ �����Ͱ� ������ On/Off ǥ��
enum saveSlotState
{
	NONE, ON, OFF
};

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


class SaveScene : public GameNode
{
private:

	// ���嵥���� : ������, ��������Ʈ, �÷��̽ð�, ���� ���൵ ? 
	vector<tagSaveSlot> _vSave;
	//	vector<tagSaveSlot, vector<string>> _vSave; // ������� �����͸� ���� �� �ְ� ������ �� 
	vector<tagSaveSlot>::iterator _viSave;
	int _saveIndex; // ���̺꽽�� 1, 2, 3
	int _tempPoint = 1060; // �׽�Ʈ�� �ӽ� ����Ʈ
	tagOnlyText _saveMenuText[4];

	
public:
	SaveScene():_saveMenuText
	{
		L"�� ����",
		L"���",
		L"�ڷ�",
		L"����"
	}
	{}
	~SaveScene() {}


	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// save
	void selectSaveData(int saveIndex);
	void showSaveData(void);
	void addSaveData(int num);
	void loadSaveData(int num);


};

