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
	wsprintf(str, "힘내 꼬깔... 넌 할 수 있어 :D ");
	TextOut(getMemDC(), 140, 150, str, strlen(str));

	wsprintf(str, "난 깃허브 토큰이 싫다...");
	TextOut(getMemDC(), 230, 200, str, strlen(str));

	wsprintf(str, "이제 됨");
	TextOut(getMemDC(), 320, 250, str, strlen(str));

    wsprintf(str, "컴파일러가 나를 비웃는 느낌이다");
    TextOut(getMemDC(), 350, 300, str, strlen(str));

	wsprintf(str, "디버그 파일 같이 올려서 오류 터짐 ㅠㅠ ");
	TextOut(getMemDC(), 400, 350, str, strlen(str));

	wsprintf(str, "초대만 빨리 확인했어도...");
	TextOut(getMemDC(), 450, 400, str, strlen(str));

	wsprintf(str, "이 쉬운걸 너무 어렵게햇다...");
	TextOut(getMemDC(), 550, 450, str, strlen(str));

    wsprintf(str, "그래도 이제는 된당");
    TextOut(getMemDC(), 700, 100, str, strlen(str));

	wsprintf(str, "여기 분위기 조아 사물함에 가방 잘들어가서 다행");
	TextOut(getMemDC(), 650, 150, str, strlen(str));

	wsprintf(str, "거기에 있던 규칙보다는 좀 조용한 분위기인가 보네요");
	TextOut(getMemDC(), 650, 200, str, strlen(str));

	wsprintf(str, "난 일단 오피스 신청햇어");
	TextOut(getMemDC(), 550, 250, str, strlen(str));

    wsprintf(str, "의석이 언제 출발하닝");
    TextOut(getMemDC(), 450, 280, str, strlen(str));

	wsprintf(str, "치킨먹고싶당....");
	TextOut(getMemDC(), 220, 380, str, strlen(str));

	wsprintf(str, "오늘만 집에서 휴식을...");
	TextOut(getMemDC(), 140, 450, str, strlen(str));


	this->getBackBuffer()->render(getHDC()); //백버퍼의 내용을 HDC에 그린다.
}