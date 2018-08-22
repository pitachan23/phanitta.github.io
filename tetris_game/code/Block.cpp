#include "Block.h"

// Each Block consists of 4 texture tiles
Block::Block(int *row, int *col, int w, int h, const char* fileName, SDL_Renderer* ren) {
	//std::cout << "Block constructor" << std::endl;
	for (int i = 0; i < 4; i++) { 
		pTexture[i] = new Texture(row[i], col[i], w, h);
		pTexture[i]->loadTexture(fileName, ren);
	}
}

Block::~Block() {
	//std::cout << "Block destructor" << std::endl;
	for (int i = 0; i < 4; i++) {
		delete (pTexture + 1); // pTexture[i]
	}
}

void Block::renderBlock(SDL_Renderer* ren) {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		if (pTexture[i]) {
			pTexture[i]->renderTexture(ren);
			count++;
		}
	}
	//std::cout << "Block renderBlock x" << count << std::endl;
}

void Block::updatePos(int *rDelta, int *cDelta) {
	//std::cout << "Block updatePos" << std::endl;
	for (int i = 0; i < 4; i++) {
		pTexture[i]->updatePos(rDelta[i], cDelta[i]);
	}
}

void Block::getPos(int *row, int *col) {
	//std::cout << "Block getPos" << std::endl;
	for (int i = 0; i < 4; i++) {
		if (pTexture[i]) { 
			//std::cout << "inside getPos" << std::endl;
			row[i] = pTexture[i]->getRow();
			col[i] = pTexture[i]->getCol();
		}
	}
}

void Block::destroyTexture(int row, int col) {
	//std::cout << "Block destroyTexture" << std::endl;
	for (int i = 0; i < 4; i++) {
		if (pTexture[i]) {
			if (pTexture[i]->getRow() == row && pTexture[i]->getCol() == col) {
				//std::cout << "row: " << row / 32 << ", col: " << col / 32 << std::endl;
				pTexture[i]->destroyTexture();
				//pTexture[i]->deletePos();
				delete pTexture[i];
				pTexture[i] = nullptr;
			}
		}
	}
}