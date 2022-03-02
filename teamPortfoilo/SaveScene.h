#pragma once
#include "GameNode.h"
#include "Text.h"


// 저장한 데이터가 있으면 On/Off 표시
enum saveSlotState
{
	NONE, ON, OFF
};

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


class SaveScene : public GameNode
{
private:

	// 저장데이터 : 지역명, 소지포인트, 플레이시간, 게임 진행도 ? 
	vector<tagSaveSlot> _vSave;
	//	vector<tagSaveSlot, vector<string>> _vSave; // 입출력의 데이터를 얻어올 수 있게 수정할 것 
	vector<tagSaveSlot>::iterator _viSave;
	int _saveIndex; // 세이브슬롯 1, 2, 3
	int _tempPoint = 1060; // 테스트용 임시 포인트
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

	// save
	void selectSaveData(int saveIndex);
	void showSaveData(void);
	void addSaveData(int num);
	void loadSaveData(int num);


};

