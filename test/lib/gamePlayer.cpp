#include "gamePlayer.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>
#include <limits>

Player::Player(){
	playerType=GameBoard::playerO;
	enemyType =GameBoard::playerX;
}
Player::Player(GameBoard::TYPE t){
	playerType=t;
	enemyType=t==GameBoard::playerO?GameBoard::playerX:GameBoard::playerO;
}
Player::~Player(){}

GameBoard::TYPE Player::getPlayerType(){
	return playerType;
}

GameBoard::TYPE Player::getEnemyType(){
	return enemyType;
}

Human::Human():Player(){}
Human::Human(GameBoard::TYPE t):Player(t){}
Human::~Human(){}
int Human::nextStep(GameBoard *obj){
	int i;
	printf("Input your next step :");
	std::cin >> i;
	return i;
}


Computer::Computer():Player(){
	srand(time(NULL));
}
Computer::Computer(GameBoard::TYPE t):Player(t){
	srand(time(NULL));
}
Computer::~Computer(){}

int Computer::nextStep(GameBoard *obj){
	int step = evaluateMove(obj);
	printf("Computer input next step: %d\n", step+1);
	return step+1;
}

// player 1 for x, -1 for o
int Computer::evaluateMove(GameBoard* board){
	int depth=0, player=1;
	int alpha =std::numeric_limits<int>::min(); // maximum lower bound
	int beta=std::numeric_limits<int>::max(); // minumum upper bound
	
	std::vector<int> possibleSteps = board->getAllPossibleSteps();
	for(int step:possibleSteps){ // check for win (win purpose)
		bool win = false;
		getNewState(board,player,step);
		if(board->isGameOver()==getPlayerType())win=true;
		board->undoStep();
		if (win) return step;
	}
	for(int step:possibleSteps){ // check for lose (block purpose)
		bool win = false;
		getNewState(board,-player,step);
		if(board->isGameOver()==getEnemyType())win=true;
		board->undoStep();
		if (win) return step;
	}

	
	int bestMove = possibleSteps[0];
	for(int step:possibleSteps){//maximizer
		if(alpha>=beta){
			return bestMove;
		}
		getNewState(board, player, step);
		int score = alphabeta(board, alpha, beta, depth+1,player);
		board->undoStep();
		if(score>alpha){
			bestMove = step;
			alpha=score;
		}
	}

	return bestMove;
}

int Computer::alphabeta(GameBoard* board, int alpha, int beta, int depth, int player){
	GameBoard::TYPE result = board->isGameOver();
	if (result != GameBoard::blank || depth==Computer::MAX_DEPTH){
		int score = board->getHeuristicScore(getPlayerType(), depth);
		return score;
	}

	std::vector<int> possibleSteps = board->getAllPossibleSteps();
	for(int step:possibleSteps){
		if(alpha>=beta)
			return player>0? alpha:beta; // true : maximizer, false minimizer

		if (player>0){ // maximizer
			getNewState(board, player, step);
			int score = alphabeta(board, alpha, beta, depth+1, -player);
			board->undoStep();
			if (score>alpha) alpha=score;
		} else{ // minimizer
			getNewState(board, player, step);
			int score = alphabeta(board, alpha, beta, depth+1, -player);
			board->undoStep();
			if (score<beta) beta=score;
		}
	}
	return player>0? alpha:beta;
}

void Computer::getNewState(GameBoard* obj, int player, int step){
	GameBoard::TYPE type = player>0? getPlayerType():getEnemyType();
	obj->inputStep(step+1, type);
}

