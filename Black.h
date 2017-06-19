#ifndef BLACK_H
#define BLACK_H

#include <time.h>
#include <cstdlib>
#include <string>
#include "Piece.h"

class Black : public Piece
{
public:
	Black(int r, int c, Piece **h);
	void remove (BoardElement *board[9][9], BoardElement *otherPiece, bool isByBlackSpecial);
private:
	bool special();
	std::string toString();
};



#endif // !BLACK_H