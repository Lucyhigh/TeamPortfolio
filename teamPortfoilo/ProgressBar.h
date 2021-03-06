#pragma once
#include "GameNode.h"
class ProgressBar : public GameNode
{
private:
	Image* _progressBarUp;
	Image* _progressBarDown;

	int _x;
	int _y;
	float _width;

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
	HRESULT init(float hp, float mp);
	HRESULT init(float hp); 
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


class ProgressBarBoss : public GameNode
{
private:

	int _x;
	int _y;

	RECT _rc;
	POINT _hpPos;
	float _hpMaxWidth;
	float _hpWidth;
	float _hpWidthB;

	Image* _hpBarBg;
	Image* _hpBarCover;
	Image* _hpBarTop;
	Image* _hpBarbottom;

public:
	HRESULT init(float hp); 
	void release(void);
	void update(void);
	void render(void);

	void setGauge(float currentScore, float maxScore);
	void setBossHpGauge(float hpScore);
	POINT getHpMpBar();

	void setX(int x) { _x = x; }
	void setY(int y) { _y = y; }
public:
	ProgressBarBoss() {}
	virtual ~ProgressBarBoss() {}
	
	float getHpWidth() { return _hpWidth; }
};


