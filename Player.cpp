#include "Player.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

Player::Player(BoardElement *board[9][9], BoardElement::Type newType, std::string newName)
{
	name = newName;
	victory = true;
	int sideMod = -1, baseRow = 8; 
	Piece *p, *index = NULL;

	//if the pieces it's making is red, then puts piece on the red side of the board
	if (newType == BoardElement::Type::red)
	{
		sideMod = 1;
		baseRow = 0; 
	}

	//makes the first row of the pieces
	for (int i = 1; i <= 7; i += 2) 
	{
		delete board[baseRow][i];

		if (newType == BoardElement::Type::red)
			p = new Red(baseRow, i, &firstPiece);
		else
			p = new Black(baseRow, i, &firstPiece);

		board[baseRow][i] = p;

		if (firstPiece == NULL)
		{
			firstPiece = p;
			index = p;
		}
		else
		{
			index->nextPiece = p;
			p->previousPiece = index;
			index = p;
		}
	}

	//puts the pieces on the second row
	baseRow += sideMod;
	for (int i = 2; i <= 6; i += 2) 
	{	
		delete board[baseRow][i];

		if (newType == BoardElement::Type::red)
			p = new Red(baseRow, i, &firstPiece);
		else
			p = new Black(baseRow, i, &firstPiece);

		board[baseRow][i] = p;

		index->nextPiece = p;
		p->previousPiece = index;
		index = p;
	}
}

//checks if the player still has pieces
void Player::checkPieces()
{
	if (firstPiece == NULL)
	{
		victory = false;
	}
}


void Player::takeTurn(BoardElement *board[9][9])
{
	Piece *choiceList[7], *index;
	string choiceMenu[7];
	int pieceCount = 0;

	checkPieces();

	index = firstPiece;

	//displays the list of pieces
	while (index != NULL)
	{
		ostringstream oss;

		oss << pieceCount+1 << ") Piece at (" << index->getCol() +1 << ", " << index->getRow() +1 << ")\n";
		choiceMenu[pieceCount] = oss.str();
		choiceList[pieceCount] = index;

		pieceCount++;
		index = index->nextPiece;
	}


	int choice;

	do
	{
		cout << "\nSelect a piece to move:\n";

		for (int i = 0; i < pieceCount; i++)
		{
			cout << choiceMenu[i];
		}

		cout << "\nSelection: ";
		
		//exception handling if String entered instead of an int
		std::string strNum;
		choice = -1;

		while(choice == -1)
		{
			getline(cin, strNum);
			try
			{
				choice = stoi(strNum);
			}
			catch(std::invalid_argument& e)
			{
				cout << "\nInvalid entry... Please select a number: ";
			}
			catch(std::out_of_range& e)
			{
				cout << "\nInvalid entry... Please select a number: ";
			}
		}
		
		while (choice < 1 || choice > pieceCount)
		{
			cout << "\nInvalid selection, try again: ";
			choice = -1;
			
			//exception handling if user inputs string
			while(choice == -1)
			{
				getline(cin, strNum);
				try
				{
					choice = stoi(strNum);
				}
				catch(std::invalid_argument& e)
				{
					cout << "\nInvalid entry... Please select a number: ";
				}
				catch(std::out_of_range& e)
				{
					cout << "\nInvalid entry... Please select a number: ";
				}
			}
		}
	}
	while(!(choiceList[choice-1]->getMove(board)));

	
}

bool Player::didWin() {return victory;}

std::string Player::toString() {return name;}