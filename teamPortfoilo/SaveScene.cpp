#include "Stdafx.h"
#include "SaveScene.h"


HRESULT SaveScene::init(void)
{
	// SAVE ------------
	// 세이브 파일이 있는지 체크하고, 토대로 세팅할 것. 
	for (int i = 1; i < 4; i++)
	{
		tagSaveSlot slotInfo;
		slotInfo.x = 140;
		slotInfo.y = 60 + (1 * 115);
		slotInfo.state = NONE; // 세이브 파일유무에 따라 상태 변경
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

	

	return S_OK;
}

void SaveScene::release(void)
{
	_viSave = _vSave.begin();
	for (; _viSave != _vSave.end(); _viSave++)
	{
		SAFE_DELETE(_viSave->noneImg);
		SAFE_DELETE(_viSave->onImg);
		SAFE_DELETE(_viSave->offImg);
	}
	_vSave.clear();



}

void SaveScene::update(void)
{
	if (KEYMANAGER->isOnceKeyDown(VK_ESCAPE))
	{
		SCENEMANAGER->changeScene("Title");
	}

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
		// 임시 씬 저장. 세이브 데이터에서 씬 정보 저장 필요?
		if (_saveIndex == 1) SCENEMANAGER->changeScene("Start");
		if (_saveIndex == 2) SCENEMANAGER->changeScene("Boss1");
		if (_saveIndex == 3) SCENEMANAGER->changeScene("Boss2");
	}

}

void SaveScene::render(void)
{

	IMAGEMANAGER->findImage("menuSaveBg")->render(getMemDC());
	showSaveData();

}

// SAVE ------------------------------------------------------------------------------------
void SaveScene::selectSaveData(int saveIndex)
{
	_viSave = _vSave.begin();
	for (; _viSave != _vSave.end(); _viSave++)
	{
		if (_viSave->num == saveIndex) _viSave->select = true;
		else _viSave->select = false;
	}
}

void SaveScene::showSaveData(void)
{
	IMAGEMANAGER->findImage("enter")->render(getMemDC(), CENTER_X + 20, WINSIZE_Y - 100);
	IMAGEMANAGER->findImage("esc")->render(getMemDC(), CENTER_X + 255, WINSIZE_Y - 100);

	_viSave = _vSave.begin();
	for (; _viSave != _vSave.end(); _viSave++)
	{
		/*
		if (_saveIndex < 100)
		{
			// 임시 - 저장된 파일이 없다면
			_viSave->noneImage->render(getMemDC(), _viSave->x, _viSave->y);

			// slotNum
			FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						 // 변수
				_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	 // 위치
				"둥근모꼴", 30, 100, OTEXT);

			// 저장 데이터 x , 새 게임
			FONTMANAGER->drawText(getMemDC(), (CENTER_X + 20) + IMAGEMANAGER->findImage("enter")->getWidth() + 10, WINSIZE_Y - 98,
				"둥근모꼴", 25, 100, _saveMenuText[0].text, wcslen(_saveMenuText[0].text), BTEXT);// 폰트

			// 뒤로가기
			FONTMANAGER->drawText(getMemDC(), (CENTER_X + 255) + IMAGEMANAGER->findImage("esc")->getWidth() +15, WINSIZE_Y - 98,
			"둥근모꼴", 25, 100, _saveMenuText[2].text, wcslen(_saveMenuText[2].text), BTEXT);

		}

		else*/
		{
			// 저장된 파일이 있다면
			if (_viSave->select)
			{
				_tempPoint = 1300; // 임시데이터 


				_viSave->onImg->render(getMemDC(), _viSave->x, _viSave->y);
				// slotNum
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						 // 변수
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	 // 위치
					"둥근모꼴", 30, 100, OTEXT);												 // 폰트

				// 플레이어 세이브  정보 
				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L"침묵의 비탄 수도원"; // 임시 지역 텍스트 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempArea, wcslen(tempArea), OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // 임시 포인트 
					_viSave->posEndX - 70, _viSave->y + 25,
					"둥근모꼴", 25, 100, OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L"플레이 시간 : 2h 4m ~ 16.7% 완료"; // 임시 누적시간, 진행율
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"둥근모꼴", 25, 100, tempTime, wcslen(tempTime), OTEXT);

				// 저장 데이터 o, 저장데이터로 계속
				FONTMANAGER->drawText(getMemDC(), (CENTER_X + 20) + IMAGEMANAGER->findImage("enter")->getWidth() + 65, WINSIZE_Y - 98,
					"둥근모꼴", 25, 100, _saveMenuText[1].text, wcslen(_saveMenuText[1].text), BTEXT);// 폰트

			}
			if (!_viSave->select)
			{
				// 저장파일은 있지만 선택하지 않으면
				_viSave->offImg->render(getMemDC(), _viSave->x, _viSave->y);
				_tempPoint = 470; // 임시데이터 

				// slotNum
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,
					"둥근모꼴", 30, 100, XTEXT);

				// 플레이어 세이브  정보 
				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L"갈보리의 다리"; // 임시 지역 텍스트 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempArea, wcslen(tempArea), XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // 임시 포인트 
					_viSave->posEndX - 70, _viSave->y + 25,
					"둥근모꼴", 25, 100, XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L"플레이 시간 : 1h 14m ~ 38.1% 완료"; // 임시 누적시간, 진행율
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"둥근모꼴", 25, 100, tempTime, wcslen(tempTime), XTEXT);

			}

			// 뒤로가기
			FONTMANAGER->drawText(getMemDC(), (CENTER_X + 255) + IMAGEMANAGER->findImage("esc")->getWidth() + 65, WINSIZE_Y - 98,
				"둥근모꼴", 25, 100, _saveMenuText[2].text, wcslen(_saveMenuText[2].text), BTEXT);
		}
	}


}

void SaveScene::addSaveData(int num)
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

void SaveScene::loadSaveData(int num)
{
	vector<string> vData = TEXTDATAMANAGER->load("save1.txt");
	// _x = atoi(vData[0].c_str());
	// _y = atoi(vData[1].c_str());
	// _currentHp = atoi(vData[2].c_str());
	// _maxHp = atoi(vData[3].c_str());

}




