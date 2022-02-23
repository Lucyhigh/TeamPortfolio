#include "stdafx.h"
#include "MainGame.h"
#pragma region include Scene
//UI
<<<<<<< HEAD
=======
#include "ImageClass.h"
>>>>>>> origin/SongYeeun-camera
#include "TitleScene.h"
#include "OptionScene.h"
//Stage
#include "StartScene.h"
#include "BossScene1.h"
#include "BossScene2.h"
#include "FieldScene1.h"
#include "EndingScene.h"
#pragma endregion 


HRESULT MainGame::init(void) //�ʱ�ȭ
{
	GameNode::init(TRUE);
	TIMEMANAGER->init();
	_collider = new ColliderManager();

	//�÷��̾
	_player = new PlayerCharacter();
	GAMEMANAGER->setPlayer(_player);
<<<<<<< HEAD
	GAMEMANAGER->setMonster(_monster);
	_collider = new ColliderManager();

	
=======

	ImageClass temp = ImageClass();
	temp.init();
>>>>>>> origin/SongYeeun-camera

#pragma region SceneManager

	// UI : title, system(), inventory(skill, item, equip ...) 
<<<<<<< HEAD
	SCENEMANAGER->addScene("Title", new TitleScene);
	SCENEMANAGER->addScene("Option", new OptionScene);
=======
	//SCENEMANAGER->addScene("Title", new TitleScene);
	//SCENEMANAGER->addScene("Option", new OptionScene);

>>>>>>> origin/SongYeeun-camera

	// Stage1
	SCENEMANAGER->addScene("Start", new StartScene);
	SCENEMANAGER->addScene("Boss1", new BossScene1);
	
	// Stage2
	SCENEMANAGER->addScene("Boss2", new BossScene2);
	SCENEMANAGER->addScene("Field1", new FieldScene1);
	SCENEMANAGER->addScene("Ending", new EndingScene);

	
#pragma endregion 
	// �׽�Ʈ�� ��ü����
<<<<<<< HEAD
	SCENEMANAGER->changeScene("Title");
=======
	SCENEMANAGER->changeScene("Boss1");
>>>>>>> origin/SongYeeun-camera

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	// �̹���Ŭ���� ������ �ʿ��Ѱ�?
<<<<<<< HEAD
	SCENEMANAGER->release();
=======
>>>>>>> origin/SongYeeun-camera
}

void MainGame::update(void) // ����
{
	_collider->update();
	SCENEMANAGER->update();
	GameNode::update();

	SCENEMANAGER->update();

}

void MainGame::render(void) // �׷���
{
	//������ �� ��Ʈ��
	//PatBlt() : �簢�� ������ �귯���� ä��� �Լ�
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	TIMEMANAGER->render(getMemDC());
<<<<<<< HEAD
	
	

	for (int i = 0; i < _monster.size(); i++) { _monster[i]->ObjectRender(); }
	_player->ObjectRender();

	for (int i = 0; i < _floor.size(); i++)
	{
		Rectangle(getMemDC(), _floor[i]->left, _floor[i]->top, _floor[i]->right, _floor[i]->bottom);
	}
	
	char str[254];
	sprintf_s(str, "%d", GAMEMANAGER->getPlayer()->getHp(BaseEnum::STATE));
	TextOut(getMemDC(), 1000, 10, str, strlen(str));

	// �� �� �̹��� ��� ��
	SCENEMANAGER->render();


=======
	// �� �� �̹��� ��� ��
	SCENEMANAGER->render();
>>>>>>> origin/SongYeeun-camera
	this->getBackBuffer()->render(getHDC()); //������� ������ HDC�� �׸���.
}