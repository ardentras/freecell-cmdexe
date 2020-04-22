#pragma once

#include "Array.h"
#include "Cells.h"

/************************************************************************
* Class: FreeCells
*
* Purpose: Manages the freecells region of the game board.
*
* Manager functions:
*		FreeCells()
*			Constructor.
*
* Methods:
*		GetFree()
*			Returns the number of free cells.
*
*		GetCell(int cell)
*			Returns the card held at cell, cell.
*
*		PopCell(int cell)
*			Returns the card held at cell, cell, and removes it.
*
*		SetCell(int cell, Card c)
*			Sets the passed cell to the passed card value.
*
*		Paint()
*			Repaints the freecell region.
*
*************************************************************************/

class FreeCells : public Cells
{
public:
	FreeCells();
	int GetFree() { return m_free; };
	Card & GetCell(int cell);
	Card PopCell(int cell);
	void SetCell(int cell, Card c);
	
	void Paint();

private:
	Array<Card> m_cells;
	int m_free;
};

