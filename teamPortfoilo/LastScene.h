#pragma once
#include "GameNode.h"
#include "PixelCollision.h"
#include "Camera.h"
class LastScene : public GameNode
{
private:
	Camera* _camera;
	Image* _image;
	PixelCollision* _pixel;
	int _count;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	LastScene() {}
	~LastScene() {}
};