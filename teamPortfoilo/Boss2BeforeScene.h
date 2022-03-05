#pragma once
#include "GameNode.h"
#include "UIScene.h"
#include "Camera.h"

class Boss2BeforeScene : public GameNode
{
private:
	vector<RECT*> _floor;
	Camera* _camera;
	Image* _image;

	RECT* floor0;
	RECT* floor1;
	RECT* floor2;

	float _x, _y;

	int _count;

public:
	Boss2BeforeScene() {}
	~Boss2BeforeScene() {}

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};