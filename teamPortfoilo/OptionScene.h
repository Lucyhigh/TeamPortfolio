#pragma once
#include "GameNode.h"

// �ɼ� : ������, ���� 
// ������ - â���(Ǯ��ũ��/â), �ػ�(�⺻(1200*675/ �߰�2����..?)
// ���� - ��ü����, �������, ȿ������, �������� ����
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

