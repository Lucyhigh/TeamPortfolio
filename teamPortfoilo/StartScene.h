#pragma once
#include "GameNode.h"
<<<<<<< HEAD
#include "UIScene.h"

=======
//���� Ÿ��Ʋ�ڸ�
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