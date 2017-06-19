#ifndef PIECE_H
#define PIECE_H
#include "BoardElement.h"

class Piece : public BoardElement
{
public:
//methods
	bool getMove(BoardElement *board[9][9]);
	Piece(int r, int c, int k, int d, BoardElement::Type t, Piece **h);
	int getRow();
	int getCol();
	bool canSpecial ();
	bool isKinged ();
	void kingMe ();
	void useSpecial ()
	{
		special = false;
	}
// data for linked list of pieces
	Piece *nextPiece;
	Piece *previousPiece;
	Piece **headPiece;
private:
//data
	bool special; // can the piece still use its special ability
	bool kinged; // has this piece been kinged
	int row; // the row this piece occupies on the board
	int col; // the colum this piece occupies on the board
	int kingRow; // the row the piece needs to enter to become king
	int dirMod; // a number that can be either 1 or -1 that determines which direction is forward for this piece
	enum moveType {jum, mov};
// methods
	void jump (BoardElement *board[9][9], BoardElement *targetPiece, int x, int y);
	void move (BoardElement *board[9][9], int x, int y);
	void moveChecker(BoardElement *board[9][9], int possibleMoves[8][2], string moveList[8], moveType movesTypeList[8], int moveLocation[8][4], int i, int *moveIndex);
};

#endif // !PIECE_H
