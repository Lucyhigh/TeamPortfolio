#pragma once
#include "GameNode.h"
#include "PixelCollision.h"
#include "Camera.h"
#include "Text.h"
class OpeningScene : public GameNode
{
private:
	Camera* _camera;
    tagOnlyText _text[6];
    Image* _image;
    PixelCollision* _pixel;

    int _count;
    int _bgAlpha;
    int _alpha;
    int _textAlpha;
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);
public:
    OpeningScene():_text
    {

    }
    {}
    ~OpeningScene() {}

};

