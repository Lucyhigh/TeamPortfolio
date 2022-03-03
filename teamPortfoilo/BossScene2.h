#pragma once
#include "BossIsadora.h"
#include "GameNode.h"

class BossScene2 : public GameNode
{
private:
	Image* _backGround;
	ColliderManager* _collider;
	Camera* _camera;
	BossIsadora* isdora;

	vector<RECT*> _floor;
	POINT _cameraPos;
	

public:
	BossScene2();
	~BossScene2() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

