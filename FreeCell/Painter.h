#pragma once

#define TOP_LEFT_CORNER (char)218
#define TOP_RIGHT_CORNER (char)191
#define BOTTOM_LEFT_CORNER (char)192
#define BOTTOM_RIGHT_CORNER (char)217
#define HORIZ (char)196
#define VERT (char)179

#define DTOP_LEFT_CORNER (char)201
#define DTOP_RIGHT_CORNER (char)187
#define DBOTTOM_LEFT_CORNER (char)200
#define DBOTTOM_RIGHT_CORNER (char)188
#define DHORIZ (char)205
#define DVERT (char)186

#define DBLUE_WHITE (FOREGROUND_BLUE | BACKGROUND_RED \
					| BACKGROUND_GREEN | BACKGROUND_BLUE \
					| BACKGROUND_INTENSITY)
#define CYAN_BLACK (FOREGROUND_BLUE | FOREGROUND_GREEN \
					| FOREGROUND_INTENSITY)
#define RED_WHITE (FOREGROUND_RED | FOREGROUND_INTENSITY \
					| BACKGROUND_RED | BACKGROUND_GREEN \
					| BACKGROUND_BLUE | BACKGROUND_INTENSITY)
#define WHITE_RED (FOREGROUND_RED | FOREGROUND_GREEN \
					| FOREGROUND_BLUE | FOREGROUND_INTENSITY\
					| BACKGROUND_RED | BACKGROUND_INTENSITY)
#define BLACK_WHITE (BACKGROUND_RED | BACKGROUND_GREEN \
					| BACKGROUND_BLUE | BACKGROUND_INTENSITY)
#define WHITE_BLACK (FOREGROUND_RED | FOREGROUND_GREEN \
					| FOREGROUND_BLUE | FOREGROUND_INTENSITY)

#include <windows.h>

#include "Card.h"

/************************************************************************
* Class: Painter.
*
* Purpose:
*		Manages the painting of various objects to the console.
*
* Manager functions:
*		Painter()
*			Constructor.
*
* Methods:
*		DrawCard(Card c)
*			Draws the passed card to the console.
*
*		DrawMenu()
*			Draws the sidebar menu.
*
*		DisplayWin()
*			Displays the winning credits to the screen.
*
*************************************************************************/

class Painter
{
public:
	Painter();

	void DrawCard(Card c);
	void DrawMenu();
	void DisplayWin();

	COORD cursor;
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD numWrit = 0;

	WORD attrib[48];
	char buffer[48];

	Card voidCard;
};