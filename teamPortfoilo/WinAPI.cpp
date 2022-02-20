#include "stdafx.h"
#include "MainGame.h"

HINSTANCE _hInstance;
HWND _hWnd;
POINT _ptMouse = { 0, 0 };
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height);

MainGame *_mg;

int APIENTRY WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR    lpCmdLine,
	int  nCmdShow)

{
	_mg = new MainGame();

	_hInstance = hInstance;
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hInstance = hInstance;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.lpszClassName = WINNAME;
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndClass);


#ifdef FULLSCREEN
	//디바이스 모드 구조체 ( 화면 디스플레이 관련 기능)
	DEVMODE dm;

	//ZeroMemory(&dm, sizeof(DEVMODE));

	dm.dmBitsPerPel = 32;
	dm.dmPelsWidth = 1980;
	dm.dmPelsHeight = 1020;
	dm.dmDisplayFrequency = 60;

	//필드: 다양한 디스플레이 정보중 우리가 사용한 정보값만 넘겨주겠다.
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//화면이 종료되면 자동으로 원래 화면의 해상도로 복구

	if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		ChangeDisplaySettings(&dm, 0);
	}

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
		NULL,
		(HMENU)NULL,
		hInstance,
		NULL
	);


#endif

	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
	ShowWindow(_hWnd, nCmdShow);

	if (FAILED(_mg->init()))
	{
		return 0;
	}

	MSG message;
	//게임용
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
		else
		{
			TIMEMANAGER->update(60.0f);
			_mg->update();
			_mg->render();
		}
	}

	//일반용
	//while (GetMessage(&message, 0, 0, 0))
	//{
	//	TranslateMessage(&message);
	//	DispatchMessage(&message);
	//}

	_mg->release();
	////! 윈도우 클래스 등록 해제
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;
}

//LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
//{
//
//	HDC hdc;
//	PAINTSTRUCT ps;
//
//	static POINT pt = { 0, 0 };
//	char strPT[128];
//	switch (iMessage)
//	{
//	case WM_CREATE://생성자
//		break;
//
//	case WM_PAINT:
//		hdc = BeginPaint(hWnd, &ps);
//		EndPaint(hWnd, &ps);
//		break;
//
//	case WM_MOUSEMOVE:
//		break;
//
//	case WM_LBUTTONDOWN:		 //마우스 왼쪽 버튼
//
//		break;
//
//	case WM_RBUTTONDOWN:		//마우스 오른쪽 버튼
//		break;
//
//	case WM_KEYDOWN:					//키보드 키가 눌렷을때 메세지 발생
//		switch (wParam)
//		{
//		case VK_LEFT:
//			break;
//		case VK_RIGHT:
//			break;
//		case VK_UP:
//			break;
//		case VK_DOWN:
//			break;
//		case VK_ESCAPE:						//ESC키를 누르면 종료
//			PostMessage(hWnd, WM_DESTROY, 0, 0);
//			break;
//		}
//		break;
//	case WM_DESTROY:			//소멸자
//		PostQuitMessage(0);
//		return 0;
//	}
//	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
//}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
	RECT rc = { 0, 0, width, height };

	AdjustWindowRect(&rc, WINSTYLE, false);

	SetWindowPos(_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE);
}