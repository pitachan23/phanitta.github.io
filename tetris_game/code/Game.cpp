#include "Game.h"

const char *title = "Tetris!";
const char *fileName[7] = {"tex1.png", "tex2.png", "tex3.png", "tex4.png", "tex5.png", "tex6.png", "tex7.png"};
const int screenWidth = 320;
const int screenHeight = 480;
const int w = 32; // texWidth
const int h = 32; // texHeight
const int m = 15; // screenHeight / h;
const int n = 10; // screenWidth / w;
const int rLimit = screenHeight - h;
const int cLimit = screenWidth - w;

// occupancy aray
bool occArray[15][10] = { 0 };

bool justRemoved = false;
bool gameOver = false;

Game::Game() {
}

Game::~Game() {
	for (int i = 0; i < blockCount; i++) {
		delete (pBlock + 1); // pTexture[i]
	}
}

// initialize window and renderer pointers
// create a window
void Game::init() {
	srand(time(NULL));

	int flags = 0;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "SDL Initialized!..." << std::endl;

		window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, flags);
		if (window) {
			std::cout << "Window created!" << std::endl;
		}

		ren = SDL_CreateRenderer(window, -1, 0);
		if (ren) {
			SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
			std::cout << "Renderer created!" << std::endl;
		}
		isRunning = true;
	}

	releaseNewBlock = true;
}

void Game::handleEvent() {
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
	}
}

void Game::userInput() {
	const Uint8 *scancode = SDL_GetKeyboardState(NULL);
	if (scancode[SDL_SCANCODE_LEFT]) {
		isLeft = true;
		cDel = (-1) * w;
	}
	else if (scancode[SDL_SCANCODE_RIGHT]) {
		isRight = true;
		cDel = w;
	}
	else if (scancode[SDL_SCANCODE_UP]) {
		isUp = true;
		cDel = 0;
	}
	else if (scancode[SDL_SCANCODE_DOWN]) {
		isDown = true;
		cDel = 0;
	}
}

void Game::update() {
	if (!gameOver) {
		createBlock();
		moveDown();

		if (isLeft || isRight) {
			moveLeftRight();
			isLeft = false;
			isRight = false;
		}

		if (isUp) {
			rotate();
			isUp = false;
		}

		if (isDown) {
			moveDownDelay = 1; // drop the block faster
			isDown = false;
		}
	}
}

void Game::render() {
	SDL_RenderClear(ren);
	
	// render all blocks
	for (int i = 0; i < blockCount; i++) {
		pBlock[i]->renderBlock(ren);
	}

	SDL_RenderPresent(ren);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
}

///////////////////////////////////////

bool Game::isOcc(int row, int col) {
	bool occ;

	if (occArray[row / h][col / w]) { occ = true; }
	else { occ = false; }

	return occ;
}

void Game::updateOcc(int *row, int *col, int *rDelta, int *cDelta) {
	int rPrev[4], cPrev[4]; // previous row and col

	for (int i = 0; i < 4; i++) {
		// update new occupancy with (row, col) variables
		occArray[row[i]/h][col[i]/w] = 1;

		// initialize previous positions
		rPrev[i] = row[i] - rDelta[i];
		cPrev[i] = col[i] - cDelta[i];
	}

	// remove previous occupancy
	for (int i = 0; i < 4; i++) {
		// if prev position is same as new position 
		if ((rPrev[i] == row[0] && cPrev[i] == col[0]) || (rPrev[i] == row[1] && cPrev[i] == col[1]) ||
			(rPrev[i] == row[2] && cPrev[i] == col[2]) || (rPrev[i] == row[3] && cPrev[i] == col[3])) {
			// do nothing
		}
		else {
			occArray[rPrev[i]/h][cPrev[i]/w] = 0; // FIX THIS
		}
	}
	printOccArray();
	render();
	std::cout << "-----------------------------------" << std::endl;
}

