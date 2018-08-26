#include "Game.h"

Game::Game() {
	srand(time(NULL));
	int randNum = rand() % 2; // generate random num between 0 or 1
	if (randNum == 0) {
		nextPlayer = "computer1";
		std::cout << "Computer1 plays first" << std::endl;
		compPick1 = "x";
		compPick2 = "o";
	}
	else {
		nextPlayer = "computer2";
		std::cout << "Computer2 plays first" << std::endl;
		compPick2 = "x";
		compPick1 = "o";
	}
}

Game::~Game() {
}

void Game::showBoard() {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (gameBoard[i][j].empty()) {
				std::cout << " " << " "; // correct the formatting
			}
			else {
				std::cout << gameBoard[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

int Game::checkRow() {
	int win = 0;
	std::string symbol;
	for (int i = 0; i < 3; i++) {
		// get symbol in first col
		symbol = gameBoard[i][0];
		// win if find the same symbol in the next 2 col
		if (symbol == gameBoard[i][1] && symbol == gameBoard[i][2]) {
			if (symbol == "x") { win = 1; }
			else if (symbol == "o") { win = 2; }
			return win;
		}
	}
	return win;
}

int Game::checkCol() {
	int win = 0;
	std::string symbol;
	for (int i = 0; i < 3; i++) {
		// get symbol in first row
		symbol = gameBoard[0][i];
		// win if find the same symbol in the next 2 row
		if (symbol == gameBoard[1][i] && symbol == gameBoard[2][i]) {
			if (symbol == "x") { win = 1; }
			else if (symbol == "o") { win = 2; }
			return win;
		}
	}
	return win;
}

int Game::checkDiag() {
	int win = 0;
	std::string symbol;
	symbol = gameBoard[1][1];
	if (symbol == gameBoard[0][0] && symbol == gameBoard[2][2]) {
		if (symbol == "x") { win = 1; }
		else if (symbol == "o") { win = 2; }
	}
	else if (symbol == gameBoard[0][2] && symbol == gameBoard[2][0]) {
		if (symbol == "x") { win = 1; }
		else if (symbol == "o") { win = 2; }
	}
	return win;
}

// 8 total ways of winning: 3 rows, 3 cols, 2 diags
// return: 0 - no one wins, 1 - x wins, 2 - o wins
int Game::checkWinner() {
	int win = 0;
	if (checkRow() == 1 || checkCol() == 1 || checkDiag() == 1) {
		win = 1;
	}
	else if (checkRow() == 2 || checkCol() == 2 || checkDiag() == 2) {
		win = 2;
	}
	return win;
}

bool Game::isBoardFull() {
	bool full = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (gameBoard[i][j].empty()) {
				full = 0;
				return full;
			}
		}
	}
	return full;
}

// return: -1 - incomplete, 0 - a tie, 1 - x wins, 2 - o wins
int Game::checkBoardState() {
	int state;
	switch (checkWinner()) {
	case 0:
		if (isBoardFull()) {
			state = 0;
		}
		else {
			state = -1;
		}
		break;
	case 1:
		state = 1;
		break;
	case 2:
		state = 2;
		break;
	}
	return state;
}

// return: 1 - empty, 0 - occupied
bool Game::isEmpty(int row, int col) {
	bool empty = 0;
	if (gameBoard[row][col].empty()) {
		empty = 1;
	}
	return empty;
}

void Game::makeMove(int row, int col, std::string symbol) {
	gameBoard[row][col] = symbol;
}

void Game::printResult() {
	switch (checkBoardState()) {
	case -1:
		std::cout << "incomplete" << std::endl;
		break;
	case 0:
		std::cout << "a tie" << std::endl;
		break;
	case 1:
		if (compPick1 == "x") {
			std::cout << "Computer1 won!" << std::endl;
		}
		else {
			std::cout << "Computer2 won!" << std::endl;
		}
		break;
	case 2:
		if (compPick1 == "o") {
			std::cout << "Computer1 won!" << std::endl;
		}
		else {
			std::cout << "Computer2 won!" << std::endl;
		}
		break;
	}
	std::cout << std::endl;
}

bool Game::isEmpty(int move) {
	int row = getRow(move);
	int col = getCol(move);
	return isEmpty(row, col);
}

int Game::getRandMove() {
	int randNum = rand() % 9; // random number between 0 to 8
	return randNum;
}

int Game::getRow(int move) {
	int row = move / 3;
	return row;
}

int Game::getCol(int move) {
	int col;
	if (move < 3) {
		col = move;
	}
	else if (move < 6) {
		col = move - 3;
	}
	else if (move < 9) {
		col = move - 6;
	}
	return col;
}

int Game::getMove(int row, int col) {
	int moveArray[3][3] = { {0,1,2},{3,4,5},{6,7,8} };
	int move = moveArray[row][col];
	return move;
}

std::string Game::getSymbol(int row, int col) {
	std::string symbol;
	symbol = gameBoard[row][col];
	return symbol;
}

std::string Game::getSymbol(int move) {
	int row = getRow(move);
	int col = getCol(move);
	return getSymbol(row, col);
}

void Game::run() {
	// while game is incomplete
	// continue to makeMove, but check whose turn it is
	while (checkBoardState() == -1) {
		int row;
		int col;
		bool again;
		if (nextPlayer == "computer1") {
			std::cout << "Computer1's turn" << std::endl;
			do {
				// get move number
				int move = getBestMove(compPick1); //

				// convert move into row and col
				row = getRow(move);
				col = getCol(move);

				if (isEmpty(row, col)) {
					makeMove(row, col, compPick1);
					again = 0;
				}
				else {
					again = 1;
				}
			} while (again);
			nextPlayer = "computer2";
		}
		else if (nextPlayer == "computer2") {
			std::cout << "Computer2's turn" << std::endl;
			do {
				// get move number
				int move = getBestMove(compPick2); 

				// convert move into row and col
				row = getRow(move);
				col = getCol(move);

				if (isEmpty(row, col)) {
					makeMove(row, col, compPick2);
					again = 0;
				}
				else {
					again = 1;
				}
			} while (again);
			nextPlayer = "computer1";
		}
		showBoard();
	}
	printResult();
}

int Game::getBestMove(std::string compPick) {
	int bestMove;

	if (isEmpty(center[0])) {
		bestMove = center[0];
	}
	else if (checkTwoOcc(compPick) != -1) {
		bestMove = checkTwoOcc(compPick);
	}
	else {
		bestMove = checkTwoEmpty(compPick);
		bool cornerFound = false;
		// if doesn't satisfy the above cases, then bestMove = corner
		if (bestMove == -1) {
			for (int i = 0; i < 4; i++) {
				if (isEmpty(corner[i][0])) {
					bestMove = corner[i][0];
					cornerFound = true;
				}
			}
			// if no empty corner, then bestMove = edge
			if (!cornerFound) {
				for (int i = 0; i < 4; i++) {
					if (isEmpty(edge[i][0])) {
						bestMove = edge[i][0];
					}
				}
			}
		}
	}
	return bestMove;
}

// return: -1 - if there is no two empty on the same row, otherwise return move
int Game::checkTwoEmpty(std::string compPick) {
	int bestMove = -1;

	// check edge 
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 3; j += 2) {
			int move = edge[i][0];
			std::string symbol = getSymbol(move);
			if (!isEmpty(move) && symbol == compPick) {
				if (isEmpty(edge[i][j]) && isEmpty(edge[i][j + 1])) {
					if (isCorner(edge[i][j])) {
						bestMove = edge[i][j];
						return bestMove;
					}
					else if (isCorner(edge[i][j + 1])) {
						bestMove = edge[i][j + 1];
						return bestMove;
					}
					else {
						bestMove = edge[i][j];
					}
				}
			}
		}
	}

	// check corner
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 5; j += 2) {
			int move = corner[i][0];
			std::string symbol = getSymbol(move);
			if (!isEmpty(move) && symbol == compPick) {
				if (isEmpty(corner[i][j]) && isEmpty(corner[i][j + 1])) {
					if (isCorner(corner[i][j])) {
						bestMove = corner[i][j];
						return bestMove;
					}
					else if (isCorner(corner[i][j + 1])) {
						bestMove = corner[i][j + 1];
						return bestMove;
					}
					else {
						bestMove = corner[i][j];
					}
				}
			}
		}
	}

	// check center
	for (int i = 1; i <= 7; i += 2) {
		int move = center[0];
		std::string symbol = getSymbol(move);
		if (!isEmpty(move) && symbol == compPick) {
			if (isEmpty(center[i]) && isEmpty(center[i+1])) {
				if (isCorner(center[i])) {
					bestMove = center[i];
					return bestMove;
				}
				else if (isCorner(center[i+1])) {
					bestMove = center[i + 1];
					return bestMove;
				}
				else {
					bestMove = center[i];
				}
			}
		}
	}
	return bestMove;
}

