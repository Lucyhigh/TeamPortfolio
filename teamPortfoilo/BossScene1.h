#pragma once
#include "GameNode.h"
<<<<<<< HEAD
=======
#include "BossWarden.h"
#include "Camera.h"
>>>>>>> origin/SongYeeun-camera

class BossScene1 : public GameNode
{
private:
<<<<<<< HEAD


public:
	BossScene1();
	~BossScene1() {}
=======
	vector<BaseData*> _monster;
	vector<RECT*> _floor;
    Camera* _camera;
    Image* _image;
	BossWarden* boss;
	RECT* floor0;
	RECT* floor1;
	RECT* floor2;
public:
	BossScene1();
	~BossScene1();
>>>>>>> origin/SongYeeun-camera

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

