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
	wsprintf(str, "���� ����... �� �� �� �־� :D ");
	TextOut(getMemDC(), 140, 150, str, strlen(str));

	wsprintf(str, "�� ����� ��ū�� �ȴ�...");
	TextOut(getMemDC(), 230, 200, str, strlen(str));

	wsprintf(str, "���� ��");
	TextOut(getMemDC(), 320, 250, str, strlen(str));

    wsprintf(str, "�����Ϸ��� ���� ����� �����̴�");
    TextOut(getMemDC(), 350, 300, str, strlen(str));

	wsprintf(str, "����� ���� ���� �÷��� ���� ���� �Ф� ");
	TextOut(getMemDC(), 400, 350, str, strlen(str));

	wsprintf(str, "�ʴ븸 ���� Ȯ���߾...");
	TextOut(getMemDC(), 450, 400, str, strlen(str));

	wsprintf(str, "�� ����� �ʹ� ��ư��޴�...");
	TextOut(getMemDC(), 550, 450, str, strlen(str));

    wsprintf(str, "�׷��� ������ �ȴ�");
    TextOut(getMemDC(), 700, 100, str, strlen(str));

	wsprintf(str, "���� ������ ���� �繰�Կ� ���� �ߵ��� ����");
	TextOut(getMemDC(), 650, 150, str, strlen(str));

	wsprintf(str, "�ű⿡ �ִ� ��Ģ���ٴ� �� ������ �������ΰ� ���׿�");
	TextOut(getMemDC(), 650, 200, str, strlen(str));

	wsprintf(str, "�� �ϴ� ���ǽ� ��û�޾�");
	TextOut(getMemDC(), 550, 250, str, strlen(str));

    wsprintf(str, "�Ǽ��� ���� ����ϴ�");
    TextOut(getMemDC(), 450, 280, str, strlen(str));

	wsprintf(str, "ġŲ�԰�ʹ�....");
	TextOut(getMemDC(), 220, 380, str, strlen(str));

	wsprintf(str, "���ø� ������ �޽���...");
	TextOut(getMemDC(), 140, 450, str, strlen(str));


	this->getBackBuffer()->render(getHDC()); //������� ������ HDC�� �׸���.
}