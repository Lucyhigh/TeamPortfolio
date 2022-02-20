#pragma once
#include "SingletonBase.h"
#include "Timer.h"
//타이머는 추상팩토리를 쓰는 게 좋지만 일단 이렇게 구현
class TimeManager : public SingletonBase <TimeManager>
{
private:
	Timer* _timer;
public:
	//게임 노드와 상관없이 별개의 객체로 관리하겠다
	//시간은 항상 흘러가는거니까
	//그래서 원랜 추상팩토리가 좋다고 한것
	HRESULT init(void);
	void release(void);
	void update(float lock = 0.0f);
	void render(HDC hdc);

	//전체 시간
	inline float getWorldTime(void) const { return _timer->getWorldTime(); }
	//프레임 경과 시간
	inline float getElapsedTime(void) const { return _timer->getElapsedTime(); }
public:
	TimeManager() {}
	~TimeManager() {}
};

