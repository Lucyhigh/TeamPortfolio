#pragma once
#include "Image.h"

// ����� �̹����� ��������
static Image* _backBuffer = IMAGEMANAGER->addImage("backBuffer", WINSIZE_X, WINSIZE_Y);

class GameNode
{

private:
	HDC _hdc;
	bool _managerinit;

public:

	//HRESULT : �Լ��� ���������� ����Ǿ�����üũ
	// �� ������ �ƴ� ������ ������ �ǹ��ϸ� ���������� ���и� �ǹ�

	virtual	HRESULT init(void);
	virtual	HRESULT init(bool managerInit);
	virtual void release(void);
	virtual void update(void);
	virtual void render(void);

	//����� �̹������    //�����ڼ����� :Get Set
	Image* getBackBuffer(void) { return _backBuffer; }

	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }

	// ! �������ν���
	// LRESULT : �ݹ� �Լ��� ��ȯ������ ���� ���ȴ�.
	// - �޼��� ó���� ��ģ �� os ���� ��ȣ�� �ֱ� ���� ��     ????ã�ƺ���
	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	GameNode() {}
	virtual ~GameNode() {}

};
