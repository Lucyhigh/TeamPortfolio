#include "stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerInit = managerInit;

	if (managerInit)
	{
		// 로케일 설정(#include "locale.h)
		setlocale(LC_ALL, "Korean");

		// 타이머 초기화
		SetTimer(_hWnd, 1, 10, NULL);

		// 키매니저 초기화
		KEYMANAGER->init();

		// 랜덤펑션 초기화
		RND->init();

		// 이미지매니저 초기화
		IMAGEMANAGER->init();

		//임시 사운드 매니저 초기화
		TEMPSOUNDMANAGER->init();
		//타임 매니저 초기화
		TIMEMANAGER->init();
		//텍스트 데이터 매니저 초기화
		TEXTDATAMANAGER->init();
		//씬 매니저 초기화
		SCENEMANAGER->init();

		// PLAYER->init();
	}

	return S_OK;
}

void GameNode::release(void)
{
	if (_managerInit)
	{
		// 타이머 해제
		KillTimer(_hWnd, 1);

		// 키매니저 싱글톤 해제
		KEYMANAGER->releaseSingleton();

		// 랜덤펑션 싱글톤 해제
		RND->releaseSingleton();

		// 이미지매니저 해제, 싱글톤 해제
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		//폰트매니저 싱글톤해제
		FONTMANAGER->releaseSingleton();

		//타임매니저 헤제, 싱글톤 해제
		TIMEMANAGER->release();
		TIMEMANAGER->releaseSingleton();

		//타임매니저 헤제, 싱글톤 해제
		TEXTDATAMANAGER->release();
		TEXTDATAMANAGER->releaseSingleton();
		//씬 매니저 헤제, 싱글톤 해제
		SCENEMANAGER->release();
		SCENEMANAGER->releaseSingleton();

		//PLAYER->release();
		//PLAYER->releaseSingleton();
	}
	// DC 해제
	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	//InvalidateRect(_hWnd, NULL, FALSE);
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_TIMER:
		this->update();
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;

	case WM_MOUSEMOVE:
		_ptMouse.x = LOWORD(lParam);
		_ptMouse.y = HIWORD(lParam);
		break;

	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			//PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}