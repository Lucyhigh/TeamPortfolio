#pragma once
#include "GameNode.h"
//���� Ÿ��Ʋ�ڸ�
class StartScene : public GameNode
{
private:


public:
	StartScene();
	~StartScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};