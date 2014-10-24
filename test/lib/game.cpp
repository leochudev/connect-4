#include "game.h"

Connect4::Connect4(){
	round=0;
	gameBoard=new GameBoard();
	playerA=new Human(GameBoard::playerO);
	playerB=new Computer(GameBoard::playerX);
}

Connect4::~Connect4(){
	delete gameBoard;
	delete playerA;
	delete playerB;
}

void Connect4::gameStart(){
	GameBoard::TYPE state = gameBoard->isGameOver(); 
	printMenu();
	gameBoard->printGameBoard();
	while(state==GameBoard::blank){
		Player* ptr = (round++) % 2 == 0 ? playerA : playerB;
		gameBoard->inputStep(ptr->nextStep(*gameBoard), ptr->getPlayerType());
		gameBoard->printGameBoard();
		state=gameBoard->isGameOver();

		ptr=NULL;// release pointer
	}
}

void Connect4::gameLoop(){
	printf("%s\n", "gameLoop");
}

void Connect4::printMenu(){
	const char* separator="========================================================";
	const char* title="Connect - 4";
	
	printf("%s\n\n", separator);
	printf("%s\n\n", title);
	printf("%s\n\n", separator);
}