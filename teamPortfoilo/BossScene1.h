#pragma once
#include "GameNode.h"
#include "BossWarden.h"
#include "BossIsadora.h"
#include "KnifeMonster.h"
#include "ColliderManager.h"
#include "Camera.h"
#include "BossUI.h"

class BossScene1 : public GameNode
{
private:
	ColliderManager* _collider;
	vector<BaseData*> _monster;
	vector<RECT*> _floor;

    Camera* _camera;
    Image* _image;
	BossWarden* boss;
	RECT* floor0;
	RECT* floor1;
	RECT* floor2;

	BossUI* _bossHp;

public:
    BossScene1() {}
    ~BossScene1() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

