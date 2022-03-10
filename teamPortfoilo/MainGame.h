#pragma once
#include "GameNode.h"

class MainGame : public GameNode
{
private:
	PlayerCharacter* _player;
	UIScene* _ui;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	MainGame() {}
	~MainGame() {}
};
/*
�̵�Ű�Դϴ�.

AŰ ,DŰ    �¿� �̵�
SHIFTŰ     �����̵�
SPACE BAR  ����
KŰ         ����
EŰ, KŰ    ��ȣ�ۿ�
IŰ �κ��丮 (�κ��丮�� �� �� QŰ, EŰ �κ��丮 �¿��̵�)

*/