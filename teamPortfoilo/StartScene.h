#pragma once
#include "GameNode.h"
//상희 타이틀자리
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