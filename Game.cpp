#include "Game.h"
#include <iostream>

Game::Game()
{
	createBoard();
	bPlayer = new Player(board, BoardElement::Type::black, "Black");
	rPlayer = new Player(board, BoardElement::Type::red, "Red");
}

void Game::createBoard()
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board[i][j] = new EmptySpace();
		}
	}
}

void Game::drawBoard()
{
	cout << "\n";
	for(int i = 0; i < 9; i++)
	{
		cout << i + 1 << "|";
		for(int j = 0; j < 9; j++)
		{
			cout << board[i][j]->toString();
			cout << "|";
		}

		cout << i + 1 << "\n";

	}
	cout <<"  1 2 3 4 5 6 7 8 9\n";
}

void Game::runGame()
{
	cout << "\n(^_^) WELCOME TO THE GAME! (^_^) \n";

	//checks if both players are still winning
	while (rPlayer->didWin() && bPlayer->didWin())
	{
		if(rPlayer->didWin() && bPlayer->didWin())
		{   
			cout << "\nIt is your turn: " << rPlayer->toString() << "\n";
			drawBoard();
			rPlayer->takeTurn(board); 
		
		}
		
		//checks if players have any pieces remaining
		rPlayer->checkPieces();
		bPlayer->checkPieces();

		if(bPlayer->didWin() && rPlayer->didWin())
		{
			cout << "\nIt is your turn: " << bPlayer->toString() << "\n";
			drawBoard();
			bPlayer->takeTurn(board); 
		}

		rPlayer->checkPieces(); 

	}

	drawBoard();

	//checks winner
	if(rPlayer->didWin())
		cout << "\nRED player wins!\n\n";
	else if(bPlayer->didWin())
		cout << "\nBLACK player wins!\n\n";
	else 
		cout << "\nIt's a draw!\n\n";

}

Game::~Game()
{
	delete[] board;	
}