
/*
PreCompilde Header (PCH)
- 필요한 이유는 cpp 하나당 컴파일러가 컴파일하여 .obj 파일을 만들고, .obj 파일마다 코드 최적화를
매번 하기 힘들기 떄문에 파일마다 파싱을 해줘야한다.

- 최적화를 위해서, 실행속도 향상을 위해서 사용한다.
*/

#pragma once


//우리가 쓰는 apI는 리눅스꺼인데 그걸 변환해주는 애임
// 프로그램에서 지원할 os에 따라 Windows헤어데서 코드에 포함될 함수, 상수등을 제어하는데 사용된다
#include <SDKDDKVer.H>

//거의 사용되지 않는 내용은 Windows헤더에서 제외
// ㄴ GDI+ 를 사용하면 헤더파일 봉인 해제
//#include<Ole2.h>
#define WIN32_LEAN_AND_MEAN    // GDI+ 쓸때 이 안에 있는 <ole.h> 이게 필요함
//! Windows 헤더 파일:
#include <windows.h>

//! 디버깅용 콘소창
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! c런타임 헤더 파일입니다.
//stdli c언어 표준 라이브러리 함수헤더
#include <stdlib.h>
//입출력
#include <stdio.h>
// 메모리관리 -> c언어에서
//#include <maㅣloc.h>
//memset,mecpy,memmove  메모리 관련으로 자매품이 많은 만큼 중요하다
//#include <memory.h>

// 기본적으로 유니코드(문자열 출력 헤더포함)
#include <tchar.h>
#include <time.h>
/*
문자열:
유니코드(WBCS) vs 멀티바이트(MBCS)

인코딩 규칙:
컴퓨터 초기에는 아스키 OR EBCDIC 이 두가지를 통해서 표현을 했다 -> 컴퓨터에게 의사전달
-> 의사전달을 할 때 영어로 전달 -> 영어 1바이트
-> 영어로 ? -> 한글 중국 일본어 -> 한글 2바이트

이를 해결하기 위해 나온게 -> 유니코드
-> 국제 표준으로 관리하자 -> 문자+ 문자열 -> 컴퓨터에서 일관되게 처리할 수 있게끔
*/
//#include <assert.h>
#include <cassert> //c++용


//! c++런타임 헤더 파일입니다.
#include <iostream>
#include <random>

//비트연산을 좀더 쉽게 관리해주는 함수를 지원해준다. + STL
// - reset(), set(), flip(), all(), any()
#include <bitset>
#include <vector>
#include <map>

using namespace std;

// # 내가 만든 헤더파일을 이곳에 추가
#include "CommonMarcroFuntion.h"
#include "RandomFunction.h"
#include"KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "Utils.h"

using namespace MY_UTIL;


// # 싱클톤을 이곳에 추가
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()

// # 매크로 # (윈도우창 초기화)
#define WINNAME				(LPSTR)(TEXT("WindowsAPI"))

//전체화면
//#define FULLSCREEN

#ifdef FULLSCREEN  //선택적 컴파일
#define WINSTART_X			1920 //화면해상도 풀스크린...영상용으로 게임찍어라
#define WINSTART_Y			1080

//GetSystemMetrics(): 인자로 전달되는 시스템 설정 정보 반환
// ㄴ SM_CXSCREEN 현재 화면 해상도 x축 반환
// ㄴ SM_CYSCREEN 현재 화면 해상도 y축 반환
#define WINSIZE_X			GetSystemMetrics(SM_CXSCREEN)			
#define WINSIZE_Y			GetSystemMetrics(SM_CYSCREEN)	
#define WINSTYLE			WS_POPUPWINDOW | WS_MAXIMIZE //출력창 타이틀바 |  출력창 메뉴????

#else
#define WINSTART_X			150
#define WINSTART_Y			50
#define WINSIZE_X			1280			
#define WINSIZE_Y			800
#define WINSTYLE			WS_CAPTION | WS_SYSMENU   //출력창 타이틀바 |  출력창 메뉴
#endif
#define CENTER_X			WINSIZE_X/2
#define CENTER_Y			WINSIZE_Y/2
// # 매크로 함수 # (클래스에서 동적할당된 부분 해제)
#define SAFE_DELETE(p)				{if(p) {delete(p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[](p); (p)=nullptr;}}
#define SAFE_RELEASE(p)				{if(p) {(p)->release(); (p)=nullptr;}}



// # 전역변수
// h or cpp에서 변수를 공유해서 쓰기 위함
// 편리함을 얻지만 주의해서 써야한다  꼭필요한 애만 쓸것
// extern << 에 대하여
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
