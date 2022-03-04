#include "Stdafx.h"
#include "BossIsadora.h"
#include "FirePillar.h"

void BossIsadora::clearSmash(int num)
{
	smash[num].first.top = smash[num].first.bottom;
}

BossIsadora::BossIsadora()
{ 
	ObjectInit = bind(&BossIsadora::init, this, std::placeholders::_1, std::placeholders::_2);
	ObjectrRelease = bind(&BossIsadora::release, this);
	ObjectUpdate = bind(&BossIsadora::update, this);
	ObjectRender = bind(&BossIsadora::render, this);
	_hp[BaseEnum::STATE] = 1;
}

BossIsadora::~BossIsadora() { }

HRESULT BossIsadora::init(POINT point, vector<RECT*>floor)
{
	_state = UnitState::END;

	_pattenFunc =
	{
		{ UnitState::IDLE ,std::bind(&BossIsadora::_pattenIdle,this) },
		{ UnitState::TRUNATTACK ,std::bind(&BossIsadora::_pattenTurnAttack,this) },
		{ UnitState::FIREPILLARATTACK_0, std::bind(&BossIsadora::_pattenFirePollarAttack0,this) },
		{ UnitState::FIREPILLARATTACK_1, std::bind(&BossIsadora::_pattenFirePollarAttack1,this) },
		{ UnitState::START, std::bind(&BossIsadora::_pattenStart,this) },
		{ UnitState::DIE, std::bind(&BossIsadora::_pattenDie,this) }
	};

	_Collider[BaseEnum::UNIT] = RectMakeCenter(point.x, point.y, 70, 100);
	stateFloor = *floor[0];

	_pillar = new FirePillar();
	_pillar->init({stateFloor.right/2,stateFloor.top}, this);
	pillarDelly = true;
	_isLeft = 1;

	_state = UnitState::START;

	return S_OK;
}

void BossIsadora::release(void)
{
	_pillar->release();
}

void BossIsadora::update(void)
{
	if (_pattenAni != nullptr && TIMEMANAGER->getElapsedTime() >= 0.0f)
	{
		_pattenAni->frameUpdate(TIMEMANAGER->getElapsedTime());
	}

	if (_isHit != 0)
	{
		_hp[BaseEnum::STATE] -= _isHit;
		_isHit = 0;
	}

	if (_hp[BaseEnum::STATE] <= 0 && _state != UnitState::DIE)
	{
		_state = UnitState::END;
	}

	_inputSide();

	if (_state == UnitState::END) { _inputPatten(); }
	_inputAnimation();
	_inputImageXY();
	_pattenFunc[_state]();
	_inputEffect();
	_pillar->update();
}

void BossIsadora::render(void)
{

	_pillar->render();

	float left = _Collider[BaseEnum::UNIT].left - GAMEMANAGER->getPlayer()->getCamareRect().left;
	float top = _Collider[BaseEnum::UNIT].top - GAMEMANAGER->getPlayer()->getCamareRect().top;
	float right = _Collider[BaseEnum::UNIT].right - GAMEMANAGER->getPlayer()->getCamareRect().left;
	float bottom = _Collider[BaseEnum::UNIT].bottom - GAMEMANAGER->getPlayer()->getCamareRect().top;

	for (int i = 0; i < _effect.size(); i++)
	{
		_effect[i].first.aniRender(getMemDC(), _effect[i].first.getX(), _effect[i].first.getY(), _effect[i].second);
	}

	if (_image != nullptr && _pattenAni != nullptr)
	{
		float imageX = _image->getX() - GAMEMANAGER->getPlayer()->getCamareRect().left;
		float imageY = _image->getY() - GAMEMANAGER->getPlayer()->getCamareRect().top;
		_image->aniRender(getMemDC(), imageX, imageY, _pattenAni);
	}
}

