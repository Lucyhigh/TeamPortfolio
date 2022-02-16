
/*
PreCompilde Header (PCH)
- �ʿ��� ������ cpp �ϳ��� �����Ϸ��� �������Ͽ� .obj ������ �����, .obj ���ϸ��� �ڵ� ����ȭ��
�Ź� �ϱ� ����� ������ ���ϸ��� �Ľ��� ������Ѵ�.

- ����ȭ�� ���ؼ�, ����ӵ� ����� ���ؼ� ����Ѵ�.
*/

#pragma once


//�츮�� ���� apI�� ���������ε� �װ� ��ȯ���ִ� ����
// ���α׷����� ������ os�� ���� Windows���� �ڵ忡 ���Ե� �Լ�, ������� �����ϴµ� ���ȴ�
#include <SDKDDKVer.H>

//���� ������ �ʴ� ������ Windows������� ����
// �� GDI+ �� ����ϸ� ������� ���� ����
//#include<Ole2.h>
#define WIN32_LEAN_AND_MEAN    // GDI+ ���� �� �ȿ� �ִ� <ole.h> �̰� �ʿ���
//! Windows ��� ����:
#include <windows.h>

//! ������ �ܼ�â
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

//! c��Ÿ�� ��� �����Դϴ�.
//stdli c��� ǥ�� ���̺귯�� �Լ����
#include <stdlib.h>
//�����
#include <stdio.h>
// �޸𸮰��� -> c����
//#include <ma��loc.h>
//memset,mecpy,memmove  �޸� �������� �ڸ�ǰ�� ���� ��ŭ �߿��ϴ�
//#include <memory.h>

// �⺻������ �����ڵ�(���ڿ� ��� �������)
#include <tchar.h>
#include <time.h>
/*
���ڿ�:
�����ڵ�(WBCS) vs ��Ƽ����Ʈ(MBCS)

���ڵ� ��Ģ:
��ǻ�� �ʱ⿡�� �ƽ�Ű OR EBCDIC �� �ΰ����� ���ؼ� ǥ���� �ߴ� -> ��ǻ�Ϳ��� �ǻ�����
-> �ǻ������� �� �� ����� ���� -> ���� 1����Ʈ
-> ����� ? -> �ѱ� �߱� �Ϻ��� -> �ѱ� 2����Ʈ

�̸� �ذ��ϱ� ���� ���°� -> �����ڵ�
-> ���� ǥ������ �������� -> ����+ ���ڿ� -> ��ǻ�Ϳ��� �ϰ��ǰ� ó���� �� �ְԲ�
*/
//#include <assert.h>
#include <cassert> //c++��


//! c++��Ÿ�� ��� �����Դϴ�.
#include <iostream>
#include <random>

//��Ʈ������ ���� ���� �������ִ� �Լ��� �������ش�. + STL
// - reset(), set(), flip(), all(), any()
#include <bitset>
#include <vector>
#include <map>

using namespace std;

// # ���� ���� ��������� �̰��� �߰�
#include "CommonMarcroFuntion.h"
#include "RandomFunction.h"
#include"KeyManager.h"
#include "ImageManager.h"
#include "FontManager.h"
#include "Utils.h"

using namespace MY_UTIL;


// # ��Ŭ���� �̰��� �߰�
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define FONTMANAGER FontManager::getSingleton()

// # ��ũ�� # (������â �ʱ�ȭ)
#define WINNAME				(LPSTR)(TEXT("WindowsAPI"))

//��üȭ��
//#define FULLSCREEN

#ifdef FULLSCREEN  //������ ������
#define WINSTART_X			1920 //ȭ���ػ� Ǯ��ũ��...��������� ��������
#define WINSTART_Y			1080

//GetSystemMetrics(): ���ڷ� ���޵Ǵ� �ý��� ���� ���� ��ȯ
// �� SM_CXSCREEN ���� ȭ�� �ػ� x�� ��ȯ
// �� SM_CYSCREEN ���� ȭ�� �ػ� y�� ��ȯ
#define WINSIZE_X			GetSystemMetrics(SM_CXSCREEN)			
#define WINSIZE_Y			GetSystemMetrics(SM_CYSCREEN)	
#define WINSTYLE			WS_POPUPWINDOW | WS_MAXIMIZE //���â Ÿ��Ʋ�� |  ���â �޴�????

#else
#define WINSTART_X			150
#define WINSTART_Y			50
#define WINSIZE_X			1280			
#define WINSIZE_Y			800
#define WINSTYLE			WS_CAPTION | WS_SYSMENU   //���â Ÿ��Ʋ�� |  ���â �޴�
#endif
#define CENTER_X			WINSIZE_X/2
#define CENTER_Y			WINSIZE_Y/2
// # ��ũ�� �Լ� # (Ŭ�������� �����Ҵ�� �κ� ����)
#define SAFE_DELETE(p)				{if(p) {delete(p); (p)=nullptr;}}
#define SAFE_DELETE_ARRAY(p)		{if(p) {delete[](p); (p)=nullptr;}}
#define SAFE_RELEASE(p)				{if(p) {(p)->release(); (p)=nullptr;}}



// # ��������
// h or cpp���� ������ �����ؼ� ���� ����
// ������ ������ �����ؼ� ����Ѵ�  ���ʿ��� �ָ� ����
// extern << �� ���Ͽ�
extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;

#define GAMESPEED 5
#define GETERROR -666
#include <functional>