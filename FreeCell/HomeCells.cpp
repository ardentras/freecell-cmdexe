/*************************************************************
* Author:			Shaun Rasmusen
* Filename:			HomeCells.cpp
* Date Created:		2/13/2017
* Modifications:	None.
************************************************************/
#include "HomeCells.h"

/************************************************************************
* Purpose: Default ctor.
*
* Precondition:
*		None.
*
* Postcondition:
*		Initializes all variables to their default values.
*
************************************************************************/

HomeCells::HomeCells() : m_cells(4)
{
	painter = Painter();
}

/************************************************************************
* Purpose: Returns the card held at the top of the passed cell.
*
* Precondition:
*		cell - The cell to select from.
*
* Postcondition:
*		Returns the value at the top of m_cells[cell].
*
************************************************************************/

Card & HomeCells::GetCell(int cell)
{
	return m_cells[cell].Peek();
}

/************************************************************************
* Purpose: Pushes the passed card on top of the chosen cell.
*
* Precondition:
*		cell - The chosen cell.
*		c - The card to push.
*
* Postcondition:
*		Pushes the card onto m_cells[cell].
*
************************************************************************/

void HomeCells::SetCell(int cell, Card c)
{
	m_cells[cell].Push(c);
}

/************************************************************************
* Purpose: Returns true if the chosen cell is empty.
*
* Precondition:
*		cell - The cell to check.
*
* Postcondition:
*		Returns true if the cell is empty, else false.
*
************************************************************************/

bool HomeCells::isEmpty(int cell)
{
	return m_cells[cell].isEmpty();
}

/************************************************************************
* Purpose: Draws the homecells of the board.
*
* Precondition:
*		None.
*
* Postcondition:
*		Draws the card to the console.
*
************************************************************************/

void HomeCells::Paint()
{
	painter.cursor.X = 25;
	painter.cursor.Y = 0;

	for (int i = 0; i < 4; i++)
	{
		if (m_cells[i].isEmpty())
			painter.DrawCard(painter.voidCard);
		else
			painter.DrawCard(m_cells[i].Peek());

		// If void card, will fill center space with suit.
		COORD cursor = painter.cursor;
		cursor.X += 3;
		cursor.Y += 1;

		painter.buffer[0] = static_cast<char>(i + 3);
		WriteConsoleOutputCharacterA(painter.hStdout, painter.buffer, 1, cursor, &painter.numWrit);

		cursor.X -= 2;
		cursor.Y += 2;

		WriteConsoleOutputCharacterA(painter.hStdout, painter.buffer, 1, cursor, &painter.numWrit);

		painter.cursor.X += 6;
	}
}