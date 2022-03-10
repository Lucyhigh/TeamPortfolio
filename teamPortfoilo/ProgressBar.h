#pragma once
#include "GameNode.h"
class ProgressBar : public GameNode
{
private:
	Image* _progressBarUp;
	Image* _progressBarDown;

//	RECT _rc;
	int _x;
	int _y;
	float _width;

	// ���⼭���� �߰� - �÷��̾� �����Ϳ� ���� �ʿ�
	RECT _rc;
	POINT _hpPos;
	POINT _mpPos;
	float _hpMaxWidth;
	float _mpMaxWidth;
	float _hpWidth;
	float _mpWidth;

	Image* _hpBarBg;
	Image* _hpBarCover;
	Image* _hpBar;
	Image* _mpBar; 
	Image* _mpFullBar;
	Image* _mpFullBarEffect;

public:
	HRESULT init(float hp, float mp); // player
	HRESULT init(float hp); // boss
	void release(void);
	void update(void);
	void render(void);

	void setGauge(float currentScore, float maxScore);
	void setPlayerHpGauge(float hpScore);
	void setPlayerMpGauge(float mpScore);
	POINT getHpMpBar();

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
public:
	ProgressBar() {}
	virtual ~ProgressBar() {}
};

