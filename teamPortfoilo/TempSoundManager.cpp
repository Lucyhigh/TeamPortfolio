#include "Stdafx.h"
#include "TempSoundManager.h"

HRESULT TempSoundManager::init()
{
	return S_OK;
}

void TempSoundManager::addMp3FileWithKey(string key, string fileName)
{
	string first="open \""; // 디렉토리를 찾아서 내용을 읽음
	string end = "\" type mpegvideo alias ";
	string finalQuery = first + fileName + end + key;

	// C++ 문자열을 C스타일로 변환 
	const char* str = finalQuery.c_str(); 

	// mciSendString() : 편재 장치에 명령어를 전송하여 필요한 장치를 구동시키는 함수
	// 문자열 명령어, 반환값 문자열, 반환될 길이, 핸들 콜백 
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::addWaveFileWithKey(string key, string fileName)
{
	string first = "open \""; // 디렉토리를 찾아서 내용을 읽음
	string end = "\" type waveaudio alias ";
	string finalQuery = first + fileName + end + key;

	// C++ 문자열을 C스타일로 변환 
	const char* str = finalQuery.c_str();

	// mciSendString() : 편재 장치에 명령어를 전송하여 필요한 장치를 구동시키는 함수
	// 문자열 명령어, 반환값 문자열, 반환될 길이, 핸들 콜백 
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::playEffectSoundWave(char* fileName)
{
	// 파일이름.wave , 핸들(NULL -> 파일명을 사용한다.), sound: 옵션 | 옵션 | 옵션
	// PlaySound(fileName, NULL, SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	// 사운드를 어떻게 재생할건지 : 파일 확인 , 옵션 | 반복 | 파일 없는 경우 경고문(안씀) 
	
	// 루프를 사용하는 경우 SND_ASYNC가 없으면 반복하는동안 컴파일러는 아무것도 할 수 없다.
	// SND_ASYNC : 재생하면서 다음 코드 실행(비동기적으로 작동하라는 플래그)
	// 비동기적 -> 스레드가 작동하나? -> 스레드가 작동한다면 무거운 코드겠군....
	PlaySound(fileName, NULL, SND_ASYNC );

}


void TempSoundManager::playSoundWithKey(string key)
{
	string first = "play ";
	string finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}

void TempSoundManager::stopMp3WithKey(string key)
{
	string first = "stop ";
	string finalQuery = "";
	finalQuery = first + key;

	const char* str = finalQuery.c_str();
	mciSendString(str, NULL, 0, NULL);
}
