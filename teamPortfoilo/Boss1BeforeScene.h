#pragma once
#include "GameNode.h"
#include "UIScene.h"
#include "Camera.h"
#include "Text.h"
#define TEXTNUM 11
class Boss1BeforeScene : public GameNode
{
private:
	vector<RECT*> _floor;
	Camera* _camera;
	Image* _mapImage;
	Image* _objectImage;
	Image* _symbolImage;
	Image* _breakSymbolImage;
	Image* _SkeletonImage;
	Image* _frameNpcImage;
	tagOnlyText  _text[TEXTNUM];
	RECT* floor0;
	RECT* floor1;  
	RECT* floor2;
	RECT _ObjectRc;
	RECT _SymbolRc;
	RECT _breakSymbolRc;
	RECT _SkeletonRc;
	RECT _npcRc;

	UIScene* _ui;

	float _x, _y;

	int _count;
	int _indexA, _indexB, _indexC, _indexD, _indexE, _indexF;

	int _symbolPosX, _symbolPosY;
	int _symbolCenterX, _symbolCenterY;

	int _breaksymbolPosX, _breaksymbolPosY;

	int _skeletonPosX, _skeletonPosY;
	int _skeletonCenterX, _skeletonCenterY;

	int _npcPosX, _npcPosY;
	int _npcRcCenterX, _npcRcCenterY;

	int _bgAlpha;
	int _alpha;
	int _textAlpha;
	int  _textIndex;

	bool _isBreak, _isBreakS, _isBreakEnd, _isTalk;


	bool _areaTextOn;
	int _areaTextAlpha;

public:
	Boss1BeforeScene() :_text
	{
		L"마음은 비애로 가득하여라, 참회자여.고뇌는 이제 끝을 맺을 것이리라",

		L"나는 데오그라시아스.비탄의 기적이 불러온 업의 화자이며 증인이다.",

		L"너의 침묵이 속죄의 방식이니만큼, 너의 인도가 나의 속죄이니라.",

		L"그대가 찾는 것은 기적과 고통의 요람이 아닌가.",

		L"그 요람은 성하의 의자에 있으리라.",

		L"그 장소는 신성한 금기의 문으로 인해, 우리의 이 땅에서 멀리 떨어진 곳에 있다.",

		L"저 높은 벽 너머에 무엇이 기다리고 있는지는, 그 어떤 현명한 참회자도 알 수 없으니.",

		L"이 가시를 받아 칼자루에 박아넣으시게.",

		L"때가 되면, 그대가 이 칼을 강하게 움켜쥐는 만큼, 가시가 그대를 상처입혀 피흘리게 할 것이네...",

		L"자라나는 가시는 칼 손잡이의, 아버지의 조각상을 점차 얽어갈것이네...",

		L"그것이 벌이든 면죄든, 비통한 기적의 자비를 얻었음을 증명하리니."
	}
	{}
	~Boss1BeforeScene() {}

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};