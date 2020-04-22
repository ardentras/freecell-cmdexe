/*************************************************************
* Author:			Shaun Rasmusen
* Filename:			FreeCells.cpp
* Date Created:		2/13/2017
* Modifications:	None.
************************************************************/
#include "FreeCells.h"

/************************************************************************
* Purpose: Default ctor.
*
* Precondition:
*		None.
*
* Postcondition:
*		Initializes all variables to their default states.
*
************************************************************************/

FreeCells::FreeCells() : m_cells(4), m_free(4)
{
	painter = Painter();
	for (int i = 0; i < 4; i++)
		m_cells[i] = painter.voidCard;
}

/************************************************************************
* Purpose: Returns the card held at the passed cell.
*
* Precondition:
*		cell - The cell to select from.
*
* Postcondition:
*		Returns the value of m_cells[cell].
*
************************************************************************/

Card & FreeCells::GetCell(int cell)
{
	return m_cells[cell];
}

/************************************************************************
* Purpose: Returns the card held at the passed cell and pops it.
*
* Precondition:
*		cell - The cell to select from.
*
* Postcondition:
*		Returns the value of m_cells[cell] and removes it.
*
************************************************************************/

Card FreeCells::PopCell(int cell)
{
	m_free++;
	Card temp = m_cells[cell];
	m_cells[cell] = painter.voidCard;

	return temp;
}

/************************************************************************
* Purpose: Sets the card at position, cell.
*
* Precondition:
*		cell - The cell to place a card.
*		c - The card to set.
*
* Postcondition:
*		Sets m_cells[cell] to the passed card.
*
************************************************************************/

void FreeCells::SetCell(int cell, Card c)
{
	m_cells[cell] = c;
	m_free--;
}

/************************************************************************
* Purpose: Draws the freecells section of the board.
*
* Precondition:
*		None.
*
* Postcondition:
*		Draws the card to the console.
*
************************************************************************/

void FreeCells::Paint()
{
	painter.cursor.X = 1;
	painter.cursor.Y = 0;

	for (int i = 0; i < 4; i++)
	{
		painter.DrawCard(m_cells[i]);
		painter.cursor.X += 6;
	}
}