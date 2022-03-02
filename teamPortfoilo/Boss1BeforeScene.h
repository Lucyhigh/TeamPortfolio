#pragma once
#include "GameNode.h"
#include "Camera.h"

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

	RECT* floor0;
    RECT* floor1;
    RECT* floor2;
    RECT _ObjectRc;
	RECT _SymbolRc;
	RECT _breakSymbolRc;
	RECT _SkeletonRc;


    float _x, _y;
    int _count;
    int _indexA, _indexB, _indexC, _indexD;

	int _symbolPosX, _symbolPosY;
	int _symbolCenterX, _symbolCenterY;

	int _breaksymbolPosX, _breaksymbolPosY;

	int _skeletonPosX, _skeletonPosY;
	int _skeletonCenterX, _skeletonCenterY;

	bool _isBreak, _isBreakS, _isBreakEnd;

public:
    Boss1BeforeScene() {}
    ~Boss1BeforeScene() {}

public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
};