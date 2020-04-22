/*************************************************************
* Author:			Shaun Rasmusen
* Filename:			Board.cpp
* Date Created:		2/13/2017
* Modifications:	None.
************************************************************/
#include "Board.h"

#include <iostream>
#include <Windows.h>

/************************************************************************
* Purpose: Default constructor for the Board class.
*
* Precondition:
*		None.
*
* Postcondition:
*		Sets all parameters to default values, resizes the window and
*		draws the initial state of the board.
*
************************************************************************/

Board::Board() : m_deck(), m_win(false), voidCard(Card(RERR, SERR, 1))
{
	HANDLE cHandle = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(cHandle, ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS);

	HWND console = GetConsoleWindow();
	
	int monitorWidth = GetSystemMetrics(SM_CXSCREEN);
	int monitorHeight = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(console, monitorWidth / 2 - 300, monitorHeight / 2 - 400, 600, 800, TRUE);

	InitBoard();
}

/************************************************************************
* Purpose: Initializes the main elements on the board.
*
* Precondition:
*		None.
*
* Postcondition:
*		Shuffles the deck and deals out cards to m_play.
*		Draws the initial elements of the Board to the console window.
*
************************************************************************/

void Board::InitBoard()
{
	m_deck.Shuffle();

	// Deals out cards to the stacks.
	for (int i = 0; i < 52; i++)
	{
		m_play.SetCell(i % 8, m_deck.Deal());
	}
	
	m_play.Paint();

	for (int i = 0; i < 8; i++)
	{
		m_play.Paint(i);
	}

	m_home.Paint();

	m_free.Paint();
}

/************************************************************************
* Purpose: Finds the location (if valid) of the card selected by the
*			cursor.
*
* Precondition:
*		x - The x coordinate of the cursor.
*		y - The y coordinate of the cursor.
*
* Postcondition:
*		Returns a value corresponding to the location of the selected
*		card (0 - play; 1 - home; 2 - free).
*
************************************************************************/

int Board::FindCard(int x, int y)	// 0 - play; 1 - home; 2 - free
{
	if (y < 5)
	{
		if (x >= 0 && x < 4)
			return 2;
	}
	else if (y > 5)
	{
		y -= 6;
		if (x < 8)
		{ 
			int height = ((m_play.GetCol(x).Size() * 2) - 1 + 5); // "- 1" to zero-base, "+ 5" for height of card.
			
			if (y < height)
				return 0;
		}
	}

	return -1;
}

/************************************************************************
* Purpose: Moves card(s) onto the play stacks.
*
* Precondition:
*		fromArr - The starting location of the card(s) to move.
*
* Postcondition:
*		Moves card(s) onto the playing field stacks.
*
************************************************************************/

void Board::MoveToPlay(int fromArr)
{
	if (fromArr == 0)
	{
		int fromY = (m_select[1] - 6) / 2 + 1;
		if (fromY > m_play.GetCol(m_select[0]).Size())
			fromY = m_play.GetCol(m_select[0]).Size();

		int numEmptyCols = 0;
		for (int i = 0; i < 8; i++)
		{
			if (m_play.GetCell(i) == voidCard)
				numEmptyCols++;
		}

		if (m_play.GetCell(m_select[2]) == voidCard)
			numEmptyCols--;

		if (m_play.GetCol(m_select[0]).Size() - fromY < (m_free.GetFree() + 1) * pow(2, numEmptyCols))
		{
			ListStack<Card> temp;

			while (m_play.GetCol(m_select[0]).Size() - fromY >= 0)
				temp.Push(m_play.GetCol(m_select[0]).Pop());

			if (m_select[0] != m_select[2])
			{
				if (m_play.GetCell(m_select[2]) == voidCard ||
					(m_play.GetCell(m_select[2]).GetRank() - 1 == temp.Peek().GetRank()) &&
					((m_play.GetCell(m_select[2]).GetSuit() < CLUBS && temp.Peek().GetSuit() > DIAMONDS) ||
						(m_play.GetCell(m_select[2]).GetSuit() > DIAMONDS && temp.Peek().GetSuit() < CLUBS)))
				{
					if (m_play.GetCol(m_select[0]).isEmpty())
						m_play.SetCell(m_select[0], voidCard);

					if (m_play.GetCell(m_select[2]) == voidCard)
						m_play.GetCol(m_select[2]).Pop();

					while (!temp.isEmpty())
						m_play.SetCell(m_select[2], temp.Pop());
				}
				else
				{
					while (!temp.isEmpty())
						m_play.SetCell(m_select[0], temp.Pop());
				}
			}
			else if (temp.Size() == 1)
			{
				m_select[2] = temp.Peek().GetSuit() + 4;
				m_play.SetCell(m_select[0], temp.Pop());
				try
				{
					MoveToHome(0);
				}
				catch (Exception)
				{}
			}
			else
			{
				while (!temp.isEmpty())
					m_play.SetCell(m_select[0], temp.Pop());
			}

			m_play.Paint(m_select[0]);
		}
	}
	else if (fromArr == 2)
	{
		Card temp = m_free.PopCell(m_select[0]);

		if (m_play.GetCell(m_select[2]) == voidCard ||
			(m_play.GetCell(m_select[2]).GetRank() - 1 == temp.GetRank() &&
				((m_play.GetCell(m_select[2]).GetSuit() < CLUBS && temp.GetSuit() > DIAMONDS) ||
					(m_play.GetCell(m_select[2]).GetSuit() > DIAMONDS && temp.GetSuit() < CLUBS))))
		{
			if (m_play.GetCol(m_select[0]).isEmpty())
				m_play.SetCell(m_select[0], voidCard);

			if (m_play.GetCell(m_select[2]) == voidCard)
				m_play.GetCol(m_select[2]).Pop();

			m_play.SetCell(m_select[2], temp);
		}
		else
		{
			m_free.SetCell(m_select[0], temp);
		}

		m_free.Paint();
	}
	
	m_play.Paint(m_select[2]);
}

