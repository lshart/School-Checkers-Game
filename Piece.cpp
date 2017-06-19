#include "Piece.h"
#include <iostream>
#include <sstream>
#include <stdexcept>
using namespace std;

// moves this piece on board "board" to the postion on the board at [r][c]
void Piece::move (BoardElement *board[9][9], int r, int c)
{
	delete board[r][c];
	board[r][c] = this;
	board[row][col] = new EmptySpace();
	row = r;
	col = c;

	if (r == kingRow) // handles kinging of the piece
		kingMe();
}

// jumps targetPiece on board to positon [r][c]
void Piece::jump(BoardElement *board[9][9], BoardElement *targetPiece, int r, int c)
{
	BoardElement *b = board[Piece::getRow()][Piece::getCol()];
	move(board, r, c);
	targetPiece->remove(board, b, false);
}

// creates a list of possible moves for this piece on board and then asks the user what move they would like to make
bool Piece::getMove(BoardElement *board[9][9])
{
	string moveList[8];  // array of strings representing possible moves
	moveType movesTypeList[8]; // array of moveTypes that represents if the move at a given index is a jump or a move
	int moveLocation[8][4]; // array of rows and colums of possible moves. [i][0] & [i][1] represent the row and column 
							// of the pieces destination, where [i][2] & [i][3] represent the possible row and column of the piece to be jumped

	// represents the spaces surrounding any given piece on board, with forward direction determined by didMod
	int possibleMoves[8][2] = {{-1, dirMod}, {0, dirMod}, {1, dirMod}, {-1,0}, {1,0}, {-1,-dirMod}, {0,-dirMod}, {1,-dirMod}};

	int moveIndex = 0; //index of the move being looked at currently and also the total number of moves

	//checks moves for non-kinged pieces
	if(!isKinged())
	{
		for (int i = 0; i <= 2; i = i+2)
		{
			moveChecker(board, possibleMoves, moveList, movesTypeList, moveLocation, i, &moveIndex);
		}
	}
	//checks moves for kinged pieces
	else
	{
		for (int i = 0; i < 8; i++)
		{
			moveChecker(board, possibleMoves, moveList, movesTypeList, moveLocation, i, &moveIndex);
		}
	}

	//if there are moves then print list of moves and execute
	if (moveIndex != 0)
	{
		cout << "\nThe piece at (" << col + 1 << ", " << row + 1 << ") can:\n";
		for (int i = 0; i < moveIndex; i++)
		{
			cout << moveList[i];
		}

		cout << endl;

		cout << "Enter the number of your selection (or 0 to cancel your selection): ";
		int choice = -1;
		std::string strNum;
			
		// exception handling for strings
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

		while (choice < 0 || choice > moveIndex)
		{
			cout << "Please enter a valid choice: ";
			choice = -1;
			
			// exception handling for strings
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

		if (choice == 0)
			return false;

		//retrieving the move's coordinates
		int posMovRow = moveLocation[choice-1][0];
		int posMovCol = moveLocation[choice-1][1];
		int posJumRow = moveLocation[choice-1][2];
		int posJumCol = moveLocation[choice-1][3];

		BoardElement *b = board[posJumRow][posJumCol];
		
		//exectures the move depending on what type of move it is
		switch (movesTypeList[choice-1])
		{
		case Piece::moveType::jum:
			Piece::jump(board, b, posMovRow, posMovCol);
			break;
		case Piece::moveType::mov:
			Piece::move(board, posMovRow, posMovCol);
			break;
		}

		return true;
	}
	else
	{
		cout << "This piece has no available moves.\n";
		return false;
	}

}

Piece::Piece(int r, int c, int k, int d, Type t, Piece **h) : BoardElement(t)
{
	row = r;
	col = c;
	kingRow = k;
	special = true;
	kinged = false;
	dirMod = d;
	previousPiece = NULL;
	nextPiece = NULL;
	headPiece = h;
}

// Checks if the direction specified by i has a legal move
void Piece::moveChecker(BoardElement *board[9][9], int possibleMoves[8][2], string moveList[8], moveType movesTypeList[8], int moveLocation[8][4], int i, int *moveIndex)
{
	int possibleCol = col + possibleMoves[i][0];
	int possibleRow = row + possibleMoves[i][1];
	BoardElement *b;
	Type t = this->getType();

	if (possibleRow <= 8 && possibleRow >= 0 && possibleCol <= 8 && possibleCol >= 0)
	{

		b = board[possibleRow][possibleCol];
		if (b->getType() == empty)
		{
			ostringstream oss;
			oss << ((*moveIndex)+1) << ") move to (" << possibleCol + 1 << ", " << possibleRow + 1 << ")\n";
			moveList[(*moveIndex)] = oss.str();
			movesTypeList[(*moveIndex)] = Piece::moveType::mov;
			moveLocation[(*moveIndex)][0] = (possibleRow);
			moveLocation[(*moveIndex)][1] = (possibleCol);
			(*moveIndex)++;
		}
		else if (b->getType() != t)
		{
			int pieceAtRow = possibleRow;
			int pieceAtCol = possibleCol;

			possibleRow += possibleMoves[i][1];
			possibleCol += possibleMoves[i][0];

			if (possibleRow <= 8 && possibleRow >= 0 && possibleCol <= 8 && possibleCol >= 0)
			{
				b = board[possibleRow][possibleCol];

				if (b->getType() == empty)
				{
					ostringstream oss;
					oss << (*moveIndex)+1 << ") jump piece at (" << pieceAtCol +1 << ", " << pieceAtRow + 1 << ")\n";
					moveList[(*moveIndex)] = oss.str();

					movesTypeList[(*moveIndex)] = Piece::moveType::jum;
					moveLocation[(*moveIndex)][0] = possibleRow;
					moveLocation[(*moveIndex)][1] = possibleCol;
					moveLocation[(*moveIndex)][2] = pieceAtRow;
					moveLocation[(*moveIndex)][3] = pieceAtCol;
					(*moveIndex)++;
				}
			}
		}
	}
}

int Piece::getRow() {return row;}

int Piece::getCol() {return col;}

bool Piece::canSpecial () {return special;}

bool Piece::isKinged () {return kinged;}

void Piece::kingMe () {kinged = true;}