#include "Stdafx.h"
#include "TitleScene.h"

HRESULT TitleScene::init(void)
{
	_ani = new AniSceneTitle;
	_ani->init();

	_titleName = SAVE;
	_pushButton = false;

	int w = IMAGEMANAGER->findImage("AnyButtonLogo")->getWidth();
	int h = IMAGEMANAGER->findImage("AnyButtonLogo")->getHeight();
	_logoRc = RectMakeCenter(CENTER_X,CENTER_Y,w,h);

	_alpha = 0;
	_menuIndex = 0;

	// Text

	// SAVE ------------
	// 세이브 파일이 있는지 체크하고, 토대로 세팅할 것. 
	//for (int i = 1; i < 4; i++)
	{

			// 이미지 좌표 이상함.... 왜그럴까 수정 필요 
		tagSaveSlot slotInfo;
		slotInfo.pos.x = 140; 
		slotInfo.pos.y = 60 + ( 1 * 115 ) ; 
		slotInfo.state = NONE; // 세이브 파일유무에 따라 상태 변경
		slotInfo.noneImg = new Image;
		slotInfo.noneImg->init("Resources/Images/UI/saveNoData.bmp", slotInfo.pos.x, slotInfo.pos.y, 848, 112, MGT);
		slotInfo.onImg = new Image;
		slotInfo.onImg->init("Resources/Images/UI/saveOn.bmp", slotInfo.pos.x, slotInfo.pos.y, 848, 112, MGT);
		slotInfo.offImg = new Image;
		slotInfo.offImg->init("Resources/Images/UI/saveOff.bmp", slotInfo.pos.x, slotInfo.pos.y, 848, 112, MGT);
		slotInfo.num = 1;
		slotInfo.posEndX = slotInfo.pos.x + IMAGEMANAGER->findImage("saveNoData")->getWidth();
		slotInfo.select = false;
		_vSave.push_back(slotInfo);
	}

	_saveIndex = 1;


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


	// Title-Menu select
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN)  && _titleName == TITLE && _menuIndex == 0)
	{
		_titleName = SAVE;
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_RETURN) && _titleName == TITLE && _menuIndex == 1)
	{
		_titleName = OPTION;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RETURN) && _titleName == TITLE && _menuIndex == 2)
	{
		 PostQuitMessage(0);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE) && _titleName == SAVE || _titleName == OPTION)
	{
		_titleName = TITLE;
	}
	

	if (_titleName == SAVE)
	{
		//SCENEMANAGER->changeScene("Start");

		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_menuIndex--;
			if (_menuIndex < 1) _menuIndex = 3;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_menuIndex++;
			if (_menuIndex > 3) _menuIndex = 1;
		}
		
		selectSaveData(_menuIndex);

	}

	if (_titleName == OPTION)
	{
		
	}

}

void TitleScene::render(void)
{
	if (_titleName == ANYBUTTON)
	{
		IMAGEMANAGER->findImage("AnyButtonBg")->render(getMemDC());
		IMAGEMANAGER->findImage("AnyButtonLogo")->alphaRender(getMemDC(), _logoRc.left, _logoRc.top, _alpha);

		//FONTMANAGER->drawText(getMemDC(), CENTER_X-150, _logoRc.bottom+10, "둥근모꼴", 25, 100, script,
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

	}
	
}


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
	_viSave = _vSave.begin();
	for (; _viSave != _vSave.end(); _viSave++)
	{
			_viSave->noneImg->render(getMemDC() ,_viSave->pos.x, _viSave->pos.y); // 임시 - 저장된 파일이 없다면 
		if (_saveIndex > 100)
		{
		} 
		else {
			// 저장된 파일이 있다면
			if (_viSave->select)
			{
				_viSave->onImg->render(getMemDC(), _viSave->pos.x, _viSave->pos.y);
				// slotNum
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,								 // 변수
					_viSave->pos.x - 20, _viSave->pos.y + _viSave->noneImg->getHeight()*0.5,		 // 위치
					"둥근모꼴", 25, 100, OTEXT);											 // 폰트

				// 플레이어 세이브  정보 
				LPCWSTR tempArea = L"침묵의 비탄 수도원"; // 임시 지역 텍스트 
				FONTMANAGER->drawText(getMemDC(), _viSave->pos.x + 80, _viSave->pos.y + 20,
					"둥근모꼴", 25, 100, tempArea, wcslen(tempArea), OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // 임시 포인트 
					_viSave->posEndX - 60, _viSave->pos.y + 20,
					"둥근모꼴", 25, 100, OTEXT);

				LPCWSTR tempTime = L"플레이 시간 : 2h 4m ~ 16.7% 완료"; // 임시 누적시간, 진행율
				FONTMANAGER->drawText(getMemDC(), _viSave->pos.x - 50, _viSave->pos.y + 66,
					"둥근모꼴", 25, 100, tempTime, wcslen(tempTime), OTEXT);
			}
			else
			{
				_viSave->offImg->render(getMemDC(), _viSave->pos.x, _viSave->pos.y);
				_tempPoint = 470; // 임시데이터 

				// slotNum
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,
					_viSave->pos.x - 20, _viSave->pos.y + _viSave->noneImg->getHeight()*0.5,
					"둥근모꼴", 25, 100, XTEXT);

				// 플레이어 세이브  정보 
				LPCWSTR tempArea = L"갈보리의 다리"; // 임시 지역 텍스트 
				FONTMANAGER->drawText(getMemDC(), _viSave->pos.x + 80, _viSave->pos.y + 20,
					"둥근모꼴", 25, 100, tempArea, wcslen(tempArea), XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // 임시 포인트 
					_viSave->posEndX - 60, _viSave->pos.y + 20,
					"둥근모꼴", 25, 100, XTEXT);

				LPCWSTR tempTime = L"플레이 시간 : 1h 14m ~ 38.1% 완료"; // 임시 누적시간, 진행율
				FONTMANAGER->drawText(getMemDC(), _viSave->pos.x - 50, _viSave->pos.y + 66,
					"둥근모꼴", 25, 100, tempTime, wcslen(tempTime), XTEXT);

			}
		}
	}
}


void TitleScene::addSaveData(int num)
{
	char temp[32];
	vector<string> data;

	// itoa:인티저 투 아스키 (정수형을 문자열로 반환)
	// 오류뜸ㅋ
	
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

	// 파일이름 생성 : save + SolotNum + .txt 로 문자 생성해서 저장 
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

