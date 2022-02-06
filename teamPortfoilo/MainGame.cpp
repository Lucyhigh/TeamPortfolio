#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void) //�ʱ�ȭ
{
	GameNode::init(TRUE);
	IMAGEMANAGER->addImage("���� ��", "Resources/Images/BackGround/ShootingBG.bmp", WINSIZE_X,WINSIZE_Y);

	_rocket = new Rocket;
	_rocket->init();
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();	
	_rocket->release();
}

void MainGame::update(void) // ����
{
	GameNode::update();
	_rocket->update();
}

void MainGame::render(void) // �׷���
{
	//������ �� ��Ʈ��
	//PatBlt() : �簢�� ������ �귯���� ä��� �Լ�
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	IMAGEMANAGER->findImage("���� ��")->render(getMemDC());
	_rocket->render();

	this->getBackBuffer()->render(getHDC()); //������� ������ HDC�� �׸���.
}