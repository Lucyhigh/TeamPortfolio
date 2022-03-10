#pragma once
#include "GameNode.h"
#include "Camera.h"
#include "Animation.h"
class PixelCollision : public GameNode
{
private:
	Image* _playerIdleImage;
	Image* _playerMoveImage;
	Image* _playerIdleImageL;
	Image* _playerMoveImageL;
	Image* _playerWakeUpImage;
	Image* _bgImage;
	Animation* _ani;
	Animation* _ani2;
	Animation* _ani3;
	Animation* _ani4;
	Animation* _ani5;
	RECT _rc;
	RECT _cameraRect;

	int _probeY;
	float _speed;
	int _x;
	int _y;
	int _count;
	bool _isWalk;
	bool _isLeft;
	bool _isWakeUp;
public:
	HRESULT init(float x, float y, char* image);
	void release(void);
	void update(char* image);
	void render(void);

	int getX();
	int getY();
	void setX(int x);

	bool getWakeUp();
    void setWakeUp(bool state);
	float getPlayerPosX();
	void setPlayerPosX(float x);

	void setPlayerPosY(float y);
	RECT getPlayerRect();

	void setCameraRect(RECT rect);
public:
	PixelCollision() {}
	~PixelCollision() {}
};
