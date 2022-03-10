#include "Stdafx.h"
#include "SaveScene.h"

HRESULT SaveScene::init(void)
{
	for (int i = 1; i < 4; i++)
	{
		tagSaveSlot slotInfo;
		slotInfo.x = 170;
		slotInfo.y = 40 + (i * 135);
		slotInfo.state = NONE; 
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

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		if (_saveIndex == 1) SCENEMANAGER->changeScene("Last");
		if (_saveIndex == 2) SCENEMANAGER->changeScene("Opening");
		if (_saveIndex == 3) SCENEMANAGER->changeScene("Opening");
	}

}

void SaveScene::render(void)
{

	IMAGEMANAGER->findImage("menuSaveBg")->render(getMemDC());
	showSaveData();
}

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
	FONTMANAGER->drawText(getMemDC(), (CENTER_X + 255) + IMAGEMANAGER->findImage("esc")->getWidth() + 65, WINSIZE_Y - 98,
		"µÕ±Ù¸ð²Ã", 25, 100, _saveMenuText[2].text, wcslen(_saveMenuText[2].text), BTEXT);

	_viSave = _vSave.begin();
	for (; _viSave != _vSave.end(); _viSave++)
	{
		_viSave->noneImg->render(getMemDC(), _viSave->x, _viSave->y);

		if (_viSave->num == 1) 
		{
			if (_viSave->select) 
			{
				_tempPoint = 1300; 

				_viSave->onImg->render(getMemDC(), _viSave->x, _viSave->y);
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	
					"µÕ±Ù¸ð²Ã", 30, 100, OTEXT);												

				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L"±âÀûÀÇ ¿ä¶÷";  
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, tempArea, wcslen(tempArea), OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				FONTMANAGER->drawTextValue(getMemDC(), _tempPoint,
					_viSave->posEndX - 70, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L"ÇÃ·¹ÀÌ ½Ã°£ : 4h 4m ~ 86.7% ¿Ï·á"; 
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"µÕ±Ù¸ð²Ã", 25, 100, tempTime, wcslen(tempTime), OTEXT);

				FONTMANAGER->drawText(getMemDC(), (CENTER_X + 20) + IMAGEMANAGER->findImage("enter")->getWidth() + 65, WINSIZE_Y - 98,
					"µÕ±Ù¸ð²Ã", 25, 100, _saveMenuText[1].text, wcslen(_saveMenuText[1].text), BTEXT);

			}
			else
			{
				_viSave->offImg->render(getMemDC(), _viSave->x, _viSave->y);

				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	
					"µÕ±Ù¸ð²Ã", 30, 100, XTEXT);												

				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L"±âÀûÀÇ ¿ä¶÷"; 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, tempArea, wcslen(tempArea), XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				FONTMANAGER->drawTextValue(getMemDC(), _tempPoint, 
					_viSave->posEndX - 70, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L"ÇÃ·¹ÀÌ ½Ã°£ : 4h 4m ~ 86.7% ¿Ï·á"; 
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"µÕ±Ù¸ð²Ã", 25, 100, tempTime, wcslen(tempTime), XTEXT);

			}
		}
		if (_viSave->num == 2)  
		{
			if (_viSave->select)
			{

				_viSave->onImg->render(getMemDC(), _viSave->x, _viSave->y);
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	
					"µÕ±Ù¸ð²Ã", 30, 100, OTEXT);												

				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L" ";   
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, tempArea, wcslen(tempArea), OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempPoint = L" ";
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 70, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, tempPoint, wcslen(tempPoint), OTEXT);
				 
				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L" "; 
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"µÕ±Ù¸ð²Ã", 25, 100, tempTime, wcslen(tempTime), OTEXT);

				FONTMANAGER->drawText(getMemDC(), (CENTER_X + 20) + IMAGEMANAGER->findImage("enter")->getWidth() + 95, WINSIZE_Y - 98,
					"µÕ±Ù¸ð²Ã", 25, 100, _saveMenuText[0].text, wcslen(_saveMenuText[0].text), BTEXT);

			}
			else
			{
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	
					"µÕ±Ù¸ð²Ã", 30, 100, XTEXT);												

				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L" "; 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, tempArea, wcslen(tempArea), XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempPoint = L" ";
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 70, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, tempPoint, wcslen(tempPoint), XTEXT);
		
				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L" "; 
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"µÕ±Ù¸ð²Ã", 25, 100, tempTime, wcslen(tempTime), XTEXT);

			}
		}


		if (_viSave->num == 3)  
		{
			if (_viSave->select)  
			{

				_viSave->onImg->render(getMemDC(), _viSave->x, _viSave->y);
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	
					"µÕ±Ù¸ð²Ã", 30, 100, OTEXT);												

				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L" ";  
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, tempArea, wcslen(tempArea), OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempPoint = L" ";
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 70, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, tempPoint, wcslen(tempPoint), OTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L" "; 
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"µÕ±Ù¸ð²Ã", 25, 100, tempTime, wcslen(tempTime), OTEXT);

				FONTMANAGER->drawText(getMemDC(), (CENTER_X + 20) + IMAGEMANAGER->findImage("enter")->getWidth() + 95, WINSIZE_Y - 98,
					"µÕ±Ù¸ð²Ã", 25, 100, _saveMenuText[0].text, wcslen(_saveMenuText[0].text), BTEXT);

			}
			else
			{
				FONTMANAGER->drawTextValue(getMemDC(), _viSave->num,						 
					_viSave->x - 20, (_viSave->y + _viSave->noneImg->getHeight()*0.5) - 7,	 
					"µÕ±Ù¸ð²Ã", 30, 100, XTEXT);												 

				SetTextAlign(getMemDC(), TA_LEFT);
				LPCWSTR tempArea = L" "; 
				FONTMANAGER->drawText(getMemDC(), _viSave->x + 90, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, tempArea, wcslen(tempArea), XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempPoint = L" ";
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 70, _viSave->y + 25,
					"µÕ±Ù¸ð²Ã", 25, 100, tempPoint, wcslen(tempPoint), XTEXT);

				SetTextAlign(getMemDC(), TA_RIGHT);
				LPCWSTR tempTime = L" ";  
				FONTMANAGER->drawText(getMemDC(), _viSave->posEndX - 50, _viSave->y + 76,
					"µÕ±Ù¸ð²Ã", 25, 100, tempTime, wcslen(tempTime), XTEXT);
			}
		}
	}
}

void SaveScene::addSaveData(int num)
{
	char temp[32];
	vector<string> data;
	float _x = GAMEMANAGER->getPlayer()->getCollider().left;
	float _y = GAMEMANAGER->getPlayer()->getCollider().top;
	float _currentHp = GAMEMANAGER->getPlayer()->getHp(BaseEnum::STATE);
	float _maxHp = GAMEMANAGER->getPlayer()->getHp(BaseEnum::MAX);
	float _currentMp = GAMEMANAGER->getPlayer()->getMp(BaseEnum::STATE);
	float _maxMp = GAMEMANAGER->getPlayer()->getMp(BaseEnum::MAX);
 
	char saveFileName[128];
	int saveNum = num;

	TEXTDATAMANAGER->save("save1.txt", data);
}

void SaveScene::loadSaveData(int num)
{
	vector<string> vData = TEXTDATAMANAGER->load("save1.txt");
}