#include "Texture.h"

Texture::Texture(int row, int col, int w, int h) {
	// set positions and dimensions
	destR.y = row;
	destR.x = col;
	destR.w = w;
	destR.h = h;
}

Texture::~Texture(){
	if (tex) { destroyTexture(); }
}

void Texture::loadTexture(const char* fileName, SDL_Renderer* ren) {
	SDL_Surface* tmpSurface = IMG_Load(fileName);
	tex = SDL_CreateTextureFromSurface(ren, tmpSurface);
	SDL_FreeSurface(tmpSurface);
}

void Texture::destroyTexture() {
	SDL_DestroyTexture(tex);
}

void Texture::renderTexture(SDL_Renderer *ren) {
	SDL_RenderCopy(ren, tex, NULL, &destR);
}

void Texture::updatePos(int rDelta, int cDelta) {
	destR.y += rDelta;
	destR.x += cDelta;
}
