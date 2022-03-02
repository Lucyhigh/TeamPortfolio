#pragma once
#include "GameNode.h"
#include "Text.h"

class EndingScene :public GameNode
{
private:
    tagOnlyText _text[4];
    float _textAlpha;
    float _timer;
    int _textIndex;
    int _alpha;
    int _textBufferCnt;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
public:
    EndingScene() :
        _text
        {
            L"죄업도 죄인도 똑같이 삼켜 가는 잿더미는, 그대에게도 인정사정없었다.",
            L"기적의 자비로운 모습이었던 그대는, 기적의 자비로 남아 있게 되었다.",
            L"그대는 이제 목소리도 의지도 없이, 허망한 무명의 한 인간이 되어버렸다.",
            L"그대의 참회는 끝났다. 아아 마음이 비애로 가득하여라, 참회자여."
        }
    {}
	~EndingScene() {}

};

