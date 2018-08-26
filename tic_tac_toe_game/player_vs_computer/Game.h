#pragma once
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Game
{
public:
	Game();
	~Game();

	void run();
private:
	std::string gameBoard[3][3];
	std::string nextPlayer; // "computer" or "player"
	std::string playerPick;
	std::string compPick;
	int edge[4][5] = { { 1,0,2,4,7 },{ 3,4,5,0,6 },{ 5,3,4,2,8 },{ 7,6,8,1,4 } };
	int corner[4][7] = { { 0,1,2,3,6,4,8 },{ 2,0,1,5,8,6,4 },{ 6,7,8,0,3,4,2 },{ 8,6,7,2,5,0,4 } };
	int center[9] = { 4,3,5,1,7,6,2,0,8 };

	void showBoard();
	int checkBoardState(); //return: -1 - incomplete, 0 - a tie, 1 - x wins, 2 - o wins
	int checkRow();
	int checkCol();
	int checkDiag();
	int checkWinner();
	bool isBoardFull();
	void makeMove(int row, int col, std::string symbol);
	bool isEmpty(int row, int col);
	bool isEmpty(int move);
	void printResult();
	int getRandMove();
	int getBestMove();
	int checkTwoOcc();
	int checkTwoEmpty();
	bool isEdge(int move);
	bool isCorner(int move);

	int getRow(int move);
	int getCol(int move);
	int getMove(int row, int col);
	std::string getSymbol(int row, int col);
	std::string getSymbol(int move);
};