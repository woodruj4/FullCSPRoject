#include "OBlock.h"
vector<vector<int>> OBlock::getBlock() {
	vector<vector<int>> block;
	block.resize(4, vector<int>(4, 0));
	block = r0;
	return block;
}