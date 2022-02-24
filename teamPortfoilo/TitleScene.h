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


// 저장한 데이터가 있으면 On/Off 표시
enum saveSlotState
{ NONE,ON,OFF};

// 저장데이터 - 플레이어가 기도대에서 상호작용 시 데이터 저장 
// ㄴ UI씬에서 저장할 수 있게
struct tagSaveSlot
{
	int num; // 슬롯이미지 순번
	saveSlotState state;
	float x; // 슬롯이미지 좌표 
	float y;
	Image* noneImg;
	Image* onImg;
	Image* offImg;
	float posEndX;
	bool select; // 선택여부
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
	// 저장데이터 : 지역명, 소지포인트, 플레이시간, 게임 진행도 ? 
	vector<tagSaveSlot> _vSave;
//	vector<tagSaveSlot, vector<string>> _vSave;
	vector<tagSaveSlot>::iterator _viSave;
	int _saveIndex;
	int _tempPoint = 1060; // 테스트용 임시 포인트

	
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
