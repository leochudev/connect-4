#ifndef _GAME_BOARD_H_
#define _GAME_BOARD_H_

#include <vector>

class GameBoard{
public:
	enum TYPE{
		blank=0,
		playerX,
		playerO,
		draw
	};

	// constant variables
	const static int COL = 7;
	const static int ROW = 7;
	typedef TYPE board[COL][ROW];

	// instructors & destructors
	GameBoard();
	GameBoard(const GameBoard &obj); // copy constructor
	~GameBoard();
	
	void printGameBoard();
	bool inputStep(int i, TYPE t);
	int undoStep();
	int getHeuristicScore(TYPE currentPlayer, int depth);
	int getUnitScore(bool isPlayer, int playerCount, int enemyCount);
	TYPE isGameOver();
	char getTypeChar(TYPE t);
	std::vector<int> getAllPossibleSteps();

private:
	int lastMove;
	int gameBoardNum[ROW];
	int moves[128];
	board gameBoard;

	bool isDrawGame();
};

#endif