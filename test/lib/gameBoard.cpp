#include <iostream>
#include "gameBoard.h"


GameBoard::GameBoard(){
	lastMove=-1;
	for(auto& item: gameBoardNum){
		item=0;
	}
	for(auto& rows: gameBoard){ // Iterating over rows
	    for(auto& item: rows){
	        item=blank;
	    }
	}
}

GameBoard::GameBoard(const GameBoard &obj){
	int i=0,j;
	
	lastMove=obj.lastMove;
	for(auto& item: gameBoardNum){
		item=obj.gameBoardNum[i++];
	}
	for(i=0;i<ROW;i++){
		for(j=0;j<COL;j++){
			gameBoard[i][j]=obj.gameBoard[i][j];
		}
	}
}

GameBoard::~GameBoard(){}

void GameBoard::printGameBoard(){
	int i=0;

	const char* boardSeparator	= "---------------------------";
	const char* boardPattern 	= " %c | %c | %c | %c | %c | %c | %c \n";
	printf(boardPattern, '1','2','3','4','5','6','7');
	printf("%s\n", boardSeparator);

	for(i=COL-1;i>=0;i--){
		printf(boardPattern, getTypeChar(gameBoard[0][i]),getTypeChar(gameBoard[1][i]),getTypeChar(gameBoard[2][i]),
							 getTypeChar(gameBoard[3][i]),getTypeChar(gameBoard[4][i]),getTypeChar(gameBoard[5][i]),
							 getTypeChar(gameBoard[6][i]));
	}
	printf("%s\n", boardSeparator);
}

bool GameBoard::inputStep(int i, TYPE t){
	if(gameBoardNum[i-1]>=COL || i>ROW) return false;
	lastMove = i-1;
	gameBoard[lastMove][gameBoardNum[lastMove]]=t;
	gameBoardNum[lastMove]++;
	return true;
}

bool GameBoard::isDrawGame(){
	for(int item: gameBoardNum){
		if (item<COL) { return false;}
	}
	return true;	
}

GameBoard::TYPE GameBoard::isGameOver(){
	if (lastMove<0) return blank;
	if (isDrawGame()) return draw;

	int v, h, x=lastMove, y=gameBoardNum[lastMove]-1;
	int vertical=1;
	int horizontal=1;
	int diagonalA=1;
	int diagonalB=1;
	
	TYPE target = gameBoard[x][y];

	// check for vertical
	for(v=y+1; gameBoard[x][v]==target && v<ROW; v++, vertical++); // check upward
	for(v=y-1; gameBoard[x][v]==target && v>=0;  v--, vertical++); // check downward
	if(vertical>=4) {return target;}
	// check for horizontal
	for(h=x+1; gameBoard[h][y]==target && h<COL; h++, horizontal++); // check right
	for(h=x-1; gameBoard[h][y]==target && h>=0;  h--, horizontal++); // check left
	if(horizontal>=4) {return target;}
	// check for diagonalA
	for(h=x+1, v=y+1;gameBoard[h][v] == target && v<COL && h<ROW; h ++, v ++, diagonalA++);//up and right
	for(h=x-1, v=y-1;gameBoard[h][v] == target && v>=0 && h >= 0; h --, v --, diagonalA++);//down and left
	if(diagonalA>=4) {return target;}
	// check for diagonalB
	for(h=x-1, v=y+1;gameBoard[h][v] == target && v<COL && h>=0; h --, v ++, diagonalB++);//up and left
	for(h=x+1, v=y-1;gameBoard[h][v] == target && v>=0 && h<ROW; h ++, v --, diagonalB++);//down and right
	if(diagonalB>=4) {return target;}
	
	return blank;
}

std::vector<int> GameBoard::getAllPossibleSteps(){
	std::vector<int> v;
	int i=0;
	for (i=0; i<ROW;i++){
		if (gameBoardNum[i]<COL)
			v.push_back(i);
	}
	return v;
}

char GameBoard::getTypeChar(TYPE t){
	switch(t){
		default:
		case blank:
			return ' ';
		case playerX:
			return 'X';
		case playerO:
			return 'O';
	}
}