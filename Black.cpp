#include "Black.h"

Black::Black(int r, int c, Piece **h) : Piece(r, c, 0, -1, black, h) {}

//removes pieces off board accounting for black's special
void Black::remove (BoardElement *board[9][9], BoardElement *otherPiece, bool isByBlackSpecial)
{
	BoardElement *b = board[Piece::getRow()][Piece::getCol()];
	if (previousPiece != NULL)
	{
		previousPiece->nextPiece = nextPiece;
	}
	else
	{
		*headPiece = nextPiece;
	}
	if (nextPiece != NULL)
	{
		nextPiece->previousPiece = previousPiece;
	}
	if (nextPiece == NULL && previousPiece == NULL)
	{
		*headPiece = NULL;
	}

	if(special())
	{
		otherPiece->remove(board, b, true);
	}

	board[Piece::getRow()][Piece::getCol()] = new EmptySpace(); //puts an empty space in this piece's location on board

	delete b; //deletes piece from memory
}

//randomly selects true or false to activate black's special
bool Black::special()
{
	srand((unsigned int)time(0));
	int i = rand() % 2;

	if (i == 0)
		return false;
	else
		return true;
}

std::string Black::toString()
{
	if (isKinged())
		return "B";
	else
		return "b";
}