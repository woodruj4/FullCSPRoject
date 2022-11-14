#include "Block.h"
Block::Block() {
	bCoords.resize(2, vector<int>(4, 0));
	cBlock.resize(4, vector<int>(4, 0));
}

void Block::setBlock(vector<vector<int>> b) {
	cBlock = b;
}

void Block::setCoords() {
	int count = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (cBlock[i][j] == 1) {
				bCoords[0][count] = x + j;
				bCoords[1][count] = y + i;
				count++;
			}
		}
		
	}
}

int Block::getCoords(int r, int c) {
	return bCoords[r][c];
}

ostream& operator <<(ostream& os, Block b) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			os << b.cBlock[i][j];
		}
		os << endl;
	}
	return os;
}
