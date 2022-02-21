#pragma once
#include "GameNode.h"
#include "Animation.h"

class AniScene : public GameNode
{
private:
	Image* _aniImg;
	Animation* _animationA;

public:
	AniScene() {}
	~AniScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};

