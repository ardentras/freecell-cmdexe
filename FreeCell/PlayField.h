#pragma once

#include "Cells.h"
#include "Array.h"
#include "ListStack.h"

/************************************************************************
* Class: PlayField
*
* Purpose: Manages the playing field region of the game board.
*
* Manager functions:
*		PlayField()
*			Constructor.
*
* Methods:
*		GetCol(int cell)
*			Returns the column at cell, cell.
*
*		GetCell(int cell)
*			Returns the card held at cell, cell.
*
*		SetCell(int cell, Card c)
*			Pushes the passed card value onto the passed cell stack.
*
*		Paint()
*			Clears the playing field to black.
*
*		Paint(int x)
*			Repaints the column at position x of the playing field region.
*
*************************************************************************/

class PlayField : public Cells
{
public:
	PlayField();
	ListStack<Card> & GetCol(int col);
	Card & GetCell(int cell);
	void SetCell(int cell, Card c);
	void Paint();
	void Paint(int x);

private:
	Array<ListStack<Card>> m_cells;
};

