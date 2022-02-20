#include "Stdafx.h"
#include "TempSoundTest.h"

HRESULT TempSoundTest::init(void)
{
	// 배경정도는 넣어보자..
	TEMPSOUNDMANAGER->addMp3FileWithKey("beam", "Resources/sounds/epic.mp3");
	TEMPSOUNDMANAGER->addMp3FileWithKey("ending", "Resources/sounds/end.mp3"); 
	TEMPSOUNDMANAGER->addWaveFileWithKey("8bit", "Resources/sounds/8bit.wav");

	return S_OK;
}

void TempSoundTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		TEMPSOUNDMANAGER->playSoundWithKey("beam");
		//TEMPSOUNDMANAGER->playSoundWithKey("ending");
	}

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		TEMPSOUNDMANAGER->playEffectSoundWave("Resources/sounds/8bit.wav");
	}
}
