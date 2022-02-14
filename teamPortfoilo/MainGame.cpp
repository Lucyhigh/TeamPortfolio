#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void) //�ʱ�ȭ
{
	GameNode::init(TRUE);
	IMAGEMANAGER->addImage("���� ��", "Resources/Images/BackGround/ShootingBG.bmp", WINSIZE_X,WINSIZE_Y);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();	
}

void MainGame::update(void) // ����
{
	GameNode::update();
}

void MainGame::render(void) // �׷���
{
	//������ �� ��Ʈ��
	//PatBlt() : �簢�� ������ �귯���� ä��� �Լ�
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	IMAGEMANAGER->findImage("���� ��")->render(getMemDC());
    char str[128];
    wsprintf(str, "���� ������ ��������");
    TextOut(getMemDC(), 100, 100, str, strlen(str));

	char str1[128];
	wsprintf(str1, "���� ����... �� �� �� �־� :D ");
	TextOut(getMemDC(), 140, 150, str1, strlen(str1));

	wsprintf(str, "�� ����� ��ū�� �ȴ�...");
	TextOut(getMemDC(), 230, 200, str, strlen(str));

	wsprintf(str, "���� ��");
	TextOut(getMemDC(), 320, 250, str, strlen(str));

    wsprintf(str, "�����Ϸ��� ���� ����� �����̴�");
    TextOut(getMemDC(), 350, 300, str, strlen(str));

	wsprintf(str, "����� ���� ���� �÷��� ���� ������.. �������ʹ� ��������");
	TextOut(getMemDC(), 400, 350, str, strlen(str));

	this->getBackBuffer()->render(getHDC()); //������� ������ HDC�� �׸���.
}