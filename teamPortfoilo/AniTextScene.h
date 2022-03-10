#pragma once
#include "GameNode.h"
#include "Text.h"

#define TEXTNUM 3

enum class AREA
{ 	NONE, ALBERO };

enum class NPC
{NONE,GREENCORN};

class AniTextScene : public GameNode
{
private:

	tagText _text[3];

	int _count; 
	int _moveCount;
	int _nameIndex;
	int _textIndex;
	int _alpha;
	NPC _npc;


public:

	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	
	AniTextScene() :
		_text
	{
		L" ",L"��ȸ�ڿ�, �����ض�",
		L" ",L"���� �� ���̺��.",
		L" ",L" �������."
	}
	{}

	~AniTextScene() {}



};

