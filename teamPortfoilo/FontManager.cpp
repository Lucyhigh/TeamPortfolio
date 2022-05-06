#include "stdafx.h"
#include "FontManager.h"

void FontManager::drawText(HDC hdc, int destX, int destY, char* fileName, char* fontName, int fontSize, int fontWidth, char* printString, int Iength, COLORREF color)
{
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, char * printString, int Iength, COLORREF color)
{

}


void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, string str, int Iength, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	TextOut(hdc, destX, destY, str.c_str(), Iength);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, LPCWSTR printString, int Iength, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	TextOutW(hdc, destX, destY, printString, Iength);

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, LPCWSTR* printStringArr, int Iength, COLORREF color)
{
	int arraySize = sizeof(printStringArr) / sizeof(*printStringArr);
}

void FontManager::drawTextValue(HDC hdc, int Value, int destX, int destY, char* fontName, int fontSize, int fontWidth, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	char int2char[256];

	wsprintf(int2char, "%d", Value);
 	TextOut(hdc, destX, destY, int2char, strlen(int2char));

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}

void FontManager::drawTextValue(HDC hdc, float Value, int destX, int destY, char* fontName, int fontSize, int fontWidth, COLORREF color)
{
	SetBkMode(hdc, TRANSPARENT);

	HFONT hFont = CreateFont
	(
		fontSize, 0, 0, 5, fontWidth,
		0, 0, 0,
		HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName)
	);

	auto oldFont = (HFONT)SelectObject(hdc, hFont);
	auto oldColor = GetTextColor(hdc);

	SetTextColor(hdc, color);
	char float2char[256];

	wsprintf(float2char, "%d", Value);
	TextOut(hdc, destX, destY, float2char, strlen(float2char));

	SelectObject(hdc, oldFont);
	DeleteObject(hFont);

	SetTextColor(hdc, oldColor);
}
