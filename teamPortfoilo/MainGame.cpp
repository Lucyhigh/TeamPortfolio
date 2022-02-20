#include "stdafx.h"
#include "MainGame.h"

//	�ŸŴ��� 
// �ؽ�Ʈ������ �Ŵ���
// Ÿ�� �Ŵ���
// �ȼ� �ݸ���
// ���α׷�����

HRESULT MainGame::init(void) //�ʱ�ȭ
{
	GameNode::init(TRUE);

	// �׽�Ʈ ��Ʈ�� 
	floor.push_back(&reference[0]);
	floor.push_back(&reference[1]);

	//�÷��̾
	player = new PlayerCharacter();
	player->init({ 0,0 }, floor);

	mon = new BaseData();
	mon->setCollider(RECT{ 800,350,900,450 });
	monster.push_back(mon);

	collider = new ColliderManager();
	collider->init(player, monster);

	TIMEMANAGER->init();

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();	
}

void MainGame::update(void) // ����
{
	GameNode::update();
	collider->update();
	player->update();
}

void MainGame::render(void) // �׷���
{
	//������ �� ��Ʈ��
	//PatBlt() : �簢�� ������ �귯���� ä��� �Լ�
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	TIMEMANAGER->render(getMemDC());
		
	for (int i = 0; i < monster.size(); i++)
	{ Rectangle(getMemDC(), monster[i]->getCollider().left, monster[i]->getCollider().top, monster[i]->getCollider().right, monster[i]->getCollider().bottom); }
	
	player->render();

	for (int i = 0; i < floor.size(); i++)
	{ Rectangle(getMemDC(), floor[i]->left, floor[i]->top, floor[i]->right, floor[i]->bottom); }
	
	this->getBackBuffer()->render(getHDC()); //������� ������ HDC�� �׸���.
}