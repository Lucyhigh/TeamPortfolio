#include "stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
    IMAGEMANAGER->addImage("����ȭ��", "Resources/Images/BackGround/bgAll.bmp", 1280, 800);
    IMAGEMANAGER->addFrameImage("ĳ���ʹ��", "Resources/Images/Object/plWait.bmp", 1500, 800, 10, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ���Ͱ���", "Resources/Images/Object/plAtt.bmp", 6000, 887,10,2,true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ĳ���͹��", "Resources/Images/Object/plDefend.bmp", 750, 790,5,2, true, RGB(255, 0, 255));
    //IMAGEMANAGER->addFrameImage("ĳ�����̵�", "Resources/Images/Object/plDefend.bmp", 750, 790,5,2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("�����", "Resources/Images/Object/enemyWait.bmp", 5364, 491,12,1, true, RGB(255, 0, 255)); 
    IMAGEMANAGER->addFrameImage("���ǰ�", "Resources/Images/Object/enemyDanage.bmp", 2745, 500,5,1, true, RGB(255, 0, 255)); 
    IMAGEMANAGER->addFrameImage("������", "Resources/Images/Object/enemyAtt.bmp", 6000, 500,10,1, true, RGB(255, 0, 255));
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
        IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameY(0);
        if (_indexA > 10)
        {
            _indexA = 0;
        }
        IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameX(_indexA);
      }
      else if (!_player._isLeft)
      {
          _indexA--;
          IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameY(1);
          if (_indexA < 0)
          {
              _indexA = 10;
          }
          IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameX(_indexA);
      }
    }

    if (KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
        _player._isLeft = true;
        _player._isWaiting = true;//�̵������ �����Ұ�
        _player._rcPlayer.left -= 5;
        _player._rcPlayer.right -= 5;
       
        _indexA++;
        IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameY(0);
        if (_indexA >= 10)
        {
            _indexA = 0;
        }
        IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameX(_indexA);
    }
    else if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
    {
        _player._isLeft = false;
        _player._isWaiting = true;
        _player._rcPlayer.left += 5;
        _player._rcPlayer.right += 5;

        _indexA--;
        IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameY(1);
        if (_indexA < 0)
        {
            _indexA = 10;
        }
        IMAGEMANAGER->findImage("ĳ���ʹ��")->setFrameX(_indexA);
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
				IMAGEMANAGER->findImage("������")->setFrameX(_indexB);
				IMAGEMANAGER->findImage("������")->setFrameY(0);
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
			IMAGEMANAGER->findImage("�����")->setFrameY(0);
			if (_indexB >= 12)
			{
				_indexB = 0;
			}
			IMAGEMANAGER->findImage("�����")->setFrameX(_indexB);
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
            IMAGEMANAGER->findImage("���ǰ�")->setFrameY(0);
            if (_count %3== 0)
            {
                _indexB = 0;
            }
            IMAGEMANAGER->findImage("���ǰ�")->setFrameX(_indexB);
        }

        if (_player._isLeft)
        {
           
            _indexA = 0;
            IMAGEMANAGER->findImage("ĳ���Ͱ���")->setFrameY(0);
            if (_player._skillTime - _count /5 == 0)
            {
                _indexA ++;
            }
            IMAGEMANAGER->findImage("ĳ���Ͱ���")->setFrameX(_player._skillTime-_count);
        }
        else
        {
           
            _indexA=10;
            IMAGEMANAGER->findImage("ĳ���Ͱ���")->setFrameY(1);
            if (_player._skillTime - _count / 5 == 0)
            {
                _indexA--;
            }
            IMAGEMANAGER->findImage("ĳ���Ͱ���")->setFrameX(_indexA);
        }
        
    }

    //else if (KEYMANAGER->isOnceKeyDown('E'))
    //{
    //    _player._isDefend = true;
    //    if (_player._isLeft) 
    //    {
    //        IMAGEMANAGER->findImage("ĳ���͹��")->setFrameY(0);
    //    }
    //    else
    //    {
    //        IMAGEMANAGER->findImage("ĳ���Ͱ���")->setFrameY(1);
    //        IMAGEMANAGER->findImage("�����")->setFrameY(1);
    //    }

    //    if (!_player._isLeft && _count % 3 == 0)
    //    {
    //        IMAGEMANAGER->findImage("ĳ���͹��")->setFrameX(_index);
    //        IMAGEMANAGER->findImage("�����")->setFrameX(_index);
    //    }
    //}

   
}

