#pragma once
#include "GameNode.h"
#include "Text.h"

class EndingScene :public GameNode
{
private:
    tagOnlyText _text[4];
    int _textAlpha;
    int _alpha;
    int _bgAlpha;
    float _timer;
    int _textIndex;
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
public:
    EndingScene() :
        _text
    {
        L"�˾��� ���ε� �Ȱ��� ���� ���� ����̴�, �״뿡�Ե� ��������������.",
        L"������ �ں�ο� ����̾��� �״��, ������ �ں�� ���� �ְ� �Ǿ���.",
        L"�״�� ���� ��Ҹ��� ������ ����, ����� ������ �� �ΰ��� �Ǿ���ȴ�.",
        L"�״��� ��ȸ�� ������. �ƾ� ������ ��ַ� �����Ͽ���, ��ȸ�ڿ�."
    }
    {}
    ~EndingScene() {}
};

