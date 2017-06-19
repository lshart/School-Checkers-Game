#ifndef GAME_H
#define GAME_H

#include <string>
#include "Player.h"

using namespace std;

class Game 
{
private:
	//data
	Player *bPlayer;
	Player *rPlayer;
	BoardElement *board[9][9];
	
	//methods
	void createBoard();
	void drawBoard();

public:
	Game();
	~Game();
	void runGame();
};


#endif //!GAME_H