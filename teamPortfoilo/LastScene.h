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
	//�����׶�ý� ��� �ѹ� �� ���� �Ŀ��� ���Ŀ� 4����� �ݺ�
	LastScene() :_text
	{
		L"�״�� ������ �濡���� ������� �ع���״�.",

		L"������ ������ ���, ������ ������",

		L"�ູ�� �ο� ��Ʋ���鼭 ������ ��ź�ϰ� �����ϴ� �ƹ����� �̸����� ������� �ǿ� Ȳ���� ���� ����.",

		L"�������� ��Ȳ������ ������ ������ �Ը����� ���� ������ ������ ��, �� ����� ���� ����⿡ �ִ�.",

		L"�׸��� ����, �������� ������ ������ �״븦 ��ٸ��� �ִ�.",

		L"�㳪, ������ �״��� �� ���� ���忡 �󸶳� ������������ �״븸�� �ƴ� ���̴�."
	}
	{}
	~LastScene() {}
};