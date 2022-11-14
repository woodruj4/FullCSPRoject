#pragma once
//Love Sosa
#include <iostream>
#include <vector>
#include "Block.h"
using namespace std;
class OBlock
{
private:
	vector<vector<int>> r0 = {
		{0,0,0,0},
		{0,1,1,0},
		{0,1,1,0},
		{0,0,0,0}
	};
public:
	~OBlock() { cout << "OBlock destroyed" << endl; }
	vector<vector<int>> getBlock(int);
};

