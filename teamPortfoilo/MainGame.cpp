#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void) //�ʱ�ȭ
{
	GameNode::init(TRUE);
	TIMEMANAGER->init();
	// �׽�Ʈ ��Ʈ�� 
	_floor.push_back(&reference[0]);

	//�÷��̾
	player = new PlayerCharacter();
	player->init({ 0,600 }, _floor);
	_player = player;
	mon = new BossWarden();
	mon->init({ 0,0 }, _floor);
	mon->setCollider(RECT{ 800,350,900,450 });
	_monster.push_back(mon);

	GAMEMANAGER->setPlayer(_player);
	GAMEMANAGER->setMonster(_monster);
	_collider = new ColliderManager();
	return S_OK;
}

void MainGame::release(void)
{

	GameNode::release();
}

void MainGame::update(void) // ����
{
	_player->ObjectUpdate();
	for (int i = 0; i < _monster.size(); i++) { _monster[i]->ObjectUpdate(); }
	_collider->update();

	GameNode::update();
}

void MainGame::render(void) // �׷���
{
	//������ �� ��Ʈ��
	//PatBlt() : �簢�� ������ �귯���� ä��� �Լ�
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	for (int i = 0; i < _monster.size(); i++) { _monster[i]->ObjectRender(); }
	_player->ObjectRender();

	for (int i = 0; i < _floor.size(); i++)
	{
		Rectangle(getMemDC(), _floor[i]->left, _floor[i]->top, _floor[i]->right, _floor[i]->bottom);
	}

	this->getBackBuffer()->render(getHDC()); //������� ������ HDC�� �׸���.
}