#pragma once
/*
타이머의 좋고 나쁘고 기준은 고해상도 vs 저해상도
기존에 사용한  API 공용 함수
GetTickCount(); -> 1000 1초
ㄴ 버그있음
GetTickCount64(); ->
ㄴ그래서 이게 나옴
//고성능 타이머는 구백만분의 1초로 됨
*/
/*
Timer
- 시간을 측정하는 함수들은 굉장히 많고 기본적으로 윈도우가 시작된 이후 지난 시간을 Milli Second 단위로 반환
- 보통 타이머를 구현할때 알아둬야 할 개념은 해상도와 클럭

해상도?
-다양한 시간 함수들은 시간을 측정하기 위한 저마다의 tick 계산 로직이 잇다.
	ㄴ 1분을 기준으로 얼마나 많은 프레임으로 나눌 수 있는지를 뜻한다
	ㄴ1분동안 얼마나 많은 tick으로 나눠서 시간의 정확도를 높이느냐에 따라서 고해상도와 저해상도로 나뉜다.

Clock(진동수)
- 타이머에서 애기하는 클럭은 CPU클럭(clock)을 의미한다.
- 클럭 자체는 디지털 회로의 전기적 진동 수이며 Hz로 표기한다.
	ㄴ 1Hz : 1초라는 가정하에 신호(0or1)를 한 번 준다.
								ㄴ 1비트를 한번 옮긴다.
	i5-4690 CPU @ 3.50GHz   3.50 GHz
	ㄴ 1GHz 1기가헤르츠 : 10의 9제곱 -> 10억번
	ㄴ 3GHz 3기가 헤르츠 : 30억번
							ㄴ 1초에 30억개의 비트를 옮길 수 있다.

# 고성능 타이머의 경우 성능 향상 시키기 위해서는 중첩이 필요하다. - cpu의 부담을 메모리로 바꾸는...
	ㄴ 대략 9백만분의 1초까지 측정
- 기본값으로 셋팅하고 사용할 시 백만분의 1초까지 측정 가능

-근데 쓰겠다고 해서 os가 쓸수있는지 여부를 판단함 (거부할수도있음)
ㄴ 체크해서 예외를 줘야함
*/
class Timer
{
private:
	float _timeScale; //경과시간 체크
	float _timeElapsed; // 마지막 시간과 현재시간의 경과값으로 FPS추출 가능
	bool _isHardware; // 고성능 타이멍 지원 여부 확인

	// __int64 == INT64_MAX;
	__int64 _curTime;		//현재 시간
	__int64 _lastTime;			//이전 시간
	__int64 _periodFrequency;	//시간 주기

	unsigned long _frameRate;
	unsigned long _FPSFrameCount;
	float _FPSTimeElapsed;
	float _worldTime;

public:
	HRESULT init(void);
	//현재 시간을 계산해줄;
	void tick(float lockFPS = 0.0f);

	//현재 FPS
	unsigned long getFrameRate(char* str = nullptr) const;
	//마지막 시간과 현재 시간의 경과량
	inline float getElapsedTime(void) const { return _timeElapsed; }
	// 전체 경과 시간
	inline float getWorldTime(void) const { return _worldTime; }
public:
	Timer() {}
	~Timer() {}
};

