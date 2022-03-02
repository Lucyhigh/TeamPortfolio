#pragma once
#include "GameNode.h"
#include "AniScene.h"

class TitleScene : public GameNode
{
private :

	// Sequence--------------------------------------------------------
	bool _anyButton;
	bool _title;

	// ANYBUTTON --------------------------------------------------------
	RECT _logoRc;
	bool _pushButton;
	int _alpha;
	
	// TITLE -------------------------------------------------------------
	AniSceneTitle* _ani;
	int _menuIndex; // 순례, 옵션, 나가기 

	
public:
	TitleScene() {}
	~TitleScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);


};
