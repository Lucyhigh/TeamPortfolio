#pragma once
#include "GameNode.h"

class TitleScene :public GameNode
{
private :
public:
	TitleScene() {}
	~TitleScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
