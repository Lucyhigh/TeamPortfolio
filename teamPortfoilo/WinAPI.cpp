#include "Stdafx.h"
#include "MainGame.h"

//! ���� ����
//! �ν��Ͻ� : ������ OS�� ���� ����ǰ� �ִ� ���α׷��� Ȯ���ϱ� ���� ��
// ���� ���α׷��̸� ���� �ν��Ͻ� ���� ������.
// �� Ŭ������ �޸𸮿� ������ ������ ��ü
// �� ����ǰ� �ִ� ������ ���α׷��� ��� ������ �ν��Ͻ��� ������.
HINSTANCE _hInstance;
//! ������ �ڵ� : ������â
HWND _hWnd;
POINT _ptMouse ;
//! ������ Ÿ��Ʋ
LPTSTR _lpszClass = TEXT("WindowsAPI");
//LPTSTR _lpszClass = (L "WindowsAPI");
//TCHAR* _lpszClass = _T("WindowsAPI"); // _T : �̰� ���ؼ�  TCHAR�� ������  �����ڵ带 ó�����ִ� ��ũ��  �ڵ�


// #�Լ� ���漱��
//! �ݹ� �Լ�
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

void setWindowSize(int x, int y, int width, int height);

// 20211230_�������� �� �̱���
int centerX;
int centerY;

//20211231
MainGame* _mg;

//! ������ ���� �Լ�
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{	
	_mg = new MainGame(); //20211231

	_hInstance = hInstance;

	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0; //Ŭ���� ���� �޸� (�Ƚ��̰ſ츮)
	wndClass.cbWndExtra = 0;  //������ ���� �޸� (�Ƚ��̰ſ츮)
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);  //��׶���
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);  //���콺Ŀ��
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);  //������
	wndClass.hInstance = hInstance;  //�����츦 ������ �ĺ��� ����
	wndClass.lpfnWndProc = (WNDPROC)WndProc;  //������ ���ν���     
	wndClass.lpszClassName = WINNAME;  //Ŭ�����̸�
	wndClass.lpszMenuName = NULL;  //�޴��̸�
	wndClass.style = CS_HREDRAW | CS_VREDRAW;  //������ ��Ÿ�� (�ٽ� �׸��� ����)

	RegisterClass(&wndClass);



#ifdef FULLSCREEN

	//����̽� ��� ����ü(ȭ�� ���÷��� ���� ���)
	DEVMODE dm;

	//ZeroMemory(&dm, sizeof(DEVMODE));
	dm.dmBitsPerPel = 32;		//32��Ʈ Ʈ���÷�
	dm.dmPelsWidth = 1980;		//�ػ�
	dm.dmPelsHeight = 1020;
	dm.dmDisplayFrequency = 60;	//�����

	//Fields: �پ��� ���÷��� ������ �츮�� ����� �������� �Ѱ��ְڴ�. Ƽ� ����� ��������
	dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

	//ȭ������� �ڵ����� ���� ȭ���� �ػ󵵷� ����
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
		NULL, //Ȯ�强�� ���� ��		  //�θ� ������ //GetDesktopWindow() �̰� ���� ��
		(HMENU)NULL, //����ȯ�� ������ �;���  //�޴� �ڵ�
		hInstance,   //�ν��Ͻ� ����
		NULL //�������� �ڽ� �����츦 �����ϸ� ����, �׷��� ������ NULL
									  // ���ʿ信 ���ؼ� ��������� ������ NULL
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
		NULL, //Ȯ�强�� ���� ��		  //�θ� ������ //GetDesktopWindow() �̰� ���� ��
		(HMENU)NULL, //����ȯ�� ������ �;���  //�޴� �ڵ�
		hInstance,   //�ν��Ͻ� ����
		NULL //�������� �ڽ� �����츦 �����ϸ� ����, �׷��� ������ NULL
									  // ���ʿ信 ���ؼ� ��������� ������ NULL
	);

	//Ŭ���̾�Ʈ ������ ����� ��Ȯ�� ����ش�

	//UpdateWindow(_hWnd);
#endif 
	setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);
	ShowWindow(_hWnd, nCmdShow);

	// 20211231_ �ʱ�� �߰� 
	// ���ΰ��� Ŭ���� �ʱ�ȭ ���н� ���� ( ���ΰ��� : init �κ�)
	if (FAILED(_mg->init()))
	{
		return 0;  // ���� �̻��� ��� �����ض��� ����
	}


	MSG message; 

	//ZeroMemory(&message, sizeof(message));
	//InvalidateRect �� �־ �޸𸮸� ���÷� ��������

	//���ӿ�
	/*  get�̶� peek ���� �˾Ƶα�
	while (true)
	{
		if (PeekMessage(&message, NULL , 0, 0, PM_REMOVE))  //api�� c++���
		{
			if (message.message == WM_QUIT)break;
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
	*/

	//�Ϲ� ���α׷���
	//2. �޽�������
	while (GetMessage(&message, 0, 0, 0))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	//20211231
	_mg->release();
	//! ������ Ŭ���� ��� ����
	UnregisterClass(WINNAME, hInstance);

	return message.wParam;


}


// API ��
//! ������ ���ν��� - �⺻ ���� �߿� ! ��������
LRESULT CALLBACK WndProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam)
{
	return _mg->MainProc(hWnd, imessage, wParam, lParam); // 20211231_���: ��ȭ�鿡 �簢���� ���;���
}

void setWindowSize(int x, int y, int width, int height)
{
	//Ŭ���̾�Ʈ ����� �����
	RECT rc = { 0,0,width,height };

	//���� ������ ũ�� ����
	AdjustWindowRect(&rc, WINSTYLE, false);

	// ���� ��Ʈ�� ������ ������ ������ ����
	SetWindowPos(
		_hWnd, NULL, x, y,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		SWP_NOZORDER | SWP_NOMOVE
	);  //ZORDER�� ĳ���ͳ� �繰�� �㫉���� ���� ���� ���̳ĸ� ��Ÿ���°�
}


/*
api ����  ������ ��� �����ϴ�
1 ���� �� (�簢��) :ĳ���� ��� �̴�>>>>>>>>>>>>>>>2���� �� (��): �Ѿ�> 3���� �ﰢ��
*/