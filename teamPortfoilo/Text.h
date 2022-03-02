#pragma once

// O(Select) , X(NotSelect) , Title, Button , Menu(NotSelect) :  TEXT COLOR
#define OTEXT RGB(254, 211, 17)
#define XTEXT RGB(134, 118, 53)
#define TTEXT RGB(144,98,79)
#define BTEXT RGB(136,127,77)
#define MTEXT RGB(134,118,102)

struct tagText
{
	LPCWSTR name;
	LPCWSTR script;
};



struct tagImageWithText
{
	LPCWSTR name;
	string imageVec;
	LPCWSTR script;
};


struct tagOnlyText
{
	LPCWSTR text;
};