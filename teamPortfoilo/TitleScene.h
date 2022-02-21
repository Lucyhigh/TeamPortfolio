#pragma once
#include "GameNode.h"

enum titleName
{
	ANYBUTTON,TITLE
};

class TitleScene :public GameNode
{
private :
	titleName _onTitle;

public:
	TitleScene() {}
	~TitleScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
