#ifndef _GAME_PLAYER_H_
#define _GAME_PLAYER_H_

#include "gameBoard.h"


class Player{
public:
	Player();
	Player(GameBoard::TYPE t);
	virtual ~Player();

	GameBoard::TYPE getPlayerType();
	GameBoard::TYPE getEnemyType();
	
	virtual int nextStep(GameBoard *obj)=0;
private:
	GameBoard::TYPE playerType;
	GameBoard::TYPE enemyType;
};

class Human: public Player{
public:
	Human();
	Human(GameBoard::TYPE t);
	~Human();

	virtual int nextStep(GameBoard *obj);
};

class Computer: public Player{
public:
	// struct Bound
	// {
	// 	int alpha;	// best already explored option along path to the root for maximizer
	// 	int beta; 	// best already explored option along path to the root for minimizer
	// 	int depth;	// the depth of the minimax tree
	// 	int value;	// the current best option value
    //	Bound(int a=-100, int b=100, int d=0, int v=0) : alpha(a), beta(b), depth(d), value(v){}
    //	Bound(const A& a) : alpha(a.alpha), beta(a.beta), depth(a.depth), value(a.value) {} // user-defined copy ctor
	// };
	Computer();
	Computer(GameBoard::TYPE t);
	~Computer();

	virtual int nextStep(GameBoard *obj);
private:
	void getNewState(GameBoard* obj, int depth, int step);
	int alphabeta(GameBoard* board, int alpha, int beta, int depth, int player);
	int evaluateMove(GameBoard* board);

	const int MAX_DEPTH=8;
};

#endif