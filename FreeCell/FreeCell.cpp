#include "FreeCell.h"

/************************************************************************
* Purpose: Default ctor for the FreeCell game class.
*
* Precondition:
*		None.
*
* Postcondition:
*		Initializes all variables to their default values.
*
************************************************************************/

FreeCell::FreeCell() : mouse()
{
	m_board = new Board();
}

/************************************************************************
* Purpose: Destructor.
*
* Precondition:
*		None.
*
* Postcondition:
*		Deallocates memory used for the FreeCell class.
*
************************************************************************/

FreeCell::~FreeCell()
{
	delete m_board;
}

/************************************************************************
* Purpose: The primary game loop for Solitaire.
*
* Precondition:
*		None.
*
* Postcondition:
*		Handles all logic for the game and collisions involving cursor
*		position and buttons displayed in the console.
*
************************************************************************/

bool FreeCell::Run()
{

	int inSelect = 0;
	time_t lastTime = 0;
	bool exit = false;
	
	while (!m_board->GetWin() && !exit)
	{
		if (mouse.PollInput())
		{
			COORD cursor = mouse.GetCursor();
			m_board->SetSelect(inSelect++, cursor.X);
			m_board->SetSelect(inSelect++, cursor.Y);

			if (cursor.X >= 50 && cursor.X < 58)
			{
				if (cursor.Y >= 31 && cursor.Y < 34) // New Game
				{
					delete m_board;
					m_board = new Board();
					inSelect = 0;
				}

				if (cursor.Y >= 35 && cursor.Y < 38) // Exit
				{
					exit = true;
				}
			}

			if (inSelect == 2)
			{
				if (!m_board->GetFrom())
					inSelect = 0;
			}

			if (inSelect == 4)
			{
				m_board->MoveCards();
				inSelect = 0;
			}
		}
	}

	if (m_board->GetWin())
	{
		bool select = false;

		m_board->DisplayWin();
		while (!select)
		{
			if (mouse.PollInput())
			{
				COORD cursor = mouse.GetCursor();

				if (cursor.X >= 50 && cursor.X < 58)
				{
					if (cursor.Y >= 31 && cursor.Y < 34)
					{
						delete m_board;
						m_board = new Board();
						select = true;
					}

					if (cursor.Y >= 35 && cursor.Y < 38) // Exit
					{
						exit = true;
						select = true;
					}
				}

				if (inSelect == 2)
				{
					if (!m_board->GetFrom())
						inSelect = 0;
					select = true;
				}

				if (inSelect == 4)
				{
					m_board->MoveCards();
					inSelect = 0;
					select = true;
				}
			}
		}
	}

	return exit;
}