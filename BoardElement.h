#ifndef BOARDELEMENT_H
#define BOARDELEMENT_H

#include <string>
using namespace std;

// Type of object that can exist on a checkers board
class BoardElement
{
public:
	typedef enum {empty, red, black} Type;
	Type type;

	// sets what type of object the BoardElement object will be
	BoardElement(Type t)
	{
		type = t;
	}

	// returns the type of BoardElement the object is
	Type getType()
	{
		return type;
	}

	// list of methods every child will have 
	virtual string toString() = 0;
	virtual bool getMove(BoardElement *board[9][9]) = 0;
	virtual void remove (BoardElement *board[9][9], BoardElement *otherPiece, bool isByBlackSpecial) = 0;
	virtual bool special () = 0;
};

// Object that represents an empty space on a checkers board
class EmptySpace : public BoardElement
{
public:
	EmptySpace () : BoardElement(empty){}

	// returns a string representation of an empty space
	string toString ()
	{
		return "_";
	}

	// empty definitions of unused methods
	bool getMove(BoardElement *board[9][9]){return false;}
	bool special (){ return false;}
	void remove (BoardElement *board[9][9], BoardElement *otherPiece, bool isByBlackSpecial){}
};

#endif // !BOARDELEMENT_H