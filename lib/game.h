#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include "gameBoard.h"
#include "gamePlayer.h"

class Connect4{
private:
	GameBoard* gameBoard;
	Player* playerA;
	Player* playerB;
	int round;

public:
	Connect4();
	~Connect4();

	void gameStart();
	void gameLoop();
	void printMenu();
};

#endif