void SecondScene::render(void)
{
    IMAGEMANAGER->render("����ȭ��", getMemDC(), 0, 0);

    if (_player._isWaiting)
    {
        IMAGEMANAGER->frameRender("ĳ���ʹ��", getMemDC(), _player._rcPlayer.left, _player._rcPlayer.top);
    }
    /*else if (KEYMANAGER->isStayKeyDown(VK_RIGHT)|| KEYMANAGER->isStayKeyDown(VK_LEFT))
    {
    }*/
    else if (KEYMANAGER->isOnceKeyDown('Q'))
    {
        IMAGEMANAGER->frameRender("ĳ���Ͱ���", getMemDC(), _player._rcPlayer.left, _player._rcPlayer.top);
    }
    //else 

    if (_enemy._isWaiting)
    {
        IMAGEMANAGER->frameRender("�����", getMemDC(), _enemy._rcEnemy.left+170, _enemy._rcEnemy.top);
    }
	else 
	{
		IMAGEMANAGER->frameRender("������", getMemDC(), _enemy._rcEnemy.left, _enemy._rcEnemy.top);
	}
   /*
    if (KEYMANAGER->isOnceKeyDown('e'))
    {
        IMAGEMANAGER->frameRender("ĳ���͹��", getMemDC(), _player._rcPlayer.left, _player._rcPlayer.top);
    }*/
 
    /*
   if (_enemy._rcEnemy.left - 40 < _player._rcPlayer.right)
   {
       _enemyAttCount++;
       if (_enemyAttCount % 10 == 0)
       {
           IMAGEMANAGER->frameRender("������", getMemDC(), _enemy._rcEnemy.left, _enemy._rcEnemy.top);
       }
   }
*/
    //Rectangle(getMemDC(), _player._rcPlayer.left, _player._rcPlayer.top, _player._rcPlayer.right, _player._rcPlayer.bottom);
    //Rectangle(getMemDC(), _enemy._rcEnemy.left, _enemy._rcEnemy.top, _enemy._rcEnemy.right, _enemy._rcEnemy.bottom);
//IMAGEMANAGER->frameRender("ĳ�����̵�", getMemDC(), _player._rcPlayer.left, _player._rcPlayer.top);�̰ɾ��߳�
  //std::cout << "ĳ���� ��ġ" << _player._rcPlayer.left << _player._rcPlayer.top << std::endl;
  std::cout << "�� ��ġ" << _enemy._rcEnemy.left<< _enemy._rcEnemy.top << std::endl;
  std::cout << _enemyAttCount << std::endl;
   
   //���� ��Ʈ//
	//SetBkMode() : �����ϰ� �ϴ� �Լ� (���� �ڷ� ����� ���̰� �Ѵ�)
	//SetBkMode(getMemDC(), TRANSPARENT);

	//// ���ο� ���
	//HFONT font;
	//HFONT oldFont;

 //   char str[128];
	//font = CreateFont
	//(
	//	70, 0, 0, 0, 600,
	//	0, 0, 1,
	//	HANGEUL_CHARSET, 0, 0, 0, 0, TEXT("�޸ձ���")
	//);

	//oldFont = (HFONT)SelectObject(getMemDC(), font);

	//wsprintf(str, "���ο� ��Ʈ");
	//TextOut(getMemDC(), 100, 400, str, strlen(str));

	//SelectObject(getMemDC(), oldFont);
	//DeleteObject(font);

}
