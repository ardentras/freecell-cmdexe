/*************************************************************
* Author:			Shaun Rasmusen
* Filename:			Painter.cpp
* Date Created:		2/13/2017
* Modifications:	None.
************************************************************/
#define _CRT_SECURE_NO_WARNINGS 0
#include "Painter.h"

const char * logo =
"|      | "
"| ____ | "
"| |__  | "
"| |    | "
"|  __  | "
"| |__) | "
"| |  \\ | "
"|  ___ | "
"| |__  | "
"| |___ | "
"|  ___ | "
"| |__  | "
"| |___ | "
"|  ___ | "
"| /    | "
"| \\___ | "
"|  ___ | "
"| |__  | "
"| |___ | "
"|      | "
"| |    | "
"| |___ | "
"|      | "
"| |    | "
"| |___ | "
"|      | "
"|      |\0";

/************************************************************************
* Purpose: Default ctor.
*
* Precondition:
*		None.
*
* Postcondition:
*		Initializes all variables to the default state and draws the
*		sidebar menu.
*
************************************************************************/

Painter::Painter() : voidCard(Card(RERR, SERR, 1))
{
	DrawMenu();
}

/************************************************************************
* Purpose: Displays a single card to the console.
*
* Precondition:
*		c - A Card object to be drawn.
*
* Postcondition:
*		Prints a Card object to the console in the form of:
*			?????
*			?R  ?
*			? S ?
*			?  R?
*			?????
*		Will print differently based on the type attribute of the Card.
*
************************************************************************/

void Painter::DrawCard(Card c)
{
	buffer[0] = DTOP_LEFT_CORNER;
	for (int i = 1; i < 4; i++)
		buffer[i] = DHORIZ;
	buffer[4] = DTOP_RIGHT_CORNER;

	for (int i = 1; i < 4; i++)
	{
		buffer[i * 5] = DVERT;
		for (int j = 1; j < 4; j++)
			buffer[i * 5 + j] = ' ';
		buffer[i * 5 + 4] = DVERT;
	}

	buffer[4 * 5] = DBOTTOM_LEFT_CORNER;
	for (int i = 1; i < 4; i++)
		buffer[4 * 5 + i] = DHORIZ;
	buffer[4 * 5 + 4] = DBOTTOM_RIGHT_CORNER;

	if (c.GetSide() == 0 || c.GetSide() == 2)			// Face up/selected
	{
		// Set top rank
		if (c.GetRank() == ACE)
			buffer[1 * 5 + 1] = 'A';
		else if (c.GetRank() == JACK)
			buffer[1 * 5 + 1] = 'J';
		else if (c.GetRank() == QUEEN)
			buffer[1 * 5 + 1] = 'Q';
		else if (c.GetRank() == KING)
			buffer[1 * 5 + 1] = 'K';
		else if (c.GetRank() == RERR)
			buffer[1 * 5 + 1] = '!';
		else
			_itoa(c.GetRank(), &buffer[1 * 5 + 1], 10);

		// Set suit character
		buffer[1 * 5 + 3] = static_cast<char>(c.GetSuit() + 3);
		buffer[3 * 5 + 1] = static_cast<char>(c.GetSuit() + 3);

		// Set bottom rank
		if (c.GetRank() != TEN)
			buffer[3 * 5 + 3] = buffer[1 * 5 + 1];
		else
		{
			buffer[3 * 5 + 2] = '1';
			buffer[3 * 5 + 3] = '0';
		}

		if (c.GetSide() != 2)
		{
			memset(attrib, DBLUE_WHITE, 25 * sizeof(WORD));
			if (c.GetSuit() == DIAMONDS || c.GetSuit() == HEARTS)
			{
				for (int i = 1; i < 4; i++)
					memset(&attrib[i * 5 + 1], RED_WHITE, 3 * sizeof(WORD));
			}
			else
			{
				for (int i = 1; i < 4; i++)
					memset(&attrib[i * 5 + 1], BLACK_WHITE, 3 * sizeof(WORD));
			}
		}
		else
		{
			memset(attrib, WHITE_BLACK, 25 * sizeof(WORD));
			if (c.GetSuit() == DIAMONDS || c.GetSuit() == HEARTS)
			{
				for (int i = 1; i < 4; i++)
					memset(&attrib[i * 5 + 1], CYAN_BLACK, 3 * sizeof(WORD));
			}
		}
	}
	else if (c.GetSide() == 1)			// No card
	{
		buffer[0] = TOP_LEFT_CORNER;
		for (int i = 1; i < 4; i++)
			buffer[i] = HORIZ;
		buffer[4] = TOP_RIGHT_CORNER;

		for (int i = 1; i < 4; i++)
		{
			buffer[i * 5] = VERT;
			for (int j = 1; j < 4; j++)
				buffer[i * 5 + j] = ' ';
			buffer[i * 5 + 4] = VERT;
		}

		buffer[4 * 5] = BOTTOM_LEFT_CORNER;
		for (int i = 1; i < 4; i++)
			buffer[4 * 5 + i] = HORIZ;
		buffer[4 * 5 + 4] = BOTTOM_RIGHT_CORNER;

		memset(attrib, WHITE_BLACK, 25 * sizeof(WORD));
	}

	// Draw the card
	for (int i = 0; i < 5; i++)
	{
		WriteConsoleOutputAttribute(hStdout, &attrib[i * 5], 5, cursor, &numWrit);
		WriteConsoleOutputCharacterA(hStdout, &buffer[i * 5], 5, cursor, &numWrit);
		cursor.Y++;
	}

	cursor.Y -= 5;
}

