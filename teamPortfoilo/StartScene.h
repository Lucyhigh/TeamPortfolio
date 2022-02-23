#pragma once
#include "GameNode.h"
<<<<<<< HEAD
#include "UIScene.h"

=======
//상희 타이틀자리
>>>>>>> origin/SongYeeun-camera
class StartScene : public GameNode
{
private:

<<<<<<< HEAD
	UIScene* _ui;

=======
>>>>>>> origin/SongYeeun-camera

public:
	StartScene();
	~StartScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};