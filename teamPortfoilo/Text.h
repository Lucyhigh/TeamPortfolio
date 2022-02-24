#pragma once

// O , X , Button TEXT COLOR
#define OTEXT RGB(254, 211, 17)
#define XTEXT RGB(134, 118, 53)
#define BTEXT RGB(136,127,77)

struct tagText
{
	LPCWSTR name;
	LPCWSTR script;
};



struct tagImageWithText
{
	LPCWSTR name;
	vector<string> imageMoodVec;
	LPCWSTR script;
};


struct tagOnlyText
{
	LPCWSTR text;
};