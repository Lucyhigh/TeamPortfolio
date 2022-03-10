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
		L" ",L"참회자여, 수행해라",
		L" ",L"뭐지 이 사이비는.",
		L" ",L" 수고수고."
	}
	{}

	~AniTextScene() {}



};

