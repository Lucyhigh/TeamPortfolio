#pragma once
#include "GameNode.h"
#include "ImageClass.h"
#include "AniScene.h"

enum titleName
{
	ANYBUTTON,TITLE
};

class TitleScene :public GameNode
{
private :

	ImageClass* _img;
	LPCWSTR script;

	titleName _onTitle;

	RECT _logoRc;

	bool _pushButton;
	int _alpha;
	
	AniScene* _ani;

public:
	TitleScene() {}
	~TitleScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
