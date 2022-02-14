#include "stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
    IMAGEMANAGER->addImage("시작화면", "Resources/Images/BackGround/bgAll.bmp", 1280, 800);
    IMAGEMANAGER->addFrameImage("캐릭터대기", "Resources/Images/Object/plWait.bmp", 1500, 800, 10, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터공격", "Resources/Images/Object/plAtt.bmp", 6000, 887,10,2,true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("캐릭터방어", "Resources/Images/Object/plDefend.bmp", 750, 790,5,2, true, RGB(255, 0, 255));
    //IMAGEMANAGER->addFrameImage("캐릭터이동", "Resources/Images/Object/plDefend.bmp", 750, 790,5,2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("적대기", "Resources/Images/Object/enemyWait.bmp", 5364, 491,12,1, true, RGB(255, 0, 255)); 
    IMAGEMANAGER->addFrameImage("적피격", "Resources/Images/Object/enemyDanage.bmp", 2745, 500,5,1, true, RGB(255, 0, 255)); 
    IMAGEMANAGER->addFrameImage("적공격", "Resources/Images/Object/enemyAtt.bmp", 6000, 500,10,1, true, RGB(255, 0, 255));
    _player._rcPlayer = RectMakeCenter(200, 500, 150, 400);
    _enemy._rcEnemy = RectMakeCenter(700, 450, 150, 500);

    _count = 0;
    _indexA = _indexB = 0;
    _alphaA = 0;
	_player._isWaiting = true;
	_player._isDefend = false;
	_player._isLeft = false;
	_enemy._isDamage = false;
	_enemy._isWaiting = true;
	_player._plHp = 100;
	_enemy._enemyHp = 100;
	return S_OK;
}

void SecondScene::release(void)
{
}

void SecondScene::update(void)
{
    _count++;
  
    
    if (_player._isWaiting && _count % 5 == 0)
    {
      if (_player._isLeft)
      {
        _indexA++;
        IMAGEMANAGER->findImage("캐릭터대기")->setFrameY(0);
        if (_indexA > 10)
        {
            _indexA = 0;
        }
        IMAGEMANAGER->findImage("캐릭터대기")->setFrameX(_indexA);
      }
      else if (!_player._isLeft)
      {
          _indexA--;
          IMAGEMANAGER->findImage("캐릭터대기")->setFrameY(1);
          if (_indexA < 0)
          {
              _indexA = 10;
          }
          IMAGEMANAGER->findImage("캐릭터대기")->setFrameX(_indexA);
      }
    }

    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        _player._isLeft = true;
        _player._isWaiting = true;//이동만들곤 수정할것
        _player._rcPlayer.left -= 5;
        _player._rcPlayer.right -= 5;
       
        _indexA++;
        IMAGEMANAGER->findImage("캐릭터대기")->setFrameY(0);
        if (_indexA >= 10)
        {
            _indexA = 0;
        }
        IMAGEMANAGER->findImage("캐릭터대기")->setFrameX(_indexA);
    }
    else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        _player._isLeft = false;
        _player._isWaiting = true;
        _player._rcPlayer.left += 5;
        _player._rcPlayer.right += 5;

        _indexA--;
        IMAGEMANAGER->findImage("캐릭터대기")->setFrameY(1);
        if (_indexA < 0)
        {
            _indexA = 10;
        }
        IMAGEMANAGER->findImage("캐릭터대기")->setFrameX(_indexA);
    }

	if (_count % 5 == 0)
	{
		if (_enemy._rcEnemy.left - 40 < _player._rcPlayer.right)
		{
			if (_enemyAttCount < 10)
			{
				_enemyAttCount++;
			}
			else
			{
				_indexB++;
				_enemy._isWaiting = false;
				IMAGEMANAGER->findImage("적공격")->setFrameX(_indexB);
				IMAGEMANAGER->findImage("적공격")->setFrameY(0);
				if (_indexB >= 10)
				{
					_indexB = 0;
					_enemyAttCount = 0;
				}
				if (_indexB == 7 && !_player._isDefend)
				{
					_player._plHp -= 10;
				}
			}
		}
		else 
		{
			_enemy._isWaiting = true;
		}
		
		if (_enemy._isWaiting)
		{
			_indexB++;
			IMAGEMANAGER->findImage("적대기")->setFrameY(0);
			if (_indexB >= 12)
			{
				_indexB = 0;
			}
			IMAGEMANAGER->findImage("적대기")->setFrameX(_indexB);
		}
	}

    if (KEYMANAGER->isOnceKeyDown('Q'))
    {
        _player._skillTime = 50;
        if (_player._skillTime <0 )
        {
            _player._isWaiting = true;
        }
        if (_enemy._rcEnemy.left - 40 < _player._rcPlayer.right && !_player._isLeft)
        {
            _enemy._enemyHp -= 10;
            _enemy._isDamage =true; 
            _enemy._isWaiting = false;
            _indexB++;
            IMAGEMANAGER->findImage("적피격")->setFrameY(0);
            if (_count %3== 0)
            {
                _indexB = 0;
            }
            IMAGEMANAGER->findImage("적피격")->setFrameX(_indexB);
        }

        if (_player._isLeft)
        {
           
            _indexA = 0;
            IMAGEMANAGER->findImage("캐릭터공격")->setFrameY(0);
            if (_player._skillTime - _count /5 == 0)
            {
                _indexA ++;
            }
            IMAGEMANAGER->findImage("캐릭터공격")->setFrameX(_player._skillTime-_count);
        }
        else
        {
           
            _indexA=10;
            IMAGEMANAGER->findImage("캐릭터공격")->setFrameY(1);
            if (_player._skillTime - _count / 5 == 0)
            {
                _indexA--;
            }
            IMAGEMANAGER->findImage("캐릭터공격")->setFrameX(_indexA);
        }
        
    }

    //else if (KEYMANAGER->isOnceKeyDown('E'))
    //{
    //    _player._isDefend = true;
    //    if (_player._isLeft) 
    //    {
    //        IMAGEMANAGER->findImage("캐릭터방어")->setFrameY(0);
    //    }
    //    else
    //    {
    //        IMAGEMANAGER->findImage("캐릭터공격")->setFrameY(1);
    //        IMAGEMANAGER->findImage("적대기")->setFrameY(1);
    //    }

    //    if (!_player._isLeft && _count % 3 == 0)
    //    {
    //        IMAGEMANAGER->findImage("캐릭터방어")->setFrameX(_index);
    //        IMAGEMANAGER->findImage("적대기")->setFrameX(_index);
    //    }
    //}

   
}

