#pragma once
#include "GameNode.h"
<<<<<<< HEAD
#include "ImageClass.h"
#include "AniScene.h"

enum sceneName
{
	ANYBUTTON,TITLE, SAVE, OPTION
};

class TitleScene : public GameNode
{
private :
	ImageClass* _img;
	AniSceneTitle* _ani;
	LPCWSTR script;

	sceneName _titleName;

	RECT _logoRc;

	bool _pushButton;
	int _alpha;
	int _menuIndex;

	// SAVE ------------

	
=======

enum titleName
{
	ANYBUTTON,TITLE
};

class TitleScene :public GameNode
{
private :
	titleName _onTitle;

>>>>>>> origin/SongYeeun-camera
public:
	TitleScene() {}
	~TitleScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
