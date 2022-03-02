#pragma once
#include "GameNode.h"

// 옵션 : 동영상, 사운드 
// 동영상 - 창모드(풀스크린/창), 해상도(기본(1200*675/ 추가2가지..?)
// 사운드 - 전체음량, 배경음량, 효과음량, 음성음량 조정
class OptionScene : public GameNode
{
private:

public:
	OptionScene() {}
	~OptionScene() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

