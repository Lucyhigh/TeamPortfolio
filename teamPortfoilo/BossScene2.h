#pragma once
#include "BossIsadora.h"
#include "GameNode.h"
#include "BossUI.h"

class BossScene2 : public GameNode
{
private:
	Image* _image;
	ColliderManager* _collider;
	Camera* _camera;
	BossIsadora* isdora;

	vector<RECT*> _floor;
	POINT _cameraPos;
	
	BossUI* _bossHp;

public:
	BossScene2();
	~BossScene2() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

