#include "JBlock.h"
vector<vector<int>> JBlock::getBlock(int r) {
	vector<vector<int>> block;
	block.resize(4, vector<int>(4, 0));
	if (r == 0) {
		block = r0;
	}
	else if (r == 1) {
		block = r1;
	}
	else if (r == 2) {
		block = r2;
	}
	else {
		block = r3;
	}

	return block;
}