/************************************************************************
* Purpose: Moves a card to a free cell.
*
* Precondition:
*		fromArr - The starting location of the card to move.
*
* Postcondition:
*		Moves a card onto a free cell.
*
************************************************************************/

void Board::MoveToFree(int fromArr)
{
	if (fromArr == 0)
	{
		if (m_free.GetCell(m_select[2]) == voidCard)
			m_free.SetCell(m_select[2], m_play.GetCol(m_select[0]).Pop());
		
		if (m_play.GetCol(m_select[0]).isEmpty())
			m_play.SetCell(m_select[0], voidCard);

		m_play.Paint(m_select[0]);
	}
	else if (fromArr == 2)
	{
		if (m_select[0] != m_select[2])
		{
			if (m_free.GetCell(m_select[2]) == voidCard)
				m_free.SetCell(m_select[2], m_free.PopCell(m_select[0]));
		}
		else
		{
			m_select[2] = m_free.GetCell(m_select[2]).GetSuit() + 4;
			try
			{
				MoveToHome(2);
			}
			catch (Exception)
			{
			}
		}
	}

	m_free.Paint();
}

/************************************************************************
* Purpose: Moves a card onto a home cell.
*
* Precondition:
*		fromArr - The starting location of the card to move.
*
* Postcondition:
*		Moves a card onto a home cell.
*
************************************************************************/

void Board::MoveToHome(int fromArr)
{
	if (fromArr == 0)
	{
		m_select[2] -= 4;

		if (((m_home.isEmpty(m_select[2]) && m_play.GetCell(m_select[0]).GetRank() == ACE) || 
			m_home.GetCell(m_select[2]).GetRank() + 1 == m_play.GetCell(m_select[0]).GetRank()) &&
			m_play.GetCell(m_select[0]).GetSuit() == m_select[2])
			m_home.SetCell(m_select[2], m_play.GetCol(m_select[0]).Pop());

		if (m_play.GetCol(m_select[0]).isEmpty())
			m_play.SetCell(m_select[0], voidCard);

		m_play.Paint(m_select[0]);
	}
	else if (fromArr == 2)
	{
		m_select[2] -= 4;
		
		if (((m_home.isEmpty(m_select[2]) && m_free.GetCell(m_select[0]).GetRank() == ACE) ||
			m_home.GetCell(m_select[2]).GetRank() + 1 == m_free.GetCell(m_select[0]).GetRank()) &&
			m_free.GetCell(m_select[0]).GetSuit() == m_select[2])
			m_home.SetCell(m_select[2], m_free.PopCell(m_select[0]));
		
		m_free.Paint();
	}

	m_home.Paint();
}


/************************************************************************
* Purpose: Determines what cards belong to the selection and highlights
*			them.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns true if the card selected is a valid choice.
*
************************************************************************/

