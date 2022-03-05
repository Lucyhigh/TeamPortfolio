#pragma once
#include "GameNode.h"

#define TITLEMENU 6
#define INMENU 9


struct tagOptionSlot
{
	int num; // 슬롯이미지 순번
	float x; // 슬롯이미지 좌표 
	float y;
	Image* onImg;
	bool select; // 선택여부
};

// 옵션 : 동영상, 사운드 
// 동영상 - 창모드(풀스크린/창), 해상도(기본(1200*675/ 추가2가지..?)
// 사운드 - 전체음량, 배경음량, 효과음량, 음성음량 조정
class OptionSceneTITLE : public GameNode
{
private:
	bool _isTitleMenu; // 타이틀에서 메뉴 진입?

	// Title option ------------------------------------------------------------
	vector<tagOptionSlot> _vTOption;
	vector<tagOptionSlot>::iterator _viTOption;
	int _TOptinIndex; // 동영상, 소리, 등등
	tagOnlyText _TitleText[TITLEMENU];

public:
	OptionSceneTITLE() :
		_TitleText
	{	
		L"게임",
		L"접근성",
		L"동영상",
		L"사운드",
		L"수락",
		L"뒤로",
	}
	{}
	~OptionSceneTITLE() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	// option : T - Title / I - InGame
	void setIsTitleOption(bool state) {  _isTitleMenu = state; } // 외부에서 옵션으로 진입 시 
	void selectOption(int optionIndex);
	void showOption(void);


};


class OptionScene : public GameNode
{
private:

	// InGame option ------------------------------------------------------------
	vector<tagOptionSlot> _vIOption;
	vector<tagOptionSlot>::iterator _viIOption;
	int _IOptinIndex; // 동영상, 소리, 등등
	tagOnlyText _InGameText[INMENU];

public:
	OptionScene() :
	_InGameText
	{
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
	void release(void);
	void update(void);
	void render(void);

	// option : T - Title / I - InGame
	void selectIOption(int optionIndex);
	void showIOption(void);

};

