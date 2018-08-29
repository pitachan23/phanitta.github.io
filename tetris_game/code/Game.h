#pragma once
#include "Block.h"
#include <SDL2/SDL.h>
#include <cstdlib>
#include <ctime>
#include <vector>

class Game {
public:
	Game();
	~Game();

	void init();
	void handleEvent();
	void userInput();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }

	bool isOcc(int row, int col);
	void updateOcc(int *row, int *col, int *rDelta, int *cDelta);
	void printOccArray();
	void checkRow();
	void removeRow(std::vector<int> rVec);
	void removeOcc(int row, int col); 
	void checkGameOver();

	void createBlock();
	//void checkConditions();

	void moveDown();
	void moveLeftRight();
	void rotate();

	bool checkBottom(int *row, int *col);
	bool checkCollision(int *row, int *col, int *rNext, int *cNext);

	int findMin(int *arr);
	int findMax(int *arr);

private:
	SDL_Window * window = nullptr;
	SDL_Renderer *ren = nullptr;
	//Block *pBlock[100];
	std::vector<Block*> vBlock;
	int blockCount = 0;

	// true if key is pressed
	bool isLeft = false;
	bool isRight = false;
	bool isUp = false;
	bool isDown = false;

	bool releaseNewBlock = false;
	int blockType; // 0 to 6
	bool isRunning = false;
	int cDel = 0;
	int rotatePos = 0;
	bool enableRotate = true;

	// Time Delay
	int moveDownCount = 0;
	int moveLeftRightCount = 0;
	int rotateCount = 0;
	int moveDownDelay = 50;
	const int moveLeftRightDelay = 5;
	const int rotateDelay = 20;

	// long, square, L, inverse L, s, z, inverse T
	const int initTiles[7][4] = { { 0,1,2,3 },{ 0,1,4,5 },{ 0,4,5,6 },
							{ 2,4,5,6 },{ 1,2,4,5 },{ 0,1,5,6 },{ 1,4,5,6 } };

	const int rotDelta[4][7][8] = {
								{
									{ 2, -2, 1, -1, 0, 0, -1, 1 },
									{ 0, 0, 0, 0, 0, 0, 0, 0 },
									{ 2, -1, 1, -2, 0, -1, -1, 0 },
									{ 0, 1, 1, -2, 0, -1, -1, 0 },
									{ 1, 0, 0, 1, 1, -2, 0, -1 },
									{ 2, -1, 1, 0, 0, -1, -1, 0 },
									{ 1, 1, 1, -1, 0, 0, -1, 1 }
								},
								{
									{ -2, 2, -1, 1, 0, 0, 1, -1 },
									{ 0, 0, 0, 0, 0, 0, 0, 0 },
									{ 0, 2, 1, 1, 0, 0, -1, -1 },
									{ -2, 0, 1, 1, 0, 0, -1, -1 },
									{ -1, 1, -2, 0, 1, 1, 0, 0 },
									{ 0, 2, -1, 1, 0, 0, -1, -1 },
									{ -1, 1, 1, 1, 0, 0, -1, -1 }
								},
								{
									{ 1, -2, 0, -1, -1, 0, -2, 1 },
									{ 0, 0, 0, 0, 0, 0, 0, 0 },
									{ -2, 0, -1, 1, 0, 0, 1, -1 },
									{ 0, -2, -1, 1, 0, 0, 1, -1 },
									{ -1, -1, 0, -2, -1, 1, 0, 0 },
									{ -2, 0, -1, -1, 0, 0, 1, -1 },
									{ -1, -1, -1, 1, 0, 0, 1, -1 }
								},
								{
									{ -1, 2, 0, 1, 1, 0, 2, -1 },
									{ 0, 0, 0, 0, 0, 0, 0, 0 },
									{ 0, -1, -1, 0, 0, 1, 1, 2 },
									{ 2, 1, -1, 0, 0, 1, 1, 2 },
									{ 1, 0, 2, 1, -1, 0, 0, 1 },
									{ 0, -1, 1, 0, 0, 1, 1, 2 },
									{ 1, -1, -1, -1, 0, 0, 1, 1 }
								}
	};

};
