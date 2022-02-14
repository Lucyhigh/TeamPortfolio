#include "stdafx.h"
#include "MainGame.h"

HRESULT MainGame::init(void) //초기화
{
	GameNode::init(TRUE);
	IMAGEMANAGER->addImage("슈팅 맵", "Resources/Images/BackGround/ShootingBG.bmp", WINSIZE_X,WINSIZE_Y);

	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();	
}

void MainGame::update(void) // 갱신
{
	GameNode::update();
}

void MainGame::render(void) // 그려줘
{
	//검은색 빈 비트맵
	//PatBlt() : 사각형 영역을 브러쉬로 채우는 함수
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	IMAGEMANAGER->findImage("슈팅 맵")->render(getMemDC());
    char str[128];
    wsprintf(str, "꼬깔 원정대 영차영차");
    TextOut(getMemDC(), 100, 100, str, strlen(str));

	char str1[128];
	wsprintf(str1, "힘내 꼬깔... 넌 할 수 있어 :D ");
	TextOut(getMemDC(), 140, 150, str1, strlen(str1));

	wsprintf(str, "난 깃허브 토큰이 싫다...");
	TextOut(getMemDC(), 230, 200, str, strlen(str));

	wsprintf(str, "이제 됨");
	TextOut(getMemDC(), 320, 250, str, strlen(str));

    wsprintf(str, "컴파일러가 나를 비웃는 느낌이다");
    TextOut(getMemDC(), 350, 300, str, strlen(str));

	wsprintf(str, "디버그 파일 같이 올려서 오류 터졌음.. 다음부터는 조심해줘");
	TextOut(getMemDC(), 400, 350, str, strlen(str));

	this->getBackBuffer()->render(getHDC()); //백버퍼의 내용을 HDC에 그린다.
}