#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
	_titleName = ANYBUTTON;

	// ANYBUTTON ------------
	_pushButton = false;

	int w = IMAGEMANAGER->findImage("AnyButtonLogo")->getWidth();
	int h = IMAGEMANAGER->findImage("AnyButtonLogo")->getHeight();
	_logoRc = RectMakeCenter(CENTER_X,CENTER_Y,w,h);

	_alpha = 0;

	// TITLE ------------
	_ani = new AniSceneTitle;
	_ani->init();
	_menuIndex = 0;

	// SAVE ------------
	// ���̺� ������ �ִ��� üũ�ϰ�, ���� ������ ��. 
	for (int i = 1; i < 4; i++)
	{
		tagSaveSlot slotInfo;
		slotInfo.x = 140; 
		slotInfo.y = 60 + ( 1 * 115 ) ; 
		slotInfo.state = NONE; // ���̺� ���������� ���� ���� ����
		slotInfo.noneImg = new Image;
		slotInfo.noneImg->init("Resources/Images/UI/saveNoData.bmp", slotInfo.x, slotInfo.y, 848, 112, MGT);
		slotInfo.onImg = new Image;
		slotInfo.onImg->init("Resources/Images/UI/saveOn.bmp", slotInfo.x, slotInfo.y, 848, 112, MGT);
		slotInfo.offImg = new Image;
		slotInfo.offImg->init("Resources/Images/UI/saveOff.bmp", slotInfo.x, slotInfo.y, 848, 112, MGT);
		slotInfo.num = 1;
		slotInfo.posEndX = slotInfo.x + IMAGEMANAGER->findImage("saveNoData")->getWidth();
		slotInfo.select = false;
		_vSave.push_back(slotInfo);
	}
	_saveIndex = 1;

	// OPTION ------------
	for (int i = 0; i < OPTIONMENU; i++)
	{
		tagOptionSlot optionInfo;
		optionInfo.num = i;
		optionInfo.x = 340;
		optionInfo.y = 140 + ( i* 57 );
		optionInfo.onImg = new Image;
		optionInfo.onImg->init("Resources/Images/UI/optionSelect.bmp", optionInfo.x, optionInfo.y, 16, 31, MGT);
		optionInfo.select = false;
		_vOption.push_back(optionInfo);
	}
	_optinIndex = 1; 

	return S_OK;
}

void TitleScene::release(void)
{
	SAFE_DELETE(_ani);

	_viSave = _vSave.begin();
	for (; _viSave != _vSave.end(); _viSave++)
	{
		SAFE_DELETE(_viSave->noneImg);
		SAFE_DELETE(_viSave->onImg);
		SAFE_DELETE(_viSave->offImg);
	}
	_vSave.clear();

	_viOption = _vOption.begin();
	for (; _viOption != _vOption.end(); _viOption++)
	{
		SAFE_DELETE(_viOption->onImg);
	}
	_vOption.clear();
}

void TitleScene::update(void)
{

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) _pushButton = true;

	if (_pushButton)
	{
		_alpha++;
		if (_alpha >= 255)
		{
			_alpha = 255;
			_titleName = TITLE;
		}
	}

	if (_titleName == TITLE)
	{
		IMAGEMANAGER->findImage("titleMenu")->setFrameY(0);
		IMAGEMANAGER->findImage("titleMenu")->setFrameX(0);

		_ani->update();

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuIndex--;
			if (_menuIndex < 0) _menuIndex = 2;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuIndex++;
			if (_menuIndex > 2) _menuIndex = 0;
		}
		IMAGEMANAGER->findImage("titleMenu")->setFrameX(_menuIndex);
	}

	if (_menuIndex == 0)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			_titleName = SAVE;
		}
	}
	
	if (_menuIndex == 1)
	{

		if (KEYMANAGER->isOnceKeyDown(VK_RETURN)) _titleName = OPTION;
	}

	if (_menuIndex == 2)
	{
		if (KEYMANAGER->isOnceKeyUp(VK_RETURN)) PostQuitMessage(0);
	}

	if ( _titleName == SAVE || _titleName == OPTION)
	{
		if(KEYMANAGER->isOnceKeyDown(VK_ESCAPE)) _titleName = TITLE;
	}

	if (_titleName == SAVE)
	{

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_saveIndex--;
			if (_saveIndex < 1) _saveIndex = 3;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_saveIndex++;
			if (_saveIndex > 3) _saveIndex = 1;
		}
		
		selectSaveData(_saveIndex);

		// Scene Change -> GameScene
		if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
		{
			// �ӽ� �� ����. ���̺� �����Ϳ��� �� ���� ���� �ʿ�?
			if (_saveIndex == 1) SCENEMANAGER->changeScene("Start");
			if (_saveIndex == 2) SCENEMANAGER->changeScene("Boss1");
			if (_saveIndex == 3) SCENEMANAGER->changeScene("Boss2");
		}
	}
	

	if (_titleName == OPTION)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_optinIndex--;
			if (_optinIndex < 1) _optinIndex = OPTIONMENU - 3;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_optinIndex++;
			if (_optinIndex > OPTIONMENU - 3 ) _optinIndex = 1;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
		{
			_titleName == TITLE;
		}

		selectOption(_optinIndex);
	}
}

