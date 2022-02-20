#include "Stdafx.h"
#include "MainGame.h"

//! 전역 변수
//! 인스턴스 : 윈도우 OS가 현재 실행되고 있는 프로그램을 확인하기 위한 값
// 같은 프로그램이면 같은 인스턴스 값을 가진다.
// ㄴ 클래스가 메모리에 실제로 구현된 실체
// ㄴ 실행되고 있는 각각의 프로그램은 모두 각자의 인스턴스를 가진다.
HINSTANCE _hInstance;
//! 윈도우 핸들 : 윈도우창
HWND _hWnd;
POINT _ptMouse ;
//! 윈도우 타이틀
LPTSTR _lpszClass = TEXT("WindowsAPI");
//LPTSTR _lpszClass = (L "WindowsAPI");
//TCHAR* _lpszClass = _T("WindowsAPI"); // _T : 이걸 통해서  TCHAR에 들어오는  유니코드를 처리해주는 매크로  자동


// #함수 전방선언
//! 콜백 함수
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height);

// 20211230_필터정리 후 싱글톤
int centerX;
int centerY;

//20211231
MainGame* _mg;

//! 윈도우 메인 함수
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{	
	_mg = new MainGame(); //20211231

	_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0; //클래스 여분 메모리 (안써이거우리)
	wndClass.cbWndExtra = 0;  //윈도우 여분 메모리 (안써이거우리)
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //백그라운드
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);  //마우스커서
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //아이콘
	wndClass.hInstance = hInstance;  //윈도우를 소유한 식별자 정보
	wndClass.lpfnWndProc = (WNDPROC)WndProc;  //윈도우 프로시저     
	wndClass.lpszClassName = WINNAME;  //클래스이름
	wndClass.lpszMenuName = NULL;  //메뉴이름
	wndClass.style = CS_HREDRAW | CS_VREDRAW;  //윈도우 스타일 (다시 그리기 정보)

	RegisterClass(&wndClass);



#ifdef FULLSCREEN

	//디바이스 모드 구조체(화면 디스플레이 관련 기능)
	DEVMODE dm;

	//ZeroMemory(&dm, sizeof(DEVMODE));
	dm.dmBitsPerPel = 32;		//32비트 트루컬러
	dm.dmPelsWidth = 1980;		//해상도
	dm.dmPelsHeight = 1020;
	dm.dmDisplayFrequency = 60;	//재생빈도

	//Fields: 다양한 디스플레이 정보중 우리가 사용한 정보값만 넘겨주겠다. 티어링 현상과 관련있음
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//화면종료시 자동으로 원래 화면의 해상도로 복구
	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}
	_hWnd = CreateWindow
	(
		WINNAME,
		WINNAME,
		WINSTYLE,
		WINSTART_X,
		WINSTART_Y,
		WINSIZE_X,
		WINSIZE_Y,
		NULL, //확장성을 위해 널		  //부모 윈도우 //GetDesktopWindow() 이걸 많이 줌
		(HMENU)NULL, //형변환은 앞으로 와야함  //메뉴 핸들
		hInstance,   //인스턴스 지정
		NULL //윈도우의 자식 윈도우를 생성하면 지정, 그렇지 않으면 NULL
									  // ㄴ필요에 의해서 사용하지만 지금은 NULL
	);
#else
	_hWnd = CreateWindow
	(
		WINNAME,
		WINNAME,
		WINSTYLE,
		WINSTART_X, 
		WINSTART_Y, 
		WINSIZE_X,
		WINSIZE_Y,
		NULL, //확장성을 위해 널		  //부모 윈도우 //GetDesktopWindow() 이걸 많이 줌
		(HMENU)NULL, //형변환은 앞으로 와야함  //메뉴 핸들
		hInstance,   //인스턴스 지정
		NULL //윈도우의 자식 윈도우를 생성하면 지정, 그렇지 않으면 NULL
									  // ㄴ필요에 의해서 사용하지만 지금은 NULL
	);

	//클라이언트 영역의 사이즈를 정확히 잡아준다

	//UpdateWindow(_hWnd);
#endif 
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
	ShowWindow(_hWnd, nCmdShow);

	// 20211231_ 초기식 추가 
	// 메인게임 클래스 초기화 실패시 종료 ( 메인게임 : init 부분)
	if (FAILED(_mg->init()))
	{
		return 0;  // 값이 이상할 경우 종료해라라는 뜻임
	}


	MSG message; 

	//ZeroMemory(&message, sizeof(message));
	//InvalidateRect 가 있어서 메모리를 수시로 비워줘야함

	//게임용
	/*  get이랑 peek 차이 알아두기
	while (true)
	{
		if (PeekMessage(&message, NULL , 0, 0, PM_REMOVE))  //api는 c++기반
		{
			if (message.message == WM_QUIT)break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	*/

	//일반 프로그래밍
	//2. 메시지루프
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//20211231
	_mg->release();
	//! 윈도우 클래스 등록 해제
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;


}


// API 꽃
//! 윈도우 프로시저 - 기본 구조 중요 ! 잊지말것
LRESULT CALLBACK WndProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, imessage, wParam, lParam); // 20211231_결과: 흰화면에 사각형이 나와야함
}

void setWindowSize(int x, int y, int width, int height)
{
	//클라이언트 사이즈를 잡아줌
	RECT rc = { 0,0,width,height };

	//실제 윈도우 크기 조정
	AdjustWindowRect(&rc, WINSTYLE, false);

	// 얻어온 렉트의 정보로 윈도우 사이즈 셋팅
	SetWindowPos(
		_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE
	);  //ZORDER는 캐릭터나 사물이 겹쳣을때 누가 먼저 보이냐를 나타내는거
}


/*
api 에선  도형이 사용 가능하다
1 순위 ㅁ (사각형) :캐릭터 배경 이다>>>>>>>>>>>>>>>2순위 ㅇ (원): 총알> 3순위 삼각형
*/