#pragma once
#include "GameNode.h"
#include "Animation.h"

#pragma region TitleScene Animation
class AniSceneTitle : public GameNode
{
private:
	Image* _aITitleBg;
	Image* _aITitleMain;
	Image* _aITitleEff;
	Image* _aITitleSelecte;
	Animation* _aMTitleBg;
	Animation* _aMTitleMain;
	Animation* _aMTitleEff;
	Animation* _aMTitleSelecte;

	bool _isAniStart;

public:
	AniSceneTitle() {}
	~AniSceneTitle() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void render(int x, int y);

};
#pragma endregion

#pragma region Item Select Animation
class AniSceneItem : public GameNode
{
private:
	Image* _aIItemSelect;
	Animation* _aMItemSelect;

public:
	AniSceneItem() {}
	~AniSceneItem() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(int x, int y);

};
#pragma endregion

class AniScene : public GameNode
{
private:
	Image* _aITitleBg;
	Animation* _aMTitleBg;

public:
	AniScene() {}
	~AniScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};
