#pragma once
#include "Texture.h"

class Block
{
public:
	Block(int *row, int *col, int w, int h, const char* fileName, SDL_Renderer* ren);
	~Block();

	void renderBlock(SDL_Renderer* ren);
	void updatePos(int *rDelta, int *cDelta);
	void getPos(int *row, int *col);
	void destroyTexture(int row, int col);

private:
	Texture *pTexture[4] = { nullptr };
};