bool Board::GetFrom()
{
	int fromX = m_select[0];
	int fromY = m_select[1];
	int fromArr = FindCard(fromX / 6, m_select[1]);

	bool isValid = true;
	
	if (fromX % 6 != 0 && fromArr != -1)
	{
		fromX /= 6;
		if (fromArr == 0) // 0 - play
		{
			fromY = (fromY - 6) / 2 + 1;			// Zero-bases y from the top of the stack.

			if (fromY > m_play.GetCol(fromX).Size())
				fromY = m_play.GetCol(fromX).Size();

			ListStack<Card> temp;
			temp.Push(m_play.GetCol(fromX).Pop());

			while (!m_play.GetCol(fromX).isEmpty() && m_play.GetCol(fromX).Size() - fromY >= 0 &&
				m_play.GetCell(fromX).GetRank() - 1 == temp.Peek().GetRank() && 
				((m_play.GetCell(fromX).GetSuit() < CLUBS && temp.Peek().GetSuit() > DIAMONDS) ||
				(m_play.GetCell(fromX).GetSuit() > DIAMONDS && temp.Peek().GetSuit() < CLUBS)))
			{
				temp.Push(m_play.GetCol(fromX).Pop());
			}

			if (fromY <= m_play.GetCol(fromX).Size())
			{
				isValid = false;
				while (!temp.isEmpty())
					m_play.SetCell(fromX, temp.Pop());
			}
			else
			{
				while (!temp.isEmpty())
				{
					Card card = temp.Pop();
					if (card != voidCard)
						card.SetSide(2);
					m_play.SetCell(fromX, card);
				}
			}

			m_play.Paint(fromX);
		}
		else if (fromArr == 2) // 2 - free
		{
			if (m_free.GetCell(fromX) == voidCard)
				isValid = false;
			else
			{
				m_free.GetCell(fromX).SetSide(2);
				m_free.Paint();
			}
		}
	}
	else
		isValid = false;

	return isValid;
}

/************************************************************************
* Purpose: Moves cards from one location to another.
*
* Precondition:
*		None.
*
* Postcondition:
*		Moves cards from one valid location to another.
*
************************************************************************/

void Board::MoveCards()
{
	int fromArr = FindCard(m_select[0] / 6, m_select[1]);
	int toArr = FindCard(m_select[2] / 6, m_select[3]);

	ClearSelect(fromArr);

	if (m_select[2] % 6 != 0 && toArr != -1)
	{
		m_select[0] /= 6;
		m_select[2] /= 6;
		if (toArr == 0)			// To play...
		{
			MoveToPlay(fromArr);
		}
		else if (toArr == 1)	// To home...
		{
			MoveToHome(fromArr);
		}
		else if (toArr == 2)		// To free...
		{
			MoveToFree(fromArr);
		}		// endif toArr
	}		// endif fromArr

	CheckWin();
}

/************************************************************************
* Purpose: Clears the selection by resetting the cards type to 0.
*
* Precondition:
*		None.
*
* Postcondition:
*		Resets any card with type 2 to type 0.
*
************************************************************************/

void Board::ClearSelect(int fromArr)
{
	if (fromArr == 0)
	{
		int fromY = (m_select[1] - 6) / 2 + 1;	// Zero-bases y from the top of the stack.
		int fromX = m_select[0] / 6;

		if (fromY > m_play.GetCol(fromX).Size())
			fromY = m_play.GetCol(fromX).Size();

		int val = (m_play.GetCol(fromX).Size()) - fromY;
		ListStack<Card> temp;

		while (val >= 0)
		{
			temp.Push(m_play.GetCol(fromX).Pop());
			val--;
		}

		while (!temp.isEmpty())
		{
			Card card = temp.Pop();
			if (card != voidCard)
				card.SetSide(0);
			m_play.SetCell(fromX, card);
		}

		m_play.Paint(fromX);
	}
	else if (fromArr == 2)
	{
		m_free.GetCell(m_select[0] / 6).SetSide(0);
		m_free.Paint();
	}
}

/************************************************************************
* Purpose: Checks if the player has won the game.
*
* Precondition:
*		None.
*
* Postcondition:
*		Checks if the board is cleared.
*
************************************************************************/

void Board::CheckWin()
{
	m_win = true;

	for (int i = 0; i < 8; i++)
	{
		if (m_play.GetCell(i) != voidCard)
			m_win = false;
	}

	if (m_free.GetFree() != 4)
		m_win = false;
}

/************************************************************************
* Purpose: Returns true if the win state is true.
*
* Precondition:
*		None.
*
* Postcondition:
*		Returns the value of m_win.
*
************************************************************************/

bool Board::GetWin()
{
	return m_win;
}

/************************************************************************
* Purpose: Creates a painter object and displays the win state.
*
* Precondition:
*		None.
*
* Postcondition:
*		Prints a winning message to the screen.
*
************************************************************************/

void Board::DisplayWin()
{
	Painter painter;
	painter.DisplayWin();
}