void BossIsadora::_inputPatten()
{
	if (_hp[BaseEnum::STATE] <= 0)
	{
		_state = UnitState::DIE;
		smash.clear();
		_effect.clear();
		_isWarp = 0;
		_pattenAni = nullptr;
		return;
	}

	_state = (UnitState)3;//RND->getInt(3); // 현재 임시 ;
	_pattenAni = nullptr;

	if (_state == UnitState::IDLE)
	{
		_pattenDely = TIMEMANAGER->getWorldTime() + 2;
	}

	if (_state == UnitState::TRUNATTACK || _state == UnitState::FIREPILLARATTACK_0 || _state == UnitState::FIREPILLARATTACK_1)
	{
		_isWarp = 1;
		_inputWarpPoint();
	}

	if (_state == UnitState::TRUNATTACK)
	{
		_pattenSub.push_back(3);
	}

	if (_state == UnitState::FIREPILLARATTACK_0)
	{
		_pattenSub.push_back(CENTER_X+CENTER_X/2);
		_pattenSub.push_back(CENTER_X);
		_pattenSub.push_back(CENTER_X/2);
	}
}

int BossIsadora::_inputSide()
{
	RECT tamp[2];
	for (int i = 0; i < floor.size(); i++)
	{
		if (IntersectRect(&tamp[0], &_Collider[BaseEnum::UNIT], floor[i]))
		{
			tamp[1] = { _Collider[BaseEnum::UNIT].left - GAMESPEED, _Collider[BaseEnum::UNIT].top - GAMESPEED,
							_Collider[BaseEnum::UNIT].left, _Collider[BaseEnum::UNIT].bottom - GAMESPEED };

			if (IntersectRect(&tamp[0], &tamp[1], floor[i]))
			{
				_Collider[BaseEnum::UNIT].right += floor[i]->right - _Collider[BaseEnum::UNIT].left;
				_Collider[BaseEnum::UNIT].left += floor[i]->right - _Collider[BaseEnum::UNIT].left;
				return -1;
			}

			tamp[1] = { _Collider[BaseEnum::UNIT].right, _Collider[BaseEnum::UNIT].top - GAMESPEED,
							_Collider[BaseEnum::UNIT].right + GAMESPEED, _Collider[BaseEnum::UNIT].bottom - GAMESPEED };
			if (IntersectRect(&tamp[0], &tamp[1], floor[i]))
			{
				_Collider[BaseEnum::UNIT].left -= _Collider[BaseEnum::UNIT].right - floor[i]->left;
				_Collider[BaseEnum::UNIT].right -= _Collider[BaseEnum::UNIT].right - floor[i]->left;
				return 1;
			}
		}
	}
	return 0;
}

void BossIsadora::_pattenStart()
{
	if (_image != nullptr && _pattenAni != nullptr && _pattenAni->isPlay() == false)
	{  _state = UnitState::END; }
}

void BossIsadora::_pattenDie()
{
	_Collider[BaseEnum::UNIT].top+= 1;
	_Collider[BaseEnum::UNIT].bottom+= 1;

	RECT tamp;
	if (IntersectRect(&tamp, &_Collider[BaseEnum::UNIT], &stateFloor))
	{
		_Collider[BaseEnum::UNIT].top -= _Collider[BaseEnum::UNIT].bottom - stateFloor.top;
		_Collider[BaseEnum::UNIT].bottom -= _Collider[BaseEnum::UNIT].bottom - stateFloor.top;
	}
}

void BossIsadora::_pattenIdle()
{
	if (_pattenDely <= TIMEMANAGER->getWorldTime())
	{ _state = UnitState::END; }
}