void TitleScene::render(void)
{
	if (_titleName == ANYBUTTON)
	{
		IMAGEMANAGER->findImage("AnyButtonBg")->render(getMemDC());
		IMAGEMANAGER->findImage("AnyButtonLogo")->alphaRender(getMemDC(), _logoRc.left, _logoRc.top, _alpha);

		//FONTMANAGER->drawText(getMemDC(), CENTER_X-150, _logoRc.bottom+10, "�ձٸ��", 25, 100, script,
		//	wcslen(script), RGB(171, 124, 117));
	}

	if (_titleName == TITLE)
	{
		_ani->render();
		IMAGEMANAGER->findImage("titleMenu")->frameRender(getMemDC(),WINSIZE_X - 200, CENTER_Y+150 );
		_ani->render(WINSIZE_X - 150, CENTER_Y + 100 + (_menuIndex*40));
	}

	if (_titleName == SAVE)
	{
		IMAGEMANAGER->findImage("menuSaveBg")->render(getMemDC());
		showSaveData();
	}


	if (_titleName == OPTION)
	{
		IMAGEMANAGER->findImage("menuOptionBg")->render(getMemDC());
		showOption();
	}
	
}

// SAVE ------------------------------------------------------------------------------------
void TitleScene::selectSaveData(int saveIndex)
{
	_viSave = _vSave.begin();
	for (; _viSave != _vSave.end(); _viSave++)
	{
		if (_viSave->num == saveIndex) _viSave->select = true;
		else _viSave->select = false;
	}
}

void TitleScene::showSaveData(void)
{
	IMAGEMANAGER->findImage("enter")->render(getMemDC(), CENTER_X + 20, WINSIZE_Y - 100);
	IMAGEMANAGER->findImage("esc")->render(getMemDC(), CENTER_X + 255, WINSIZE_Y - 100);

	_viSave = _vSave.begin();
	for (; _viSave != _vSave.end(); _viSave++)
	{
		/*
		if (_saveIndex < 100)
		{
			// �ӽ� - ����� ������ ���ٸ� 
			_viSave->noneImage->render(getMemDC(), _viSave->x, _viSave->y);

			// slotNum
			FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						 // ����
				_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	 // ��ġ
				"�ձٸ��", 30, 100, OTEXT);	

			// ���� ������ x , �� ����
			FONTMANAGER->drawText(getMemDC(), (CENTER_X + 20) + IMAGEMANAGER->findImage("enter")->getWidth() + 10, WINSIZE_Y - 98,
				"�ձٸ��", 25, 100, _saveMenuText[0].text, wcslen(_saveMenuText[0].text), BTEXT);// ��Ʈ

			// �ڷΰ���
			FONTMANAGER->drawText(getMemDC(), (CENTER_X + 255) + IMAGEMANAGER->findImage("esc")->getWidth() +15, WINSIZE_Y - 98,
			"�ձٸ��", 25, 100, _saveMenuText[2].text, wcslen(_saveMenuText[2].text), BTEXT);

		}
		
		else*/
		{
			// ����� ������ �ִٸ�
			if (_viSave->select)
			{
				_tempPoint = 1300; // �ӽõ����� 


				_viSave->onImg->render(getMemDC(), _viSave->x, _viSave->y);
				// slotNum
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						 // ����
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	 // ��ġ
					"�ձٸ��", 30, 100, OTEXT);												 // ��Ʈ

				// �÷��̾� ���̺�  ���� 
				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L"ħ���� ��ź ������"; // �ӽ� ���� �ؽ�Ʈ 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"�ձٸ��", 25, 100, tempArea, wcslen(tempArea), OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // �ӽ� ����Ʈ 
					_viSave->posEndX - 70, _viSave->y + 25,
					"�ձٸ��", 25, 100, OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L"�÷��� �ð� : 2h 4m ~ 16.7% �Ϸ�"; // �ӽ� �����ð�, ������
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"�ձٸ��", 25, 100, tempTime, wcslen(tempTime), OTEXT);

				// ���� ������ o, ���嵥���ͷ� ���
				FONTMANAGER->drawText(getMemDC(), (CENTER_X + 20) + IMAGEMANAGER->findImage("enter")->getWidth() + 65, WINSIZE_Y - 98,
					"�ձٸ��", 25, 100, _saveMenuText[1].text, wcslen(_saveMenuText[1].text), BTEXT);// ��Ʈ

			}
			if (!_viSave->select)
			{
				// ���������� ������ �������� ������
				_viSave->offImg->render(getMemDC(), _viSave->x, _viSave->y);
				_tempPoint = 470; // �ӽõ����� 

				// slotNum
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,
					"�ձٸ��", 30, 100, XTEXT);

				// �÷��̾� ���̺�  ���� 
				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L"�������� �ٸ�"; // �ӽ� ���� �ؽ�Ʈ 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"�ձٸ��", 25, 100, tempArea, wcslen(tempArea), XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // �ӽ� ����Ʈ 
					_viSave->posEndX - 70, _viSave->y + 25,
					"�ձٸ��", 25, 100, XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L"�÷��� �ð� : 1h 14m ~ 38.1% �Ϸ�"; // �ӽ� �����ð�, ������
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"�ձٸ��", 25, 100, tempTime, wcslen(tempTime), XTEXT);

			}

			// �ڷΰ���
			FONTMANAGER->drawText(getMemDC(), (CENTER_X + 255) + IMAGEMANAGER->findImage("esc")->getWidth() + 65, WINSIZE_Y - 98,
			"�ձٸ��", 25, 100, _saveMenuText[2].text, wcslen(_saveMenuText[2].text), BTEXT);
		}
	}


}

