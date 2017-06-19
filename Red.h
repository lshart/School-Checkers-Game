#ifndef RED_H
#define RED_H

#include "Piece.h"
#include <string>

class Red : public Piece
{
public:
	Red(int x, int y, Piece **h);
	void remove (BoardElement *board[9][9], BoardElement *otherPiece, bool isByBlackSpecial);
	bool special();
	string toString();

};

#endif // !RED_H