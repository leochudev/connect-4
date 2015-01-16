
#include <iostream>
#include <limits>
#include "gameBoard.h"


GameBoard::GameBoard(){
	lastMove=0;

	for(int item: moves){
		item=-1;
	}
	for(int item: gameBoardNum){
		item=0;
	}
	for(auto& rows: gameBoard){ // Iterating over rows
	    for(auto& item: rows){
	        item=blank;
	    }
	}
}

GameBoard::GameBoard(const GameBoard &obj){
	int i=0,j=0;
	
	lastMove=obj.lastMove;

	for(int item: moves){
		item=obj.moves[i++];
	}
	for(int item: gameBoardNum){
		item=obj.gameBoardNum[j++];
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

int GameBoard::getHeuristicScore(TYPE ai, int depth){
    int score = 0,
    	xCount = 0,//black count
    	oCount = 0;//red count

	int v, h, x=moves[lastMove], y=gameBoardNum[moves[lastMove]]-1;
	int vertical=1,
		horizontal=1,
		diagonalA=1,
		diagonalB=1;

	bool connect = true;

	TYPE target = gameBoard[x][y];
	bool isPlayerX = target==playerX?true:false;

	// ==========check for vertical
	xCount = oCount = 0;
	for(v=y+1;v<ROW; v++) {// check upward
		if(connect && gameBoard[x][v]==target)
			vertical++;
		else
			connect = false;

		if (gameBoard[x][v]==playerX){
			xCount++;
		} else if (gameBoard[x][v]==playerO){
			oCount++;
		}
	}
	connect = true;
	for(v=y-1; v>=0;  v--){ // check downward
		if(connect && gameBoard[x][v]==target)
			vertical++;
		else
			connect = false;

		if (gameBoard[x][v]==playerX){
			xCount++;
		} else if (gameBoard[x][v]==playerO){
			oCount++;
		}
	}
	connect = true;
	// check vertical score
	if(vertical>=4) {
		if (depth < 3)
			return isPlayerX? std::numeric_limits<int>::max():std::numeric_limits<int>::min();
	} 
	score += getUnitScore(isPlayerX, oCount, xCount);

	

	// ==========check for horizontal
	xCount = oCount = 0;
	for(h=x+1; h<COL; h++){ // check right
		if(connect && gameBoard[h][y]==target)
			horizontal++;
		else
			connect = false;

		if (gameBoard[h][y]==playerX){
			xCount++;
		} else if (gameBoard[h][y]==playerO){
			oCount++;
		}
	} 
	connect = true;
	for(h=x-1; h>=0;  h--){// check left
		if(connect && gameBoard[h][y]==target)
			horizontal++;
		else
			connect = false;

		if (gameBoard[h][y]==playerX){
			xCount++;
		} else if (gameBoard[h][y]==playerO){
			oCount++;
		}
	}
	connect = true; 
	// check horizontal score
	if(horizontal>=4) {
		if (depth < 3)
			return isPlayerX? std::numeric_limits<int>::max():std::numeric_limits<int>::min();
	} 
	score += getUnitScore(isPlayerX, oCount, xCount);
	


	// check for diagonalA
	xCount = oCount = 0;
	for(h=x+1, v=y+1; v<COL && h<ROW; h ++, v ++){//up and right
		if(connect && gameBoard[h][v]==target)
			diagonalA++;
		else
			connect = false;

		if (gameBoard[h][v]==playerX){
			xCount++;
		} else if (gameBoard[h][v]==playerO){
			oCount++;
		}
	}
	connect = true;
	for(h=x-1, v=y-1; v>=0 && h >= 0; h --, v --){//down and left
		if(connect && gameBoard[h][v]==target)
			diagonalA++;
		else
			connect = false;

		if (gameBoard[h][v]==playerX){
			xCount++;
		} else if (gameBoard[h][v]==playerO){
			oCount++;
		}
	}
	connect = true;
	// check diagonalA score
	if(diagonalA>=4) {
		if (depth < 3)
			return isPlayerX? std::numeric_limits<int>::max():std::numeric_limits<int>::min();
	} 
	score += getUnitScore(isPlayerX, oCount, xCount);
	
	// check for diagonalB
	xCount = oCount = 0;
	for(h=x-1, v=y+1; v<COL && h>=0; h --, v ++){//up and left
		if(connect && gameBoard[h][v]==target)
			diagonalB++;
		else
			connect = false;

		if (gameBoard[h][v]==playerX){
			xCount++;
		} else if (gameBoard[h][v]==playerO){
			oCount++;
		}
	}
	connect = true;
	for(h=x+1, v=y-1; v>=0 && h<ROW; h ++, v --){//down and right
		if(connect && gameBoard[h][v]==target)
			diagonalB++;
		else
			connect = false;

		if (gameBoard[h][v]==playerX){
			xCount++;
		} else if (gameBoard[h][v]==playerO){
			oCount++;
		}
	}
	connect = true;
	// check diagonalB score
	if(diagonalB>=4) {
		if (depth < 3)
			return isPlayerX? std::numeric_limits<int>::max():std::numeric_limits<int>::min();
	} 
	score += getUnitScore(isPlayerX, oCount, xCount);

	return score;
}

/** 
 * get the leaf node score for minimax algorithm.
 * assume x is the computer ai,
 * and o is the enemy of the computer ai.
 * if isX is true, then the node is max node. Else is min node.
 * @param isX true if x is the lastmove, false if o is the lastmove
 * @param oCount the number of o in the same line
 * @param xCount the number of x in the same line
 * @return the score of the leaf node for the minimax purpose
 */
int GameBoard::getUnitScore(bool isX, int oCount, int xCount){
	int INCREMENT[7] = {0, 1, 4, 32, 128, 512, 2048};
	if (oCount == xCount) {
        if (isX) {
            return 1;
        }
        return -1;
    } else if (oCount < xCount) {
        if (isX) {
        	return INCREMENT[xCount + 1] - INCREMENT[oCount];
        }
        return INCREMENT[xCount] - INCREMENT[oCount];
    } else {
        if (isX) {
        	return -INCREMENT[oCount] + INCREMENT[xCount];    
        }
        return -INCREMENT[oCount + 1] + INCREMENT[xCount];
    }
}


bool GameBoard::inputStep(int i, TYPE t){
	if(gameBoardNum[i-1]>=COL || i>ROW){return false;} 
	moves[++lastMove]=i-1;
	gameBoard[moves[lastMove]][gameBoardNum[moves[lastMove]]]=t;
	gameBoardNum[moves[lastMove]]++;
	return true;
}

int GameBoard::undoStep(){
	if (lastMove<0)
		return -1;
	int tmp = moves[lastMove];
	int row = gameBoardNum[moves[lastMove]]-1;
	gameBoardNum[moves[lastMove]]--;
	gameBoard[tmp][row] = blank;

	moves[lastMove--]=-1;
	return tmp;
}

bool GameBoard::isDrawGame(){
	for(int item: gameBoardNum){
		if (item<COL) { return false;}
	}
	return true;	
}

GameBoard::TYPE GameBoard::isGameOver(){
	if (lastMove<=0) return blank;
	if (isDrawGame()) return draw;

	int v, h, x=moves[lastMove], y=gameBoardNum[moves[lastMove]]-1;
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
		if (gameBoardNum[i]<COL){
			v.push_back(i);
		}
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