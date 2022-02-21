#pragma once
#include "GameNode.h"
#include "Animation.h"

class AniScene : public GameNode
{
private:

	// aI : Animation Image
	Image* _aITitleBg;
	Image* _aITitleMain;
	Image* _aITitleEff;

	// aM : Animation
	Animation* _aMTitleBg;
	Animation* _aMTitleMain;
	Animation* _aMTitleEff;

public:
	AniScene() {}
	~AniScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

};



