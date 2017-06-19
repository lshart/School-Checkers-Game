#include "Red.h"

Red::Red(int r, int c, Piece **h) : Piece(r, c, 8, 1, red, h) {}

//removes pieces off board accounting for red's special
void Red::remove (BoardElement *board[9][9], BoardElement *otherPiece, bool isByRedSpecial)
{
	BoardElement *r = board[Piece::getRow()][Piece::getCol()];
	if(special())
	{
		if (previousPiece != NULL)
		{
			previousPiece->nextPiece = nextPiece;
		}
		if (nextPiece != NULL)
		{
			nextPiece->previousPiece = previousPiece;
		}
		if (nextPiece == NULL && previousPiece == NULL)
		{
			*headPiece = NULL;
		}
	
		board[Piece::getRow()][Piece::getCol()] = new EmptySpace(); //puts an empty space in this piece's location on board
		
		delete r; //deletes piece from memory
	}
}

//checks red's special and uses it up
bool Red::special()
{
	if (canSpecial())
	{
		useSpecial();
		return false;
	}
	else
		return true;
}

std::string Red::toString()
{
	if (isKinged())
		return "R";
	else
		return "r";
}