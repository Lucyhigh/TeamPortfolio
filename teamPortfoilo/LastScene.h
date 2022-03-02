#pragma once
#include "GameNode.h"
#include "PixelCollision.h"
#include "Camera.h"
#include "Text.h"
class LastScene : public GameNode
{
private:
	Camera* _camera;
    tagOnlyText _text[6];
	Image* _image;
	PixelCollision* _pixel;
	int _count;
    
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