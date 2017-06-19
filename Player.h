#ifndef PLAYER_H
#define PLAYER_H

#include "Black.h"
#include "Red.h"
#include <string>

class Player
{
private:
	Piece *firstPiece;
	std::string name;
	bool victory;
public:
	Player(BoardElement *board[9][9], BoardElement::Type t, std::string n);
	void takeTurn(BoardElement *board[9][9]);
	bool didWin();
	std::string toString();
	void checkPieces();
};

#endif