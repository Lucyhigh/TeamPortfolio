#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{

	//함수가 성공적으로 실행되었음을 알리는 S_OK 변환
	//Success_ok
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerinit = managerInit;

	//타이머 초기화
	if (managerInit)
	{
		//로케일설정(#include "locale.h") LC_ALL 한국꺼 한국타임 등등 다 가져오겠다~************면접질문마니나옴 카테고리라고함 시간
		setlocale(LC_ALL, "Korean");
		SetTimer(_hWnd, 1, 10, NULL);
		//키매니저 초기화
		KEYMANAGER->init();
		//랜덤 펑션 초기화
		RND->init();
		//이미지매니저 초기화
		IMAGEMANAGER->init();
	
	}

	return S_OK;
}

void GameNode::release(void)
{
	if (_managerinit)
	{
		//타이머 해제
		KillTimer(_hWnd, 1);
		//키매니저 싱글톤 해제
		KEYMANAGER->releaseSingleton();
		// 랜덤펑션 싱글톤 해제
		RND->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		//폰트매니저 싱글톤 해제
		FONTMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	//새로고침
	//버퍼링이 추가되면 고민이 필요하다
	InvalidateRect(_hWnd, NULL, FALSE);
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		//핸들DC
	PAINTSTRUCT ps;	//페인트구조체

	switch (imessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_CREATE:  //생성자
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		//20211230 마우스좌표 
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			break;

		case VK_RIGHT:
			break;

		case VK_UP:
			break;

		case VK_DOWN:
			break;

		case VK_ESCAPE:
			//esc누르면 소멸자 부르기
			//0224 게임테스트를 위해 F11로 변경 
			//PostMessage(hWnd, WM_DESTROY, 0, 0); 
			break;

		case VK_F11:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;

		}
		InvalidateRect(hWnd, NULL, false);  // 화면이 계속 반짝거린다면 false 로 수정해야함 (지금 고쳐진상태임)
		break;

	case WM_DESTROY:    //소멸자
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, imessage, wParam, lParam);
	return LRESULT();
}