void BossIsadora::_inputWarpPoint()
{
	warpPoint.second.x = _Collider[BaseEnum::UNIT].right - _Collider[BaseEnum::UNIT].left;
	warpPoint.second.y = _Collider[BaseEnum::UNIT].bottom - _Collider[BaseEnum::UNIT].top;

	if (_state == UnitState::TRUNATTACK)
	{
		if (GAMEMANAGER->getPlayer()->getPoint().x - (stateFloor.right/2) <= 0)
		{
			_isLeft = -1;
			warpPoint.first.x = WINSIZE_X - 150 - warpPoint.second.x;
			warpPoint.first.x = GAMEMANAGER->getPlayer()->getPoint().x + 150 + warpPoint.second.x;
		}
		else
		{
			_isLeft = 1;
			warpPoint.first.x = 150 + warpPoint.second.x;
			warpPoint.first.x = GAMEMANAGER->getPlayer()->getPoint().x - 150 - warpPoint.second.x;
		}
		_pattenSub.push_back(3.0f);
		warpPoint.first.y = stateFloor.top - warpPoint.second.y;
	}
	else if (_state == UnitState::FIREPILLARATTACK_0)
	{
		_isLeft = -1;
		warpPoint.first.x = stateFloor.right - 150 - warpPoint.second.x;
		warpPoint.first.y = WINSIZE_Y / 3 ;
	}

	else if (_state == UnitState::FIREPILLARATTACK_1)
	{
		warpPoint.first.x = _pillar->getPoint().x - 30;
		warpPoint.first.y = 200;
	}
}

void BossIsadora::_pattenWarp()
{
	if (_pattenAni != nullptr && _pattenAni->isPlay() == false)
	{
		_Collider[BaseEnum::UNIT] = { warpPoint.first.x, warpPoint.first.y, warpPoint.first.x + warpPoint.second.x, warpPoint.first.y + warpPoint.second.y };
		if (_isWarp != 2)
		{
			_isWarp = 2;
			_pattenAni = nullptr;
		}
		else
		{
			_isWarp = 0;
			_pattenAni = nullptr;
		}
	}
}

void BossIsadora::_pattenTurnAttack()
{
	if (_isWarp != 0)
	{
		_pattenWarp();
		return;
	}

	if(_pattenAni->getFrame() <= 8 )
	{
		return;
	}

	if (smash.size() == 0)
	{
		RECT smashPoint = {
			_Collider[BaseEnum::UNIT].left, stateFloor.top-25,
			_Collider[BaseEnum::UNIT].right, stateFloor.top
		};
		smash.push_back({ smashPoint, Image() });
	}

	if (_pattenAni->getFrame() <= 22)
	{
		if (_isLeft == 1 && _Collider[BaseEnum::UNIT].right <= (stateFloor.right) - GAMESPEED ||
			_isLeft == -1 && _Collider[BaseEnum::UNIT].left >= GAMESPEED)
		{
			if (smash.size() != 0)
			{
				smash.back().first.left += _isLeft * GAMESPEED;
				smash.back().first.right += _isLeft * GAMESPEED;
			}
			_Collider[BaseEnum::UNIT].left += _isLeft * GAMESPEED;
			_Collider[BaseEnum::UNIT].right += _isLeft * GAMESPEED;
		}
	}
	else
	{
		if (_isLeft == -1)
		{
			smash.back().first = {
				_Collider[BaseEnum::UNIT].left - 50, _Collider[BaseEnum::UNIT].top,
				_Collider[BaseEnum::UNIT].left, _Collider[BaseEnum::UNIT].bottom
			};
		}
		else
		{
			smash.back().first = {
				_Collider[BaseEnum::UNIT].right, _Collider[BaseEnum::UNIT].top,
				_Collider[BaseEnum::UNIT].right +50, _Collider[BaseEnum::UNIT].bottom
			};
		}
	}

	if (_pattenAni->isPlay() == false)
	{
		smash.clear();
		_pattenSub.clear();
		_state = UnitState::END;
		_pattenAni = nullptr;
	}
}

