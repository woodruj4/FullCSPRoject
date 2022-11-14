#pragma once
#include <iostream>
#include <vector>
#include "Block.h"

using namespace std;
class IBlock : public Block
{
private:
	vector<vector<int>> r0 = {
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0},
		{0,0,1,0}
	};
	vector<vector<int>> r1 = {
		{0,0,0,0},
		{0,0,0,0},
		{1,1,1,1},
		{0,0,0,0}
	};
public: 
	~IBlock() { cout << "IBlock destroyed" << endl; }
	vector<vector<int>> getBlock(int);

};