// return: -1 - if doesn't exist, move - where winning/losing case happens
int Game::checkTwoOcc(std::string compPick) {
	int bestMove = -1;

	// check edge 
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 3; j += 2) {
			int move = edge[i][0];
			if (!isEmpty(move)) {
				std::string symbol = getSymbol(move);
				if (symbol == getSymbol(edge[i][j]) && isEmpty(edge[i][j + 1])) {
					bestMove = edge[i][j + 1];
					if (symbol == compPick) { return bestMove; }
				}
				else if (symbol == getSymbol(edge[i][j + 1]) && isEmpty(edge[i][j])) {
					bestMove = edge[i][j];
					if (symbol == compPick) { return bestMove; }
				}
			}
		}
	}

	// check corner
	for (int i = 0; i < 4; i++) {
		for (int j = 1; j <= 5; j += 2) {
			int move = corner[i][0];
			if (!isEmpty(move)) {
				std::string symbol = getSymbol(move);
				if (symbol == getSymbol(corner[i][j]) && isEmpty(corner[i][j + 1])) {
					bestMove = corner[i][j + 1];
					if (symbol == compPick) { return bestMove; }
				}
				else if (symbol == getSymbol(corner[i][j + 1]) && isEmpty(corner[i][j])) {
					bestMove = corner[i][j];
					if (symbol == compPick) { return bestMove; }
				}
			}
		}
	}

	return bestMove;
}

bool Game::isEdge(int move) {
	bool state = false;
	if (move == 1 || move == 3 || move == 5 || move == 7) {
		state = true;
	}
	return state;
}

bool Game::isCorner(int move) {
	bool state = false;
	if (move == 0 || move == 2 || move == 6 || move == 8) {
		state = true;
	}
	return state;
}