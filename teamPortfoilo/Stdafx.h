#pragma once
#include <sdkddkver.h>

// 거의 사용되지 않는 내용은 Windows 헤더에서 제외
#define WIN32_LEAN_AND_MEAN 

// 형변환 데이터 손실 
#pragma warning(disable:4244)

//! Windows 헤더 파일
#include <Windows.h>

// 디버깅용 콘솔창
//!라이브러리
#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")
#pragma comment(lib,"Winmm.lib")
// 알파 블렌드를 사용하기 위한 라이브러리 추가 
#pragma comment (lib,"msimg32.lib")

//! C 런타임 헤더 파일
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

// 윈도우 내장 재생 라이브러리 
// PlaySound()를 사용하기 위해 
#include <mmsystem.h>

// Media Control Interface(장치관리자) API 
// mciSendString()을 사용하기 위해 
#include <mciapi.h>

//! C++ 런타임 헤더 파일
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
// bind 함수 기능 묶어주는
#include <functional>
using namespace std;

//===================================
// # 내가 만든 헤더파일을 이곳에 추가 #
//===================================
#include "CommonMarcroFuntion.h"
#include "randomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "TempSoundManager.h"
#include "Utils.h"
#include "TimeManager.h"
#include "TextDataManager.h"
#include "SceneManager.h"

using namespace MY_UTIL;


//========================
// # 싱글톤을 이곳에 추가 #
//========================
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()

//============================
// # 매크로 # (윈도우창 초기화)
//============================
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))

//#define FULLSCREEN

#ifdef FULLSCREEN
#define WINSTART_X	 1920 // 모니터에 따라 다름 
#define WINSTART_Y	 1080
// GetSystemMetrics 인자로 전달되는 시스템 설정 정보 현황
// ㄴSM_CXSCREEN / SM_CYSCREEN :  현재 화면 해상도 X, Y축 반환 
#define WINSIZE_X	 GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y	 GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE	 WS_POPUPWINDOW | WS_MAXWIZE

#else //1200*675 기준으로 제작중 바닥은 WINSIZE_Y-35
#define WINSTART_X	 300
#define WINSTART_Y	 0
#define WINSIZE_X	 1200
#define WINSIZE_Y	 675
#define WINSTYLE	 WS_CAPTION | WS_SYSMENU
#endif 


//============================
// # 매크로 # (기능 및 효율)
//============================
#define CENTER_X WINSIZE_X/2
#define CENTER_Y WINSIZE_Y/2
#define MGT true,RGB(255,0,255)

//===============================================
// # 매크로 함수 # (클래스에서 동적할당된 부분 해제)
//===============================================
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

//=============
// # 전역변수 #
//=============
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

#include "GameManger.h"
#define GAMEMANAGER GameManger::getSingleton()

#define GETERROR -666
#define GAMESPEED 10