void BossIsadora::_pattenFirePollar(UnitState state, POINT point = {0,0} )
{
	pair<RECT, Image> result;
	int temp = 80;
	if (state == UnitState::FIREPILLARATTACK_0)
	{
		for (int i = 0; i < 3; i++)
		{
			if (i == 0) { point.x -= 100; } else { point.x += 100; }
			result.first = RECT{ point.x - 40, 0, point.x + 80 / 2, point.y };

			smash.push_back(result);
			_effect.push_back({ Image(), new Animation() });
			_effect.back().first.init("Resources/Images/Monster/Boss_Isidora/FireColumnAnticipation.bmp", 410 * 2, 900 * 2, 5, 3, MGT);
			_effect.back().second->init(_effect.back().first.getWidth(), _effect.back().first.getHeight(), _effect.back().first.getFrameWidth(), _effect.back().first.getFrameHeight());
			_effect.back().first.setX(smash.back().first.left - 45);
			_effect.back().first.setY(smash.back().first.top - 68);
			_effect.back().second->setDefPlayFrame(true, false);
			_effect.back().second->setFPS(28, 4);
			_effect.back().second->AniStart();
		}
	}
	else if (state == UnitState::FIREPILLARATTACK_1)
	{
		_effect.push_back({ Image(), new Animation() });
		_effect.back().first.init("Resources/Images/Monster/Boss_Isidora/FireColumnAnticipation.bmp", 410 * 2, 900 * 2, 5, 3, MGT);
	
		for (int i=0; i < 5; i++)
		{



		}
	

		/*
		result.first = RECT{ point.x - 40, 0, point.x + 80 / 2, point.y };
		result.first = 
		smash.push_back(result);
		*/



	}
}

void BossIsadora::_pattenFirePollarAttack0()
{
	if (_isWarp != 0)
	{
		_pattenWarp();
		return;
	}

	if (_pattenAni->getFrame() == 10)
	{
		pillarDelly = false;
		_pattenAni = new Animation();
		_pattenAni->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());

		_isLeft = -1;
		_pattenAni->setPlayReverseFrame(44, 53, 5, true);
		_pattenAni->setFPS(9, 2);
		_pattenAni->AniStart();
	}

	if ( _isLeft == -1 && _Collider[BaseEnum::UNIT].left >= GAMESPEED)
	{
		if (_pattenSub.size() == 0)
		{
			pillarDelly = true;
			_pattenSub.clear();
			smash.clear();
			_state = UnitState::END;
			return;
		}
		else
		{
			_Collider[BaseEnum::UNIT].left += _isLeft * GAMESPEED / 2;
			_Collider[BaseEnum::UNIT].right += _isLeft * GAMESPEED / 2;
		}
	}

	if (getPoint().x < _pattenSub.front())
	{
		POINT point;
		point.x = _pattenSub.front();
		point.y = stateFloor.top;
		_pattenFirePollar(_state,point);
		_pattenSub.erase(_pattenSub.begin());
	}
}

void BossIsadora::_pattenFirePollarAttack1()
{
	if (_isWarp != 0)
	{
		_pattenWarp();
		return;
	}

	if (_pattenAni->getFrame() == 10)
	{
		pillarDelly = false;
		_pattenAni = new Animation();
		_pattenAni->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());

		_isLeft = -1;
		_pattenAni->setPlayReverseFrame(44, 53, 5, true);
		_pattenAni->setFPS(9, 2);
		_pattenAni->AniStart();
	}

	_pattenFirePollar(_state);


}

