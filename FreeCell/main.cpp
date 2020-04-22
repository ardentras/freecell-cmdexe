/**************************************************************
* Author:			Shaun Rasmusen
* Filename:			main.cpp
* Date Created:		2/13/2017
* Modifications:	None.
*
* Lab/Assignment: CST 211, Lab 3, "FreeCell"
*
* Overview: A console version of the classic game of FreeCell
*	
* Input:
*	The mouse is the sole source of input and can be used to
*	manipulate cards and navigate the game.
*
* Output:
*	A board that is drawn similar to the Windows version of
*	FreeCell with a sidebar containing information and the
*	to either replay or exit the game.
*
**************************************************************/
#define _CRT_SECURE_NO_WARNINGS 
#define _CRTDBG_MAP_ALLOC
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <crtdbg.h>

#include "FreeCell.h"

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	FreeCell freecell;

	while (!freecell.Run());

	return 0;
}