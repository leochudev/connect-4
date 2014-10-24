#include "gamePlayer.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <vector>

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
int Human::nextStep(const GameBoard &obj){
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

int Computer::nextStep(const GameBoard &obj){
	GameBoard* tmp = new GameBoard(obj);
	int step = evaluateMove(tmp);
	free(tmp);
	printf("Computer input next step: %d\n", step+1);
	return step+1;
}

int Computer::evaluateMove(GameBoard* board){ // TODO AI bugs
	int depth=0, alpha =100, beta=-100, player=1;
	int bestMove=0, bestScore=100;
	
	std::vector<int> possibleSteps = board->getAllPossibleSteps();
	for(int step:possibleSteps){
		GameBoard* tmpboard = getNewState(board, player, step);
		int score = alphabeta(tmpboard, alpha, beta, depth+1,-player);
		free(tmpboard);


		printf("%d\n", score);
		if(score<bestScore){
			bestScore = score;
			bestMove = step;
		}
	}

	return bestMove;
}

int Computer::alphabeta(GameBoard* board, int alpha, int beta, int depth, int player){
	GameBoard::TYPE result = board->isGameOver();
	if (result != GameBoard::blank || depth==Computer::MAX_DEPTH){
		return unitScore(result, depth);
	}

	int v = player>0?alpha:beta;
	std::vector<int> possibleSteps = board->getAllPossibleSteps();
	for(int step:possibleSteps){
		GameBoard* tmpboard = getNewState(board, player, step);
		if (player>0){ // maximizer
			int score = alphabeta(tmpboard, v, beta, depth+1, -player);
			if (score>v) v=score;
			if (v>beta) return beta;
		} else{ // minimizer
			int score = alphabeta(tmpboard, alpha, v, depth+1, -player);
			if (score<v) v=score;
			if (v<alpha) return alpha;
		}
		free(tmpboard);
	}
	return v;
}

GameBoard* Computer::getNewState(GameBoard* obj, int player, int step){
	GameBoard* tmp = new GameBoard(*obj);
	GameBoard::TYPE type = player>0? getPlayerType():getEnemyType();
	tmp->inputStep(step+1, type);
	return tmp;
}

int Computer::unitScore(GameBoard::TYPE winner, int depth){
	if (winner == GameBoard::blank) return 0;
	if (winner == GameBoard::draw) return 0;
	return winner == getPlayerType()?50-depth:depth-50;
}