void BossIsadora::_inputAnimation()
{
	if (_pattenAni != nullptr) return;
	
	if (_state == UnitState::START)
	{
		_image = IMAGEMANAGER->findImage("bIsiIntro");
		_pattenAni = new Animation();
		_pattenAni->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());

		_pattenAni->setPlayFrame(0, 50, false, false);
		_pattenAni->setFPS(50, 15);
		_pattenAni->AniStart();
	}
	else if (_state == UnitState::IDLE)
	{
		_image = IMAGEMANAGER->findImage("blsiIdle");
		_pattenAni = new Animation();
		_pattenAni->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());

		if (_isLeft == 1)
		{
			_pattenAni->setPlayFrame(0, 13, false, true);
		}
		else
		{
			_pattenAni->setPlayReverseFrame(19, 30, 4, true);
		}
		_pattenAni->setFPS(13, 4);
		_pattenAni->AniStart();
	}
	else if(_isWarp == 1)
	{
		_image = IMAGEMANAGER->findImage("bIsiWarpOn");
		_pattenAni = new Animation();
		_pattenAni->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());

		if (_isLeft == 1)
		{
			_pattenAni->setPlayFrame(0, 15, false, false);
		}
		else
		{
			_pattenAni->setPlayReverseFrame(19, 28, 4, false);
		}
		_pattenAni->setFPS(15, 4);
		_pattenAni->AniStart();
	}
	else if (_isWarp == 2)
	{
		_image = IMAGEMANAGER->findImage("bIsiWarpOff");
		_pattenAni = new Animation();
		_pattenAni->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());

		if (_isLeft == 1)
		{
			_pattenAni->setPlayReverseFrame(2, 7, 3, false);
		}
		else
		{
			_pattenAni->setPlayFrame(9, 16, false, false);
		}
		_pattenAni->setFPS(8, 2);
		_pattenAni->AniStart();
	}
	else if (_state == UnitState::TRUNATTACK)
	{
		_image = IMAGEMANAGER->findImage("bIsiWarpAttack");
		_pattenAni = new Animation();
		_pattenAni->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());

		if (_isLeft == 1)
		{
			_pattenAni->setPlayFrame(36, 69, false, false);
		}
		else
		{
			_pattenAni->setPlayReverseFrame(5, 32, 6, false);
		}
		_pattenAni->setFPS(32, 8);
		_pattenAni->AniStart();
	}
	else if (_state == UnitState::FIREPILLARATTACK_0 || _state == UnitState::FIREPILLARATTACK_1)
	{
		_image = IMAGEMANAGER->findImage("blsiFirePillarAttack0");
		_pattenAni = new Animation();
		_pattenAni->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());

		if (_isLeft == 1)
		{
			_pattenAni->setPlayFrame(0, 29, false, false);
		}
		else
		{
			_pattenAni->setPlayReverseFrame(34, 59, 5, true);
		}
		_pattenAni->setFPS(32, 10);
		_pattenAni->AniStart();
	}
	else if (_state == UnitState::DIE)
	{
		_image = IMAGEMANAGER->findImage("blsiDie");
		_pattenAni = new Animation();
		_pattenAni->init(_image->getWidth(), _image->getHeight(), _image->getFrameWidth(), _image->getFrameHeight());

		_isLeft = -1;
		if (_isLeft == 1)
		{
			_pattenAni->setPlayFrame(0, 118, false, false);
		}
		else
		{
			_pattenAni->setPlayReverseFrame(129, 231, 10, false);
		}
		_pattenAni->setFPS(119, 40);
		_pattenAni->AniStart();
	}
}

void BossIsadora::_inputImageXY()
{
	if (_image == nullptr) return;

	if (_state == UnitState::START)
	{
		_image->setX(_Collider[BaseEnum::UNIT].left - 95);
		_image->setY(_Collider[BaseEnum::UNIT].top - 90);
	}
	if (_state == UnitState::IDLE)
	{
		_image->setX(_Collider[BaseEnum::UNIT].left -140);
		_image->setY(_Collider[BaseEnum::UNIT].top -125);
	}
	else if (_isWarp != 0)
	{
		_image->setX(_Collider[BaseEnum::UNIT].left - 140);
		_image->setY(_Collider[BaseEnum::UNIT].top - 125);
	}
	else if (_state == UnitState::TRUNATTACK)
	{
		_image->setX(_Collider[BaseEnum::UNIT].left - 140);
		_image->setY(_Collider[BaseEnum::UNIT].top - 125);
	}
	else if (_state == UnitState::FIREPILLARATTACK_0 || _state == UnitState::FIREPILLARATTACK_1)
	{
		_image->setX(_Collider[BaseEnum::UNIT].left - 140);
		_image->setY(_Collider[BaseEnum::UNIT].top - 125);
	}
	else if (_state == UnitState::DIE)
	{
		_image->setX(_Collider[BaseEnum::UNIT].left - 140);
		_image->setY(_Collider[BaseEnum::UNIT].top - 125);
	}
}

void BossIsadora::_inputEffect()
{
	for (int i = 0; i < _effect.size(); i++)
	{
		_effect[i].second->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);

		if (_effect[i].second->isPlay() == false)
		{
			smash.clear();
			_effect.erase(_effect.begin() + i);
			return;
		}
	}
}


