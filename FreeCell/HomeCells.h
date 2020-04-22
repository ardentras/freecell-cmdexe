#pragma once

#include "ArrStack.h"
#include "Cells.h"

/************************************************************************
* Class: HomeCells
*
* Purpose: Manages the homecells region of the game board.
*
* Manager functions:
*		HomeCells()
*			Constructor.
*
* Methods:
*		GetCell(int cell)
*			Returns the card held at cell, cell.
*
*		isEmpty(int cell)
*			Returns true if the chosen cell is empty.
*
*		SetCell(int cell, Card c)
*			Pushes the passed card value onto the passed cell stack.
*
*		Paint()
*			Repaints the homecell region.
*
*************************************************************************/

class HomeCells : public Cells
{
public:
	HomeCells();
	Card & GetCell(int cell);
	bool isEmpty(int cell);
	void SetCell(int cell, Card c);
	void Paint();

private:
	Array<ArrStack<Card>> m_cells;
};