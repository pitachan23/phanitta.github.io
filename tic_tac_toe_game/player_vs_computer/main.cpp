#include "Game.h"

Game game;

int main() {

	////////////////////////////////////////////////////

	game.run();

	////////////////////////////////////////////////////

	// delay closing of the window
	char userInput;
	std::cin >> userInput;
	if (userInput) {
		return 0;
	}
}