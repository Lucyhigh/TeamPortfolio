#pragma once
#include "GameNode.h"

class FieldScene1 :public GameNode
{
private:

public:
	FieldScene1();
	~FieldScene1() {}

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
};

