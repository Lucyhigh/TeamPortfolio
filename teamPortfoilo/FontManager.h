#pragma once
#include "SingletonBase.h"
class FontManager : public SingletonBase <FontManager>
{
public:
	void drawText(HDC hdc, int destX, int destY, char* fileName, char* fontName, int fontSize, int fontWidth, char* printString, int Iength, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, char* printString, int Iength, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, string str, int Iength, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, LPCWSTR printStringArr, int Iength, COLORREF color);

	void drawText(HDC hdc, int destX, int destY, char* fontName, int fontSize, int fontWidth, LPCWSTR* printString, int Iength, COLORREF color);

	void drawTextValue(HDC hdc, int Value, int destX, int destY, char* fontName, int fontSize, int fontWidth, COLORREF color);
	void drawTextValue(HDC hdc, float Value, int destX, int destY, char* fontName, int fontSize, int fontWidth, COLORREF color);


	FontManager() { }
	~FontManager() { }
};

