#pragma once
#include "GameNode.h"
#include "AniScene.h"

class TitleScene : public GameNode
{
private :
	bool _anyButton;
	bool _title;

	RECT _logoRc;
	bool _pushButton;
	int _alpha;
	
	AniSceneTitle* _ani;
	int _menuIndex;  
	
public:
	TitleScene() {}
	~TitleScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
