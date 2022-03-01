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

public:
	LastScene() {}
	~LastScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};