void TitleScene::addSaveData(int num)
{
	char temp[32];
	vector<string> data;

	// itoa:��Ƽ�� �� �ƽ�Ű (�������� ���ڿ��� ��ȯ)
	// �����䤻
	
	float _x = GAMEMANAGER->getPlayer()->getCollider().left;
	float _y = GAMEMANAGER->getPlayer()->getCollider().top;
	float _currentHp = GAMEMANAGER->getPlayer()->getHp(BaseEnum::STATE);
	float _maxHp = GAMEMANAGER->getPlayer()->getHp(BaseEnum::MAX);
	float _currentMp = GAMEMANAGER->getPlayer()->getMp(BaseEnum::STATE);
	float _maxMp = GAMEMANAGER->getPlayer()->getMp(BaseEnum::MAX);

	// data.push_back(itoa((int)_x, temp, 10));
	// data.push_back(itoa((int)_y, temp, 10));
	// data.push_back(itoa((int)_currentHp, temp, 10));
	// data.push_back(itoa((int)_maxHp, temp, 10));
	// data.push_back(itoa((int)_currentMp, temp, 10));
	// data.push_back(itoa((int)_maxMp, temp, 10));

	// �����̸� ���� : save + SolotNum + .txt �� ���� �����ؼ� ���� 
	char saveFileName[128];
	int saveNum = num;
	// itoa((int)num, temp, 10);
	// saveFileName = "save.txt";
	TEXTDATAMANAGER->save("save1.txt", data);
}

void TitleScene::loadSaveData(int num)
{
	vector<string> vData = TEXTDATAMANAGER->load("save1.txt");
	// _x = atoi(vData[0].c_str());
	// _y = atoi(vData[1].c_str());
	// _currentHp = atoi(vData[2].c_str());
	// _maxHp = atoi(vData[3].c_str());

}

// OPTION ------------------------------------------------------------------------------------
void TitleScene::selectOption(int optionIndex)
{
	_viOption = _vOption.begin();
	for (; _viOption != _vOption.end(); _viOption++)
	{
		if (_viOption->num == optionIndex) _viOption->select = true;
		else _viOption->select = false;
	}
}

void TitleScene::showOption(void)
{
	IMAGEMANAGER->findImage("enter")->render(getMemDC(), CENTER_X + 120, WINSIZE_Y - 100);
	IMAGEMANAGER->findImage("esc")->render(getMemDC(), CENTER_X + 355, WINSIZE_Y - 100);

	// Menu title 
	_viOption = _vOption.begin();
	FONTMANAGER->drawText(getMemDC(), _viOption->x -10 , _viOption->y-5,
		"�ձٸ��", 27, 100, _optionText[_viOption->num].text, wcslen(_optionText[_viOption->num].text), TTEXT);


	_viOption = _vOption.begin()+1; // 0�� Ÿ��Ʋ �� 
	for (; _viOption != _vOption.end()-2; _viOption++) // 2�� ����, �ڷ� 
	{
		SetTextAlign(getMemDC(), TA_LEFT);
		if (_viOption->select) // ������ �ɼ��� ����� + ��ũ
		{
			_viOption->onImg->render(getMemDC(), _viOption->x-25, _viOption->y-2);

			FONTMANAGER->drawText(getMemDC(), _viOption->x , _viOption->y ,
				"�ձٸ��", 25, 100, _optionText[_viOption->num].text, wcslen(_optionText[_viOption->num].text), OTEXT);
		}
		if (!_viOption->select)
		{
			FONTMANAGER->drawText(getMemDC(), _viOption->x, _viOption->y,
				"�ձٸ��", 25, 100, _optionText[_viOption->num].text, wcslen(_optionText[_viOption->num].text), MTEXT);
		}
	}

		// ����, �ڷ� 
		_viOption = _vOption.end() -2;
		FONTMANAGER->drawText(getMemDC(), (CENTER_X + 120) + IMAGEMANAGER->findImage("enter")->getWidth() + 25, WINSIZE_Y - 98,
			"�ձٸ��", 25, 100, _optionText[_viOption->num].text, wcslen(_optionText[_viOption->num].text), BTEXT);

		_viOption = _vOption.end() - 1;
		FONTMANAGER->drawText(getMemDC(), (CENTER_X + 355) + IMAGEMANAGER->findImage("esc")->getWidth() + 25, WINSIZE_Y - 98,
			"�ձٸ��", 25, 100, _optionText[_viOption->num].text, wcslen(_optionText[_viOption->num].text), BTEXT);
}

