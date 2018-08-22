#pragma once
#include <iostream>
#include <SDL2/SDL_image.h>

class Texture
{
public:
	Texture(int row, int col, int w, int h);
	~Texture();

	void loadTexture(const char* fileName, SDL_Renderer *ren);
	void destroyTexture();
	void renderTexture(SDL_Renderer *ren);
	void updatePos(int rDelta, int cDelta);
	void deletePos() {
		destR.y = -1;
		destR.x = -1;
		destR.h = 0;
		destR.w = 0;
	}

	int getRow() { return destR.y; }
	int getCol() { return destR.x; }

private:
	SDL_Texture *tex = nullptr;
	SDL_Rect destR;
};