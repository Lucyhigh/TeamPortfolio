#include "Stdafx.h"
#include "SaveScene.h"


HRESULT SaveScene::init(void)
{
	// SAVE ------------
	// 세이브 파일이 있는지 체크하고, 토대로 세팅할 것. 
	for (int i = 1; i < 4; i++)
	{
		tagSaveSlot slotInfo;
		slotInfo.x = 170;
		slotInfo.y = 40 + (i * 135);
		slotInfo.state = NONE; // 세이브 파일유무에 따라 상태 변경
		slotInfo.noneImg = new Image;
		slotInfo.noneImg->init("Resources/Images/UI/saveNoData.bmp", slotInfo.x, slotInfo.y, 848, 112, MGT);
		slotInfo.onImg = new Image;
		slotInfo.onImg->init("Resources/Images/UI/saveOn.bmp", slotInfo.x, slotInfo.y, 848, 112, MGT);
		slotInfo.offImg = new Image;
		slotInfo.offImg->init("Resources/Images/UI/saveOff.bmp", slotInfo.x, slotInfo.y, 848, 112, MGT);
		slotInfo.num = i;
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
		if (_saveIndex == 1) SCENEMANAGER->changeScene("Boss2");
		if (_saveIndex == 2) SCENEMANAGER->changeScene("Opening");
		if (_saveIndex == 3) SCENEMANAGER->changeScene("Opening");
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
	// 뒤로가기
	FONTMANAGER->drawText(getMemDC(), (CENTER_X + 255) + IMAGEMANAGER->findImage("esc")->getWidth() + 65, WINSIZE_Y - 98,
		"둥근모꼴", 25, 100, _saveMenuText[2].text, wcslen(_saveMenuText[2].text), BTEXT);

	_viSave = _vSave.begin();
	for (; _viSave != _vSave.end(); _viSave++)
	{
		_viSave->noneImg->render(getMemDC(), _viSave->x, _viSave->y);

		if (_viSave->num == 1) // 1번슬롯 
		{
			// 저장된 파일을 선택 
			if (_viSave->select) //+조건으로 저장파일 있는지 확인
			{
				_tempPoint = 1300; // 임시데이터 

				_viSave->onImg->render(getMemDC(), _viSave->x, _viSave->y);
				// slotNum
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						 // 변수
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	 // 위치
					"둥근모꼴", 30, 100, OTEXT);												 // 폰트

				// 플레이어 세이브  정보 
				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L"알베로의 납골당"; // 임시 지역 텍스트 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempArea, wcslen(tempArea), OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // 임시 포인트 
					_viSave->posEndX - 70, _viSave->y + 25,
					"둥근모꼴", 25, 100, OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L"플레이 시간 : 4h 4m ~ 86.7% 완료"; // 임시 누적시간, 진행율
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"둥근모꼴", 25, 100, tempTime, wcslen(tempTime), OTEXT);

				// 저장 데이터 o, 저장데이터로 계속
				FONTMANAGER->drawText(getMemDC(), (CENTER_X + 20) + IMAGEMANAGER->findImage("enter")->getWidth() + 65, WINSIZE_Y - 98,
					"둥근모꼴", 25, 100, _saveMenuText[1].text, wcslen(_saveMenuText[1].text), BTEXT);

			}
			else
			{
				_viSave->offImg->render(getMemDC(), _viSave->x, _viSave->y);

				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						 // 변수
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	 // 위치
					"둥근모꼴", 30, 100, XTEXT);												 // 폰트

				// 플레이어 세이브  정보 
				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L"알베로의 납골당"; // 임시 지역 텍스트 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempArea, wcslen(tempArea), XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // 임시 포인트 
					_viSave->posEndX - 70, _viSave->y + 25,
					"둥근모꼴", 25, 100, XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L"플레이 시간 : 4h 4m ~ 86.7% 완료"; // 임시 누적시간, 진행율
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"둥근모꼴", 25, 100, tempTime, wcslen(tempTime), XTEXT);

			}
		}
		if (_viSave->num == 2) // 2번슬롯 
		{
			// 빈슬롯을 선택 
			if (_viSave->select) //+if로 저장파일 있는지 확인
			{
				//_tempPoint = 1300; // 임시데이터 

				_viSave->onImg->render(getMemDC(), _viSave->x, _viSave->y);
				// slotNum
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						 // 변수
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	 // 위치
					"둥근모꼴", 30, 100, OTEXT);												 // 폰트

				// 플레이어 세이브  정보 
				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L" "; // 임시 지역 텍스트 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempArea, wcslen(tempArea), OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempPoint = L" ";
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 70, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempPoint, wcslen(tempPoint), OTEXT);
				//FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // 임시 포인트 
				//	_viSave->posEndX - 70, _viSave->y + 25,
				//	"둥근모꼴", 25, 100, OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L" "; // 임시 누적시간, 진행율
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"둥근모꼴", 25, 100, tempTime, wcslen(tempTime), OTEXT);

				// 저장 데이터 o, 새 게임
				FONTMANAGER->drawText(getMemDC(), (CENTER_X + 20) + IMAGEMANAGER->findImage("enter")->getWidth() + 95, WINSIZE_Y - 98,
					"둥근모꼴", 25, 100, _saveMenuText[0].text, wcslen(_saveMenuText[0].text), BTEXT);

			}
			else
			{
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						 // 변수
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	 // 위치
					"둥근모꼴", 30, 100, XTEXT);												 // 폰트

				// 플레이어 세이브  정보 
				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L" "; // 임시 지역 텍스트 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempArea, wcslen(tempArea), XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempPoint = L" ";
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 70, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempPoint, wcslen(tempPoint), XTEXT);
				//FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // 임시 포인트 
				//	_viSave->posEndX - 70, _viSave->y + 25,
				//	"둥근모꼴", 25, 100, XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L" "; // 임시 누적시간, 진행율
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"둥근모꼴", 25, 100, tempTime, wcslen(tempTime), XTEXT);

			}
		}


		if (_viSave->num == 3) // 3번슬롯 
		{
			// 빈슬롯을 선택 
			if (_viSave->select) //+if로 저장파일 있는지 확인
			{
				//_tempPoint = 1300; // 임시데이터 

				_viSave->onImg->render(getMemDC(), _viSave->x, _viSave->y);
				// slotNum
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						 // 변수
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	 // 위치
					"둥근모꼴", 30, 100, OTEXT);												 // 폰트

				// 플레이어 세이브  정보 
				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L" "; // 임시 지역 텍스트 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempArea, wcslen(tempArea), OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempPoint = L" ";
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 70, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempPoint, wcslen(tempPoint), OTEXT);
				//FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // 임시 포인트 
				//	_viSave->posEndX - 70, _viSave->y + 25,
				//	"둥근모꼴", 25, 100, OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L" "; // 임시 누적시간, 진행율
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"둥근모꼴", 25, 100, tempTime, wcslen(tempTime), OTEXT);

				// 저장 데이터 o, 새 게임.
				FONTMANAGER->drawText(getMemDC(), (CENTER_X + 20) + IMAGEMANAGER->findImage("enter")->getWidth() + 95, WINSIZE_Y - 98,
					"둥근모꼴", 25, 100, _saveMenuText[0].text, wcslen(_saveMenuText[0].text), BTEXT);

			}
			else
			{
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						 // 변수
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	 // 위치
					"둥근모꼴", 30, 100, XTEXT);												 // 폰트

				// 플레이어 세이브  정보 
				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L" "; // 임시 지역 텍스트 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempArea, wcslen(tempArea), XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempPoint = L" ";
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 70, _viSave->y + 25,
					"둥근모꼴", 25, 100, tempPoint, wcslen(tempPoint), XTEXT);
				//FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, // 임시 포인트 
				//	_viSave->posEndX - 70, _viSave->y + 25,
				//	"둥근모꼴", 25, 100, XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L" "; // 임시 누적시간, 진행율
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"둥근모꼴", 25, 100, tempTime, wcslen(tempTime), XTEXT);


			}
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