void Game::printOccArray() {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			std::cout << occArray[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Game::checkRow() {
	std::vector<int> rVec;
	for (int i = 0; i < screenHeight; i += h) {
		int countOcc = 0;
		for (int j = 0; j < screenWidth; j += w) {
			int occ = isOcc(i, j);
			if (occ) { countOcc++; }
		}
		// Row is full
		if (countOcc == n) {
			rVec.push_back(i);
			std::cout << "Row" << i / h << " is full!" << std::endl;
		}
	}
	if (!rVec.empty()) {
		removeRow(rVec);
	}
}

void Game::removeRow(std::vector<int> rVec) {
	while (!rVec.empty()) {
		int index = rVec.size() - 1;
		int row = rVec.at(index);

		//std::cout << "row: " << row/h << std::endl;

		for (int i = 0; i < blockCount; i++) {
			for (int j = 0; j < screenWidth; j += w) {

				pBlock[i]->destroyTexture(row, j);
				// update occupancy
				removeOcc(row, j);
			}
		}
		rVec.pop_back();
	}
	std::cout << "Row(s) removed!" << std::endl;
	printOccArray();
	justRemoved = true;
}

void Game::removeOcc(int row, int col) {
	occArray[row / h][col / w] = 0;
}

void Game::checkGameOver() {
	int row = 0;
	for (int col = 0; col < screenWidth; col += w) {
		int occ = isOcc(row, col);
		if (occ) {
			gameOver = true;
			std::cout << "gameOver!" << std::endl;
		}
	}
}

///////////////////////////////////////
///////////////////////////////////////
///////////////////////////////////////

void Game::createBlock() {
	if (releaseNewBlock) {
		blockType = rand() % 7; // generate rand number between 0 to 6
		
		int row[4], col[4];
		int rDelta[4] = { 0 }; // initilize to zero (no change in position)
		int cDelta[4] = { 0 };

		// set initial positions (row, col) for each of the 4 tiles in a block
		for (int i = 0; i < 4; i++) {

			int index = initTiles[blockType][i];

			if (index < 4) {
				row[i] = (-1) * h; //0
				col[i] = w * index;
			}
			else {
				row[i] = 0; //h
				col[i] = w * (index - 4);
			}
		}

		pBlock[blockCount] = new Block(row, col, w, h, fileName[blockType], ren);
		blockCount++;
		enableRotate = true;
		rotatePos = 0;
		releaseNewBlock = false;

		std::cout << "blockCount: " << blockCount << std::endl;

		// update occupancy
		updateOcc(row, col, rDelta, cDelta);
	}
}

void Game::moveDown() {
	moveDownCount++;
	if (moveDownCount % moveDownDelay == 0) {
		int row[4], col[4];
		int rDelta[4] = { h, h, h, h };
		int cDelta[4] = { 0 };

		int currIndex = blockCount - 1;
		pBlock[currIndex]->getPos(row, col);
		/*
		std::cout << "getPos 1" << std::endl;
		std::cout << "row: " << row[0]/h << ", col: " << col[0]/w << std::endl;
		std::cout << "row: " << row[1]/h << ", col: " << col[1]/w << std::endl;
		std::cout << "row: " << row[2]/h << ", col: " << col[2]/w << std::endl;
		std::cout << "row: " << row[3]/h << ", col: " << col[3]/w << std::endl;
		*/

		// check bottom boundary of window
		if (row[0] >= rLimit || row[1] >= rLimit || row[2] >= rLimit || row[3] >= rLimit) {
			// no position update
			enableRotate = false;
			checkRow();
			releaseNewBlock = true;
			moveDownDelay = 50;
		}
		else if (checkBottom(row, col)) {
			// update position
			pBlock[currIndex]->updatePos(rDelta, cDelta);
		}

		// update occupancy
		pBlock[currIndex]->getPos(row, col);
		/*
		std::cout << "getPos 2" << std::endl;
		std::cout << "row: " << row[0] / h << ", col: " << col[0] / w << std::endl;
		std::cout << "row: " << row[1] / h << ", col: " << col[1] / w << std::endl;
		std::cout << "row: " << row[2] / h << ", col: " << col[2] / w << std::endl;
		std::cout << "row: " << row[3] / h << ", col: " << col[3] / w << std::endl;
		*/

		if (justRemoved) {
			justRemoved = false;
		}
		else {
			updateOcc(row, col, rDelta, cDelta);
		}

		moveDownCount = 0;
	}
}

void Game::moveLeftRight() {
	moveLeftRightCount++;
	if (moveLeftRightCount % moveLeftRightDelay == 0) {
		int row[4], col[4];
		int rDelta[4] = { 0 };
		int cDelta[4] = { cDel, cDel, cDel, cDel };

		int currIndex = blockCount - 1;
		pBlock[currIndex]->getPos(row, col);
		//std::cout << "getPos 3" << std::endl;

		int rNext[4], cNext[4];
		for (int i = 0; i < 4; i++) {
			rNext[i] = row[i] + rDelta[i];
			cNext[i] = col[i] + cDelta[i];
		}

		// bottom window boundary
		if (row[0] >= rLimit || row[1] >= rLimit || row[2] >= rLimit || row[3] >= rLimit) {
			// no update
		}
		else {
			// right window boundary
			if (col[0] >= cLimit || col[1] >= cLimit || col[2] >= cLimit || col[3] >= cLimit) {
				if (cDel < 0) { 
					// update position
					pBlock[currIndex]->updatePos(rDelta, cDelta);
				}
			}
			// left window boundary
			else if (col[0] <= 0 || col[1] <= 0 || col[2] <= 0 || col[3] <= 0) {
				if (cDel > 0) { 
					// update position
					pBlock[currIndex]->updatePos(rDelta, cDelta);
				}
			}
			// check for collisions
			else {
				if (checkCollision(row, col, rNext, cNext)) {
					// update position
					pBlock[currIndex]->updatePos(rDelta, cDelta);
				}
			}
		}
		// update occupancy
		pBlock[currIndex]->getPos(row, col);
		updateOcc(row, col, rDelta, cDelta);

		moveLeftRightCount = 0;
	}
}


void Game::rotate() {
	int currIndex = blockCount - 1;

	if (enableRotate) {
		rotateCount++;
		if (rotateCount % rotateDelay == 0) {
			int row[4], col[4], rNext[4], cNext[4], rDelta[4], cDelta[4];

			int currIndex = blockCount - 1;
			pBlock[currIndex]->getPos(row, col);

			for (int i = 0; i < 4; i++) {
				// get rDelta and cDelta
				rDelta[i] = rotDelta[rotatePos][blockType][2 * i + 1] * h;
				cDelta[i] = rotDelta[rotatePos][blockType][2 * i] * w;

				rNext[i] = row[i] + rDelta[i];
				cNext[i] = col[i] + cDelta[i];
			}

			int rMin = findMin(rNext);
			int rMax = findMax(rNext);
			int cMin = findMin(cNext);
			int cMax = findMax(cNext);
			int delta;

			// top window boundary
			if (rNext[0] < 0 || rNext[1] < 0 || rNext[2] < 0 || rNext[3] < 0) {
				for (int i = 0; i < 4; i++) {
					delta = rMin;
					rDelta[i] -= delta; // move down so it doesn't exceed the window
				}
			}

			// bottom window boundary
			else if (rNext[0] > rLimit || rNext[1] > rLimit || rNext[2] > rLimit || rNext[3] > rLimit) {
				for (int i = 0; i < 4; i++) {
					delta = rMax - rLimit;
					rDelta[i] -= delta; // move up so it doesn't exceed the window
				}
			}

			// left window boundary
			else if (cNext[0] < 0 || cNext[1] < 0 || cNext[2] < 0 || cNext[3] < 0) {
				for (int i = 0; i < 4; i++) {
					delta = cMin;
					cDelta[i] -= delta; // move right
				}
			}

			// right window boundary
			else if (cNext[0] > cLimit || cNext[1] > cLimit || cNext[2] > cLimit || cNext[3] > cLimit) {
				for (int i = 0; i < 4; i++) {
					delta = cMax - cLimit;
					cDelta[i] -= delta; // move left
				}
			}

			rotatePos++;
			if (rotatePos == 4) {
				rotatePos = 0;
			}

			// update position
			pBlock[currIndex]->updatePos(rDelta, cDelta);

			// update occupancy
			pBlock[currIndex]->getPos(row, col);
			updateOcc(row, col, rDelta, cDelta);

			rotateCount = 0;
		}
	}
}

////////////////////////////////////////////////////////////

bool Game::checkBottom(int *row, int *col) {
	bool canMove = false;

	int rNext[4], cNext[4]; // next row and col
	for (int i = 0; i < 4; i++) {
		rNext[i] = row[i] + h;
		cNext[i] = col[i];
	}

	// check for collision
	canMove = checkCollision(row, col, rNext, cNext);

	if (!canMove) {
		checkRow();
		checkGameOver();
		releaseNewBlock = true;
		moveDownDelay = 50;
	}
	return canMove;
}

bool Game::checkCollision(int *row, int *col, int *rNext, int *cNext) {
	bool canMove = false;
	int count = 0;
	for (int i = 0; i < 4; i++) {
		int occ = isOcc(rNext[i], cNext[i]);
		if (occ) {
			// if next position is same as current position
			if ((rNext[i] == row[0] && cNext[i] == col[0]) || (rNext[i] == row[1] && cNext[i] == col[1]) ||
				(rNext[i] == row[2] && cNext[i] == col[2]) || (rNext[i] == row[3] && cNext[i] == col[3])) {
				count++;
			}
		}
		else {
			count++;
		}
	}
	if (count == 4) {
		canMove = true;
	}
	return canMove;
}

///////////////////////////////////////////

int Game::findMin(int *arr) {
	int min = arr[0];
	for (int i = 1; i < 4; i++) {
		if (arr[i] < min) {
			min = arr[i];
		}
	}
	return min;
}

int Game::findMax(int *arr) {
	int max = arr[0];
	for (int i = 1; i < 4; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}