void SecondScene::render(void)
{
    IMAGEMANAGER->render("시작화면", getMemDC(), 0, 0);

    if (_player._isWaiting)
    {
        IMAGEMANAGER->frameRender("캐릭터대기", getMemDC(), _player._rcPlayer.left, _player._rcPlayer.top);
    }
    /*else if (KEYMANAGER->isStayKeyDown(VK_RIGHT)|| KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
    }*/
    else if (KEYMANAGER->isOnceKeyDown('Q'))
    {
        IMAGEMANAGER->frameRender("캐릭터공격", getMemDC(), _player._rcPlayer.left, _player._rcPlayer.top);
    }
    //else 

    if (_enemy._isWaiting)
    {
        IMAGEMANAGER->frameRender("적대기", getMemDC(), _enemy._rcEnemy.left+170, _enemy._rcEnemy.top);
    }
	else 
	{
		IMAGEMANAGER->frameRender("적공격", getMemDC(), _enemy._rcEnemy.left, _enemy._rcEnemy.top);
	}
   /*
    if (KEYMANAGER->isOnceKeyDown('e'))
    {
        IMAGEMANAGER->frameRender("캐릭터방어", getMemDC(), _player._rcPlayer.left, _player._rcPlayer.top);
    }*/
 
    /*
   if (_enemy._rcEnemy.left - 40 < _player._rcPlayer.right)
   {
       _enemyAttCount++;
       if (_enemyAttCount % 10 == 0)
       {
           IMAGEMANAGER->frameRender("적공격", getMemDC(), _enemy._rcEnemy.left, _enemy._rcEnemy.top);
       }
   }
*/
    //Rectangle(getMemDC(), _player._rcPlayer.left, _player._rcPlayer.top, _player._rcPlayer.right, _player._rcPlayer.bottom);
    //Rectangle(getMemDC(), _enemy._rcEnemy.left, _enemy._rcEnemy.top, _enemy._rcEnemy.right, _enemy._rcEnemy.bottom);
//IMAGEMANAGER->frameRender("캐릭터이동", getMemDC(), _player._rcPlayer.left, _player._rcPlayer.top);이걸안했네
  //std::cout << "캐릭터 위치" << _player._rcPlayer.left << _player._rcPlayer.top << std::endl;
  std::cout << "적 위치" << _enemy._rcEnemy.left<< _enemy._rcEnemy.top << std::endl;
  std::cout << _enemyAttCount << std::endl;
   
   //밑은 폰트//
	//SetBkMode() : 투명하게 하는 함수 (글자 뒤로 배경이 보이게 한다)
	//SetBkMode(getMemDC(), TRANSPARENT);

	//// 새로운 방법
	//HFONT font;
	//HFONT oldFont;

 //   char str[128];
	//font = CreateFont
	//(
	//	70, 0, 0, 0, 600,
	//	0, 0, 1,
	//	HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림")
	//);

	//oldFont = (HFONT)SelectObject(getMemDC(), font);

	//wsprintf(str, "새로운 폰트");
	//TextOut(getMemDC(), 100, 400, str, strlen(str));

	//SelectObject(getMemDC(), oldFont);
	//DeleteObject(font);

}
