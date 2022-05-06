#pragma once
#include <sdkddkver.h>

#define WIN32_LEAN_AND_MEAN 

#pragma warning(disable:4244)

#include <Windows.h>

#pragma comment(lib,"Winmm.lib")
#pragma comment (lib,"msimg32.lib")

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>

#include <mmsystem.h>
#include <mciapi.h>
#include <iostream>
#include <random>
#include <bitset>
#include <vector>
#include <map>
#include <cassert>
#include <algorithm>
#include <functional>
using namespace std;

#include <fstream>

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

#include "Text.h"

#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()
#define TEMPSOUNDMANAGER TempSoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()
#define TEXTDATAMANAGER TextDataManager::getSingleton()
#define SCENEMANAGER SceneManager::getSingleton()
#define WINNAME		 (LPTSTR)(TEXT("WindowsAPI"))


#ifdef FULLSCREEN
#define WINSTART_X	 1920  
#define WINSTART_Y	 1080

#define WINSIZE_X	 GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y	 GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE	 WS_POPUPWINDOW | WS_MAXWIZE
#endif 

#define WINSTART_X	 300
#define WINSTART_Y	 0
#define WINSIZE_X	 1200
#define WINSIZE_Y	 675
#define WINSTYLE	 WS_CAPTION | WS_SYSMENU
 
#define CENTER_X WINSIZE_X/2
#define CENTER_Y WINSIZE_Y/2
#define MGT true,RGB(255,0,255)
 
#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}
 
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

#include "GameManger.h"
#define GAMEMANAGER GameManger::getSingleton()

#define GETERROR -666
#define GAMESPEED 2