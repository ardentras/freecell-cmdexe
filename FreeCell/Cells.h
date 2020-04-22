#pragma once

#include "Painter.h"

class Card;

/************************************************************************
* Class: Cells
*
* Purpose: ABC for the various cell regions of the FreeCell board.
*
* Manager functions:
*		None.
*
* Methods:
*		GetCell(int cell)
*			Returns the value held at the cell.
*
*		SetCell(int cell, Card c)
*			Sets the card at the chosen cell.
*
*		Paint()
*			Paints a region.
*
*************************************************************************/

class Cells
{
public:
	virtual Card & GetCell(int cell) = 0;
	virtual void SetCell(int cell, Card c) = 0;
	virtual void Paint() = 0;

protected:
	Painter painter;
};