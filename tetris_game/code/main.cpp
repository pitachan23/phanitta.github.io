#include "Game.h"

Game *game = nullptr;

int main(int argc, char** argv) {

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;

	game = new Game();
	game->init();

	while (game->running()) {

		frameStart = SDL_GetTicks();

		game->handleEvent(); // check if window is closed
		game->userInput(); // check user inputs
		game->update(); // game updates
		//game->render(); // render changes to the display

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) {
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();
	delete game;

	return 0;
}