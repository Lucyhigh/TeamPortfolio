#pragma once
#include "GameNode.h"
#include "UIScene.h"
#include "Camera.h"
#include "Text.h"

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
    tagOnlyText  _text[11];
    RECT* floor0;
    RECT* floor1;
    RECT* floor2;
    RECT _ObjectRc;
    RECT _SymbolRc;
    RECT _breakSymbolRc;
    RECT _SkeletonRc;


    UIScene* _ui;

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
    Boss1BeforeScene() :_text
    {
        L"������ ��ַ� �����Ͽ���, ��ȸ�ڿ�.����� ���� ���� ���� ���̸���",

        L"���� �����׶�þƽ�.��ź�� ������ �ҷ��� ���� ȭ���̸� �����̴�.",

        L"���� ħ���� ������ ����̴ϸ�ŭ, ���� �ε��� ���� �����̴϶�.",

        L"�״밡 ã�� ���� ������ ������ ����� �ƴѰ�.",

        L"�� ����� ������ ���ڿ� ��������.",

        L"�� ��Ҵ� �ż��� �ݱ��� ������ ����, �츮�� �� ������ �ָ� ������ ���� �ִ�.",

        L"�� ���� �� �ʸӿ� ������ ��ٸ��� �ִ�����, �� � ������ ��ȸ�ڵ� �� �� ������.",

        L"�� ���ø� �޾� Į�ڷ翡 �ھƳ����ð�.",

        L"���� �Ǹ�, �״밡 �� Į�� ���ϰ� ������� ��ŭ, ���ð� �״븦 ��ó���� ���긮�� �� ���̳�...",

        L"�ڶ󳪴� ���ô� Į ��������, �ƹ����� �������� ���� ������̳�...",

        L"�װ��� ���̵� ���˵�, ������ ������ �ں� ������� �����ϸ���."
    }
    {}
    ~Boss1BeforeScene() {}

public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
};