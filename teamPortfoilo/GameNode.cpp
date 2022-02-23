#include "Stdafx.h"
#include "GameNode.h"

HRESULT GameNode::init(void)
{

	//�Լ��� ���������� ����Ǿ����� �˸��� S_OK ��ȯ
	//Success_ok
	return S_OK;
}

HRESULT GameNode::init(bool managerInit)
{
	_hdc = GetDC(_hWnd);
	_managerinit = managerInit;

	//Ÿ�̸� �ʱ�ȭ
	if (managerInit)
	{
		//�����ϼ���(#include "locale.h") LC_ALL �ѱ��� �ѱ�Ÿ�� ��� �� �������ڴ�~************�����������ϳ��� ī�װ������ �ð�
		setlocale(LC_ALL, "Korean");
		SetTimer(_hWnd, 1, 10, NULL);
		//Ű�Ŵ��� �ʱ�ȭ
		KEYMANAGER->init();
		//���� ��� �ʱ�ȭ
		RND->init();
		//�̹����Ŵ��� �ʱ�ȭ
		IMAGEMANAGER->init();
	
	}

	return S_OK;
}

void GameNode::release(void)
{
	if (_managerinit)
	{
		//Ÿ�̸� ����
		KillTimer(_hWnd, 1);
		//Ű�Ŵ��� �̱��� ����
		KEYMANAGER->releaseSingleton();
		// ������� �̱��� ����
		RND->releaseSingleton();
		IMAGEMANAGER->release();
		IMAGEMANAGER->releaseSingleton();

		//��Ʈ�Ŵ��� �̱��� ����
		FONTMANAGER->releaseSingleton();
	}

	ReleaseDC(_hWnd, _hdc);
}

void GameNode::update(void)
{
	//���ΰ�ħ
	//���۸��� �߰��Ǹ� ����� �ʿ��ϴ�
	InvalidateRect(_hWnd, NULL, FALSE);
}

void GameNode::render(void)
{
}

LRESULT GameNode::MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		//�ڵ�DC
	PAINTSTRUCT ps;	//����Ʈ����ü

	switch (imessage)
	{
	case WM_TIMER:
		this->update();
		break;
	case WM_CREATE:  //������
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		this->render();
		EndPaint(hWnd, &ps);
		break;
	case WM_MOUSEMOVE:
		//20211230 ���콺��ǥ 
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
			//esc������ �Ҹ��� �θ���
			//0224 �����׽�Ʈ�� ���� F11�� ���� 
			//PostMessage(hWnd, WM_DESTROY, 0, 0); 
			break;

		case VK_F11:
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;

		}
		InvalidateRect(hWnd, NULL, false);  // ȭ���� ��� ��¦�Ÿ��ٸ� false �� �����ؾ��� (���� ������������)
		break;

	case WM_DESTROY:    //�Ҹ���
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, imessage, wParam, lParam);
	return LRESULT();
}
