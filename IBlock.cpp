#include "IBlock.h"
vector<vector<int>> IBlock::getBlock(int r) {
	vector<vector<int>> block;
	block.resize(4, vector<int>(4, 0));

	if (r == 0 || r == 2) {
		block = r0;
	}
	else {
		block = r1;
	}
	return block;
}