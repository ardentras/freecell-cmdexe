#ifndef _BOARD_H
#define _BOARD_H

#include <vector>
using std::vector;
#include <string>
using std::string;
#include <ctime>
using std::time;

#include "Deck.h"
#include "FreeCells.h"
#include "HomeCells.h"
#include "PlayField.h"

/************************************************************************
* Class: Board
*
* Purpose: Handles the game logic and movement of cards for freecell.
*
* Manager functions:
*		Board()
*
* Methods:
*		InitBoard()
*			Initializes the sections of the board and draws initial setup.
*		
*		MoveToPlay(int fromArr)
*			Moves cards to the play region.
*
*		MoveToFree(int fromArr)
*			Moves a card to the freecell region.
*
*		MoveToHome(int fromArr)
*			Moves a card to the homecell region.
*	
*		FindCard(int x, int y)
*			Determines if a cursor selection is valid.
*
*		GetFrom()
*			Gets the cards in a selection and stores them in temp.
*
*		MoveCards()
*			Moves cards from one location to another.
*		
*		ClearSelect()
*			Resets card types from 2 to 0, clearing a selection.
*		
*		CheckWin()
*			Checks if the stacks and draw pile are clear.
*
*		DisplayWin()
*			Display winning information, including score.
*	
*		SetSelect(int select, int val)
*			Sets the coordinates of the current selections.
*		
*		GetWin()
*			Returns the value of m_win.
*
*************************************************************************/

class Board
{
private:
	FreeCells m_free;
	HomeCells m_home;
	PlayField m_play;

	Deck m_deck;

	Card voidCard;

	bool m_win;

	int m_select[4];	// 0/2 - x coords from & to; 1/3 - y coords from & to.

	COORD cursor;
public:
	Board();

	void InitBoard();

	void MoveCards();
	void MoveToPlay(int fromArr);
	void MoveToFree(int fromArr);
	void MoveToHome(int fromArr);

	void DisplayWin();
	bool GetFrom();
	int FindCard(int x, int y);
	void ClearSelect(int toArr);
	void SetSelect(int select, int val) { m_select[select] = val; }

	void CheckWin();
	bool GetWin();
};

#endif // _BOARD_H