#pragma once
#include "GameNode.h"
#include "PixelCollision.h"
#include "Camera.h"
#include "Text.h"

#define TEXTNUM 6
class LastScene : public GameNode
{
private:
	Camera* _camera;
	tagOnlyText _text[TEXTNUM];
	Image* _image;
	PixelCollision* _pixel;
	Image* _frameNpcImage;
	RECT _npcRc;

	float _x, _y;
	int _count;
	int _bgAlpha;
	int _textAlpha;
	int _textIndex;
	int _indexCount;

	int _npcRcCenterX, _npcRcCenterY;
	int _npcPosX, _npcPosY;
	int _indexA, _indexB;

	bool _isTalk;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

public:
	//데오그라시스 대사 한번 다 뱉은 후에는 이후에 4번대사 반복
	LastScene() :_text
	{
		L"그대는 지나온 길에서의 고통들을 해방시켰다.",

		L"비통한 기적의 요람, 최후의 성유물",

		L"축복에 싸여 뒤틀리면서 조용히 한탄하고 슬퍼하는 아버지의 이마에서 새어나오는 피와 황금을 담은 성배.",

		L"성유물은 교황성하의 기적과 고통의 입맞춤을 받은 뒤집힌 옥좌의 옆, 이 잿더미 산의 꼭대기에 있다.",

		L"그리고 지금, 기적과의 마지막 교분이 그대를 기다리고 있다.",

		L"허나, 기적이 그대의 죄 많은 심장에 얼마나 스며들었는지는 그대만이 아는 것이다."
	}
	{}
	~LastScene() {}
};