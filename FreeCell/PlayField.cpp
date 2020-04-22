/*************************************************************
* Author:			Shaun Rasmusen
* Filename:			PlayField.cpp
* Date Created:		2/13/2017
* Modifications:	None.
************************************************************/
#include "PlayField.h"

/************************************************************************
* Purpose: Default ctor.
*
* Precondition:
*		None.
*
* Postcondition:
*		Initializes painter and creates 8 cells for cards.
*
************************************************************************/

PlayField::PlayField() : m_cells(8)
{
	painter = Painter();
}

/************************************************************************
* Purpose: Returns the selected column stack.
*
* Precondition:
*		col - The column to return.
*
* Postcondition:
*		Returns the value of m_cells[col].
*
************************************************************************/

ListStack<Card> & PlayField::GetCol(int col)
{
	return m_cells[col];
}

/************************************************************************
* Purpose: Returns the card at the top of the selected stack.
*
* Precondition:
*		cell - The chosen cell to select from.
*
* Postcondition:
*		Returns the value held at the top of m_cells[cell].
*
************************************************************************/

Card & PlayField::GetCell(int cell)
{
	return m_cells[cell].Peek();
}

/************************************************************************
* Purpose: Pushes the passed card onto the chosen stack.
*
* Precondition:
*		cell - The position of the stack.
*		c - The card to push.
*
* Postcondition:
*		Pushes the passed card onto m_cells[cell].
*
************************************************************************/

void PlayField::SetCell(int cell, Card c)
{
	m_cells[cell].Push(c);
}

/************************************************************************
* Purpose: Default Paint function. Clears the board.
*
* Precondition:
*		None.
*
* Postcondition:
*		Wipes the play field by drawing 60 black lines.
*
************************************************************************/

void PlayField::Paint()
{
	memset(painter.attrib, WHITE_BLACK, 48 * sizeof(WORD));

	COORD cursor = painter.cursor;

	memset(painter.buffer, ' ', 48 * sizeof(char));
	cursor.X = 0;
	cursor.Y = 6;

	for (int i = 0; i < 60; i++)
	{
		WriteConsoleOutputAttribute(painter.hStdout, painter.attrib, 48, cursor, &painter.numWrit);
		WriteConsoleOutputCharacterA(painter.hStdout, painter.buffer, 48, cursor, &painter.numWrit);
		cursor.Y++;
	}
}

/************************************************************************
* Purpose: Draws the stacks section of the board.
*
* Precondition:
*		x - The index of the stack to be drawn.
*
* Postcondition:
*		Draws a stack of cards to the console.
*
************************************************************************/

void PlayField::Paint(int x)
{
	memset(painter.attrib, WHITE_BLACK, 6 * sizeof(WORD));

	COORD cursor = painter.cursor;

	memset(painter.buffer, ' ', 6 * sizeof(char));
	cursor.X = x * 6;
	cursor.Y = (m_cells[x].Size() * 2) + 9;

	for (int i = 0; i < 32; i++)
	{
		WriteConsoleOutputAttribute(painter.hStdout, painter.attrib, 6, cursor, &painter.numWrit);
		WriteConsoleOutputCharacterA(painter.hStdout, painter.buffer, 6, cursor, &painter.numWrit);
		cursor.Y++;
	}

	ListStack<Card> temp = ListStack<Card>();
	int size = m_cells[x].Size();

	for (int i = 0; i < size; i++)
		temp.Push(m_cells[x].Pop());

	for (int j = 0; j < size; j++)
	{
		painter.cursor.X = (x * 6) + 1;
		painter.cursor.Y = (j * 2) + 6;

		Card card = temp.Pop();

		painter.DrawCard(card);

		m_cells[x].Push(card);
	}
}