/************************************************************************
* Purpose: Draws the sidebar menu.
*
* Precondition:
*		None.
*
* Postcondition:
*		Draws the sidebar menu.
*
************************************************************************/

void Painter::DrawMenu()
{
	cursor.X = 50;
	cursor.Y = 0;
	WORD logoAttrib[8];
	memset(logoAttrib, CYAN_BLACK, 8 * sizeof(WORD));

	for (int i = 0; i < 27; i++)
	{
		WriteConsoleOutputAttribute(hStdout, logoAttrib, 8, cursor, &numWrit);
		WriteConsoleOutputCharacterA(hStdout, &logo[i * 9], 9, cursor, &numWrit);
		cursor.Y++;
	}

	cursor.X = 50;
	cursor.Y = 31;

	WriteConsoleOutputCharacterA(hStdout, "+------+", 8, cursor, &numWrit);
	cursor.Y++;
	WriteConsoleOutputCharacterA(hStdout, "|Replay|", 8, cursor, &numWrit);
	cursor.Y++;
	WriteConsoleOutputCharacterA(hStdout, "+------+", 8, cursor, &numWrit);

	cursor.Y += 2;

	WriteConsoleOutputCharacterA(hStdout, "+------+", 8, cursor, &numWrit);
	cursor.Y++;
	WriteConsoleOutputCharacterA(hStdout, "| Exit |", 8, cursor, &numWrit);
	cursor.Y++;
	WriteConsoleOutputCharacterA(hStdout, "+------+", 8, cursor, &numWrit);

	cursor.Y += 2;

	WriteConsoleOutputCharacterA(hStdout, "Shaun", 8, cursor, &numWrit);
	cursor.Y++;
	WriteConsoleOutputCharacterA(hStdout, "Rasmusen", 8, cursor, &numWrit);
	cursor.Y++;
	WriteConsoleOutputCharacterA(hStdout, "(c) 2017", 8, cursor, &numWrit);
}

/************************************************************************
* Purpose: Prints out information pertaining to a winning state.
*
* Precondition:
*		None.
*
* Postcondition:
*		Displays winning message to the console.
*
************************************************************************/

void Painter::DisplayWin()
{
	cursor.X = 14;
	cursor.Y = 7;

	WORD winAttrib[22];
	memset(winAttrib, RED_WHITE, 22 * sizeof(WORD));

	char content[22];
	content[0] = DTOP_LEFT_CORNER;
	for (int i = 1; i < 20; i++)
		content[i] = DHORIZ;
	content[20] = DTOP_RIGHT_CORNER;

	WriteConsoleOutputAttribute(hStdout, winAttrib, 21, cursor, &numWrit);
	WriteConsoleOutputCharacterA(hStdout, content, 21, cursor, &numWrit);

	memset(winAttrib, BLACK_WHITE, 22 * sizeof(WORD));
	winAttrib[0] = RED_WHITE;
	winAttrib[20] = RED_WHITE;

	cursor.Y++;
	strcpy(content, "   CONGRATULATIONS   ");
	content[0] = DVERT;
	content[1] = static_cast<char>(SPADES + 3);
	content[19] = static_cast<char>(SPADES + 3);
	content[20] = DVERT;

	WriteConsoleOutputAttribute(hStdout, winAttrib, 21, cursor, &numWrit);
	WriteConsoleOutputCharacterA(hStdout, content, 21, cursor, &numWrit);

	memset(winAttrib, RED_WHITE, 22 * sizeof(WORD));

	cursor.Y++;
	content[0] = DBOTTOM_LEFT_CORNER;
	for (int i = 1; i < 20; i++)
		content[i] = DHORIZ;
	content[20] = DBOTTOM_RIGHT_CORNER;

	WriteConsoleOutputAttribute(hStdout, winAttrib, 21, cursor, &numWrit);
	WriteConsoleOutputCharacterA(hStdout, content, 21, cursor, &numWrit);
	cursor.Y += 3;
	cursor.X += 5;

	memset(winAttrib, WHITE_BLACK, 22 * sizeof(WORD));
	WriteConsoleOutputAttribute(hStdout, winAttrib, 12, cursor, &numWrit);
	WriteConsoleOutputCharacterA(hStdout, "You've won!", 12, cursor, &numWrit);

	cursor.Y += 2;
	cursor.X -= 5;

	WriteConsoleOutputAttribute(hStdout, winAttrib, 22, cursor, &numWrit);
	WriteConsoleOutputCharacterA(hStdout, "If you'd like to play", 22, cursor, &numWrit);
	cursor.Y++;
	WriteConsoleOutputAttribute(hStdout, winAttrib, 21, cursor, &numWrit);
	WriteConsoleOutputCharacterA(hStdout, "again, press replay,", 21, cursor, &numWrit);
	cursor.Y++;
	WriteConsoleOutputAttribute(hStdout, winAttrib, 22, cursor, &numWrit);
	WriteConsoleOutputCharacterA(hStdout, "or else press exit to", 22, cursor, &numWrit);
	cursor.Y++;
	cursor.X += 8;
	WriteConsoleOutputAttribute(hStdout, winAttrib, 5, cursor, &numWrit);
	WriteConsoleOutputCharacterA(hStdout, "quit.", 5, cursor, &numWrit);
}