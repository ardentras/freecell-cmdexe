#pragma once

#include "Board.h"
#include "Mouse.h"

/************************************************************************
* Class: Primary game class for FreeCell.
*
* Purpose: Manages mouse movements and win conditions.
*
* Manager functions:
*		FreeCell()
*			Constructor.
*
*		~FreeCell()
*			Destructor.
*
* Methods:
*		Run()
*			The primary game loop that handles mouse actions and game
*			states.
*
*************************************************************************/

class FreeCell
{
public:
	FreeCell();
	~FreeCell();

	bool Run();

private:
	Board * m_board;
	Mouse mouse;
};

