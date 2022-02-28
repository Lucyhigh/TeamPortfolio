#pragma once
#include "GameNode.h"
#include "Camera.h"
#include "Animation.h"
class PixelCollision : public GameNode
{
private:
  
    Image* _playerIdleImage;
    Image* _playerMoveImage;
	Image* _bgImage;
	Animation* _ani;
	Animation* _ani2;
    //vector<RECT*> _floor;
   // RECT* floor0;
    RECT _rc;
	RECT _cameraRect;
    //ÇÈ¼¿ Ãæµ¹ Å½ÁöÇÒ Y°ª ¼¾¼­
    int _probeY;
	float _speed;
	int _x;
	int _y;
	bool _isWalk;
	bool _isLeft;
public:
    HRESULT init(void);
    void release(void);
    void update(void);
    void render(void);

	int getX();
	int getY();
	void setX(int x);

	float getPlayerPosX();
	void setPlayerPosX(float x);

	void setPlayerPosY(float y);
	RECT getPlayerRect();

	void setCameraRect(RECT rect);

public:
    PixelCollision() {}
    ~PixelCollision() {}
};

